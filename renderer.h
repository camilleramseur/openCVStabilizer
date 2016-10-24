//
//  render.h
//  simpleStabilizer
//
//  Created by Camille Ramseur on 7/19/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.
//

#ifndef render_h
#define render_h

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include "frameReader.h"

using namespace cv;


class Renderer
{
public:
    Renderer( FrameReader * fr, std::vector< cv::Mat_<float> > renderRigidTransforms);
    
    //returns frame with warp affine
    cv::Mat getFrame(int i);
    
private:
    FrameReader * frameReader;
    std::vector< cv::Mat_<float> > rigidTransforms;
    
};

#endif