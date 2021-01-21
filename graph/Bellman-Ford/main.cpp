#include <iostream>
#include <fstream>

#define MAX_NODE 100

int M[MAX_NODE][MAX_NODE];
int distance[MAX_NODE];
int parent[MAX_NODE];

std::string *edge;

std::ifstream fin("graph_bellman.txt");

int name2int(char c)
{
    return c - 'A';
}
char int2name(int i)
{
    return i + 'A';
}

void make_adjmatrix(int m[MAX_NODE][MAX_NODE], int* V, int* E){
  char vertex[3];
  int w;
  fin >> *V >> *E;
  edge = new std::string[*E];

  for(int i = 0; i < *V; i++) {
    for(int j = 0; j < *V; j++) {
      M[i][j] = 1000;
    }
    M[i][i] = 0;
    distance[i] = 1000;
    parent[i] = -1;
  }
  for(int i = 0; i < *E; i++) {
    fin >> vertex >> w;
    std::string s(vertex);
    edge[i] = s;
    int from = name2int(vertex[0]);
    int to = name2int(vertex[1]);
    m[from][to] = w;
    // m[to][from] = w;  // undirected
  }
};


void print_adjmatrix(int a[MAX_NODE][MAX_NODE], int V){
    int i, j;
    std::cout << "\n       "; 
    for (i = 0; i < V; i++)
    {
      std::cout.width(7);
      std::cout << int2name(i);
    }
    std::cout <<"\n";

    for (i = 0; i < V; i++)
    {
        std::cout.width(7);
        std::cout <<int2name(i);
        for (j = 0; j < V; j++)
        {
          std::cout.width(7);
          std::cout << a[i][j];
        }
        std::cout <<"\n\n";
    }
}

void print_distance(int d[], int s, int V){
    std::cout <<"\n"<<" "<< int2name(s) <<"->";
    for (int i = 0; i < V; i++)
    {
        std::cout.width(7);
        std::cout <<" "<< d[i]; 
    }
}

void bellman_ford(int a[][MAX_NODE], int start, int V, int E){
  distance[start] = 0;
  int checked = 0;
  //O(V*E)
  while(checked < V){
    for(int j = 0; j < E; j++) {
      int from = name2int(edge[j][0]);
      int to = name2int(edge[j][1]);
      if(distance[to] > a[from][to] + distance[from]){
        distance[to] = a[from][to] + distance[from];
        parent[to] = from;
      }
    }
    checked++;
    };
    //reporting negative cycle
    //if it updates once again, then this graph has negative cycle
    for(int j = 0; j < E; j++) {
      int from = name2int(edge[j][0]);
      int to = name2int(edge[j][1]);
      if(distance[to] > a[from][to] + distance[from]){
        std::cout << "report : negative cycle" << std::endl;
        return;
      }
    }

  print_distance(distance, 0, V);
}

int main() {
  int V, E;
  if(!fin){
    std::cout << "Error : file open \n" <<std::endl;
    exit(100);
  }
  make_adjmatrix(M, &V, &E);
  print_adjmatrix(M, V);
  bellman_ford(M,0,V,E);

  fin.close();

  return 0;
}