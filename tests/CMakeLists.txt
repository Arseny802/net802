set(PROJECT_NAME ${CMAKE_PROJECT_NAME}_tests)
message(STATUS "Building ${PROJECT_NAME} started.")
project(${PROJECT_NAME})

include_directories(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/src)

set(project_directories
        .
        http
        console
        moex)

foreach (current_dir ${project_directories})
    file(GLOB_RECURSE inner_sources ${current_dir}/*.cpp)
    message("Adding sources from ${current_dir}: ${inner_sources}")
    set(files ${files} ${inner_sources} console/TestConsole.cpp)
endforeach ()
add_executable(${PROJECT_NAME} ${files})

#find_package(GTest REQUIRED)
#find_package(Threads REQUIRED)

set(libs
        ${CMAKE_PROJECT_NAME}
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )
target_link_libraries(${PROJECT_NAME} ${libs})

message("Including directories: ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/src")
message("Including libraries: ${libs}")

message(STATUS "Building ${PROJECT_NAME} finished.")
message("")