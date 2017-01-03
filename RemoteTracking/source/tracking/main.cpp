//
// Created by 贵阳 on 2016/11/29.
//
#include "opencv2/video/tracking.hpp"
#include "opencv2/highgui.hpp"

#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;
using namespace cv;
/*
 *第一个方程是系统的运动方程，第二个方程是系统的观测方程，其中的参数A,B,H,都是矩阵，而OpenCV中自带的kalman示例程序的编程思路也是依据上面的两个方程。
 *具体的编程主体思路大致是这样的：
 *(1).初始化以下的变量：测量矩阵，转移矩阵，过程噪声协方差矩阵，测量噪声协方差矩阵，后验错误协方差矩阵等，而这些的矩阵的初始化，即是跟上述的两个方程中的A,B,H相关。
 *(2).调用OpenCV中的cvKalmanPredict（）函数，这个函数完成的正是任务一，预测阶段。
 *(3).调用OpenCV中的cvKalmanCorrect（）函数，这个函数完成的是任务二，校正阶段。
 *(4)重复步骤2和3，直至完成kalman滤波过程。
 * */

// plot points
#define drawCross( center, color, d )                                        \
                line( img, Point( center.x - d, center.y - d ),                          \
                             Point( center.x + d, center.y + d ), color, 1, 8, 0); \
                line( img, Point( center.x + d, center.y - d ),                          \
                             Point( center.x - d, center.y + d ), color, 1, 8, 0 )

static inline Point calcPoint(Point2f center, double R, double angle)
{
    return center + Point2f((float)cos(angle), (float)-sin(angle))*(float)R;
}

static void help()
{
    printf( "\nExample of c calls to OpenCV's Kalman filter.\n"
                    "   Tracking of rotating point.\n"
                    "   Rotation speed is constant.\n"
                    "   Both state and measurements vectors are 1D (a point angle),\n"
                    "   Measurement is the real point angle + gaussian noise.\n"
                    "   The real and the estimated points are connected with yellow line segment,\n"
                    "   the real and the measured points are connected with red line segment.\n"
                    "   (if Kalman filter works correctly,\n"
                    "    the yellow segment should be shorter than the red one).\n"
                    "\n"
                    "   Pressing any key (except ESC) will reset the tracking with a different speed.\n"
                    "   Pressing ESC will stop the program.\n"
    );
}

int main(int, char**)
{
    help();
    Mat img(500, 500, CV_8UC3);
    KalmanFilter KF(2, 1, 0);
    Mat state(2, 1, CV_32F); /* (phi, delta_phi) */
    Mat processNoise(2, 1, CV_32F);
    Mat measurement = Mat_<float>(Mat::zeros(1, 1, CV_32F));
    char code = (char)-1;

    while (true) {
        randn( state, Scalar::all(0), Scalar::all(0.1) );//产生均值为0，标准差为0.1的二维高斯列向量
        KF.transitionMatrix = (Mat_<float>(2, 2) << 1, 1, 0, 1);//转移矩阵为[1,1;0,1]

        //函数setIdentity是给参数矩阵对角线赋相同值，默认对角线值值为1
        setIdentity(KF.measurementMatrix);
        setIdentity(KF.processNoiseCov, Scalar::all(1e-5));//系统过程噪声方差矩阵
        setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));//测量过程噪声方差矩阵
        setIdentity(KF.errorCovPost, Scalar::all(1));//后验错误估计协方差矩阵

        //statePost为校正状态，其本质就是前一时刻的状态
        randn(KF.statePost, Scalar::all(0), Scalar::all(0.1));

        while (true) {
            Point2f center(img.cols*0.5f, img.rows*0.5f);
            float R = img.cols/3.f;

            //state中存放起始角，state为初始状态
            double stateAngle = state.at<float>(0);
            Point statePt = calcPoint(center, R, stateAngle);

            /*
                使用kalma步骤二
                调用kalman这个类的predict方法得到状态的预测值矩阵
            */
            Mat prediction = KF.predict();

            //用kalman预测的是角度
            double predictAngle = prediction.at<float>(0);
            Point predictPt = calcPoint(center, R, predictAngle);

            randn( measurement, Scalar::all(0), Scalar::all(KF.measurementNoiseCov.at<float>(0)));

            // generate measurement
            //带噪声的测量
            measurement += KF.measurementMatrix*state;

            double measAngle = measurement.at<float>(0);
            Point measPt = calcPoint(center, R, measAngle);

            img = Scalar::all(0);
            //状态坐标白色
            drawCross( statePt, Scalar(255,255,255), 3 );
            //测量坐标蓝色
            drawCross( measPt, Scalar(0,0,255), 3 );
            //预测坐标绿色
            drawCross( predictPt, Scalar(0,255,0), 3 );
            //真实值和测量值之间用红色线连接起来
            line( img, statePt, measPt, Scalar(0,0,255), 3, 8, 0 );
            //真实值和估计值之间用黄色线连接起来
            line( img, statePt, predictPt, Scalar(0,255,255), 3, 8, 0 );

            /*
                使用kalma步骤三
                调用kalman这个类的correct方法得到加入观察值校正后的状态变量值矩阵
            */
            if(theRNG().uniform(0,4) != 0)
                KF.correct(measurement);

            randn( processNoise, Scalar(0), Scalar::all(sqrt(KF.processNoiseCov.at<float>(0, 0))));
            //不加噪声的话就是匀速圆周运动，加了点噪声类似匀速圆周运动，因为噪声的原因，运动方向可能会改变
            state = KF.transitionMatrix*state + processNoise;

            imshow( "Kalman", img );
            code = (char)waitKey(100);

            if( code > 0 )
                break;
        }
        if( code == 27 || code == 'q' || code == 'Q' )
            break;
    }

    return 0;
}
