//
//  Tracker.cpp
//  simpleStabilizer
//
//  Created by Camille Ramseur on 7/21/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include "Tracker.h"

using namespace std;
using namespace cv;

//makes rigid transform a 3X3 matrix
Tracker::Tracker():freshStart(true) {
    
    rigidTransform = cv::Mat::eye(3,3,CV_32FC1); //affine 2x3 in a 3x3 matrix (eye created a 3x3 matrix of type CV_32FC1=1)
}


//returns value currently stored of rigidtransform
cv::Mat_<float> Tracker::getRigidTransform(){
    return rigidTransform;
    
}

//uses image to pick up feature points and applys Lukas Kanade algorithm optical flow algorithm
void Tracker::processImage(cv::Mat& img) {
    
    
    cv::Mat gray;
    cvtColor(img,gray,CV_BGR2GRAY);
    
    /* creates a vector of points2f Array of (x,y) coordinates of each keypoint
     * corner is also known as an interest point
     * it is the intersection of two edges, it represents a point in which the directions of these two edges
     */
    
    vector<cv::Point2f> corners;
    if(trackedFeatures.size() < 200) {
        
        /*takes the imput converted gray image and finds to 300 interest points that fit the image
         * quality in the parameter specified.
         */
        goodFeaturesToTrack(gray,corners,300,0.01,10);
        cout << "found " << corners.size() << " features\n";
        for (int i = 0; i < corners.size(); ++i) {
            trackedFeatures.push_back(corners[i]);
        }
    }
    
    //looks at previous image and calculates the optical flow
    //releases previous image's contents in order to get ready for the
    if(!prevGray.empty()) {
        vector<uchar> status; vector<float> errors;
        
        /* function implements a sparse iterative version of the Lucas-Kanade optical flow in pyramids.
         * prevGray= gray= nothing (first time)
         * trackedFeatures= ,corners= ,status= ,errors=
         */
        
        calcOpticalFlowPyrLK(prevGray,gray,trackedFeatures,corners,status,errors,cv::Size(10,10));
        if(cv::countNonZero(status) < status.size() * 0.8) {
            // prints out error message
            cout << "cataclysmic error \n";
            //reinitialites rigidTransform like it was in the beginning
            rigidTransform = cv::Mat::eye(3,3,CV_32FC1);
            
            //clears tracked features from matrix
            trackedFeatures.clear();
            
            
            prevGray.release();
            
            
            freshStart = true;
            return;
        } else
            freshStart = false;
        
        cv::Mat_<float> newRigidTransform = estimateRigidTransform(trackedFeatures,corners,false);
        cv::Mat_<float> nrt33 = cv::Mat_<float>::eye(3,3);
        
        newRigidTransform.copyTo(nrt33.rowRange(0,2));
        rigidTransform *= nrt33;
        trackedFeatures.clear();
        for (int i = 0; i < status.size(); ++i) {
            if(status[i]) {
                trackedFeatures.push_back(corners[i]);
            }
        }
    }
    
    
}