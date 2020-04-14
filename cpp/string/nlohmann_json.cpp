#include <iostream>
#include <vector>
using namespace std;

#include <nlohmann/json.hpp>

struct DataSourceInfo
{   
    // data_level
    std::string data_level;
    // data_source_id
    std::string data_source_id;
    // coverage 
    std::string coverage;
    // name
    std::string name;
};

inline void to_json(nlohmann::json &j, const DataSourceInfo &obj)
{
    j = nlohmann::json{
        {"data_level", obj.data_level},
        {"data_source_id", obj.data_source_id},
        {"coverage", obj.coverage},
        {"name", obj.name},
    };
}

struct DataSourceInfoListResp
{
    // msg
    std::string msg; 
    // code
    int32_t code;
    // data_source_info_list
    std::vector<DataSourceInfo> data_source_info_list;
};


inline void to_json(nlohmann::json &j, const DataSourceInfoListResp &obj)
{
    j = nlohmann::json{
        {"msg", obj.msg},
        {"code", obj.code},
        {"data_source_info_list", obj.data_source_info_list},
    };
}

DataSourceInfoListResp getResp()
{
    DataSourceInfoListResp resp{};
    return resp;
}

nlohmann::json request()
{
    return getResp();
}

int main()
{
    auto j = request();
    cout << j.dump() << endl;
}
