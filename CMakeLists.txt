cmake_minimum_required(VERSION 3.15)
project(ucpp)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include(GNUInstallDirs)

option(UCPP_BUILD_TESTS "Build tests" ON)

add_library(ucpp INTERFACE)
add_library(ucpp::ucpp ALIAS ucpp)
target_include_directories(
        ucpp INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(TARGETS ucpp EXPORT ucpp)

include(CMakePackageConfigHelpers)
configure_package_config_file(
        "${CMAKE_CURRENT_LIST_DIR}/ucpp-config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/ucpp-config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ucpp"
)
install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/cmake/ucpp-config.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ucpp"
)

install(
        EXPORT ucpp
        FILE ucpp-targets.cmake
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ucpp"
        NAMESPACE ucpp::
)

install(
        DIRECTORY "${CMAKE_SOURCE_DIR}/include/ucpp"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

if (UCPP_BUILD_TESTS)
    enable_testing()

    function(ucpp_add_test name)
        add_executable("${name}" "tests/${name}.cpp")
        target_link_libraries("${name}" PRIVATE ucpp::ucpp)
        add_test(NAME "${name}" COMMAND "${name}")
    endfunction()

    ucpp_add_test(ucpp_test_finally)
    ucpp_add_test(ucpp_test_format)
    ucpp_add_test(ucpp_test_spin_lock)
    ucpp_add_test(ucpp_test_synchronized)

    if (CMAKE_CONFIGURATION_TYPES)
        add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                --force-new-ctest-process --output-on-failure
                --build-config "$<CONFIGURATION>")
    else ()
        add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                --force-new-ctest-process --output-on-failure)
    endif ()
endif ()

if ("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    file(GLOB_RECURSE ALL_SOURCES include/*.hpp tests/*.cpp tests/*.hpp)
    find_program(CLANG_FORMAT clang-format)
    if (CLANG_FORMAT)
        add_custom_target(
                format
                COMMAND "${CLANG_FORMAT}" -i -verbose ${ALL_SOURCES}
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )
    endif ()
endif ()
