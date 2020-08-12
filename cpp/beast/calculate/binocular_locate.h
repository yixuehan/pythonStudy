//
// Created by liam on 8/27/19.
//

#ifndef FIRE_DETECT_SYSTEM_BINOCULAR_LOCATE_H
#define FIRE_DETECT_SYSTEM_BINOCULAR_LOCATE_H

#include <math.h>

// using namespace std;

//定位模块计算需要预先设定的参数
struct PreSetParams{
    //camera1
    double camera1_x;    // 三维坐标 (x1, y1, z1)
    double camera1_y;
    double camera1_z;
    double camera1_installAngle1;    //水平（校准）参考角度
    double camera1_installAngle2;   //垂直（校准）参考角度
    double camera1_yaw;    // 水平角度
    double camera1_pitch;  // 俯仰角度

    //camera2
    double camera2_x;    //三维坐标 (x2, y2, z2)
    double camera2_y;
    double camera2_z;
    double camera2_installAngle1;    //水平（校准）参考角度
    double camera2_installAngle2;   //垂直（校准）参考角度
    double camera2_yaw;     // 水平角度
    double camera2_pitch;   // 俯仰角度
};

// 定位结果数据类型
struct LocRes{
    double x;
    double y;
    double z;
};


class BiCamLocate
{
public:
    BiCamLocate(PreSetParams &params); // 初始化定位模块需要的参数

    LocRes getLocRes();   //　获取定位计算结果
private:
	double getCameraDirection(double self_x, double self_y, double other_x, double other_y); // 计算相机连线的夹角，采用全局坐标
    double getInterAngle(double sita);
private:
    LocRes locRes;
	double x1, y1, z1, alpha, theta, gamma;      //相机1的参数
	double x2, y2, z2, beta;                     //相机2的参数

};






#endif //FIRE_DETECT_SYSTEM_BINOCULAR_LOCATE_H
