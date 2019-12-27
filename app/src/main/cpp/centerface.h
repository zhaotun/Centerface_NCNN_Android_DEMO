#pragma once

#ifndef __RETINAFACE_NCNN_H__
#define __RETINAFACE_NCNN_H__

#include<vector>
#include<iostream>
#include<algorithm>
#include<numeric>
#include "net.h"

#include "cmath"

#define NMS_UNION 1
#define NMS_MIN  2


#if NCNN_VULKAN
#include "gpu.h"
#endif // NCNN_VULKAN

using namespace std;

typedef struct FaceInfo {
    float x1;
    float y1;
    float x2;
    float y2;
    float score;
    float area;
    float landmarks[10];
};


class Centerface  {

public:
    Centerface(const string &model_path);
    ~Centerface();

    //void init(std::string &model_path);
    void SetNumThreads(int numThreads);

    //You can change the shape of input image by setting params :resized_w and resized_h
    void detect(ncnn::Mat &inblob, std::vector<FaceInfo>&faces, int resized_w,int resized_h,
               float scoreThresh = 0.5, float nmsThresh = 0.3);

private:
    void dynamicScale(float in_w, float in_h);
    void squareBox(std::vector<FaceInfo> &faces);
    void genIds(float *heatmap, int h, int w, float thresh, std::vector<int> &ids);
    void nms(std::vector<FaceInfo>& input, std::vector<FaceInfo>& output, float nmsthreshold = 0.3,int type=NMS_MIN);
    void decode(ncnn::Mat &heatmap, ncnn::Mat &scale, ncnn::Mat &offset, ncnn::Mat &landmarks,
                std::vector<FaceInfo>&faces, float scoreThresh, float nmsThresh);

private://部分可调参数
    ncnn::Net centerface;

    int d_h;
    int d_w;
    float d_scale_h;
    float d_scale_w;

    float scale_h;
    float scale_w;

    int image_h;
    int image_w;

//	const float threshold[3] = { 0.8f, 0.8f, 0.6f };
//	int minsize = 40;
//	const float pre_facetor = 0.709f;
//
//	int count = 10;
	int num_threads = 4;
	
};


#endif //__RETINAFACE_NCNN_H__
