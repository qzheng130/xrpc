#pragma once
#include "google/protobuf/service.h"

class RpcProvider
{
public:
    void notifyService(google::protobuf::Service *service);
    void run();
};