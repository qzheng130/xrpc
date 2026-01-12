#pragma once
<<<<<<< HEAD
#include "google/protobuf/service.h"
=======

#include "xnet/net/TcpServer.h"
#include "xnet/net/EventLoop.h"
#include "xnet/net/InetAddress.h"
#include "xnet/net/TcpConnection.h"
#include "xnet/net/Buffer.h"
#include "xnet/base/Timestamp.h"

#include <unordered_map>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>
>>>>>>> 92667ee (init.)

class RpcProvider
{
public:
    void notifyService(google::protobuf::Service *service);
    void run();
<<<<<<< HEAD
=======

private:
    void onConnection(const xnet::net::TcpConnectionPtr &);
    void onMessage(const xnet::net::TcpConnectionPtr &, xnet::net::Buffer *, xnet::Timestamp);
    void sendRpcResponse(const xnet::net::TcpConnectionPtr &, google::protobuf::Message *);

    xnet::net::EventLoop loop_;

    struct ServiceInfo
    {
        google::protobuf::Service *service;
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor *> methods;
    };

    std::unordered_map<std::string, struct ServiceInfo> services_;
>>>>>>> 92667ee (init.)
};