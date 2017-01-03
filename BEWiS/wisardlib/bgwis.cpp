//
// Change Detection based on Wisard 1.0
//
// Created by Maurizio Giordano
// Copyright 2015
//

#include "bgwis.hpp"
// C++ headers
#include <iostream>
#include <iomanip>
#include <string>

// OpenCv include
#include <opencv2/core/core.hpp>

#define RESET   "\033[0m"

//#include "wnet_lib.hpp"

using namespace cv;
using namespace std;

namespace cv {
    
    // default parameters of wisard background detection algorithm
    static const int defaultNoBits = 4;
    static const int defaultNoTics = 256;
    static const int defaultCacheSize = 32;
    static const double defaultTrainIncr = 1.0;
    static const double defaultTrainDecr = 1.0;
    static const double defaultVarThreshold = 0.75;
    static const double defaultVarWatermark = 0.0;
    static const double defaultVarUpWatermark = 50.0;
    static const int defaultSelectThreshold = 2;
    static const int defaultLearningStage = 1;

    class BackgroundSubtractorWISImpl : public BackgroundSubtractorWIS {
        public:
            int noBits;
            int noTics;
            int noRams;
            int dimTics;
            double trainIncr;
            double trainDecr;
            double varThreshold;
            double varWatermark;
            int selectThreshold;
            int learningStage;
            wvalue_t varUpWatermark;
            int frameNum_;
            int cacheSize;
            unsigned long int hits, misses, tcount;
            Size frameSize;
            int frameType;
            //! the default constructor
            BackgroundSubtractorWISImpl() {
                noBits = defaultNoBits;
                noTics = defaultNoTics;
                dimTics = (int) (256 / noTics);
                trainIncr = defaultTrainIncr;
                trainDecr = defaultTrainDecr;
                selectThreshold = defaultSelectThreshold;
                varThreshold = defaultVarThreshold;
                varWatermark = defaultVarWatermark;
                varUpWatermark = defaultVarUpWatermark;
                cacheSize = defaultCacheSize;
                learningStage = defaultLearningStage;
                hits = misses = tcount = 0;
            }
            BackgroundSubtractorWISImpl(cv::Size fsize, int ftype) {
                noBits = defaultNoBits;
                noTics = defaultNoTics;
                dimTics = (int) (256 / noTics);
                trainIncr = defaultTrainIncr;
                trainDecr = defaultTrainDecr;
                selectThreshold = defaultSelectThreshold;
                varThreshold = defaultVarThreshold;
                varWatermark = defaultVarWatermark;
                varUpWatermark = defaultVarUpWatermark;
                cacheSize = defaultCacheSize;
                learningStage = defaultLearningStage;
                hits = misses = tcount = 0;
                initialize(fsize, ftype);
            }
            BackgroundSubtractorWISImpl(cv::Size fsize, int ftype, int nb, int nt) {
                noBits = nb;
                noTics = nt;
                trainIncr = defaultTrainIncr;
                trainDecr = defaultTrainDecr;
                selectThreshold = defaultSelectThreshold;
                varThreshold = defaultVarThreshold;
                varWatermark = defaultVarWatermark;
                varUpWatermark = defaultVarUpWatermark;
                cacheSize = defaultCacheSize;
                learningStage = defaultLearningStage;
                hits = misses = tcount = 0;
                initialize(fsize, ftype);
            }
            //! the destructor
            ~BackgroundSubtractorWISImpl() {}
            //! the update operator
            void apply(InputArray _image, OutputArray _fgmask, double learningRate=-1) {
                const uchar *data;
                uchar *odata, *fgdata, *color;
                wentry_t **discr;
                wkey_t *tuple;
                keyval_t *keys;
                wvalue_t *mentals;
                int cr, cg, cb;
                cache_entry_t * cache;
                pix_t **neigh_map;
                uchar B,G,R;
                wisard_t *wiznet = _wiznet;
                int *histos = histoArray;
                
                Mat image = _image.getMat();
                double sum=0;
                neigh_map = wiznet->neigh_map;
#pragma omp parallel for schedule(static) shared(image,wiznet,neigh_map) private(sum,discr,cache,data,odata,fgdata,R,G,B,color,keys)
                for (int j=0; j<image.rows; j++) {
                    data= image.ptr<uchar>(j);
                    odata= fgmask.ptr<uchar>(j);
                    fgdata= fgdetect.ptr<uchar>(j);
                    for (int i=0; i<image.cols; i++) {
                        discr = wiznet->net[j*image.cols + i]; // get discriminator of pixel
                        cache = wiznet->cachearray[j*image.cols + i]; // get cache for pixel
                        // make tuple
                        B = *data++; G = *data++; R = *data++;
                        cache = makeTupleCached(cache,R,G,B,neigh_map);
                        wiznet->cachearray[j*image.cols + i] = cache;
                        color = maxcolor[j*image.cols + i];
                        keys = maxkeys[j*image.cols + i];
                        // train
                        for (int neuron=0;neuron<noRams;neuron++) {
                            if (learningStage > 0 || cache->weight > selectThreshold) keys[neuron] = wram_up_key_down_rest(discr[neuron], cache->tuple[neuron],trainIncr,trainDecr,varUpWatermark);
                        }
                        
                        // update output mask
                        if (sum/(double)noRams >= varThreshold) {  // (sigma) Pixel is black (BG)
                            *odata++ = (uchar)0; // set pixel to BG
                        } else {                                   // pixels is white (FG)
                            *odata++ = (uchar)255; // set pixel to FG
                        }
                        updateMaxColor(color,keys,fgdata++,fgdata++,fgdata++);  // update bgmodel in all pixels
                    }
                }
                if (learningStage > 0) {
                    learningStage--;
                }
                fgmask.copyTo(_fgmask);
            }
            
