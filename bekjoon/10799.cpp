#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main() {
    string s;
    cin >> s;

    int layers = 0;
    bool upp = true;

    int jogag = 0;

    for(int i = 0 ; i < s.size() ; i++) {
        if(s[i] == '('){
            layers++;
            upp = true;
        }else if(s[i] == ')' && upp == true){
            layers--;
            jogag += layers;
            upp = false;
        }else{
            layers--;
            jogag++;
            upp = false;
        }
    }
    cout << jogag;
    return 0;
}
