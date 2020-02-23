message("")
message("##########################")
message("######## PREBUILD ########")
message("##########################")

# base settings for cmake
cmake_minimum_required(VERSION 3.3)
set(SOLUTION_NAME net802)
project(${SOLUTION_NAME} CXX C)

# temporary global linking
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
set(CMAKE_CXX_STANDARD 17)

message("Set SOLUTION_NAME: ${SOLUTION_NAME}")
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
message("###### CUSTOM ARGS ##s####")
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

# Include fmt project for string formatting.
set(fmt_path "${third_party_dir}/fmt")
message("Loading fmt from '${fmt_path}'...")
add_subdirectory(${fmt_path})
include_directories(${fmt_path}/include)
message("fmt loaded.")

# Include spdlog project for logging.
set(spdlog_path "${third_party_dir}/spdlog")
message("Loading spdlog from '${spdlog_path}'...")
add_subdirectory(${spdlog_path})
include_directories(${spdlog_path}/include)
message("spdlog loaded.")

# Include Google test project for unit tests.
set(googletest_path "${third_party_dir}/googletest")
message("Loading googletest from '${googletest_path}'...")
add_subdirectory(${googletest_path})
include_directories(${googletest_path}/googletest/include)
message("googletest loaded.")

# Include BOOST for ASIO & other.
# # BOOST not available for Cmake now (22.02.20)!
# set(boost_path "${third_party_dir}/boost")
# message("Loading boost from '${boost_path}'...")
# add_subdirectory(${boost_path})
# include_directories(${boost_path}/include)
# message("boost loaded.")

message("")
message("#############################")
message("########## SOURCES ##########")
message("#############################")
# base libs
add_subdirectory(src/http)
#add_subdirectory(src/ftp)
#add_subdirectory(src/telnet)
#add_subdirectory(src/ssh)
add_subdirectory(src/moex)

# tests files
add_subdirectory(tests EXCLUDE_FROM_ALL)

# enable testing
enable_testing()
set(PROJECT_TESTS ${CMAKE_PROJECT_NAME}.tests)
add_test(tests/${PROJECT_TESTS} tests/${PROJECT_TESTS})
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)
add_dependencies(check ${PROJECT_TESTS})

# checking build type on platform
message("")
message("#############################")
message("###### OS DEPENDENCIES ######")
message("#############################")
if (WIN32) # building on windows
    message(STATUS "Cmake build for windows")
    add_subdirectory(src/console)
    #add_subdirectory(win__special_sources)
elseif (MSVC) # building on visual c++
    message(STATUS "Cmake build for visual c++")
    add_subdirectory(src/console)
    #add_subdirectory(win_msvc__special_sources)
elseif (UNIX) # building on unix (mac, linux)
    message(STATUS "Cmake build for unix")
    add_subdirectory(src/console)
    #add_subdirectory(unix__special_sources)
endif (WIN32)
message("")
message("##########################")
message("######### FINISH #########")
message("##########################")