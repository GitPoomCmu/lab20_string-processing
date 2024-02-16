#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string file, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(file);
    
    string textline;
    
    char format[] = {"%[^:]: %d %d %d"};
    char name[99];
    int grade1, grade2, grade3, total;
    char grade;
    
    while(getline(source, textline)){
        sscanf(textline.c_str(), format, name, &grade1, &grade2, &grade3);
        total = grade1 + grade2 + grade3;
        grade = score2grade(total);
        
        names.push_back(name);
        scores.push_back(total);
        grades.push_back(grade);
    }
}

void getCommand(string &command, string &key){
    string input;
    cout << "Please input your command: ";
    cin >> command;
    input = toUpperStr(command);
    if(input == "GRADE" || input == "NAME"){
        cin.ignore();
        getline(cin, key);
    }
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found;
    cout << "---------------------------------\n";
    for(int unsigned i=0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            found = true;
            printf("%s's score = %d\n%s's grade = ", names[i].c_str(), scores[i], names[i].c_str());
            cout << grades[i] << "\n";
        }
    }
    if(found == false){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found;
    cout << "---------------------------------\n";
    for(int unsigned i=0; i<grades.size(); i++){
        if(grades[i] == key.c_str()[0]){
            found = true;
            printf("%s (%d)\n", names[i].c_str(), scores[i]);
        }
    }
    if(found == false){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
