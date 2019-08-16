#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/program_options.hpp>
using namespace boost;

namespace po = program_options;

#include "output.h"

int main(int argc, char *argv[])
{
    // po::options_description desc("Allowed options");
    po::options_description desc;
    desc.add_options()
        ("help", "this is help message")
        ("file,F", po::value<string>(), "file full name")
        ("N", po::value<string>(), "name")
        (",H", po::value<int>(), "height")
        ("input-file", po::value<vector<string>>(), "input file")
        ;

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    // po::store(po::parse_command_line(argc, argv, desc), vm);
    po::store(po::command_line_parser(argc, argv).  options(desc).  positional(p).  run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 0;
    }

    if (vm.count("input-file")) {
        cout << vm.count("input-file") << endl;
        cout << vm["input-file"].as<vector<string>>() << endl;
    }

    if (vm.count("file")) {
        cout << vm.count("file") << endl;
        cout << vm["file"].as<string>() << endl;
    }
    if (vm.count("N")) {
        cout << vm["N"].as<string>() << endl;
    }
    if (vm.count("-H")) {
        cout << vm["-H"].as<int>() << endl;
    }
    return 0;
}