            void getBackgroundImage(OutputArray backgroundImage) const {
                fgdetect.copyTo(backgroundImage);
            }
            
            void printinfo(int fldsize) {
                cout << left << setw(fldsize) << setfill(' ') << "noBits: " << noBits << endl;
                cout << left << setw(fldsize) << setfill(' ') << "noTics: " << noTics << "(" << dimTics << ")" << endl;
                cout << left << setw(fldsize) << setfill(' ') << "noRams: " << noRams <<  endl;
                cout << left << setw(fldsize) << setfill(' ') << "Train Policy: " << trainIncr << ":" << trainDecr <<  endl;
                cout << left << setw(fldsize) << setfill(' ') << "Classification Thresh: " << varThreshold << endl;
                cout << left << setw(fldsize) << setfill(' ') << "Selection Thresh: " << selectThreshold << endl;
                cout << left << setw(fldsize) << setfill(' ') << "Watermark: " << varWatermark << endl;
                cout << left << setw(fldsize) << setfill(' ') << "Uppermark: " << varUpWatermark << endl;
                cout << left << setw(fldsize) << setfill(' ') << "LearningStage: " << learningStage << endl;
                cout << left << setw(fldsize) << setfill(' ') << "Cachesize: " << cacheSize << endl;
                ++frameNum_;
            }
        
            //! re-initiaization method
            void initialize(Size _frameSize, int _frameType) {
                frameSize = _frameSize;
                frameType = _frameType;
                frameNum_ = 0;
                string colormode = "RGB";
                
                int nchannels = CV_MAT_CN(frameType);
                dimTics = (int) (256 / noTics);
                CV_Assert( nchannels <= CV_CN_MAX );
                _wiznet = net_create(noBits,frameSize.width, frameSize.height,colormode, noTics, cacheSize);
                noRams = _wiznet->n_ram;
                histoSize = frameSize.width * frameSize.height * (noTics + 2) * nchannels;
                histoArray = (int *)malloc(sizeof(int) * histoSize);
                for (int i=0; i < histoSize; i++) histoArray[i]=0;
                maxkeys = (keyval_t **)malloc(sizeof(keyval_t *) * frameSize.width * frameSize.height);
                maxcolor = (unsigned char **)malloc(sizeof(unsigned char *) * frameSize.width * frameSize.height);
                for (int i=0; i < frameSize.width * frameSize.height; i++) {
                    maxkeys[i] = (keyval_t *)malloc(sizeof(keyval_t) * noRams);
                    maxcolor[i] = (unsigned char *)malloc(sizeof(unsigned char) * noTics * 3);
                    for (int x=0; x < noTics * 3; x++) maxcolor[i][x] = (unsigned char)0;
                }
                _neigh_map = _wiznet->neigh_map;
                
                // Create mask frame
                fgmask.create( frameSize, CV_8U );
                // Create bgmodel image
                fgdetect.create( frameSize, _frameType );
                fgdetect = Scalar(0, 0, 0);
            }
            
