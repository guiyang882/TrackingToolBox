//
// Created by 贵阳 on 5/19/16.
//

#ifndef ALGORITHMTEST_UTILTEST_H
#define ALGORITHMTEST_UTILTEST_H

#include <vector>
#include <ctime>
#include <time.h>
#include <string>
#include <cstdlib>
#include "../quality/qualityjudgeRpc.h"
#include "../fusion/wisefuseRpc.h"
#include "../retrieve/ImageRetrieveRpc.h"

using namespace std;
using namespace RPCWiseFuse;
using namespace RPCQualityJudge;
using namespace RPCImgRecong;

string generateTaskID(int len);
void createFusionTask(DirArgs& fusiontask, string panurl, string msurl, string outurl, string algname, string bandlist, string intername);
void init_fusion_alg_map();
void init_inter_alg_map();
#endif //ALGORITHMTEST_UTILTEST_H
