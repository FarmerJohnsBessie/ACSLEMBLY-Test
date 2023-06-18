#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ifstream fin("acslembly.in"); // code file
    ofstream fout("acslembly.out"); // output file(for PRINT OPCODE)
    map<string,int> st; // storage for variables
    map<string,int> br; // storage for branch indicators
    int ACC = 0; // accumulator
    
    vector<string> code[3]; // stores the code in an array of vectors
    int index = 0; // to record current index of the code
    string line; // 
    while(getline(fin,line)){
        stringstream ss(line);
        string word;
        vector<string> words;
        while(getline(ss,word,' ')){
            words.push_back(word);
        }
        if(words.size() == 1){ 
            code[0].push_back("-");
            code[1].push_back(words[0]);
            code[2].push_back("-");
        }else if(words.size() == 2){
            if(!words[1].compare("END")){
                code[0].push_back(words[0]);
                code[1].push_back(words[1]);
                code[2].push_back("-");
                br[words[0]] = index;
            }else{
                code[0].push_back("-");
                code[1].push_back(words[0]);
                code[2].push_back(words[1]);
            }
        }else{
            code[0].push_back(words[0]);
            code[1].push_back(words[1]);
            code[2].push_back(words[2]);
            if(words[1].compare("DC")){
                br[words[0]] = index;
            }
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
        } else if (!OPCODE.compare("STORE")){
            st[LOC] = ACC;

        } else if (!OPCODE.compare("ADD")){
            if (LOC[0] == '='){
                ACC += stoi(LOC.substr(1));
            } else {
                ACC += st[LOC];
            }

        } else if (!OPCODE.compare("SUB")){
            if (LOC[0] == '='){
                ACC -= stoi(LOC.substr(1));
            } else {
                ACC -= st[LOC];
            }

        } else if (!OPCODE.compare("MULT")){
            if (LOC[0] == '='){
                ACC *= stoi(LOC.substr(1));
            } else {
                ACC *= st[LOC];
            }

        } else if (!OPCODE.compare("DIV")){
            if (LOC[0] == '='){
                ACC /= stoi(LOC.substr(1));
            } else {
                ACC /= st[LOC];
            }

        } else if (!OPCODE.compare("BG")){
            if (ACC>0){
                pointer = br[LOC];
            } else {
                pointer++;
            }
        } else if (!OPCODE.compare("BE")){
            if (ACC==0){
                pointer = br[LOC];
            } else {
                pointer++;
            }

        } else if (!OPCODE.compare("BL")){
            if (ACC<0){
                pointer = br[LOC];
            } else {
                pointer++;
            }

        } else if (!OPCODE.compare("BU")){
            pointer = br[LOC];

        } else if (!OPCODE.compare("READ")){
            cout << "help";
            cin >> st[LOC];
        }
        else if (!OPCODE.compare("PRINT")){
            fout << st[LOC];
        }
        else if (!OPCODE.compare("DC")){
            st[LABEL] = stoi(LOC);

        } else if (!OPCODE.compare("END")){
            break;
        }
        else{
            cout<<OPCODE<<endl;
            fout << "ERROR";
            break;
        }
        if (OPCODE[0]!='B'){
            pointer++;
        }
    }
	
    return 0;
}
