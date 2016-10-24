//
//  frameReader.h
//  simpleStabilizer
//
//  Created by Camille Ramseur on 7/18/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.
//

#ifndef frameReader_h
#define frameReader_h


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

//Frame reader class reads and handles the individual frames from video that was inputted

class FrameReader
{
    
public:
    
    FrameReader(std::string path);
    cv::Mat getFrame(int i); // pass in what frame you want to loop at
    int getFrameCount(); // find number of frames in video and pass variable in for getFrame
    cv::VideoCapture getSource();
    
    
private:
    cv::VideoCapture source;
    
};

#endif