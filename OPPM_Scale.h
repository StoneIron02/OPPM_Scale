#ifndef OPPM_SCALE_OPPM_SCALE_H
#define OPPM_SCALE_OPPM_SCALE_H

#include <iostream>
#include <vector>
using namespace std;

void Compute_Extend_Table(const vector<int>& T, vector<int>& E_T) {
    unsigned int n = T.size();
    E_T.resize(n);

    E_T[0] = 0, E_T[1] = 0;
    for (int i = 2; i < n; i++) {
        if ((T[i - 2] < T[i - 1] && T[i - 1] < T[i]) ||
            (T[i - 2] == T[i - 1] && T[i - 1] == T[i]) ||
            (T[i - 2] > T[i - 1] && T[i - 1] > T[i])) {
            E_T[i] = E_T[i - 1];
        } else {
            E_T[i] = i - 1;
        }
    }
}

void OPPM_Scale_Matcher(const vector<int>& T, const vector<int>& P, const int k, const vector<int>& E_T, const vector<int>& LMax_P, const vector<int>& LMin_P, const vector<int>& pi_P) {
    unsigned int m = P.size(), n = T.size();
    for (int t = 0; t <= k - 1; t++) {
        int i = t, j = 1;
        while (i < n - (m - 1) * k) {
            if (E_T[i + j * k] != E_T[i + (j - 1) * k] &&
                E_T[i + j * k] != i + (j - 1) * k) {
                i = i + j * k, j = 1;
                continue;
            }
            int value1 = LMax_P[j] == INT32_MIN ? INT32_MIN : T[i + LMax_P[j] * k];
            int value2 = LMin_P[j] == INT32_MAX ? INT32_MAX : T[i + LMin_P[j] * k];
            while (!(value1 < T[i + j * k] && T[i + j * k] < value2 ||
                     T[i + j * k] == value1 && T[i + j * k] == value2)) {
                i = i + (j - pi_P[j - 1]) * k;
                j = pi_P[j - 1];
                value1 = LMax_P[j] == INT32_MIN ? INT32_MIN : T[i + LMax_P[j] * k];
                value2 = LMin_P[j] == INT32_MAX ? INT32_MAX : T[i + LMin_P[j] * k];
            }
            j++;
            if (j == m) {
                cout << "MATCH: T[" << i << ".." << (i + m * k - 1) << "]\n";
                i = i + (j - pi_P[j - 1]) * k;
                j = pi_P[j - 1];
            }
        }
    }
}

#endif //OPPM_SCALE_OPPM_SCALE_H
