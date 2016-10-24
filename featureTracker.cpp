//
//  featureTracker.cpp
//  simpleStabilizer
//
//  Created by Camille Ramseur on 7/27/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.
//

#include <stdio.h>
#include "frameReader.h"
#include <vector>
#include <iterator>
#include "featureTracker.h"

using namespace std;
using namespace cv;

FeatureTracker::FeatureTracker(FrameReader * fr):frameReader(fr){}



// Processes every frame of the underlying video source and returns the feature locations in each frame
vector< vector<cv::Point2f> > FeatureTracker::getFeatureTracks() {
    Mat previousGray;
    vector< vector<Point2f> > featureLocations;
    vector<uchar> status;
    vector<float> errors;
    vector< Point2f>  previousFeatureLocations;
    Mat firstImage = frameReader->getFrame(0); // is this a pointer -> or struct
    cvtColor(firstImage,previousGray,CV_BGR2GRAY);
    goodFeaturesToTrack(previousGray,previousFeatureLocations,300,0.01,10); //featureLocations-output of goodFeatures
    
    
    // gives `previousFeatureLocations`
    featureLocations.push_back(previousFeatureLocations);
    
    
    
    // Starting with i = 1
    for(int i = 1; i < frameReader->getFrameCount(); i++) {
        Mat image = frameReader->getFrame(i);
        // Convert image to grayscale, I think (implement)
        Mat gray;
        
        cvtColor(image,gray,CV_BGR2GRAY);
        // Compute location of new features
        
        // (implement)using LK Feature Tracker Pyramid function (takes in `previousImage`, `previousFeatureLocations`, and the new `image` (which is converted to grayscale again, i think))s
        
        vector<cv::Point2f> new_feature_locations;
        calcOpticalFlowPyrLK(previousGray,gray,previousFeatureLocations,new_feature_locations,status,errors,Size(10,10));
        
        featureLocations.push_back(new_feature_locations);
        
        // Update the previous image to be the one we just read, and the previous features to be the features for that image
        previousGray = gray;
        previousFeatureLocations = new_feature_locations;
    }
    
    
    
    return featureLocations;
}
