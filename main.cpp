
// WHAT THE CODE DOES
/*
    * receive an input image,
    * transform it to grayscale
    * then apply the GaussianBlur to  smooth the image
    * find the ROI
    * then apply the canny to detect edges
    *  look for lines with hough transform Lines 
    * finally draw the lines obtained from hough
*/
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "DetectLane.h"
#include "Circle.cpp"


// this is the main function which cond=tains all  the functions used to  detect roadlines and signs

int main( int argc, char** argv )
{   
    if (argc != 2 )
    { 
        std::cout << "Not enough arguments, please  enter ./main and the image name " << std::endl;
        return -1;
    }

    cv::Mat m_input;
    cv::Mat m_blur;
    cv::Mat m_edge;
  
    m_input =  cv::imread(argv[1], cv::IMREAD_COLOR); // read the input image file 

    DetectLane detectlane; // create the class object 

    m_blur = detectlane.d_Noise(m_input);
    m_edge = detectlane.d_Edge(m_blur);

    // int nOfpoints[] = {8};
    // int shift_x = 56;
    // int shift_y = 55;

    // cv::Point points[1][8];

    // points[0][0] = cv::Point(m_input.size().width/2 - shift_x,m_input.size().height/2 + shift_y);
    // points[0][1] = cv::Point(100, m_input.size().height);
    // points[0][2] = cv::Point(100, m_input.size().height);
    // points[0][3] = cv::Point(m_input.size().width - 50, m_input.size().height);
    // points[0][4] = cv::Point(m_input.size().width - 50, m_input.size().height);
    // points[0][5] = cv::Point(m_input.size().width/2 + shift_x, m_input.size().height/2 + shift_y);
    // points[0][6] = cv::Point(m_input.size().width/2 + shift_x, m_input.size().height/2 + shift_y);
    // points[0][7] = cv::Point(m_input.size().width/2 - shift_x, m_input.size().height/2 + shift_y);

    // const cv::Point* vertices[1] = { points[0] };
 
    // Select ROI
    //cv::Mat roi = cv::Mat::zeros(m_input.size(),m_input.type());
    //cv::fillPoly(roi, vertices, nOfpoints, 1, cv::Scalar(255), 8);
    // std::cout << m_edge.size() << std::endl;
    // std::cout << roi.size() << std::endl;
    //cv::bitwise_and(m_edge, roi,roi);
    //cv::imshow("ROI",roi);

    //detectlane.houghCircles(m_input, m_edge);
    detectlane.houghLines(m_edge);
    cv::waitKey(0); 
    return 0;
}
