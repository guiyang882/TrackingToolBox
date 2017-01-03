//
//  BackgrounSubtractorWIS.hpp
//  
//
//  Created by Maurizio Giordano on 24/04/15.
//
//

#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>
// Wisard include
#include "wisard.hpp"

using namespace std;
using namespace cv;

long int wcounter;

namespace cv {
    
    class CV_EXPORTS_W BackgroundSubtractorWIS : public BackgroundSubtractor {
    public:
        
        CV_WRAP virtual int getNoBits() const = 0;
        CV_WRAP virtual void setNoBits(int nobits) = 0;
        CV_WRAP virtual int getNoTics() const = 0;
        CV_WRAP virtual void setNoTics(int notics) = 0;
        CV_WRAP virtual int getCacheSize() const = 0;
        CV_WRAP virtual void setCacheSize(int size) = 0;
        CV_WRAP virtual double getTrainIncr() const = 0;
        CV_WRAP virtual void setTrainIncr(double incr) = 0;
        CV_WRAP virtual double getTrainDecr() const = 0;
        CV_WRAP virtual void setTrainDecr(double decr) = 0;
        CV_WRAP virtual double getVarThreshold() const = 0;
        CV_WRAP virtual void setVarThreshold(double thr) = 0;
        CV_WRAP virtual double getVarWatermark() const = 0;
        CV_WRAP virtual void setVarWatermark(double mark) = 0;
        CV_WRAP virtual double getVarUpWatermark() const = 0;
        CV_WRAP virtual void setVarUpWatermark(double mark) = 0;
        CV_WRAP virtual int getSelectThreshold() const = 0;
        CV_WRAP virtual void setSelectThreshold(int thr) = 0;
        CV_WRAP virtual int getLearningStage() const = 0;
        CV_WRAP virtual void setLearningStage(int size) = 0;
        CV_WRAP virtual int getDimTics() const = 0;
        CV_WRAP virtual void set(const String& name, int value) = 0;
        CV_WRAP virtual void set(const String& name, double value) = 0;
        CV_WRAP virtual int getInt(const String& name) = 0;
        CV_WRAP virtual double getDouble(const String& name) = 0;
        CV_WRAP virtual void printinfo(int fldsize) = 0;
        CV_WRAP virtual void initialize(Size frameSize, int frameType) = 0;

    };
    CV_EXPORTS_W Ptr<BackgroundSubtractorWIS> createBackgroundSubtractorWIS();
    CV_EXPORTS_W Ptr<BackgroundSubtractorWIS> createBackgroundSubtractorWIS(cv::Size fsize, int ftype);
    CV_EXPORTS_W Ptr<BackgroundSubtractorWIS> createBackgroundSubtractorWIS(cv::Size fsize, int ftype, int nb, int nt);
}