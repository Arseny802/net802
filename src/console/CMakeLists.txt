set(PROJECT_NAME ${SOLUTION_NAME}.console)
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

target_link_libraries(${PROJECT_NAME} PUBLIC ${SOLUTION_NAME}.moex)
message("Including library: ${SOLUTION_NAME}.moex_reader")
message("")