#include <iostream>
#include <Ice/Ice.h>

#include "source/utils/utiltest.h"

using namespace std;
using namespace RPCWiseFuse;
using namespace RPCQualityJudge;

extern map<string, int> m_fusionalg;
extern map<string, int> m_interalg;

int main(int argc, char* argv[]) {
    init_fusion_alg_map();
    init_inter_alg_map();

    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        bool isRetrieve = true;
        bool isFusion = false;
        if(isRetrieve) {
            Ice::ObjectPrx base = ic->stringToProxy("WISERETRIEVE:default -h 10.2.3.119 -p 9998");
            ImgRetrievalPrx quality_client = ImgRetrievalPrx::checkedCast(base);
            if(!quality_client) {
                throw runtime_error("Invalid proxy !");
            }

            DictStr2Str inputArgs;
            inputArgs["id"] = "10000000sdssdkjbfdkjsbd";
//            inputArgs["purl"] = "/tomcat/webapps/targetreg/userupload/test/1.jpg";
            inputArgs["purl"] = "/opt/tomcat/webapps/targetreg/admindata/remote_test/10_水立方(遥感)/10_1.JPG";
            inputArgs["upleftx"] = "0";
            inputArgs["uplefty"] = "0";
            inputArgs["height"] = "50";
            inputArgs["width"] = "50";
            inputArgs["saveurl"] = "/opt/tomcat/webapps/targetreg/admindata/photo_test/1_工人体育馆/1_4_test.jpg";
            inputArgs["featureurl"] = "/opt/tomcat/webapps/targetreg/admindata/photo_test/1_工人体育馆/1_4_test.csv";
            WordRes obj = quality_client->imgSearchSync(inputArgs);
        }

        if(isFusion) {
            Ice::ObjectPrx base = ic->stringToProxy("WISEFUSION:default -h 10.2.3.119 -p 9999");
            WiseFusionInfPrx quality_client = WiseFusionInfPrx::checkedCast(base);
            if(!quality_client) {
                throw runtime_error("Invalid proxy !");
            }

            DirArgs inputArgs;
            //k:id	v:		//任务唯一编号
            //k:panurl	v:	//图像1地址
            //k:msurl	v:	//图像2地址
            //k:outurl	v:	//输出图像地址
            //k:algname	v:	//算法名称 "数据的name"+"_"+"数据库的version"
            //k:band	v:	//波段	波段编号1|波段编号1|波段编号1
            //k:intername	v:	//插值算名称 "数据的name"+"_"+"数据库的version"
            inputArgs["id"] = "10000000sdssdkjbfdkjsbd";
            inputArgs["panurl"] = "/opt/tomcat/webapps/wisefuse/img/GF1_2m_and_GF1_8m/GF1_Pan_2m_1.tif";
            inputArgs["msurl"] = "/opt/tomcat/webapps/wisefuse/img/GF1_2m_and_GF1_8m/GF1_MSS_8m_1.tif";
            inputArgs["outurl"] = "/opt/tomcat/webapps/wisefuse/product/2016_06_16/GF1_Pan_2m_1__GF1_MSS_8m_1_6040ec01669e4f1e.tif";
            inputArgs["algname"] = "Curvelet and HCS_1_1";
            inputArgs["band"] = "1|2|3";
            inputArgs["intername"] = "Nearest_1_0";
            int obj = quality_client->fuseAsyn(inputArgs);
        }
    } catch (const Ice::Exception& ex) {
        cerr << ex << endl;
        status = 1;
    } catch (const char* msg) {
        cerr << msg << endl;
        status = 1;
    }
    if (ic)
        ic->destroy();
    return status;
    return 0;
}
