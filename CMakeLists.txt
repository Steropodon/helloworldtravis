cmake_minimum_required(VERSION 3.5)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(hello_world_1 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(hello_world_1 VERSION 0.0.42)
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(hw_version.h.in hw_version.h)

add_executable(hello_world_r main.cpp)
add_library(hello_world_lib hw.cpp)
add_executable(hw_test test_helloworld.cpp)

set_target_properties(
    hello_world_r hello_world_lib hw_test PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(hello_world_lib
    PRIVATE "${CMAKE_BINARY_DIR}")

set_target_properties(hw_test PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(hello_world_r PRIVATE
    hello_world_lib
)

target_link_libraries(hw_test
    ${Boost_LIBRARIES}
    hello_world_lib
)

target_compile_options(hello_world_r PRIVATE
    -Wall -Wextra -pedantic -Werror
)
target_compile_options(hello_world_lib PRIVATE
    -Wall -Wextra -pedantic -Werror
)
target_compile_options(hw_test PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS hello_world_r RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(hw_test hw_test)
