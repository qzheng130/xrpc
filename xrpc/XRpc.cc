#include "XRpc.h"
#include <iostream>
#include <unistd.h>
#include "base/cppbase.h"
#include <boost/program_options.hpp>
#include "ConfigManager.h"

namespace po = boost::program_options;

XRpc::XRpc(int argc, char **argv)
{
    po::options_description desc("allowed options");
    desc.add_options()
        .operator()("help,h", "help message")
        .operator()("version,v", "version message")
        .operator()("input,i", po::value<std::string>(), "input file");

    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (std::exception &e)
    {
        std::cout << "argument parse failed:" << e.what() << std::endl;
        std::cout << desc << std::endl;
        throw;
    }

    string file;
    if (vm.count("input"))
    {
        file = vm["input"].as<string>();
        cout << file << endl;
    }

    ConfigManager config("config.ini");
    config.printAllConfig();
}
