#!/bin/bash
set -e

VCPKG_ROOT="$HOME/opt/vcpkg"

if [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macOS"
    if [[ $(uname -m) == "arm64" ]]; then
        ARCH="arm64"
        TRIPLET="arm64-osx"
    else
        ARCH="x86_64"
        TRIPLET="x64-osx"
    fi
else
    OS="Linux"
    ARCH=$(uname -m)
    TRIPLET="x64-linux"
fi

echo "OS: $OS, Architecture: $ARCH, Triplet: $TRIPLET"

# 检查是否在项目根目录
if [ ! -f "CMakeLists.txt" ]; then
    echo "错误：请在项目根目录运行此脚本"
    exit 1
fi

if [ ! -d "$VCPKG_ROOT" ]; then
    echo "初始化vcpkg..."
    git clone https://github.com/microsoft/vcpkg.git "$VCPKG_ROOT"
    $VCPKG_ROOT/bootstrap-vcpkg.sh
fi

# 2. 安装依赖
# echo "安装依赖..."
# $VCPKG_ROOT/vcpkg install --triplet $TRIPLET

# 3. 创建构建目录
echo "配置CMake..."
mkdir -p build
cd build

# 4. 配置CMake
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake

# 5. 构建
echo "构建项目..."
cmake --build . --config Release

echo "构建完成！"
echo "可执行文件位置："
echo "  - 服务端: $(pwd)/greeter_server"
echo "  - 客户端: $(pwd)/greeter_client"
