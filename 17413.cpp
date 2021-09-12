#include <iostream>
#include <string>
#include <vector>

using namespace std;

//class node{
//private:
//    char alpa;
//    node* next;
//
//public:
//    void getAlpa(char x){
//        alpa = x;
//    }
//};

int main() {
    string s;
    getline(cin, s);

    vector<char> alpa;

    for(int i = 0 ; i < s.size() ; i++){
        if(s[i] == '<'){
            cout << s[i];
            i++;

            while(s[i] != '>'){
                cout << s[i];
                i++;
            }
            cout << s[i];
            continue;
        }else if(s[i] == ' '){
            while(!alpa.empty()){
                cout << alpa.back();
                alpa.pop_back();
            }
            cout << " ";
        }else if(i==s.size()-1){
            alpa.push_back(s[i]);
            while(!alpa.empty()){
                cout << alpa.back();
                alpa.pop_back();
            }
            cout << " ";
        }
        else{
            alpa.push_back(s[i]);
            if(s[i+1] == '<'){
                while(!alpa.empty()){
                    cout << alpa.back();
                    alpa.pop_back();
                }
            }
        }
    }
    return 0;
}
