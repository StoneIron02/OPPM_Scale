#include "Lmax_Lmin.h"

#include <iomanip>

int main() {
    vector<int> P, LMax_P, LMin_P;
    P.push_back(33);
    P.push_back(42);
    P.push_back(73);
    P.push_back(57);
    P.push_back(63);
    P.push_back(87);
    P.push_back(95);
    P.push_back(79);

    Compute_LMax_LMin(P, LMax_P, LMin_P);

    for (int i = 0; i < P.size(); i++) {
        cout << setw(12) << i << " ";
    }
    cout << "\n";
    for (int i = 0; i < P.size(); i++) {
        cout << setw(12) << P[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < P.size(); i++) {
        cout << setw(12) << LMax_P[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < P.size(); i++) {
        cout << setw(12) << LMin_P[i] << " ";
    }
    cout << "\n";
}