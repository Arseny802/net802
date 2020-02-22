set(PROJECT_NAME ${CMAKE_PROJECT_NAME}_tests)
message(STATUS "Building ${PROJECT_NAME} started.")
project(${PROJECT_NAME})

include_directories(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/src)

file(GLOB sources *.cc)
add_executable(${PROJECT_NAME} ${sources} TestRun.cc)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(libs
        ${CMAKE_PROJECT_NAME}
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )
target_link_libraries(${PROJECT_NAME} ${libs})

message("Including directories: ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/src")
message("Adding sources: ${sources}")
message("Including libraries: ${libs}")

message(STATUS "Building ${PROJECT_NAME} finished.")
message("")