            virtual int getNoBits() const { return noBits; }
            virtual void setNoBits(int _nobits) { noBits = _nobits; }
            virtual int getNoTics() const { return noTics; }
            virtual void setNoTics(int _notics) { noTics = _notics; }
            virtual int getNoRams() const { return noRams; }
            virtual int getCacheSize() const { return cacheSize; }
            virtual void setCacheSize(int _size) { cacheSize = _size; }
            virtual double getTrainIncr() const { return trainIncr; }
            virtual void setTrainIncr(double _incr) { trainIncr = _incr; }
            virtual double getTrainDecr() const { return trainDecr; }
            virtual void setTrainDecr(double _decr) { trainDecr = _decr; }
            virtual double getVarThreshold() const { return varThreshold; }
            virtual void setVarThreshold(double _thr) { varThreshold = _thr; }
            virtual double getVarWatermark() const { return varWatermark; };
            virtual void setVarWatermark(double _mark) { varWatermark = _mark; }
            virtual double getVarUpWatermark() const { return varUpWatermark; };
            virtual void setVarUpWatermark(double _mark) { varUpWatermark = _mark; }
            virtual int getSelectThreshold() const { return selectThreshold; };
            virtual void setSelectThreshold(int _selthr) { selectThreshold = _selthr; }
            virtual int getLearningStage() const { return learningStage; };
            virtual void setLearningStage(int _lsize) { learningStage = _lsize; }
            virtual int getDimTics() const { return dimTics; };
            void set(const String& name, int value) {
                if (name == "noBits") setNoBits(value);
                else if (name == "noTics") setNoTics(value);
                else if (name == "cacheSize") setCacheSize(value);
                else if (name == "selectThreshold") setSelectThreshold(value);
                else if (name == "learningStage") setLearningStage(value);
            } ;
            void set(const String& name, double value) {
                if (name == "trainIncr") setTrainIncr(value);
                else if (name == "trainDecr") setTrainDecr(value);
                else if (name == "varWatermark") setVarWatermark(value);
                else if (name == "varThreshold") setVarThreshold(value);
                else if (name == "varUpWatermark") setVarUpWatermark(value);
            } ;
            int getInt(const String& name) {
                if (name == "noBits") getNoBits();
                else if (name == "noTics") getNoTics();
                else if (name == "noRams") getNoRams();
                else if (name == "dimTics") getDimTics();
                else if (name == "cacheSize") getCacheSize();
                else if (name == "selectThreshold") getSelectThreshold();
                else if (name == "learningStage") getLearningStage();
            } ;
            double getDouble(const String& name) {
                if (name == "trainIncr") return getTrainIncr();
                else if (name == "trainDecr") return getTrainDecr();
                else if (name == "varWatermark") return getVarWatermark();
                else if (name == "varThreshold") return getVarThreshold();
                else if (name == "varUpWatermark") return getVarUpWatermark();
            } ;
        protected:
            wisard_t *_wiznet = (wisard_t *)NULL;
            pix_t **_neigh_map;
            std::pair <int, int > **_neigh_map_raw;
            Mat fgmask;
            Mat fgdetect;
            int histoSize;
            unsigned char **maxcolor;
            keyval_t **maxkeys;
            wvalue_t **_mentals;
            int *histoArray;

