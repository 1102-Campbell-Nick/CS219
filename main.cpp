#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> //allows uppercase + hex conversion
using namespace std;

uint32_t convert(string); //converts the read string into a uint32_t
uint32_t ADD(uint32_t,uint32_t); //adds the uint32_t's if the operator in the file is ADD

int main(){
    uint32_t r1, r2;

    ifstream readFile("Programming-Project-1.txt");
    if(!readFile.is_open()){
        cout << "File could not be opened." << endl;
        return 1;
    }

    string op, tr1, tr2;
    while(readFile >> op >> tr1 >> tr2){
        cout << op << " " << tr1 << " " << tr2 << " : ";
        r1 = convert(tr1);
        r2 = convert(tr2);
        if(op == "ADD"){ //this if can be added on with if else's for other operators
            uint32_t answer = ADD(r1,r2);
            cout << "0x" << uppercase << hex << answer << endl;
            cout << "Overflow: ";
            if(r1 > answer){
                cout << "YES" << endl; 
            }
            else{
                cout << "NO" << endl;
            }
            cout << endl;
        }
    }
    readFile.close();
}

uint32_t convert(string s){
    return static_cast<uint32_t>(stoul(s, nullptr, 16));
}

uint32_t ADD(uint32_t one,uint32_t two){
    return one + two;
}