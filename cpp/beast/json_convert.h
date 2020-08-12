#pragma once
#include "calculate/binocular_locate.h"
#include <nlohmann/json.hpp>


void to_json(nlohmann::json &j, const LocRes &obj);
void from_json(const nlohmann::json &j, PreSetParams &obj);
