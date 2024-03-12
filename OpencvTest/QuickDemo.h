#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class QuickDemo {
public:
    void colorSpace_Demo(Mat& image);//颜色空间转换
    void matCreation_Demo();//Mat创建
    void pixel_visit_Demo(Mat& image);//像素访问
    void operators_Demo(Mat& image);//运算操作
    void trackBar_Demo(Mat& image);//滑动条
    void detectFace_Demo();//人脸检测
    void colorMap_Demo(Mat& image);//伪彩色
    void bitwise_Demo(Mat& image);//位运算
    void channels_Demo(Mat& image);//通道操作
};
