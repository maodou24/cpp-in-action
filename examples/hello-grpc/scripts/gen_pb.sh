#!/bin/bash

PROTO_DIR="proto"
GEN_DIR="gen"

mkdir -p $GEN_DIR

for proto_file in $PROTO_DIR/*.proto; do
    if [ -f "$proto_file" ]; then
        protoc -I=$PROTO_DIR --cpp_out=$GEN_DIR $proto_file
        
        # 生成gRPC文件
        protoc -I=$PROTO_DIR --grpc_out=$GEN_DIR \
               --plugin=protoc-gen-grpc=./vcpkg_installed/arm64-osx/tools/grpc/grpc_cpp_plugin $proto_file
    fi
done

echo "生成完成!"