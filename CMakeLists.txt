message("")
message("##########################")
message("######## PREBUILD ########")
message("##########################")

# base settings for cmake
cmake_minimum_required(VERSION 3.3)
set(PROJECT_TARGET_NAME http_submodule)
project(${PROJECT_TARGET_NAME} CXX C)

# temporary global linking
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
set(CMAKE_CXX_STANDARD 17)

message("Set PROJECT_TARGET_NAME: ${PROJECT_TARGET_NAME}")
message("Set CMAKE_LINKER_FLAGS: ${CMAKE_LINKER_FLAGS}")
message("Set CMAKE_CXX_STANDARD: 17")
message("")

# cmake build dir & generator
set(bin_dir "${PROJECT_SOURCE_DIR}/bin")
set(third_party_dir ${PROJECT_SOURCE_DIR}/third-party)
message("#########################")
message("######## GENERAL ########")
message("#########################")
message("Generator: ${CMAKE_GENERATOR}")
message("Build tool: ${CMAKE_BUILD_TOOL}")
message("Build type: ${CMAKE_BUILD_TYPE}")
message("Build  directory: ${bin_dir}")
message("Third party  dir: ${third_party_dir}")

# set output folders
# libs	
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${bin_dir}
        CACHE PATH
        "Single Directory for all"
        )
# executables
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${bin_dir}
        CACHE PATH
        "Single Directory for all"
        )
# libs .a
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${bin_dir}
        CACHE PATH
        "Single Directory for all"
        )

message("")
message("#########################")
message("###### CUSTOM ARGS ######")
message("#########################")
# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

# text encoding for compiler
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

message("")
message("###################################")
message("######## EXTERNAL PROJECTS ########")
message("###################################")

set(EXTERNAL_INSTALL_LOCATION ${bin_dir}/external)
message("Install location is ${EXTERNAL_INSTALL_LOCATION}")

SET(fmt_path https://github.com/fmtlib/fmt.git)
message("Adding fmt from ${fmt_path}")
set(fmt_path "${third_party_dir}/fmt")

include(ExternalProject)
find_package(Git REQUIRED)
ExternalProject_Add(fmt
        GIT_REPOSITORY ${fmt_path}
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        SOURCE_DIR        "${fmt_path}/fmt_src"
        BINARY_DIR        "${fmt_path}/fmt_build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
        )
include_directories(${fmt_path})

message("")
message("#############################")
message("########## SOURCES ##########")
message("#############################")
# base libs
add_subdirectory(src/BaseHttp)
add_subdirectory(src/moex)

# tests files
add_subdirectory(tests EXCLUDE_FROM_ALL)

# enable testing
enable_testing()
set(PROJECT_TESTS ${CMAKE_PROJECT_NAME}_tests)
add_test(tests/${PROJECT_TESTS} tests/${PROJECT_TESTS})
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)
add_dependencies(check ${PROJECT_TESTS})

# if testing
#if(BUILD_TESTING)
#	add_test(FirstTest Test 1)
#endif()

# checking build type on platform
message("")
message("#############################")
message("###### OS DEPENDENCIES ######")
message("#############################")
if (WIN32) # building on windows
    message(STATUS "Cmake build for windows")
    add_subdirectory(src/Console)
    #add_subdirectory(win__special_sources)
elseif (MSVC) # building on visual c++
    message(STATUS "Cmake build for visual c++")
    add_subdirectory(src/Console)
    #add_subdirectory(win_msvc__special_sources)
elseif (UNIX) # building on unix (mac, linux)
    message(STATUS "Cmake build for unix")
    add_subdirectory(src/Console)
    #add_subdirectory(unix__special_sources)
endif (WIN32)
message("")
message("##########################")
message("######### FINISH #########")
message("##########################")