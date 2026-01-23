#include "xrpc/RpcProvider.h"
#include "xrpc/RpcConfig.h"
#include "base/cppbase.h"
#include "../user.pb.h"

#include <spdlog/spdlog.h>

class UserService : public test::UserServiceRpc
{
public:
    bool Login(string name, string pwd)
    {
        spdlog::debug(name);
        spdlog::debug(pwd);
    }

    void Login(::google::protobuf::RpcController *controller,
               const ::test::LoginRequest *request,
               ::test::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {
        string name = request->name();
        string pwd = request->pwd();

        Login(name, pwd);

        test::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("hello");
        response->set_success(true);

        done->Run();
    }
};

int main(int argc, char **argv)
{
    RpcConfig::instance().parseConfigFile(argc, argv);

    RpcProvider provider;
    provider.notifyService(new UserService());
    provider.run();
    return 0;
}