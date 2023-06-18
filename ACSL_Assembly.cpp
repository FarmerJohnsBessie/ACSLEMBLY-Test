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
    int index = 0; // to record the current index of the code
    string line; // Stores the lind read
    while(getline(fin,line)){
	// Basically a split function
        stringstream ss(line); 
        string word;
        vector<string> words; // stores the words splited
        while(getline(ss,word,' ')){
            words.push_back(word);
        }

	// Check different possible length for words
        if(words.size() == 1){ 
	    // Only push the OPCODE in
            code[0].push_back("-");
            code[1].push_back(words[0]);
            code[2].push_back("-");
        }else if(words.size() == 2){
	    // Consider two cases
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
	    // Have all the three inputs
            code[0].push_back(words[0]);
            code[1].push_back(words[1]);
            code[2].push_back(words[2]);
            if(words[1].compare("DC")){
                br[words[0]] = index;
            }
        }
        index++;
    }
    
    int pointer = 0; // points at which line of code to run
    while(true){
        string LABEL,OPCODE,LOC; //LABEL field, OPCODE field, LOC field
        LABEL = code[0][pointer]; //sets LABEL as first
        OPCODE = code[1][pointer]; //sets OPCODE as second
        LOC = code[2][pointer]; //sets LOC as third
        if (!OPCODE.compare("LOAD")){ 
            if (LOC[0] == '='){ // if the LOC contains a value, put the value into ACC
                ACC = stoi(LOC.substr(1));
            } else { // if the LOC contains a variable, put the variable into ACC
                ACC = st[LOC];
            }
        } else if (!OPCODE.compare("STORE")){ // put the variable into ACC
            st[LOC] = ACC;

        } else if (!OPCODE.compare("ADD")){ 
            if (LOC[0] == '='){ // if LOC is a value, add to ACC and store result in ACC
                ACC += stoi(LOC.substr(1));
            } else { // if LOC is a variable, add to ACC and store result in ACC
                ACC += st[LOC];
            }

        } else if (!OPCODE.compare("SUB")){ //ADD but instead of add to ACC its subtract
            if (LOC[0] == '='){
                ACC -= stoi(LOC.substr(1));
            } else {
                ACC -= st[LOC];
            }

        } else if (!OPCODE.compare("MULT")){ //ADD but multiply
            if (LOC[0] == '='){
                ACC *= stoi(LOC.substr(1));
            } else {
                ACC *= st[LOC];
            }

        } else if (!OPCODE.compare("DIV")){ //ADD but divide
            if (LOC[0] == '='){
                ACC /= stoi(LOC.substr(1));
            } else {
                ACC /= st[LOC];
            }

        } else if (!OPCODE.compare("BG")){
            if (ACC>0){ // if ACC is greater than zero, set the pointer to where the BI is in the LABEL field
                pointer = br[LOC];
            } else { // just increment the pointer for the next line
                pointer++;
            }
        } else if (!OPCODE.compare("BE")){ //BG but only if ACC==0
            if (ACC==0){
                pointer = br[LOC];
            } else {
                pointer++;
            }

        } else if (!OPCODE.compare("BL")){ //BG and BE but only if ACC<0
            if (ACC<0){
                pointer = br[LOC];
            } else {
                pointer++;
            }

        } else if (!OPCODE.compare("BU")){ //branches to the BI
            pointer = br[LOC];

        } else if (!OPCODE.compare("READ")){ //reads in an integer from the terminal
            cin >> st[LOC];
        }
        else if (!OPCODE.compare("PRINT")){ //prints the LOC in the output file
            fout << st[LOC];
        }
        else if (!OPCODE.compare("DC")){ //sets the value of a variable
            st[LABEL] = stoi(LOC);

        } else if (!OPCODE.compare("END")){ //ends the code by breaking the while loop
            break;
        }
        else{ //if the OPCODE was not in fact an OPCODE, print error
            cout<<OPCODE<<endl;
            fout << "ERROR";
            break;
        }
        if (OPCODE[0]!='B'){ // if a branch attempt did not happen, set pointer to the next line
            pointer++;
        }
    }
	
    return 0;
}
