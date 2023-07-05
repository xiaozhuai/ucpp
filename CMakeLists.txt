cmake_minimum_required(VERSION 3.15)
project(ucpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
if (APPLE)
    include(CheckLinkerFlag)
    check_linker_flag(C "-Wl,-no_warn_duplicate_libraries" HAVE_NO_WARN_DUPLICATE)
    if (HAVE_NO_WARN_DUPLICATE)
        add_link_options("-Wl,-no_warn_duplicate_libraries")
    endif ()
endif ()

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

    if (CMAKE_CONFIGURATION_TYPES)
        add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C "$<CONFIGURATION>")
    else ()
        add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)
    endif ()

    find_package(Threads REQUIRED)

    function(ucpp_add_test name)
        add_executable(${name} "tests/${name}.cpp")
        target_link_libraries(${name} PRIVATE ucpp::ucpp Threads::Threads)
        add_test(NAME ${name} COMMAND ${name})
        add_dependencies(check ${name})
    endfunction()

    ucpp_add_test(ucpp_test_countof)
    ucpp_add_test(ucpp_test_endian)
    ucpp_add_test(ucpp_test_finally)
    ucpp_add_test(ucpp_test_format)
    ucpp_add_test(ucpp_test_secstr)
    ucpp_add_test(ucpp_test_spin_lock)
    ucpp_add_test(ucpp_test_strings)
    ucpp_add_test(ucpp_test_synchronized)
    ucpp_add_test(ucpp_test_tuple_foreach)
endif ()

if (UCPP_IS_MASTER_PROJECT)
    find_program(CLANG_FORMAT clang-format NO_CMAKE_PATH)
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
