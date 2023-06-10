#include <bits/stdc++.h>
#define ll long long
using namespace std;

//hola

int main() {
	freopen("acslembly.in", "r", stdin);
	freopen("acslembly.out", "w", stdout);
    map<string,int> st;
    map<string,int> br;
    int ACC = 0;
    vector<string> code[3];
    int index = 0;
    while(true){
        string LABEL,OPCODE,LOC;
        cin >> LABEL >> OPCODE >> LOC;
        code[0].push_back(LABEL);
        code[1].push_back(OPCODE);
        code[2].push_back(LOC);
        if (code[0][index][0]!='-'){
            br[code[0][index]] = index;
        }
        if (!code[1][index].compare("END")){
            break;
        }
        index++;
    }
    
    int pointer = 0;
    while(true){
        string LABEL,OPCODE,LOC;
        LABEL = code[0][pointer];
        OPCODE = code[1][pointer];
        LOC = code[2][pointer];
        if (!OPCODE.compare("LOAD")){
            if (LOC[0] == '='){
                ACC = stoi(LOC.substr(1));
            }
            else {
                ACC = st[LOC];
            }
        }
        else if (!OPCODE.compare("STORE")){
            st[LOC] = ACC;
        }
        else if (!OPCODE.compare("ADD")){
            if (LOC[0] == '='){
                ACC += stoi(LOC.substr(1));
            }
            else {
                ACC += st[LOC];
            }
        }
        else if (!OPCODE.compare("SUB")){
            if (LOC[0] == '='){
                ACC -= stoi(LOC.substr(1));
            }
            else {
                ACC -= st[LOC];
            }
        }
        else if (!OPCODE.compare("MULT")){
            if (LOC[0] == '='){
                ACC *= stoi(LOC.substr(1));
            }
            else {
                ACC *= st[LOC];
            }
        }
        else if (!OPCODE.compare("DIV")){
            if (LOC[0] == '='){
                ACC /= stoi(LOC.substr(1));
            }
            else {
                ACC /= st[LOC];
            }
        }
        else if (!OPCODE.compare("BG")){
            if (ACC>0){
                pointer = br[LOC];
            }
            else {
                pointer++;
            }
        }
        else if (!OPCODE.compare("BE")){
            if (ACC==0){
                pointer = br[LOC];
            }
            else {
                pointer++;
            }
        }
        else if (!OPCODE.compare("BL")){
            if (ACC<0){
                pointer = br[LOC];
            }
            else {
                pointer++;
            }
        }
        else if (!OPCODE.compare("BU")){
            pointer = br[LOC];
        }
        else if (!OPCODE.compare("READ")){
            cin >> st[LOC];
        }
        else if (!OPCODE.compare("PRINT")){
            cout << st[LOC];
        }
        else if (!OPCODE.compare("DC")){
            st[LABEL] = stoi(LOC);
        }
        else if (!OPCODE.compare("END")){
            break;
        }
        else{
            cout << "ERROR";
            break;
        }
        if (OPCODE[0]!='B'){
            pointer++;
        }
    }
	
    return 0;
}
