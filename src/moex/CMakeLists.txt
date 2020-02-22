set(PROJECT_NAME moex_reader)
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

include_directories(
        ${CMAKE_SOURCE_DIR}/BaseHttp
        ${CMAKE_SOURCE_DIR}/BaseHttp/Base
        ${CMAKE_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PUBLIC base_http)

message("Including directory: ${CMAKE_SOURCE_DIR}/BaseHttp")
message("Including directory: ${CMAKE_SOURCE_DIR}")
message("Including libraries: base_http")

message(STATUS "Building ${PROJECT_NAME} finished.")
message("")