//
// Created by 贵阳 on 5/19/16.
//

#include "utiltest.h"

string generateTaskID(int length) {
    static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string result;
    result.resize(length);

    srand(time(NULL));
    for (int i = 0; i < length; i++)
        result[i] = charset[rand() % charset.length()];

    return result;
}

map<string, int> m_fusionalg;
map<string, int> m_interalg;

void init_fusion_alg_map() {
    m_fusionalg["Brovey_1_0"]=1;
    m_fusionalg["HIS_1_0"]=2;
    m_fusionalg["PCA_1_0"]=3;
    m_fusionalg["DWT and HIS_1_0"]=4;
    m_fusionalg["Curvelet and HIS_1_0"]=5;
    m_fusionalg["Curvelet and HCS_1_0"]=8;
    m_fusionalg["GramSchmidt_1_0"]=6;
    m_fusionalg["HCS_1_0"]=7;
    m_fusionalg["Curvelet and HCS_1_1"]=10;
    m_fusionalg["Curvelet and GramSchmidt_1_0"]=9;
}

void init_inter_alg_map() {
    m_interalg["Nearest_1_0"]=1;
    m_interalg["Linear_1_0"]=2;
    m_interalg["CubicConv_1_0"]=3;
}

void createFusionTask(DirArgs& fusiontask,
                      string panurl, string msurl, string outurl,
                      string algname, string bandlist, string intername) {
    fusiontask["id"] = generateTaskID(10);
    fusiontask["panurl"] = panurl;
    fusiontask["msurl"] = msurl;
    fusiontask["outurl"] = outurl;
    fusiontask["algname"] = algname;
    fusiontask["band"] = bandlist;
    fusiontask["intername"] = intername;
}

