set(PROJECT_NAME base_http)
message(STATUS "Building ${PROJECT_NAME} started.")
project(${PROJECT_NAME})

file(GLOB headers *.h Base/*.h)
file(GLOB sources *.cpp Base/*.cpp)
add_library(${PROJECT_NAME} STATIC
        ${headers}
        ${sources} Base/ErrorCode.h Base/IClientHttp.h ../http/diagnostic/Diagnostics.cpp ../http/diagnostic/Diagnostics.h)
message("Adding headers: ${headers}")
message("Adding sources: ${sources}")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
message("Including directory: ${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

FIND_PACKAGE(Boost REQUIRED COMPONENTS system program_options thread)

include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE fmt)
target_link_libraries(${PROJECT_NAME} LINK_PRIVATE spdlog)

message("Including directory: ${Boost_INCLUDE_DIR}")
message("Linking public libraries: ${Boost_LIBRARIES}")
message("Linking private  library: fmt")
message("Linking private  library: spdlog")

message(STATUS "Building ${PROJECT_NAME} finished.")
message("")