            wvalue_t mentalDiscr(wentry_t **discr, wvalue_t *mentals) {
                wentry_t *p, *m;
                int offset=0, b;
                wvalue_t maxvalue=0, value;
                for (int i=0; i< noTics * 3; i++) mentals[i] = 0;
                for (int neuron=0,offset=0;neuron<noRams;neuron++,offset+=noBits) {
                    m = discr[neuron];
                    for(p=m;;p=p->next) {
                        if (p->next==m) break;
                        for (b=0;b<noBits;b++) {
                            if (((p->next->key)>>(wkey_t)(noBits - 1 - b) & 1) > 0) {
                                //value = mentals[_neigh_map_raw[offset + b]] += p->next->value;
                                if (maxvalue < value) maxvalue = value;
                            }
                        }
                    }
                }
                return maxvalue;
            }
            // Make tuple with Cache support
            cache_entry_t *makeTupleCached(cache_entry_t *cache, unsigned char R, unsigned char G, unsigned char B, pix_t **neigh_map) {
                cache_entry_t *p, *prec;
                int cr = (int)(R / dimTics);
                int cg = (int)(G / dimTics);
                int cb = (int)(B / dimTics);
                register int neuron, k;
                int tmp, *ptr;
                // scan cache for hit or miss
                p = cache;
                prec = cache->prev;
                tcount ++;
                for (;;) {
                    if (p->cr == cr && p->cg == cg && p->cb == cb) {  // cache hit (move found in front)
                        hits++;
                        if (p == cache) {  // hit and in front
                            cache->weight += cache->idx;
                            cache->idx++;
                        } else {            // hit and not in front (move to front)
                            prec->next = p->next;   // remove item
                            p->next->prev=prec;
                            cache->prev->next = p;
                            p->prev = cache->prev;
                            p->next = cache;
                            cache->prev = p;
                            p->idx = 1;
                            cache = p;
                        }
                        return cache;
                    }
                    if (p->next == cache) {
                        // move top on first non-empty
                        misses++;
                        cache = cache->prev;
                        cache->cr = cr;
                        cache->cg = cg;
                        cache->cb = cb;
                        // initialize tuple
                        for (neuron=0;neuron<noRams;neuron++) cache->tuple[neuron] = 0;
                        // compute tuple
                        for (k=0;k<noTics;k++) {
                            if (k<cr) cache->tuple[neigh_map[0][k].first] |= neigh_map[0][k].second;
                            if (k<cg) cache->tuple[neigh_map[1][k].first] |= neigh_map[1][k].second;
                            if (k<cb) cache->tuple[neigh_map[2][k].first] |= neigh_map[2][k].second;
                        }
                        cache->weight = 0;
                        cache->idx = 1;
                        return cache;
                    }
                    p = p->next;
                    prec = prec->next;
                }
            }
            void updateMaxColor(unsigned char *color, keyval_t *keys, unsigned char *NB, unsigned char *NG,unsigned char *NR) {
                unsigned char *B, *G, *R;
                B = color;
                G = color+noTics;
                R = color+noTics+noTics;
                int cb=0,cg=0,cr=0;
                for (int k=0; k < noTics; k++) {
                    *B = (unsigned char)((keys[_neigh_map[0][k].first].first & _neigh_map[0][k].second) / _neigh_map[0][k].second);
                    *G = (unsigned char)((keys[_neigh_map[1][k].first].first & _neigh_map[1][k].second) / _neigh_map[1][k].second);
                    *R = (unsigned char)((keys[_neigh_map[2][k].first].first & _neigh_map[2][k].second) / _neigh_map[2][k].second);
                    if (*B == (unsigned char)1 ) { cb++; }
                    if (*G == (unsigned char)1 ) { cg++; }
                    if (*R == (unsigned char)1 ) { cr++; }
                    B++; G++; R++;
                }
                *NB = (unsigned char)(cb * dimTics);
                *NG = (unsigned char)(cg * dimTics);
                *NR = (unsigned char)(cr * dimTics);
            }
    };

    Ptr<BackgroundSubtractorWIS> createBackgroundSubtractorWIS() {
        return makePtr<BackgroundSubtractorWISImpl>();
    }
    Ptr<BackgroundSubtractorWIS> createBackgroundSubtractorWIS(cv::Size fsize, int ftype) {
        return makePtr<BackgroundSubtractorWISImpl>(fsize,ftype);
    }
    Ptr<BackgroundSubtractorWIS> createBackgroundSubtractorWIS(cv::Size fsize, int ftype, int nb, int nt) {
        return makePtr<BackgroundSubtractorWISImpl>(fsize,ftype,nb,nt);
    }
    
}
