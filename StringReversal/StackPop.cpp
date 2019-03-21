#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main(){
  stack <char> stk;
  string newstring = "";
  char str[] = "Invention, my dear friends, is 93% perspiration, 6% electricity, 4% evaporation, and 2% butterscotch ripple";
  for (int i = 0; i < sizeof(str)/sizeof(char); i++){
    stk.push(str[i]);
  };
  for (int i = 0; i < sizeof(str)/sizeof(char); i++){
    newstring += stk.top();
    stk.pop();
  };
  cout << newstring;
  return 0;
};
