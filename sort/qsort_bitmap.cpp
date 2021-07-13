#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#define CUTOFF 10
// #define ARR_SIZE 9
/*
  1. median 3 randomized quick sort
  2. tail recursive quick sort
  3. bitmap sorting(but don't assume that there is a same value)
  4. quickSort + InsertionSort => which will alleviate some overhead comes with handling small arrays

  running time(shortest to longest) : bitmap sorting << quickSort + insertionSort < quickSort
*/

int get_random (int min, int max){
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(min, max);
  return dist(mt);
}

void generate_rand_numbers(std::vector<int>& a, int max_val, int until) {
  for(int i = 0 ; i < until; i++) {
    int rand = get_random (1, max_val);
    a.push_back(rand);
  }
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
void insertionSort(std::vector<int> &a, int s_ind, int e_ind){
  for (int i = s_ind + 1; i <= e_ind; i++) {
    compareAndSwap(a, i, s_ind);
  }
}

void quickSort_(std::vector<int> &a, int s_ind, int e_ind){
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
  else if (e_ind - s_ind + 1 <= CUTOFF) {
    return;
  }
  else 
    q = partition(a, s_ind, e_ind);
 
  // left, right quickSort
  quickSort_(a, s_ind, q-1);
  quickSort_(a, q+1, e_ind);
}

void quickSortWithInsertionSort(std::vector<int> &a, int s_ind, int e_ind) {
  quickSort_(a, s_ind, e_ind);
  insertionSort(a, s_ind, e_ind);
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


// sorting integer value using bitmap

void bitmap_int_sort(std::vector <int> &r, std::vector <int> &bitmap, std::vector <int> &output) {

  for(int i = 0 ; i < r.size() ; i++) {
    bitmap[r[i]] = 1;
  }

  for(int j = 0 ; j < bitmap.size()-1; j++){
    if(bitmap[j] == 1) {
      output.push_back(j);
    }
  }
}

int main() {
  std::vector <int> r;
  generate_rand_numbers(r, 1000000, 100000);

  std::vector <int> b = {1,5,9,4,2,8,7,6,3};

  // quickSort(b, 0, b.size()-1);
  // tail_recursive_qsort(b, 0, b.size()-1);


  // comparing time it takes to implementing quickSort and bitmap operation
  // bitmap is 500 times faster than quickSort
  auto start = std::chrono::high_resolution_clock::now();

  quickSort(r, 0, r.size()-1);

  
  auto stop = std::chrono::high_resolution_clock::now(); 

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  std::cout << "\ntime it tooks to implement qsort : " << duration.count() << '\n';

  auto start2 = std::chrono::high_resolution_clock::now();

  quickSortWithInsertionSort(r, 0, r.size()-1);

  
  auto stop2 = std::chrono::high_resolution_clock::now(); 

  auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

  std::cout << "\ntime it tooks to implement qsort : " << duration2.count() << '\n';

  std::vector <int> bitmap (1000000);
  std::vector <int> output;

  auto start_ = std::chrono::high_resolution_clock::now();
  
  bitmap_int_sort(r, bitmap, output);

  // for(int i = 0 ; i < output.size() ; i++)
  //   std::cout << output[i] << ' ';
  auto stop_ = std::chrono::high_resolution_clock::now();

  auto duration_ = std::chrono::duration_cast<std::chrono::microseconds>(stop_ - start_);

  std::cout << "\ntime it tooks to implement bitmap sort : " << duration_.count() << '\n';
  // for(int i = 0 ; i < 9; i++)
  //   std::cout << '\n'<< b[i];
}
