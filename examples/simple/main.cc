#include "xrpc/RpcProvider.h"
#include "xrpc/XRpc.h"
#include "base/cppbase.h"

int main(int argc, char **argv)
{
    XRpc xrpc(argc, argv);

    RpcProvider provider;
    provider.notifyService(nullptr);
    provider.run();
}