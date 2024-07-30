#include <iostream>
#include <vector>
#include <string>
using namespace std;
void powerset(const vector<string>& set,vector<string>& crt, int index) {
    if (index == set.size()) {
        cout << "{ ";
        for (const auto& elem : crt) {
            cout << elem << " ";
        }
        cout << "}" << endl;
        return;
    }
    powerset(set, crt, index + 1);
    crt.push_back(set[index]);
    powerset(set, crt, index + 1);
    crt.pop_back();
}

int main() {
    vector<string> set;
    string input;
    cout << "輸入0為終止" << endl;
    while (true) {
        cin >> input;
        if (input == "0") {
            break;
        }
        set.push_back(input);
    }

    vector<string> crt;
    powerset(set, crt, 0);

    return 0;
}