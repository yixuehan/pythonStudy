#include <iostream>
using namespace std;

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


int main()
{
    const char *json = "{\"project\":\"rapidjson\",\"stars\":10}";
    rapidjson::Document d;
    d.Parse(json);
    cout << d["stars"].GetString() << endl;
}
