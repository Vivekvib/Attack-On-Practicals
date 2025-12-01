//FA that is a intersection of two languages:- L1: words starting with a & L2: words ending with a

#include <iostream>
using namespace std;

class FA{
    public:
        void state1(string str, int index){
            //initial state
            if(str.length()==index){
                cout<<"String Rejected!"<<endl;
                return;
            }
            else{
                if(str[index] == 'a'){
                    state2(str, index+1);
                }
                else{
                    state4(str, index+1);
                }
            }
            
        }
        void state2(string str, int index){
            //final state
            if(str.length()==index){
                cout<<"String Accepted!"<<endl;
                return;
            }
            else{
                if(str[index] == 'a'){
                    state2(str, index+1);
                }
                else{
                    state3(str, index+1);
                }
            }
        }
        void state3(string str, int index){
            //transition state
            if(str.length() == index){
                cout<<"String Rejected"<<endl;
                return;
            }
            else{
                if(str[index] == 'a'){
                    state2(str, index+1);
                }
                else{
                    state3(str, index+1);
                }
            }
        }
        void state4(string str, int index){
            //transition state
            if(str.length() == index){
                cout<<"String Rejected"<<endl;
                return;
            }
            else{
                if(str[index] == 'a'){
                    state5(str, index+1);
                }
                else{
                    state4(str, index+1);
                }
            }
        }
        void state5(string str, int index){
            //transition state
            if(str.length() == index){
                cout<<"String Rejected"<<endl;
                return;
            }
            else{
                if(str[index] == 'a'){
                    state5(str, index+1);
                }
                else{
                    state4(str, index+1);
                }
            }
        }
};

int main(){
    string str;
    cout<<"Enter your string: "<<endl;
    getline(cin,str);

    FA f;
    f.state1(str,0);
    return 0;
}