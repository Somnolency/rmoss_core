/*******************************************************************************
 *  Copyright (c) 2020 robomaster-oss, All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it 
 *  under the terms of the MIT License, See the MIT License for more details.
 *
 *  You should have received a copy of the MIT License along with this program.
 *  If not, see <https://opensource.org/licenses/MIT/>.
 *
 ******************************************************************************/
#ifndef RM_COMMON_MONO_MEASURE_TOOL_HPP
#define RM_COMMON_MONO_MEASURE_TOOL_HPP

#include "opencv2/opencv.hpp"

namespace rm_common {

//基于单目视觉位置测量。
class MonoMeasureTool {
private:
    //相机参数
    cv::Mat camera_intrinsic_; //相机内参3*3
    cv::Mat camera_distortion_; //相机畸变参数1*5

public:
    bool setCameraInfo(std::vector<double> camera_intrinsic, std::vector<double> camera_distortion);
    //////////3d点坐标求解（use solve pnp）
    // points2d: input,一组图像上的2d点（4个点）
    // points3d: input,一组3d点（世界坐标系），对应图像上的点（4个点）
    // position: output,世界坐标系原点在相机坐标系下的位置。
    // return :state
    bool solvePnP4Points(std::vector<cv::Point2f>& points2d, std::vector<cv::Point3f>& points3d,
        cv::Point3f& position);
    ////// 逆投影，已知深度，2d->3d点求解
    //p: intput,图像上点坐标
    //distance: input,已知的真实距离
    //return :对应的真实3d点坐标
    cv::Point3f unproject(cv::Point2f p, double distance);
    //////视角求解
    //p: intput,图像上点坐标
    //pitch: output,视角pitch
    //yaw: output,视角yaw
    //return :state
    void calcViewAngle(cv::Point2f p, float& pitch, float& yaw);
};

} // namespace rm_common

#endif // RM_COMMON_MONO_MEASURE_TOOL_HPP
