#include "Lmax_Lmin.h"
#include "OPPM_Original.h"

#include <iomanip>

int main() {
    vector<int> T, P, LMax_P, LMin_P, pi_P;
    P = {33, 42, 73, 57, 63, 87, 95, 79};
    T = {11, 15, 33, 21, 24, 50, 29, 36, 73, 85, 63, 69, 78, 88, 44, 62};

    Compute_LMax_LMin(P, LMax_P, LMin_P);
    Compute_Failure_Function(P, LMax_P, LMin_P, pi_P);

    cout << setw(10) << "i";
    for (int i = 0; i < P.size(); i++) {
        cout << setw(12) << i << " ";
    }
    cout << "\n";
    cout << setw(10) << "P[i]";
    for (int i = 0; i < P.size(); i++) {
        cout << setw(12) << P[i] << " ";
    }
    cout << "\n";
    cout << setw(10) << "LMax_P[i]";
    for (int i = 0; i < P.size(); i++) {
        cout << setw(12) << LMax_P[i] << " ";
    }
    cout << "\n";
    cout << setw(10) << "LMin_P[i]";
    for (int i = 0; i < P.size(); i++) {
        cout << setw(12) << LMin_P[i] << " ";
    }
    cout << "\n";
    cout << setw(10) << "pi_P[i]";
    for (int i = 0; i < P.size(); i++) {
        cout << setw(12) << pi_P[i] << " ";
    }
    cout << "\n";

    OPPM_Original_Matcher(T, P, LMax_P, LMin_P, pi_P);
}
