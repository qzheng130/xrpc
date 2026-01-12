#include "RpcProvider.h"
<<<<<<< HEAD

void RpcProvider::notifyService(google::protobuf::Service *service) { }

void RpcProvider::run() { }
=======
#include "RpcConfig.h"
#include "base/cppbase.h"
#include "rpcheader.pb.h"

#include <spdlog/spdlog.h>

using namespace google::protobuf;

void RpcProvider::notifyService(Service *service)
{
    const ServiceDescriptor *serviceDescriptor = service->GetDescriptor();
    string serviceName = serviceDescriptor->name();
    spdlog::debug("service name is:%s", serviceName);
    int methodCount = serviceDescriptor->method_count();

    ServiceInfo si;
    si.service = service;

    for (int i = 0; i < methodCount; ++i)
    {
        const MethodDescriptor *methodDesc = serviceDescriptor->method(i);
        string methodName = methodDesc->name();
        spdlog::debug("method name is:%s", methodName);
        si.methods.insert({ methodName, methodDesc });
    }

    services_.insert({ serviceName, si });
}

void RpcProvider::run()
{
    string ip = RpcConfig::instance().ip();
    int port = RpcConfig::instance().port();

    xnet::net::InetAddress addr(ip, static_cast<uint16_t>(port));
    xnet::net::TcpServer server(&loop_, addr, "RpcProvider");
    server.setConnectionCallback(
        [this](const xnet::net::TcpConnectionPtr &coon) { onConnection(coon); });
    server.setMessageCallback([this](const xnet::net::TcpConnectionPtr &coon,
                                     xnet::net::Buffer *buf,
                                     xnet::Timestamp time) { onMessage(coon, buf, time); });

    spdlog::debug("start server.");
    server.setThreadNum(2);
    server.start();
    loop_.loop();
}

void RpcProvider::onConnection(const xnet::net::TcpConnectionPtr &conn)
{
    if (!conn->connected())
    {
        conn->shutdown();
    }
}

void RpcProvider::onMessage(const xnet::net::TcpConnectionPtr &conn,
                            xnet::net::Buffer *buffer,
                            xnet::Timestamp ts)
{
    string buf = buffer->retrieveAllAsString();

    uint32_t headerSize = 0;
    buf.copy((char *)&headerSize, 4, 0);

    string header = buf.substr(4, headerSize);
    rpc::RpcHeader rpcHeader;

    string serviceName;
    string methodName;
    uint32_t argsSize;

    if (rpcHeader.ParseFromString(header))
    {
        serviceName = rpcHeader.service_name();
        methodName = rpcHeader.method_name();
        argsSize = rpcHeader.args_size();

        spdlog::debug(serviceName);
        spdlog::debug(methodName);
        spdlog::debug(argsSize);
    }
    else
    {
        spdlog::debug("rpc header parse error.");
    }

    auto it = services_.find(serviceName);
    if (it == services_.end())
    {
        spdlog::debug("can not find service:%s", serviceName);
    }

    Service *service = it->second.service;

    auto mit = it->second.methods.find(methodName);
    if (mit == it->second.methods.end())
    {
        spdlog::debug("can not find method:%s", methodName);
    }
    const MethodDescriptor *method = mit->second;

    Message *request = service->GetRequestPrototype(method).New();
    Message *response = service->GetResponsePrototype(method).New();

    string args = buf.substr(4 + headerSize, argsSize);

    if (!request->ParseFromString(args))
    {
        spdlog::debug("catn not parse args:%s", args.c_str());
    }

    Closure *done = NewCallback<RpcProvider, const xnet::net::TcpConnectionPtr &, Message *>(
        this, &RpcProvider::sendRpcResponse, conn, response);

    service->CallMethod(method, nullptr, request, response, done);
}

void RpcProvider::sendRpcResponse(const xnet::net::TcpConnectionPtr &conn, Message *response)
{
    string str;
    if (response->SerializeToString(&str))
    {
        conn->send(str);
    }
    else
    {
        spdlog::debug("cant serialize response.");
    }

    conn->shutdown();
}
>>>>>>> 92667ee (init.)
