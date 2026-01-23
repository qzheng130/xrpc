#include <iostream>
#include "../user.pb.h"
#include "xrpc/RpcConfig.h"
#include "xrpc/XRpcChannel.h"

int main(int argc, char **argv)
{
    RpcConfig::instance().parseConfigFile(argc, argv);

    test::UserServiceRpc_Stub stub(new XRpcChannel());
    test::LoginRequest request;

    request.set_name("cuism");
    request.set_pwd("123456");

    test::LoginResponse response;

    stub.Login(nullptr, &request, &response, nullptr);

    if (0 == response.result().errcode())
    {
        std::cout << "rpc Login response: " << response.success() << '\n';
    }
    else
    {
        std::cout << "rpc Login response error: " << response.result().errmsg() << '\n';
    }

    // test::RegistRequest req;
    // req.set_id(6868);
    // req.set_name("cui");
    // req.set_pwd("666888");
    // test::RegistResponse res;
    // stub.Register(nullptr, &req, &res, nullptr);

    // // rpc 同步调用，等待返回结果
    // if (0 == response.result().errcode())
    // {
    //     std::cout << "res regist response: " << response.success() << '\n';
    // }
    // else
    // {
    //     std::cout << "res regist response error: " << response.result().errmsg() << '\n';
    // }
    return 0;
}