#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/filesystem.hpp>
using namespace boost;

vector<string> get_all_files(const char *dirname)
{
    for (auto &file : filesystem::recursive_directory_iterator(dirname)) {
        if (!filesystem::is_directory(file.status())) {
            cout << file.path().string() << endl;
        }
    }   
    return {};
}

void traversal(filesystem::path p)
{
    for (auto &sub_node : p) {
        cout << sub_node.c_str() << endl;
    }
}

filesystem::path remove_path_copy(const filesystem::path &p, const std::string &find_node_name)
{
    filesystem::path r_p;
    for (auto &sub_node : p) {
        if (sub_node == find_node_name) {
            continue;
        }
        r_p /= sub_node;
        cout << sub_node << endl;
    }
    return r_p;
}

int main()
{
    // get_all_files(".");
    traversal(filesystem::current_path());
    auto current_path = filesystem::current_path();
    auto p = remove_path_copy(current_path, "home");
    cout << p << endl;
    remove_copy(current_path.begin(), current_path.end(), p.begin(), boost::filesystem::path("home"));
    cout << p << endl;
}
