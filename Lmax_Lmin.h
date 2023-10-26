#ifndef OPPM_SCALE_LMAX_LMIN_H
#define OPPM_SCALE_LMAX_LMIN_H

#include "OST.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;

void Compute_LMax_LMin(const vector<int>& P, vector<int>& LMax_P, vector<int>& LMin_P) {
    unsigned int m = P.size();
    LMax_P.resize(m);
    LMin_P.resize(m);

    multimap<int, int> T;
    T.insert({P[0], 0});
    LMax_P[0] = INT32_MIN;
    LMin_P[0] = INT32_MAX;

    for (int k = 1; k < m; k++) {
        int Max = INT32_MIN, Min = INT32_MAX;
        int LMax = INT32_MIN, LMin = INT32_MAX;
        for (int i = 0; i < k; i++) {
            if (P[i] <= P[k]) {
                if (Max <= P[i]) {
                    Max = P[i];
                    LMax = i;
                }
            }
            if (P[i] >= P[k]) {
                if (Min >= P[i]) {
                    Min = P[i];
                    LMin = i;
                }
            }
        }
        LMax_P[k] = LMax;
        LMin_P[k] = LMin;
    }
}

// OST 구조 재구현할 때까지 잠금
//void Compute_LMax_LMin(const vector<int>& P, vector<int>& LMax_P, vector<int>& LMin_P) {
//    unsigned int m = P.size();
//    LMax_P.resize(m);
//    LMin_P.resize(m);
//
//    ost T;
//    T.insert({P[0], 0});
//    LMax_P[0] = INT32_MIN;
//    LMin_P[0] = INT32_MAX;
//
//    for (int k = 1; k < m; k++) {
//        T.insert({P[k], k});
//        int order = T.order_of_key(P[k]);
//
//        int min, max;
//        if (order == k) {
//            min = INT32_MAX;
//        } else {
//            min = T.find_by_order(order + 1)->second;
//        }
//        if (order == 0) {
//            max = INT32_MIN;
//        } else {
//            max = T.find_by_order(order - 1)->second;
//        }
//
//        LMax_P[k] = max;
//        LMin_P[k] = min;
//    }
//}

#endif //OPPM_SCALE_LMAX_LMIN_H
