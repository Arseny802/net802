set(PROJECT_NAME console)
message(STATUS "Building ${PROJECT_NAME}")
project(${PROJECT_NAME})

file(GLOB headers *.h)
file(GLOB sources *.cpp)
add_executable(${PROJECT_NAME}
        ${headers}
        ${sources})
message("Adding headers: ${headers}")
message("Adding sources: ${sources}")

include_directories(
        ${CMAKE_SOURCE_DIR}
)
message("Including directory: ${CMAKE_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME} PUBLIC moex_reader)
message("Including library: moex_reader")
message("")