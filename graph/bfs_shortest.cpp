#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;
#define GRAPH_SIZE 30

unordered_map<int, vector<int>> level;
vector <int> parent;

//to check whether this node was visited 
int check [GRAPH_SIZE] = {0,};

typedef struct Node{
  int val;
  struct Node *next;
}node;

node *l_graph[GRAPH_SIZE];

//for the convenience, use integer instead of char
char itoc(int i) {
  return i + 97;
}
int ctoi(char c) {
  return c - 97;
}

//making a indirect graph
void make_graph(node *a[], int V, const char* E[], int size) {
  for (int i = 0; i < V; i++) {
    a[i] = NULL;
    parent.push_back(-1);
  }
  for (int i = 0; i < size; i++) {
    node *t = new node;
    int v = ctoi(E[i][1]);
    int v1 = ctoi(E[i][0]);

    t-> val = v;
    t-> next = a[v1];
    a[v1] = t;

    node *t1 = new node;
    t1-> val = v1;
    t1->next = a[v];
    a[v] = t1;
  }
}

//bfs search
void BFS(node *a[], int start, int V) {
  node *cur;
  level[0].push_back(start);
  check[start] = 1;
  int cl = 1;
  vector <int> frontier = {start};
  while (frontier.size() > 0){  
    vector <int> next = {};
    for(int i = 0; i <frontier.size(); i++) {
      cur = a[frontier[i]];
      start = frontier[i];
      while(cur != NULL){
          if(check[cur->val] == 0){
              check[cur->val] = 1;
              parent[cur->val] = start;
              level[cl].push_back(cur->val);
              cout << '\n' << itoc(cur->val) <<" visited\n";
              next.push_back(cur->val);
          }   
          cur = cur->next;
        }      
      }
    cl++;
    frontier = next; 
  }  
}

void print_graph(node *a[], int V) {
  for (int i = 0; i < V; i++) {
    cout << '\n' <<itoc(i) << " --> ";
    while(a[i] != NULL) {
      cout << itoc(a[i]-> val) << " --> ";
      a[i] = a[i]->next;
    }
  }
}
//print out shortest path to start node(a)
void shortest_path(node *a[], int V) {
  for(int i = 0; i < V; i++){
    cout <<'\n'<< itoc(i) <<" -->";
    int j = i ;
    while (parent[j] != -1) {
      j = parent[j];
      cout << itoc(j) <<" --> ";    
      }
  } 
}

int main() {
  int V = 6;
  const char* E[7] = {
    "ab",
    "ac",
    "bd", "cd","cf","de", "ef"
  };
  make_graph(l_graph, V, E, 7);
  // print_graph(l_graph, V);

  BFS(l_graph, 0, V);
  //print out parent node 
  for (int i = 0; i < parent.size();i++) {
    cout <<'\n' <<' '<< itoc(parent[i]); 
  }
  //print out level : the highest number is the worst case
  for (auto i = level.begin(); i!= level.end(); i++) {
    cout <<'\n'  << i->first;
    for(int j = 0; j < i->second.size(); j++) {
      cout <<"  "<< itoc(i->second[j]) <<',';
    }
  }

  shortest_path(l_graph, V);
}
