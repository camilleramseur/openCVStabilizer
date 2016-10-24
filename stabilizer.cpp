//
//  stabilizer.cpp
//  simpleStabilizer
//
//  Created by Camille Ramseur on 8/2/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.
//

#include <stdio.h>
#include "stabilizer.h"
#include "featureTracker.h"
#include "Tracker.h"
using namespace std;
using namespace cv;

//Constructor that takes in feature points and feature loactions from the feature tracker

Stabilizer::Stabilizer(vector< vector<Point2f> > featureTrajectories):trajectories(featureTrajectories){
 
}
//aligns the points in the last frame and applies it ot the last frames points to stabilie it
std::vector<cv::Mat_<float> > Stabilizer::getRigidTransforms(){
    
    
    vector<cv::Point2f> corners;
    vector<Mat_<float> > transforms;
    transforms.push_back(Mat::eye(3,3,CV_32FC1)); // rigid transform ( takes into account for the first frame and performs the identity matrix
    
    
    for(int i=1; i<trajectories.size(); i++){
        vector <Point2f> previousFeatures=trajectories[i-1]; // looks at the second frame. begins: frame 2 looking at frame 1
        vector <Point2f> currentFeatures = trajectories[i];
        
        //compute transform (rigid transform)
        Mat_<float> transform = estimateRigidTransform(currentFeatures,previousFeatures,false);
        cv::Mat_<float> nrt33 = cv::Mat_<float>::eye(3,3);
        transform.copyTo(nrt33.rowRange(0,2));
        //from current frames to previous features
        transforms.push_back(transforms[i-1] * nrt33 );
        
        
    }
    
    return transforms;
}






