cmake_minimum_required(VERSION 3.15)
project(ucpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include(GNUInstallDirs)

set(UCPP_IS_MASTER_PROJECT OFF)
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(UCPP_IS_MASTER_PROJECT ON)
endif ()

option(UCPP_BUILD_TESTS "Build tests" ${UCPP_IS_MASTER_PROJECT})
option(UCPP_BUILD_INSTALL "Build install" ${UCPP_IS_MASTER_PROJECT})

add_library(ucpp INTERFACE)
add_library(ucpp::ucpp ALIAS ucpp)
target_include_directories(
        ucpp INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

if (UCPP_BUILD_INSTALL)
    install(TARGETS ucpp EXPORT ucpp)

    include(CMakePackageConfigHelpers)
    configure_package_config_file(
            "${CMAKE_CURRENT_LIST_DIR}/ucpp-config.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake/ucpp-config.cmake"
            INSTALL_DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/ucpp"
    )
    install(
            FILES "${CMAKE_CURRENT_BINARY_DIR}/cmake/ucpp-config.cmake"
            DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/ucpp"
    )

    install(
            EXPORT ucpp
            FILE ucpp-targets.cmake
            DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/ucpp"
            NAMESPACE ucpp::
    )

    install(
            DIRECTORY "${CMAKE_SOURCE_DIR}/include/ucpp"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )
endif ()

if (UCPP_BUILD_TESTS)
    enable_testing()

    find_package(Threads REQUIRED)

    function(ucpp_add_test name)
        add_executable("${name}" "tests/${name}.cpp")
        target_link_libraries("${name}" PRIVATE ucpp::ucpp Threads::Threads)
        add_test(NAME "${name}" COMMAND "${name}")
    endfunction()

    if (WIN32)
        ucpp_add_test(ucpp_test_codecvt_win32)
    endif ()
    ucpp_add_test(ucpp_test_countof)
    ucpp_add_test(ucpp_test_endian)
    ucpp_add_test(ucpp_test_finally)
    ucpp_add_test(ucpp_test_format)
    ucpp_add_test(ucpp_test_secstr)
    ucpp_add_test(ucpp_test_spin_lock)
    ucpp_add_test(ucpp_test_strings)
    ucpp_add_test(ucpp_test_synchronized)
    ucpp_add_test(ucpp_test_tuple_foreach)

    if (CMAKE_CONFIGURATION_TYPES)
        add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                --force-new-ctest-process --output-on-failure
                --build-config "$<CONFIGURATION>")
    else ()
        add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                --force-new-ctest-process --output-on-failure)
    endif ()
endif ()

if (UCPP_IS_MASTER_PROJECT)
    find_program(CLANG_FORMAT clang-format)
    if (CLANG_FORMAT)
        file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS include/*.hpp tests/*.cpp tests/*.hpp)
        add_custom_target(
                format
                COMMAND "${CLANG_FORMAT}" -i --verbose ${ALL_SOURCES}
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )
        add_custom_target(
                check-format
                COMMAND "${CLANG_FORMAT}" --dry-run --Werror --verbose ${ALL_SOURCES}
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )
    endif ()
endif ()
