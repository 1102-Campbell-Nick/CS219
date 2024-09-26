#include <iostream>
#include <fstream>
#include <string>
using namespace std;



int main(){
    uint32_t r1, r2;

    ifstream readFile("Programming-Project-1.txt");
    if(!readFile.is_open()){
        cout << "File could not be opened." << endl;
        return 1;
    }

    string op, tr1, tr2;
    readFile >> op >> tr1 >> tr2;
    r1 = static_cast<uint32_t>(stoul(tr1, nullptr, 16));
        cout << r1 << endl;
    r2 = static_cast<uint32_t>(stoul(tr2, nullptr, 16));
        cout << r2 << endl;
}