#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

#include <grpcpp/grpcpp.h>
#include <grpcpp/create_channel.h>

#include "helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloRequest;
using helloworld::HelloReply;

class GreeterClient {
public:
    GreeterClient(std::shared_ptr<Channel> channel)
        : stub_(Greeter::NewStub(channel)) {}
    
    // 简单RPC调用
    void SayHello(const std::string& name) {
        std::cout << "[Client] Sending simple RPC request..." << std::endl;
        
        HelloRequest request;
        request.set_name(name);
        
        HelloReply reply;
        ClientContext context;
        
        // 设置超时
        context.set_deadline(std::chrono::system_clock::now() + 
                            std::chrono::seconds(10));
        
        Status status = stub_->SayHello(&context, request, &reply);
        
        if (status.ok()) {
            std::cout << "[Client] Received response: " 
                      << reply.message() << std::endl;
        } else {
            std::cout << "[Client] RPC failed: " 
                      << status.error_code() << ": " 
                      << status.error_message() << std::endl;
        }
    }
   
private:
    std::unique_ptr<Greeter::Stub> stub_;
};

void RunAllExamples() {
    std::string server_address("localhost:50051");
    
    // 创建客户端
    GreeterClient greeter(
        grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials())
    );
    
    std::cout << "========================================" << std::endl;
    std::cout << "gRPC Helloworld Client" << std::endl;
    std::cout << "Connecting to: " << server_address << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 等待服务器启动
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // 示例1: 简单RPC
    std::cout << "\n=== Example 1: Simple RPC ===" << std::endl;
    greeter.SayHello("Alice");
    greeter.SayHello("Bob");
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "All examples completed!" << std::endl;
    std::cout << "========================================" << std::endl;
}

int main(int argc, char** argv) {
    try {
        RunAllExamples();
    } catch (const std::exception& e) {
        std::cerr << "Client exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}