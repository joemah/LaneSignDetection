#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <string> 
#include "DetectLane.h"


// BLURING THE IMAGE
/*  
    *convert  the color of the input image
    *apply  the gaussian filter to denoise the image
    *return the blurred image for future use
    
*/

cv::Mat DetectLane::d_Noise(cv::Mat m_input)
{   
    cv::Mat m_gray, m_blur;
    cv::cvtColor(m_input,m_gray, cv::COLOR_RGB2GRAY); // change the color of the image to gray
    cv::GaussianBlur(m_gray, m_blur, cv::Size(9, 9), 0, 0); // smoothees the gray  image

    return m_blur;

}
//ROI
// void DetectLane.h::ROI( cv::Mat& m_input, cv::Mat& dst, const cv::Point** vertices, int nVertices); // select the region of interest
// {
//     // create a mask that starts out as black
//     cv::Mat m_mask = cv::Mat(m_input.size(), m_input.type(), cv::Scalar(0, 0, 0));
//     cv::fillPoly(mask, vertices, &nVertices, 1, cv::Scalar(255, 255, 255));

//     // the output image will  only have color in the region of interest
//     cv::bitwise_and(m_input,m_input,dst, mask);
// }

// DETECT EDGES
/* 
    *detect all the edges from  the blurred image 
    *use the Canny  edge detector to perform the task manually
    *return the edges of the image
*/

cv::Mat DetectLane::d_Edge(cv::Mat m_blur)
{   
    cv::Mat m_edge;
    cv::Canny(m_blur, m_edge, 50, 150, 3);

    return m_edge;
}


// HOUGH LINES

/*
    *get all the lane segments in the masked image 
    *the m_edge is the image from the previous function that contains all
    *the detected edges
*/

//std::vector<cv::Vec4i>
void DetectLane::houghLines(cv::Mat m_edge)
{   
    cv::Mat m_dst;
    std::vector<cv::Vec2f> lines;  //vector to store the lines 
    cv::cvtColor(m_edge, m_dst, cv::COLOR_GRAY2BGR);
    HoughLines(m_edge, lines, 1, CV_PI/180, 150, 0, 0);

    // draw the lines 
    for ( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b  = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound( x0 + 1000*(-b) );
        pt1.y = cvRound( y0 + 1000*(a) );
        pt2.x = cvRound( x0 - 1000*(-b) );
        pt2.y = cvRound( y0 - 1000*(a) );
        cv::line(m_dst, pt1, pt2, cv::Scalar(0, 255, 0), 2, cv::LINE_AA );//
            
    }
    cv::namedWindow("Detected");
    cv::imshow("Detected",m_dst);

}