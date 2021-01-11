#include <iostream>
#include <vector>
using namespace std;
#define MAX_SIZE 30

vector <int> stack;

void initStack(){
  stack.clear();
}
char itoc(int i) {
  return i + 97;
}
int ctoi(char c) {
  return c - 97;
}
int pop() {
  int p = stack.back();
  stack.pop_back();
  return p;
}
typedef struct node {
  int val;
  struct node *next;
}NODE;

typedef struct head {
  int count;
  struct node *next;
}head;


int parent[MAX_SIZE];
int in_degree[MAX_SIZE];
NODE * G[MAX_SIZE];
head h[MAX_SIZE];
int visit[MAX_SIZE] = {0,};

void print(int i, int level){
  cout << '\n' << "level "<< level << ":" << itoc(i) << " visited ";
}
void make_graph(node *a[], int V, const char* e[], int size) {
  for (int i = 0; i < V; i++) {
    a[i] = NULL;
    parent[i] = -1;
    in_degree[i] = 1;
  }
  for (int i = 0; i < size; i++) {
    node *t = new node;
    int v = ctoi(e[i][1]);
    int v1 = ctoi(e[i][0]);

    t-> val = v;
    t-> next = a[v1];
    a[v1] = t;
    parent[v] = v1;
    //for undirected
    // node *t1 = new node;
    // t1-> val = v1;
    // t1->next = a[v];
    // a[v] = t1;
  }
}

//DFS using stack concept
void DFS(head net[], int V, char start) {
  int s = ctoi(start);
  visit[s] = 1;
  stack.push_back(s);
  while (stack.size()){
    s = pop();
    cout <<'\n' << "popping: "<< itoc(s) << ' ';
    while(net[s].next != nullptr){
      if(!visit[net[s].next->val]) {
        stack.push_back(net[s].next->val);
        visit[net[s].next->val] = 1;
      }
      net[s].next = net[s].next->next;
    }
    
  }
};

//recursive DFS
void rec_DFS(head net[], int V, char start) {
  int i = ctoi(start);
  visit[i] = 1;
  cout <<'\n' << "visiting: "<< itoc(i) << ' ';
  while(net[i].next)
  {
    if(!visit[net[i].next->val]){
      in_degree[net[i].next->val] += in_degree[i];
      rec_DFS(net, V, itoc(net[i].next->val));
    }
      
    net[i].next = net[i].next->next;
  }
}


void top_sort(head net[],int V) {
  vector <int> start;
  int cur = 1;
  while(1){
    start = {};
    for(int i = 0; i < V; i++) {
      if(in_degree[i] == cur) start.push_back(i);
    }
    if (start.size() == 0) break;
    for(int i = 0; i < start.size(); i++) {
      print(start[i], cur-1);
    }
    cur++;
  }
}

void print_graph(head net[], int V) {
  for (int i = 0; i < V; i++) {
    cout << '\n' <<itoc(i) << " --> ";
    while(net[i].next != NULL) {
      cout << itoc(net[i].next-> val) << " --> ";
      net[i].next = net[i].next->next;
    }
  }
}
int main() {
  int V = 7;
  const char* E[8] = {
    "ab",
    "ac",
    "bd", "cd","cf","de", "ef", "gc"
  };
  make_graph(G, V, E, 8);

  for (int i = 0; i < V; i++) {
    h[i].next = G[i];
  };

  // print_graph(h, V);

  // DFS(h, V, 'a');
  rec_DFS(h, V, 'a');
  top_sort(h,V);
  // for(int i = 0; i < V; i++){
  //   cout << '\n' << itoc(i) << ":" << in_degree[i] << ' ';
  // }


}