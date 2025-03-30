cmake_minimum_required(VERSION 3.10.0)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(custom_allocator VERSION ${PROJECT_VERSION} LANGUAGES CXX)

option(WITH_GTEST_TEST "Whether to build GTEST test" ON)

configure_file(version.h.in version.h)

add_executable(custom_allocator 
    src/main.cpp )

target_include_directories(custom_allocator PUBLIC
    inc/
)

if(WITH_GTEST_TEST)
    find_package(GTest REQUIRED)
    add_executable(vector_test tests/vector_test.cpp)


    target_include_directories(vector_test PUBLIC inc/)

    set_target_properties(vector_test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(vector_test GTest::GTest)

    find_package(GTest REQUIRED)
    add_executable(allocator_test tests/allocator_test.cpp)


    target_include_directories(allocator_test PUBLIC inc/)

    set_target_properties(allocator_test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(allocator_test GTest::GTest)

endif()

if (MSVC)
    target_compile_options(custom_allocator PRIVATE
        /W4
    )

else ()
    target_compile_options(custom_allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

    if(WITH_GTEST_TEST)
    target_compile_options(vector_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    endif()

    if(WITH_GTEST_TEST)
    target_compile_options(allocator_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    endif()

endif()

install(TARGETS custom_allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_GTEST_TEST)
    enable_testing()
    add_test(vector_test vector_test)
    add_test(allocator_test allocator_test)
endif()