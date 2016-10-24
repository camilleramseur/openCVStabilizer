//
//  stabilizer.h
//  simpleStabilizer
//
//  Created by Camille Ramseur on 7/18/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.
//

#ifndef stabilizer_h
#define stabilizer_h

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>



/*Takes in points from the feature tracker and transforms it
 * may cause deformaties
 */


class Stabilizer
{
public:
    
    
    Stabilizer(std::vector <std::vector<cv::Point2f> > featureTrajectories);
    
    std::vector<cv::Mat_<float> > getRigidTransforms();
    
    
private:
    
    std::vector< std::vector<cv::Point2f> > trajectories;
    
    
};
#endif /* stabilizer_h */