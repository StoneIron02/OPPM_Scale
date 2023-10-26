#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include "Lmax_Lmin.h"
#include "OPPM_Original.h"
#include "OPPM_Scale.h"
using namespace std;
using namespace std::filesystem;

void OPPM(const vector<int>& T, const vector<int>& P_origin, ofstream& resultOPPM) {
    vector<int> P, LMax_P, LMin_P, pi_P;
    P.push_back(P_origin[0]);
    for (int i = 1; i < P_origin.size(); i++) {
        P.push_back((P_origin[i - 1] + P_origin[i]) / 2);
        P.push_back(P_origin[i]);
    }

    Compute_LMax_LMin(P, LMax_P, LMin_P);
    Compute_Failure_Function(P, LMax_P, LMin_P, pi_P);

    auto result = OPPM_Original_Matcher(T, P, LMax_P, LMin_P, pi_P);
    cout << "Count: " << result << "\n";
    resultOPPM << result << "\n";
}

void SOPPM(const vector<int>& T, const vector<int>& P, const int k, ofstream& resultSOPPM) {
    vector<int> LMax_P, LMin_P, pi_P, E_T;

    Compute_LMax_LMin(P, LMax_P, LMin_P);
    Compute_Failure_Function(P, LMax_P, LMin_P, pi_P);
    Compute_Extend_Table(T, E_T);

    auto result = OPPM_Scale_Matcher(T, P, k, E_T, LMax_P, LMin_P, pi_P);
    cout << "Count: " << result << "\n";
    resultSOPPM << result << "\n";
}

void PrintPattern(const std::vector<int>& pattern, ofstream& logFile) {
    for (int i : pattern) {
        cout << i << " ";
        logFile << i << " ";
    }
    cout << std::endl;
    logFile << std::endl;
}

void CalculateOPPM(const vector<int>& T) {
    if (!exists("../result/")) {
        if (!create_directory("../result/")) {
            std::cerr << "디렉토리 생성 실패." << std::endl;
            return;
        }
    }

    std::ofstream logFile("../result/log.txt");
    if (!logFile) {
        std::cerr << "로그 파일을 열 수 없습니다." << std::endl;
        return;
    }

    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(logFile.rdbuf());

    cout << "T.size(): " << T.size() << "\n";

    vector<int> P;
    for (int patternLen = 2; patternLen <= 5; patternLen++) {
        P.clear();

        std::ofstream resultPatternByLen("../result/resultPattern-" + to_string(patternLen) + ".txt");
        if (!resultPatternByLen) {
            std::cerr << "결과 파일을 열 수 없습니다." << std::endl;
            return;
        }

        std::ofstream resultOPPMByLen("../result/resultOPPM-" + to_string(patternLen) + ".txt");
        if (!resultOPPMByLen) {
            std::cerr << "결과 파일을 열 수 없습니다." << std::endl;
            return;
        }

        std::ofstream resultSOPPMByLen("../result/resultSOPPM-" + to_string(patternLen) + ".txt");
        if (!resultSOPPMByLen) {
            std::cerr << "결과 파일을 열 수 없습니다." << std::endl;
            return;
        }

        for (int i = 2; i <= 2 * patternLen; i += 2) {
            P.push_back(i);
        }

        do {
            PrintPattern(P, resultPatternByLen);
            int k = 2;
            cout << "OPPM\n";
            OPPM(T, P, resultOPPMByLen);
            cout << "SOPPM\n";
            SOPPM(T, P, k, resultSOPPMByLen);
        } while (std::next_permutation(P.begin(), P.end()));

        resultPatternByLen.close();
        resultOPPMByLen.close();
        resultSOPPMByLen.close();
    }

    std::cout.rdbuf(coutbuf);
    logFile.close();
}

vector<int> ParseETTh1Dataset() {
    vector<int> T;

    struct Record {
        std::string date;
        double HUFL{}, HULL{}, MUFL{}, MULL{}, LUFL{}, LULL{}, OT{};
    };

    string filename = R"(D:\Project\OPPM_Scale\dataset\04_ETTh1Dataset.csv)";

    std::vector<Record> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return T;
    }

    std::string line;

    // 헤더 라인을 읽고 무시
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        Record record;
        std::string token; // 임시 문자열 변수

        // date 필드를 쉼표로 구분
        if (std::getline(lineStream, token, ',')) {
            record.date = token;
        }

        // 나머지 필드를 문자열로 읽고, atof 함수로 double로 변환
        while (std::getline(lineStream, token, ',')) {
            double value = std::atof(token.c_str());
            if (lineStream.peek() == ',') {
                lineStream.ignore();
            }

            if (record.HUFL == 0.0) {
                record.HUFL = value;
            } else if (record.HULL == 0.0) {
                record.HULL = value;
            } else if (record.MUFL == 0.0) {
                record.MUFL = value;
            } else if (record.MULL == 0.0) {
                record.MULL = value;
            } else if (record.LUFL == 0.0) {
                record.LUFL = value;
            } else if (record.LULL == 0.0) {
                record.LULL = value;
            } else {
                record.OT = value;
            }
        }

        data.push_back(record);
    }

    for (const Record& record : data) {
        T.push_back((int)(record.OT * 1000));
    }

    cout << "T.size(): " << T.size() << "\n";
    return T;
}

int main() {
    auto T = ParseETTh1Dataset();
    CalculateOPPM(T);
}
