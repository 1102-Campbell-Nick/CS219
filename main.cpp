#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> //allows uppercase + hex conversion
#include <bitset> //allows binary operations and shifting easily
#include <cctype> //helps with trimming spaces off readfile
#include <algorithm> //also helps with spaces
using namespace std;

void initialize(uint32_t regs[8]); //initializes the registers to 0
string trim(string&); //takes off leading and trailing spaces
uint32_t convertU(string); //converts the read string into a uint32_t
int32_t convertS(string); //converts the read string into a int32_t (for ASR)
int convertI(string); //converts the read string into an int (for shifting)
int findReg(string); //finds the register number
void display(uint32_t*); //displays the registers

int main(){
    uint32_t registers[8];
    bool n = 0, z = 0, c = 0, v = 0;
    int shift;
    
    ifstream readFile("Programming-Project-3.txt");
    if(!readFile.is_open()){
        cout << "File could not be opened." << endl;
        return 1;
    }

    initialize(registers);
    string op, tr1, tr2, tr3, trash;
    while(readFile >> op){
        if((op == "ADD" || op == "ADDS") || (op == "add" || op == "adds")){
            getline(readFile, tr1, ',');
            getline(readFile, tr2, ',');
            getline(readFile, tr3);
            cout << op << " " << tr1 << " " << tr2 << " " << tr3 << endl;
            registers[findReg(trim(tr1))] = registers[findReg(trim(tr2))] + registers[findReg(trim(tr3))];
            if(op == "ADDS" || op == "adds"){
                c = (registers[findReg(trim(tr1))] < registers[findReg(trim(tr2))]);
                v = (((registers[findReg(trim(tr2))] & 0x80000000) == (registers[findReg(trim(tr3))] & 0x80000000)) && ((registers[findReg(trim(tr2))] & 0x80000000) != (registers[findReg(trim(tr1))] & 0x80000000)));
            }
        }
        else if((op == "AND" || op == "ANDS") || (op == "and" || op == "ands")){
            getline(readFile, tr1, ',');
            getline(readFile, tr2, ',');
            getline(readFile, tr3);
            cout << op << " " << tr1 << " " << tr2 << " " << tr3 << endl;
            registers[findReg(trim(tr1))] = registers[findReg(trim(tr2))] & registers[findReg(trim(tr3))];
        }
        else if((op == "LSR" || op == "LSRS") || (op == "lsr" || op == "lsrs")){
            getline(readFile, tr1, ',');
            getline(readFile, tr2, ',');
            getline(readFile, trash, '#');
            getline(readFile, tr3);
            cout << op << " " << tr1 << " " << tr2 << " " << tr3 << endl;
            registers[findReg(trim(tr1))] = registers[findReg(trim(tr2))] >> convertI(tr3);
            if(op == "LSRS" || op == "lsrs"){
                c = ((registers[findReg(trim(tr2))] & (((1 << convertI(tr3)) - 1))) != 0x0);
            }
        }
        else if((op == "LSL" || op == "LSLS") || (op == "lsl" || op == "lsls")){
            getline(readFile, tr1, ',');
            getline(readFile, tr2, ',');
            getline(readFile, trash, '#');
            getline(readFile, tr3);
            cout << op << " " << tr1 << " " << tr2 << " " << tr3 << endl;
            registers[findReg(trim(tr1))] = registers[findReg(trim(tr2))] << convertI(tr3);
            if(op == "LSLS" || op == "lsls"){
                c = (((registers[findReg(trim(tr2))] >> (32 - convertI(tr3))) & 0x1) != 0x0);
            }
        }
        else if((op == "NOT" || op == "NOTS") || (op == "not" || op == "nots")){
            getline(readFile, tr1, ',');
            cout << op << " " << tr1 << " " << tr2 << endl;
            registers[findReg(trim(tr1))] = ~registers[findReg(trim(tr2))];
        }
        else if((op == "ORR" || op == "ORRS") || (op == "orr" || op == "orrs")){
            getline(readFile, tr1, ',');
            getline(readFile, tr2, ',');
            getline(readFile, tr3);
            cout << op << " " << tr1 << " " << tr2 << " " << tr3 << endl;
            registers[findReg(trim(tr1))] = registers[findReg(trim(tr2))] | registers[findReg(trim(tr3))];
        }
        else if((op == "SUB" || op == "SUBS") || (op == "sub" || op == "subs")){
            getline(readFile, tr1, ',');
            getline(readFile, tr2, ',');
            getline(readFile, tr3);
            cout << op << " " << tr1 << " " << tr2 << " " << tr3 << endl;
            registers[findReg(trim(tr1))] = registers[findReg(trim(tr2))] - registers[findReg(trim(tr3))];
            if(op == "SUBS" || op == "subs"){
                c = (registers[findReg(trim(tr2))] >= registers[findReg(trim(tr3))]);
                v = (((registers[findReg(trim(tr2))] & 0x80000000) == (registers[findReg(trim(tr3))] & 0x80000000)) && ((registers[findReg(trim(tr2))] & 0x80000000) != (registers[findReg(trim(tr1))] & 0x80000000)));
            }
        }
        else if((op == "XOR" || op == "XORS") || (op == "xor" || op == "xors")){
            getline(readFile, tr1, ',');
            getline(readFile, tr2, ',');
            getline(readFile, tr3);
            cout << op << " " << tr1 << " " << tr2 << " " << tr3 << endl;
            registers[findReg(trim(tr1))] = registers[findReg(trim(tr2))] ^ registers[findReg(trim(tr3))];
        }
        else if(op == "MOV" || op == "mov"){
            getline(readFile, tr1, ',');
            getline(readFile, trash, '#');
            getline(readFile, tr2);
            cout << op << " " << tr1 << " #" << tr2 << endl;
            registers[findReg(trim(tr1))] = convertU(tr2);
            n = ((registers[findReg(trim(tr1))] & 0x80000000) == 0x80000000);
            z = (registers[findReg(trim(tr1))] == 0);
        }
        else if(op == "CMP" || op == "cmp"){
            getline(readFile, tr1, ',');
            getline(readFile, tr2, '<');
            getline(readFile, trash);
            cout << op << " " << tr1 << " " << tr2 << endl;
            uint32_t temp = registers[findReg(trim(tr1))] - registers[findReg(trim(tr2))];
            n = ((temp & 0x80000000) == 0x80000000);
            z = (temp == 0);
            c = (registers[findReg(trim(tr1))] >= registers[findReg(trim(tr2))]);
            v = (((registers[findReg(trim(tr1))] & 0x80000000) == (registers[findReg(trim(tr2))] & 0x80000000)) && ((registers[findReg(trim(tr1))] & 0x80000000) != (temp & 0x80000000)));
        }
        else if(op == "TST" || op == "tst"){
            getline(readFile, tr1, ',');
            getline(readFile, tr2, '<');
            getline(readFile, trash);
            cout << op << " " << tr1 << " " << tr2 << endl;
            uint32_t temp = registers[findReg(trim(tr1))] & registers[findReg(trim(tr2))];
            n = ((temp & 0x80000000) == 0x80000000);
            z = (temp == 0);
        }

        display(registers);
        if(op[op.size() - 1] == 'S' || op[op.size() - 1] == 's'){
            n = ((registers[findReg(trim(tr1))] & 0x80000000) == 0x80000000);
            z = (registers[findReg(trim(tr1))] == 0);
        }
        cout << "N: " << n << " | Z: " << z << " | C: " << c << " | V: " << v << endl << endl;
    }
    readFile.close();
}

