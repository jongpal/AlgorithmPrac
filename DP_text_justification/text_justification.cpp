#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <tuple>

#define LINE_WIDTH 30
#define INF 1e8

using namespace std;

ifstream fin;
int *cost;
int *child;
bool isChanged = false;

// cost 함수 계산
int badness(int i, int j, int blank) {
  if(j - i > LINE_WIDTH - blank) return INF;
  else return pow((LINE_WIDTH - (j-i + blank)), 3);
}

//cost minimum 저장
int get_min(int val, int off, int pos) {
  if(cost[off] == -1){
    cost[off] = val;
    isChanged = true;
  }
  else {
    if(cost[off] > val){
      cost[off] = val;
      isChanged = true;
    } else {
      isChanged = false;
    }
  } 

  return pos; // pos : first position of next line
              // i : first position of this line
}

int DP(int i, vector<string> &words, unordered_map<int, int> & word_count, int sender){

  if(i >= words.size()-1) // final word
  {
    int length = 0;
    
    cost[i]= badness(word_count[sender], word_count[i], i-sender+1);
  } 
  else if(cost[i] != -1)
    return cost[i]; // dp : memoization
  else 
    for(int j = i+1; j < words.size(); j++) {
      //dp : recursion
      int dp = DP(j , words, word_count, i);
      int pos = get_min(badness(word_count[i], word_count[j], j-i-1) + dp,i,j);
      // if minimum was updated
      if(isChanged) {
        //word[i] ~ word[pos-1] 이 한 문장 구성
        child[i] = pos;
      }
    }
  return cost[i];
}

// text 의 word만 분리해주고 dp로 넘기는 함수
void text_justification(int from , vector<string> &words){

  unordered_map<int, int> word_count;
  word_count[0] = 0;
  string word;
  int count = 0;
  int word_num = 0;
  
  while(!fin.eof()){
    fin >> word;
    count += word.length();
    word_num += 1;
    word_count[word_num] = count; // 1번째 단어 전에 글자 count개
    words.push_back(word);
  }

  cost = new int[word_num];
  child = new int[word_num];

  //initialization
  for(int i = 0 ; i < word_num; i++){
    cost[i] = -1;
    child[i] = 0;
  }

  DP(0 , words, word_count,0);

  delete[] cost;
  delete[] child;
}


  
int main() {
  vector<string> words;
  vector<int> child_list;
  fin.open("text.txt");
  if(fin.is_open()){
    text_justification(0, words);  // from 0th syllable
  }
  fin.close();
  // 시작 문자들을 따로 벡터에 집어넣기
  int i = 0;
  while(child[i] != 0) {
    // cout << endl << child[i] << ":" << words[child[i]] << endl;
    if(child[child[i]] != 0)
      child_list.push_back(child[i]);
    i = child[i];
  }

  // 결과 문장 출력
  int cur = 0;
  for(int i = 0; i < words.size(); i++){
    if(child_list[cur] == i) {
      cout << '\n';
      cur++;
    }
    cout << words[i] << ' ';
  }
}