#include "Lmax_Lmin.h"
#include "OPPM_Original.h"
#include "OPPM_Scale.h"

#include <iomanip>

int main() {
    vector<int> T, P, LMax_P, LMin_P, pi_P, E_T;
    P = {1, 7, 2, 9};
    T = {2, 4, 10, 8, 5, 9, 15, 12, 7, 10, 9};

    int k = 2;

    Compute_LMax_LMin(P, LMax_P, LMin_P);
    Compute_Failure_Function(P, LMax_P, LMin_P, pi_P);
    Compute_Extend_Table(T, E_T);

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
    cout << setw(10) << "E_T[i]";
    for (int i = 0; i < T.size(); i++) {
        cout << setw(6) << E_T[i] << " ";
    }
    cout << "\n";

    OPPM_Scale_Matcher(T, P, k, E_T, LMax_P, LMin_P, pi_P);
}