void initialize(uint32_t regs[8]){
    for(int i = 0; i < 8; i++){
        regs[i] = 0x0;
    }
}

string trim(string& str) {
    // Trim leading spaces
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == string::npos) {
        return ""; // No non-space characters
    }
    // Trim trailing spaces
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    // Return the trimmed string
    return str.substr(first, last - first + 1);
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

int findReg(string reg){
    if(reg == "R0" || reg == "r0"){
        return 0;
    }
    else if(reg == "R1" || reg == "r1"){
        return 1;
    }
    else if(reg == "R2" || reg == "r2"){
        return 2;
    }
    else if(reg == "R3" || reg == "r3"){
        return 3;
    }
    else if(reg == "R4" || reg == "r4"){
        return 4;
    }
    else if(reg == "R5" || reg == "r5"){
        return 5;
    }
    else if(reg == "R6" || reg == "r6"){
        return 6;
    }
    else if(reg == "R7" || reg == "r7"){
        return 7;
    }
}

void display(uint32_t* regs){
    for(int i = 0; i < 7; i++){
        cout << "r" << i << ": 0x" << uppercase << hex << regs[i] << " | ";
    }
    cout << "r7: 0x" << uppercase << hex << regs[7] << endl;
}

//Moving asr down here because it's not needed right now
/*      
        int32_t registers[findReg(trim(tr1))];

        else if((op == "ASR" || op == "ASRS")){
            //not used for PA3
            readFile >> tr2;
            cout << op << " " << tr1 << " " << tr2 << " : ";
            registers[findReg(trim(tr1))] = convertS(tr1) >> convertI(tr2);
            cout << "0x" << uppercase << hex << registers[findReg(trim(tr1))] << endl;
        }

        else if(op == "ASRS"){ //need this because ASRS uses registers[findReg(trim(tr1))], but these should always be the flags for ASRS so i just hardset them
            n = 1;
            z = 0;
        }      
*/