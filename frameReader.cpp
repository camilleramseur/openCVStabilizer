//
//  frameReader.cpp
//  simpleStabilizer
//
//  Created by Camille Ramseur on 7/25/16.
//  Copyright © 2016 Camille Ramseur. All rights reserved.
//

#include <stdio.h>
#include <iostream>
//using namespace std;
#include "frameReader.h"
#include "Tracker.h"


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <vector>

using namespace std;


//take input from user and integrate it into main
cv::VideoCapture FrameReader::getSource(){
    return source;
    
}
//Frame reader class contructor that reads in the path of where the video
FrameReader::FrameReader(std::string path){ //constructor
    source.open(path);
}

//returns the number of frames in the inputted video
int FrameReader:: getFrameCount(){
    
    return 80; //the number of frames you want the program to read
    
    return source.get(cv::CAP_PROP_FRAME_COUNT);
    
    
    cv::Mat frame;
    int count=0;
    while(source.isOpened()){
        source>>frame;
        if(frame.empty()) break;
        count++;
        cout<<count; //using this for testing purposes
    }
    return count;
    
}

//Function allows you to choose what frame you want to evaluate
cv::Mat FrameReader::getFrame(int i){
    source.set(cv::CAP_PROP_POS_FRAMES, i+1);
    cv::Mat image;
    source >> image;
    return image;
    
    
    
    
}









