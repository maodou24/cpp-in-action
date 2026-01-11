#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "helloworld.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloRequest;
using helloworld::HelloReply;

class GreeterServiceImpl final : public Greeter::Service {
public:
    // 简单RPC
    Status SayHello(ServerContext* context, const HelloRequest* request,
                    HelloReply* reply) override {
        std::cout << "[Server] Received simple RPC request from: " 
                  << request->name() << std::endl;
        
        std::string message = "Hello " + request->name() + "! (Simple RPC)";
        reply->set_message(message);
        
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    GreeterServiceImpl service;
    
    // 启用健康检查服务
    grpc::EnableDefaultHealthCheckService(true);
    // 启用反射服务（方便调试）
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    
    ServerBuilder builder;
    
    // 监听端口（无加密）
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    
    // 注册服务
    builder.RegisterService(&service);
    
    // 设置并发选项
    builder.SetSyncServerOption(ServerBuilder::SyncServerOption::MIN_POLLERS, 1);
    builder.SetSyncServerOption(ServerBuilder::SyncServerOption::MAX_POLLERS, 10);
    
    // 构建并启动服务器
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "========================================" << std::endl;
    std::cout << "gRPC Helloworld Server" << std::endl;
    std::cout << "Listening on: " << server_address << std::endl;
    std::cout << "Press Ctrl+C to stop the server" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 等待服务器终止
    server->Wait();
}

int main(int argc, char** argv) {
    try {
        RunServer();
    } catch (const std::exception& e) {
        std::cerr << "Server exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}