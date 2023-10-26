#ifndef OPPM_SCALE_OPPM_ORIGINAL_H
#define OPPM_SCALE_OPPM_ORIGINAL_H

#include <iostream>
#include <vector>
using namespace std;

void Compute_Failure_Function(const vector<int>& P, const vector<int>& LMax_P, const vector<int>& LMin_P, vector<int>& pi_P) {
    unsigned int m = P.size();
    pi_P.resize(m);

    pi_P[0] = 0;
    int q = 0;
    for (int i = 1; i < m; i++) {
        int j1 = LMax_P[q], j2 = LMin_P[q];
        int value1 = j1 == INT32_MIN ? INT32_MIN : P[i - q + j1];
        int value2 = j2 == INT32_MAX ? INT32_MAX : P[i - q + j2];
        while (q > 0 && (!(value1 < P[i] && P[i] < value2))) {
            q = pi_P[q - 1];
            j1 = LMax_P[q], j2 = LMin_P[q];
            value1 = j1 == INT32_MIN ? INT32_MIN : P[i - q + j1];
            value2 = j2 == INT32_MAX ? INT32_MAX : P[i - q + j2];
        }
        q++;
        pi_P[i] = q;
    }
}

unsigned int OPPM_Original_Matcher(const vector<int>& T, const vector<int>& P, const vector<int>& LMax_P, const vector<int>& LMin_P, const vector<int>& pi_P) {
    unsigned int matchCount = 0;
    unsigned int n = T.size(), m = P.size();
    int q = 0;
    for (int i = 0; i < n; i++) {
        int j1 = LMax_P[q], j2 = LMin_P[q];
        int value1 = j1 == INT32_MIN ? INT32_MIN : T[i - q + j1];
        int value2 = j2 == INT32_MAX ? INT32_MAX : T[i - q + j2];
        while (q > 0 && (!(value1 < T[i] && T[i] < value2))) {
            q = pi_P[q - 1];
            j1 = LMax_P[q], j2 = LMin_P[q];
            value1 = j1 == INT32_MIN ? INT32_MIN : T[i - q + j1];
            value2 = j2 == INT32_MAX ? INT32_MAX : T[i - q + j2];
        }
        q++;
        if (q == m) {
            matchCount++;
            cout << "MATCH: T[" << (i - m + 1) << ".." << i << "]\n";
            q = pi_P[q - 1];
        }
    }
    return matchCount;
}

#endif //OPPM_SCALE_OPPM_ORIGINAL_H
