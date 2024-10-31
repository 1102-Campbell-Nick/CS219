#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> //allows uppercase + hex conversion
#include <bitset> //allows binary operations and shifting easily
using namespace std;

uint32_t convertU(string); //converts the read string into a uint32_t
int32_t convertS(string); //converts the read string into a int32_t (for ASR)
int convertI(string); //converts the read string into an int (for shifting)

int main(){
    uint32_t answer;
    int32_t anSwer;
    bool n, z;
    int shift;

    ifstream readFile("Programming-Project-2.txt");
    if(!readFile.is_open()){
        cout << "File could not be opened." << endl;
        return 1;
    }

    string op, tr1, tr2;
    while(readFile >> op >> tr1){
        n = z = 0; //Resets the flag values to 0 for every command, will remove for PA3
        if(op == "ADD" || op == "ADDS"){
            readFile >> tr2;
            cout << op << " " << tr1 << " " << tr2 << " : ";
            answer = convertU(tr1) + convertU(tr2);
            cout << "0x" << uppercase << hex << answer << endl;
        }
        else if(op == "AND" || op == "ANDS"){
            readFile >> tr2;
            cout << op << " " << tr1 << " " << tr2 << " : ";
            answer = convertU(tr1) & convertU(tr2);
            cout << "0x" << uppercase << hex << answer << endl;
        }
        else if(op == "ASR" || op == "ASRS"){
            readFile >> tr2;
            cout << op << " " << tr1 << " " << tr2 << " : ";
            anSwer = convertS(tr1) >> convertI(tr2);
            cout << "0x" << uppercase << hex << anSwer << endl;
        }
        else if(op == "LSR" || op == "LSRS"){
            readFile >> tr2;
            cout << op << " " << tr1 << " " << tr2 << " : ";
            answer = convertU(tr1) >> convertI(tr2);
            cout << "0x" << uppercase << hex << answer << endl;
        }
        else if(op == "LSL" || op == "LSLS"){
            readFile >> tr2;
            cout << op << " " << tr1 << " " << tr2 << " : ";
            answer = convertU(tr1) << convertI(tr2);
            cout << "0x" << uppercase << hex << answer << endl;
        }
        else if(op == "NOT" || op == "NOTS"){
            cout << op << " " << tr1 << " : ";
            answer = ~convertU(tr1);
            cout << "0x" << uppercase << hex << answer << endl;
        }
        else if(op == "ORR" || op == "ORRS"){
            readFile >> tr2;
            cout << op << " " << tr1 << " " << tr2 << " : ";
            answer = convertU(tr1) | convertU(tr2);
            cout << "0x" << uppercase << hex << answer << endl;
        }
        else if(op == "SUB" || op == "SUBS"){
            readFile >> tr2;
            cout << op << " " << tr1 << " " << tr2 << " : ";
            answer = convertU(tr1) - convertU(tr2);
            cout << "0x" << uppercase << hex << answer << endl;
        }
        else if(op == "XOR" || op == "XORS"){
            readFile >> tr2;
            cout << op << " " << tr1 << " " << tr2 << " : ";
            answer = convertU(tr1) ^ convertU(tr2);
            cout << "0x" << uppercase << hex << answer << endl;
        }

        if(op != "ASRS" && op[op.size() - 1] == 'S'){
            n = (answer & 0x8000000);
            z = (answer == 0);
        }
        else if(op == "ASRS"){ //need this because ASRS uses anSwer, but these should always be the flags for ASRS so i just hardset them
            n = 1;
            z = 0;
        }
        cout << "N: " << n << " | Z: " << z << endl;
    }
    readFile.close();
}

uint32_t convertU(string s){
    return static_cast<uint32_t>(stoul(s, nullptr, 16));
}

int32_t convertS(string s){
    return static_cast<int32_t>(stoul(s, nullptr, 16));
}

int convertI(string s){
    return stoi(s);
}