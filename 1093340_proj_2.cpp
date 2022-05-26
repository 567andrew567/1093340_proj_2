#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct predictor {
    bool history[3] = {0};
    int predictor[8] = {0};
    int misprediction = 0;
};

// #define cout debug
// ofstream debug("ALCO/out.txt", ios::out);

bool is_label(string s);
int do_inst(pair<int, string> code, int pos);
int next_state(int state, bool next);
int R[32] = {0};
map<string, int> labels;
map<string, int> Reg_map;
vector<predictor> predictors;
int entrys = 0;
string prediction[4] = {"SN", "WN", "WT", "ST"};
int insts_num = 0;
int main(int argc, char *argv[]) {

    if (argc != 3) {
        cout << "argv error\n";
        exit(0);
    }

    string path = argv[1];
    entrys = atoi(argv[2]);

    ifstream in(path);
    if (!in) {
        cout << "open file error\n";
        exit(0);
    }

    if (entrys <= 0 || int(pow(2, log2(entrys))) != entrys) {
        cout << "entry error\n";
        exit(0);
    }
    // entrys = 2;
    cout << "entrys : " << entrys << "\n";
    cout << "---------------------------------------------------------\n";
    cout << "read file:\n";
    predictors.assign(entrys, predictor());
    for (int i = 0; i < 32; i++) {
        Reg_map["R" + to_string(i)] = i;
    }

    string s;
    vector<pair<int, string>> code;
    while (getline(in, s)) {
        cout << s << "\n";
        if (is_label(s)) {

            int count = 0;
            for (int j = 0; j < s.size(); j++) {
                if (isalpha(s[j])) {
                    count = j;
                    break;
                }
            }
            s.erase(0, count);
            s.pop_back();
            code.push_back({-1, s});
            labels[s] = code.size() - 1;
        } else {
            code.push_back({insts_num++, s});
        }
    }
    cout << "---------------------------------------------------------\n";
    cout << "instruction:\n";
    for (auto &i : code) {
        if (i.second[0] == '0' && i.second[1] == 'x') {
            int count = 0;
            for (int j = 0; j < i.second.size(); j++) {
                if (!isalnum(i.second[j])) {
                    count = j;
                    break;
                }
            }
            for (int j = count; j < i.second.size(); j++) {
                if (isalpha(i.second[j])) {
                    count = j;
                    break;
                }
            }
            i.second.erase(0, count);
            i.second.erase(i.second.find(';'), i.second.size());
        }
    }
    for (auto i : code) {
        cout << i.second << "\n";
    }
    cout << "---------------------------------------------------------\n";
    cout << "label:\n";
    for (auto i : labels) {
        cout << i.first << " " << i.second << "\n";
    }
    cout << "---------------------------------------------------------\n";
    cout << "run code:\n";
    for (int i = 0; i < code.size(); i++) {
        i = do_inst(code[i], i);
    }
    cout << "done\n";
    cout << "predictors:\n";
    for (int i = 0; i < entrys; i++) {
        cout << "entry: " << i << " ";
        cout << "(";
        for (int j = 2; j >= 0; j--) {
            cout << predictors[i].history[j];
        }
        for (int j = 0; j < 8; j++) {
            cout << ", " << prediction[predictors[i].predictor[j]];
        }
        cout << ") ";
        cout << "misprediction: " << predictors[i].misprediction << "\n";
    }
    cout << "registers:\n";
    for (int i = 0; i < 32; i++) {
        cout << "R" << i << " : " << R[i] << "\n";
    }

    return 0;
}

bool is_label(string s) {

    if (s[0] == '0' && s[1] == 'x') {
        return false;
    }
    return true;
}

