#pragma once

#include "base/Singleton.h"
#include <boost/core/noncopyable.hpp>
#include <string>

class RpcConfig : public boost::noncopyable
{
public:
    static RpcConfig &instance()
    {
        static RpcConfig instance;
        return instance;
    }

    void parseConfigFile(int argc, char **argv);

    // RpcConfig(int argc, char **argv);
    std::string ip() { return ip_; }

    int port() { return port_; }

private:
    std::string ip_;
    int port_;
};
