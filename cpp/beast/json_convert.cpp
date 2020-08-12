#include "json_convert.h"

void to_json(nlohmann::json &j, const LocRes &obj)
{
    nlohmann::json pos;
    pos["x"] = obj.x;
    pos["y"] = obj.y;
    pos["z"] = obj.z;
    j["pos"] = j;
}

void from_json(const nlohmann::json &j, PreSetParams &obj)
{
    auto &camera1 = j["camera1"];
    camera1.at("install_x").get_to(obj.camera1_x);
    camera1.at("install_y").get_to(obj.camera1_y);
    camera1.at("install_z").get_to(obj.camera1_z);
    camera1.at("install_level_angle").get_to(obj.camera1_installAngle1);
    camera1.at("install_pitch_angle").get_to(obj.camera1_installAngle2);
    camera1.at("current_level_angle").get_to(obj.camera1_yaw);
    camera1.at("current_pitch_angle").get_to(obj.camera1_pitch);

    auto &camera2 = j["camera2"];
    camera2.at("install_x").get_to(obj.camera2_x);
    camera2.at("install_y").get_to(obj.camera2_y);
    camera2.at("install_z").get_to(obj.camera2_z);
    camera2.at("install_level_angle").get_to(obj.camera2_installAngle1);
    camera2.at("install_pitch_angle").get_to(obj.camera2_installAngle2);
    camera2.at("current_level_angle").get_to(obj.camera2_yaw);
    camera2.at("current_pitch_angle").get_to(obj.camera2_pitch);
}