int do_inst(pair<int, string> code, int pos) {
    int entry_num = code.first % entrys;
    string inst = code.second;
    bool predict = false, gt = false;
    string name, rd, rs1, rs2, imm, label;
    int count = 0;
    int num = 0;
    for (int i = 0; i < inst.size(); i++) {
        if (isalpha(inst[i])) {
            name += inst[i];
        } else {
            count = i + 1;
            break;
        }
    }

    cout << name;

    if (labels.find(name) != labels.end()) {
        cout << "\n";
        return pos;
    } else
        cout << " ";

    num = predictors[entry_num].history[0] + predictors[entry_num].history[1] * 2 + predictors[entry_num].history[2] * 4;
    predict = predictors[entry_num].predictor[num] >= 2;
    // cout << "num " << num << "\n";
    if (name == "li") {
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rd += inst[i];
        }
        cout << rd << " ";
        for (int i = count; i < inst.size(); i++) {
            if (!isdigit(inst[i])) {
                count = i + 1;
                break;
            }
            imm += inst[i];
        }
        cout << imm << "\n";
        R[Reg_map[rd]] = stoi(imm);
    } else if (name == "add") {
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rd += inst[i];
        }
        cout << rd << " ";
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rs1 += inst[i];
        }
        cout << rs1 << " ";
        for (int i = count; i < inst.size(); i++) {
            if (!isalnum(inst[i])) {
                count = i + 1;
                break;
            }
            rs2 += inst[i];
        }
        cout << rs2 << "\n";
        R[Reg_map[rd]] = R[Reg_map[rs1]] + R[Reg_map[rs2]];
    } else if (name == "addi") {
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rd += inst[i];
        }
        cout << rd << " ";
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rs1 += inst[i];
        }
        cout << rs1 << " ";
        for (int i = count; i < inst.size(); i++) {
            if (!isdigit(inst[i])) {
                count = i + 1;
                break;
            }
            imm += inst[i];
        }
        cout << imm << "\n";
        R[Reg_map[rd]] = R[Reg_map[rs1]] + stoi(imm);
    } else if (name == "andi") {
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rd += inst[i];
        }
        cout << rd << " ";
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rs1 += inst[i];
        }
        cout << rs1 << " ";
        for (int i = count; i < inst.size(); i++) {
            if (!isdigit(inst[i])) {
                count = i + 1;
                break;
            }
            imm += inst[i];
        }
        cout << imm << "\n";
        R[Reg_map[rd]] = R[Reg_map[rs1]] & stoi(imm);
    } else if (name == "beq") {
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rs1 += inst[i];
        }
        cout << rs1 << " ";
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rs2 += inst[i];
        }
        cout << rs2 << " ";
        for (int i = count; i < inst.size(); i++) {
            if (!isalnum(inst[i])) {
                count = i + 1;
                break;
            }
            label += inst[i];
        }
        cout << label << "\n";
        if (R[Reg_map[rs1]] == R[Reg_map[rs2]]) {
            pos = labels[label];
            gt = true;
        }
    } else if (name == "bne") {
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rs1 += inst[i];
        }
        cout << rs1 << " ";
        for (int i = count; i < inst.size(); i++) {
            if (inst[i] == ',') {
                count = i + 1;
                break;
            }
            rs2 += inst[i];
        }
        cout << rs2 << " ";
        for (int i = count; i < inst.size(); i++) {
            if (!isalnum(inst[i])) {
                count = i + 1;
                break;
            }
            label += inst[i];
        }
        cout << label << "\n";
        if (R[Reg_map[rs1]] != R[Reg_map[rs2]]) {
            pos = labels[label];
            gt = true;
        }
    } else {
        cout << "\n\nerror!!!\ninstruction not found\n\n";
        exit(0);
    }

    cout << "use entry: " << entry_num << "\n";
    for (int i = 0; i < entrys; i++) {
        cout << "entry: " << i << " ";
        cout << "(";
        for (int j = 2; j >= 0; j--) {
            cout << predictors[i].history[j];
        }
        for (int j = 0; j < 8; j++) {
            cout << ", " << prediction[predictors[i].predictor[j]];
        }
        cout << ")\n";
    }
    cout << (predict ? "T" : "N") << " ";
    cout << (gt ? "T" : "N") << " ";
    if (predict == gt) {
        cout << "correct ";
    } else {
        cout << "wrong ";
        predictors[entry_num].misprediction++;
    }
    cout << "misprediction: " << predictors[entry_num].misprediction << "\n";
    predictors[entry_num].predictor[num] = next_state(predictors[entry_num].predictor[num], gt);
    predictors[entry_num].history[2] = predictors[entry_num].history[1];
    predictors[entry_num].history[1] = predictors[entry_num].history[0];
    predictors[entry_num].history[0] = gt;
    cout << "---------------------------------------------------------\n";
    return pos;
}
int next_state(int state, bool next) {
    state += (next ? 1 : -1);
    if (state >= 4)
        state = 3;
    else if (state < 0)
        state = 0;
    return state;
}