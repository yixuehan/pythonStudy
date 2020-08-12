#include "parser.h"
#include <nlohmann/json.hpp>
#include "json_convert.h"

std::string Parser::do_request(std::string &&request)
{
    using namespace nlohmann;
    json j = json::parse(request);

}
