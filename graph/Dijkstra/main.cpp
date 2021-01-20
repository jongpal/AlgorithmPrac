#include <iostream>

#define MAX_NODE 100

int M[MAX_NODE][MAX_NODE];
int distance[MAX_NODE] = {0,};
int parent[MAX_NODE];
int check[MAX_NODE] = {0,};

FILE *fp;

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
  fscanf(fp, "%d %d", V, E);
  for(int i = 0; i < *V; i++) {
    for(int j = 0; j < *V; j++) {
      M[i][j] = 1000;
    }
    M[i][i] = 0;
  }
  for(int i = 0; i < *E; i++) {
    fscanf(fp,"%s %d", vertex, &w);
    int from = name2int(vertex[0]);
    int to = name2int(vertex[1]);
    m[from][to] = w;
    m[to][from] = w;  // undirected
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
void dijkstra(int m[][MAX_NODE], int s, int V){
  int x = 0, y, d;
  int i, checked = 0;


  for (x=0; x < V; x++){
    distance[x] = m[s][x];
    if(x != s) parent[x] = s;
  }
  check[s] = 1;
  checked++;

  while(checked < V){
    x = 0;
    while(check[x]) x++;

    for (i = x; i < V; i++)
      if(check[i] == 0 && distance[i] < distance[x]) x = i;
    check[x] = 1;
    checked++;

    for( y = 0; y < V; y++){
      if(x == y || m[x][y] >= 1000 || check[y]) continue;
      d = distance[x] + m[x][y];
      if ( d < distance[y]){
        distance[y] = d;
        parent[y] = x;
      }
    }
    
  }
  print_distance(distance, s, V);
}

int main() {
  int V, E;
  fp = fopen("graph.txt",  "rt");
  if(fp == NULL) {
    std::cout << "fail: file open \n";
  }
  make_adjmatrix(M, &V, &E);
  print_adjmatrix(M, V);
  dijkstra(M, 0, V);
  fclose(fp);
}
