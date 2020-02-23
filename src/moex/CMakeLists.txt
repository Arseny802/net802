set(PROJECT_NAME ${SOLUTION_NAME}.moex)
message(STATUS "Building ${PROJECT_NAME} started.")
project(${PROJECT_NAME})

file(GLOB headers *.h)
file(GLOB sources *.cpp)

add_library(${PROJECT_NAME} STATIC
        ${headers}
        ${sources})
message("Adding headers: ${headers}")
message("Adding sources: ${sources}")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
message("Including directory: ${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SOLUTION_NAME}.http)

message("Including directory: ${CMAKE_SOURCE_DIR}")
message("Including libraries: ${SOLUTION_NAME}.http")

message(STATUS "Building ${PROJECT_NAME} finished.")
message("")