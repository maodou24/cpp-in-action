cmake_minimum_required(VERSION 3.16)

project(hello_grpc VERSION 1.0.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置vcpkg工具链
# set(CMAKE_TOOLCHAIN_FILE 
#     "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
#     CACHE STRING "Vcpkg toolchain file")

# 开启vcpkg清单模式
set(VCPKG_MANIFEST_MODE ON)

# 查找gRPC和Protobuf
find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)

# 显示找到的包信息
message(STATUS "Found gRPC: ${gRPC_VERSION}")
message(STATUS "Found Protobuf: ${Protobuf_VERSION}")

# 设置proto文件
file(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")

# 生成protobuf和gRPC代码
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
# 生成gRPC代码
foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
    set(GRPC_SRCS "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.cc")
    set(GRPC_HDRS "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.h")
    add_custom_command(
        OUTPUT ${GRPC_SRCS} ${GRPC_HDRS}
        COMMAND ${Protobuf_PROTOC_EXECUTABLE}
        ARGS --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
             --plugin=protoc-gen-grpc=${CMAKE_CURRENT_BINARY_DIR}/vcpkg_installed/arm64-osx/tools/grpc/grpc_cpp_plugin
             -I ${CMAKE_CURRENT_SOURCE_DIR}/proto
             ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
    )
    list(APPEND ALL_GRPC_SRCS ${GRPC_SRCS})
    list(APPEND ALL_GRPC_HDRS ${GRPC_HDRS})
endforeach()
# 包含目录
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}
    ${gRPC_INCLUDE_DIRS}
)

# 服务端
add_executable(greeter_server
    src/server/greeter_server.cc
    ${PROTO_SRCS}
    ${ALL_GRPC_HDRS}
)

target_link_libraries(greeter_server
    gRPC::grpc++
    gRPC::grpc++_reflection
    protobuf::libprotobuf
    absl::any
    Threads::Threads
)

# 客户端
add_executable(greeter_client
    src/client/greeter_client.cc
    ${PROTO_SRCS}
    ${ALL_GRPC_HDRS}
)

target_link_libraries(greeer_client
    gRPC::grpc++
    protobuf::libprotobuf
    absl::any
    Threads::Threads
)

# 安装目标
install(TARGETS greeter_server greeter_client
    RUNTIME DESTINATION bin
)

# 安装proto文件
install(FILES proto/helloworld.proto
    DESTINATION share/proto
)

# 显示构建信息
message(STATUS "")
message(STATUS "=== Build Configuration ===")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Generated proto files:")
message(STATUS "  - ${PROTO_SRCS}")
message(STATUS "  - ${PROTO_HDRS}")
message(STATUS "  - ${GRPC_SRCS}")
message(STATUS "  - ${GRPC_HDRS}")