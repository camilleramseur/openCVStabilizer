//
//  featureTracker.h
//  simpleStabilizer
//
//  Created by Camille Ramseur on 7/18/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.
//

#ifndef featureTracker_h
#define featureTracker_h
#include "frameReader.h"
#include <vector>




/* Evaluate video frame by frame.
 
 */

class FeatureTracker
{
public:
    
    FeatureTracker(FrameReader * fr);
    std::vector< std:: vector<cv::Point2f> >getFeatureTracks();
    
    
    
private:
    FrameReader * frameReader;
    int count;
    
};
#endif