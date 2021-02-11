// knapsack dynamic programming
// duplicate item allowed
// text should be written ascending (size)
#include <iostream>
#include <fstream>
#include <vector>

#define SIZE 10
using namespace std;
ifstream fin;

typedef struct List {
  string stuff;
  int val, size;
}LIST;

int dp[25][SIZE+1]; // [>=# of items][SIZE+1]
                    // memoization

int max(int a, int b) {
  return a > b ? a : b;
}

int dp_knapsack(vector <List> &l, int cur, int cur_size){

  if(cur > l.size() - 1 || cur_size - l[cur].size < 0) return 0; 

  if(dp[cur][cur_size]) {
    return dp[cur][cur_size];
  }

  // cout << cur << ": " <<;
  dp[cur][cur_size] = max(dp_knapsack(l, cur+1, cur_size), dp_knapsack(l, cur+1, cur_size - l[cur].size)+l[cur].val);


  return dp[cur][cur_size];
};

vector<string> get_DPed_items(vector <List> l){
  int size = SIZE;
  vector <string> names;
  for(int i = 0 ; i < l.size(); i++){
    if(dp[i][size] != dp[i+1][size]){
      names.push_back(l[i].stuff);
      size -= l[i].size;
    }
  }
  return names;
}

int main() {
  string stuff;
  int size, val, num;
  vector <LIST> l;
  fin.open("itinerary.txt");
  
  if(fin.is_open()){
    while(!fin.eof()){
      fin >> stuff >> size >> val >> num;
      // num 만큼 더 집어넣기
      // 2개 이상부터는 val --
      int count = -1;
      for(int i = 0 ; i < num; i++){
        count ++;
        LIST li;
        li.stuff = stuff;
        li.val = val - count;
        li.size = size;
        l.push_back(li);
      }
    }
    dp_knapsack(l, 0, SIZE);
    vector <string> names = get_DPed_items(l);
    cout << "things you should be packing right now : { ";
    for(int j = 0; j < names.size(); j++){
      cout << names[j] << ", ";
    }
    cout << "}" << endl << "maximum value : "<< dp[0][10];
  }
  fin.close();
}