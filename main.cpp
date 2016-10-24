

//
//  main.cpp
//  simpleStabilizer
//
//  Created by Camille Ramseur on 6/23/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.

/*Calls different parts of the stabilizer pipeline and modular components
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include "Tracker.h"
#include "frameReader.h"
#include "stabilizer.h"
#include "featureTracker.h"
#include "renderer.h"
using namespace cv;
using namespace std;


int main() {
    
    string path="/Users/ramseur/Documents/Consumer Textures/small.mov";
    Mat frame_warped;
    
    FrameReader readVideo(path);
    FeatureTracker tracker(&readVideo);
    vector<vector<Point2f> > featureTracks = tracker.getFeatureTracks();
    
    Stabilizer stabilizer(featureTracks);
    vector<Mat_<float> > rigidTransforms = stabilizer.getRigidTransforms();
    
    Renderer renderer(&readVideo, rigidTransforms);
    
    cout << "Video has " << readVideo.getFrameCount() << " frames" << endl;
    
    bool showFeatures = false;
    bool stabilize = false;
    bool showImage = true;
    int feature = -1;
    int i = 0;
    
    while(1) {
        
        Mat frame = stabilize ? renderer.getFrame(i) : readVideo.getFrame(i);
        if(!showImage) {
            frame = frame * 0 + CV_RGB(255, 255, 255);
        }
        if(showFeatures){
            Mat_<float> transform = rigidTransforms[i];
            vector<Point2f> features = featureTracks[i];
            vector<Point2f> warpedFeatures;
            perspectiveTransform(features, warpedFeatures, transform);
            
            for(int pointCount = 0; pointCount < features.size(); pointCount++){
                auto point = (stabilize ? warpedFeatures : features).at(pointCount);
                
                int size = 2;
                int thickness = CV_FILLED;
                cv::Scalar color = CV_RGB(255, 0, 0);
                circle(frame,point,size,color,thickness);
                if(pointCount == feature){
                    cout << "Feature at " << point << endl;
                    color = CV_RGB(255, 255, 0);
                    size = 10;
                    thickness = 2;
                    circle(frame,point,size,color,thickness);
                }
                
            }
        }
        
        imshow("Video", frame);
        
        int key = waitKey(0);
        switch(key) {
            case 102: //f
                showFeatures = !showFeatures;
                break;
            case 113: //Press q to quit
                return 0;
            case 63235: // press right arrow key to go to the next frame.
                i = min(readVideo.getFrameCount()-1, i + 1);
                break;
            case 63234: // press left key to go back a frame
                i = max(0, i -1);
                break;
            case 114: //prese r to reset
                i = 0;
                break;
            case 115: // press s if you want to turn on and off stabilization
                stabilize=!stabilize;
                break;
            case 105://press i to turn off the image in the background
                showImage=!showImage;
                break;
            case 45: // - allow you to go backward in feature points you choose
                feature = max(-1, feature-1);
                cout << "Feature now " << feature << endl;
                break;
            case 61: // - allow you to go forawrd in feature points you choose
                feature = feature + 1;
                cout << "Feature now " << feature << endl;
                break;
            default:
                cout << "Unknown key " << key << endl;
                
        }
        
    }
    
    
    
    
    
}
