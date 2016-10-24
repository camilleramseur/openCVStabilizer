//
//  Tracker.h
//  simpleStabilizer
//
//  Created by Camille Ramseur on 7/21/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.
//

/*Tracker class takes in a image and Shows you the strongest feature points that are in that image
 Points will be used to help stabilizer in the next step.
 */

#ifndef Tracker_h
#define Tracker_h
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>



class Tracker {
private:
    
    bool freshStart;
    cv::Mat_<float>rigidTransform;
    
    std::vector<cv::Point2f>trackedFeatures;
    cv::Mat prevGray;
public:
    Tracker();
    
    void processImage(cv::Mat& img);
    cv::Mat_<float> getRigidTransform();
    
    
};


#endif
