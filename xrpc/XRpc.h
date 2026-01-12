#pragma once

#include "base/Singleton.h"
#include <boost/core/noncopyable.hpp>

class XRpc //: public boost::noncopyable
{
public:
    // static XRpc& instance()
    // {
    //     static XRpc instance;
    //     return instance;
    // }

    // void parseConfigFile(int argc, char **argv);

    XRpc(int argc, char **argv);

private:
};
