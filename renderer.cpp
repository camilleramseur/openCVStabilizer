//
//  renderer.cpp
//  simpleStabilizer
//
//  Created by Camille Ramseur on 8/8/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.
//

#include <stdio.h>
#include "renderer.h"
#include "frameReader.h"
#include "Tracker.h"
#include "featureTracker.h"
using namespace std;
using namespace cv;

/* Renderer class takes the rigid transform from the stabilizer and applies to every frame
 
 */

Renderer::Renderer( FrameReader* fr, std::vector< cv::Mat_<float> > rt):frameReader(fr),rigidTransforms(rt){
    
}

//Takes in rigid transformations from stabilizer class and applies final warp transforms to each frame
cv::Mat Renderer::getFrame(int i){
    
    Mat frame,frame_warped;
    frame = frameReader->getFrame(i);
    Mat_<float> transform = rigidTransforms[i];
    warpAffine(frame,frame_warped,transform.rowRange(0,2),cv::Size());
    return frame_warped;
    
}

