set(PROJECT_NAME ${SOLUTION_NAME}.http)
message(STATUS "Building ${PROJECT_NAME} started.")
project(${PROJECT_NAME})

set(project_directories
        .
        tls
        base
        codes
        clients
        diagnostic)
foreach (current_dir ${project_directories})
    file(GLOB_RECURSE inner_headers ${current_dir}/*.h)
    file(GLOB_RECURSE inner_sources ${current_dir}/*.cpp)
    message("Adding headers from ${current_dir}: ${inner_headers}")
    message("Adding sources from ${current_dir}: ${inner_sources}")
    set(files ${files} ${inner_headers} ${inner_sources})
endforeach ()
add_library(${PROJECT_NAME} STATIC ${files})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

FIND_PACKAGE(Boost REQUIRED COMPONENTS system program_options thread)

include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE fmt)
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE spdlog)

message("Including directory: ${CMAKE_CURRENT_SOURCE_DIR}")
message("Including directory: ${Boost_INCLUDE_DIR}")
message("Linking public libraries: ${Boost_LIBRARIES}")
message("Linking private  library: fmt")
message("Linking private  library: spdlog")

message(STATUS "Building ${PROJECT_NAME} finished.")
message("")