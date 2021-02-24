#include <iostream>
#include <random>
#include <vector>
// #define ARR_SIZE 9
/*
  1. median 3 randomized quick sort
  2. tail recursive quick sort
*/

int get_random (int min, int max){
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(min, max);
  return dist(mt);
}

int* median3(std::vector<int> &a, int start, int end){
  int *m3[3];
  int *bigger;
  int *smaller;
  int *middle;

  for(int i = 0; i < 3; i++){
    m3[i] = &a[get_random(start, end)];
    if(i == 1) {
      if(m3[1] >= m3[0]){
        bigger = m3[1];
        smaller = m3[0];
      } else {
        bigger = m3[0];
        smaller = m3[1];
      }
    }
    else if(i == 2) {
      if(*m3[2] >= *bigger){
        middle = bigger;
      } else if(*m3[2] >= *smaller){
        middle = m3[2];
      } else {
        middle = smaller;
      }
    }
  }
  return middle;
}

void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(std::vector<int> &a, int s_ind, int e_ind){
  int ind = a[e_ind];
  int i = s_ind - 1;
  int j = s_ind;
  for(; j <= e_ind - 1; j++){
    if(a[j] <= ind) {
      swap(&a[j], &a[++i]);
    } 
  }
  swap(&a[e_ind], &a[++i]);
  return i;
}

void quickSort(std::vector<int> &a, int s_ind, int e_ind){
  int *m_result;
  
  // partition point
  int q;
  // terminate condition
  if(s_ind >= e_ind) return;
  // initialize : median3 + swapping that value with the last one
  if((e_ind-s_ind+1) >= 3){
    m_result = median3(a, s_ind, e_ind);
    swap(m_result, &a[e_ind]);
    q = partition(a, s_ind, e_ind);
  }
  else 
    q = partition(a, s_ind, e_ind);
 
  // left, right quickSort
  quickSort(a, s_ind, q-1);
  quickSort(a, q+1, e_ind);
}

//using less memory space : using only left recursion
void tail_recursive_qsort(std::vector<int> &a, int s_ind, int e_ind){

  while(s_ind < e_ind) {
    int q;
    q = partition(a, s_ind, e_ind);
    if(q == 0) return;
    tail_recursive_qsort(a, s_ind, q-1);
    s_ind = q + 1;
  }
};

int main() {
  std::vector <int> b = {1,5,9,4,2,8,7,6,3};

  quickSort(b, 0, b.size()-1);
  // tail_recursive_qsort(b, 0, b.size()-1);

  for(int i = 0 ; i < 9; i++)
    std::cout << '\n'<< b[i];
}