#include <iostream>
#define N 12
#define R 3


void rotate_array(char A[], int I){
  int left = N % I;
  char T[I];
  int n = 0;
  for(int i = 0; i < I; i++) {
    T[i] = A[i];
    while(i+I*(n+1) < N) {
      A[i+I*n] = A[i+I*(n+1)];
      n++;    
    }
    n = 0;
  }
  for(int i = 0; i < I; i++){
    A[N - I + i] = T[i];
  }
}

void swap(char *a, char *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

void reverse(char B[], int start, int until) {
  for(int i = 0; i <= (until - start)/2; i++) {
    swap(B+start+i, B+(until-i));
  }
}

void rotate_by_reverse(char B[], int I){
  reverse(B, 0, I-1); // start position : 0, until: I-1 
  reverse(B, I, N-1); // I+1 <= x <= N-1
  reverse(B, 0, N-1);
}
int main() {
  
  char A[N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
  std::cout << "--- rotating " << R << " elements " << std::endl;

  std::cout << "--- using first method start ---\n--- before rotating ---" << std::endl;
  for(int i = 0 ; i < sizeof(A)/sizeof(char); i++) {
    std::cout << ' ' << A[i];
  }
  std::cout << std::endl << "--- after rotating ---" << std::endl;

  // moving R elements
  rotate_array(A, R);

  for(int i = 0 ; i < sizeof(A)/sizeof(char); i++) {
    std::cout << ' ' << A[i];
  }
  char B[N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};

  
  std::cout << std::endl << std::endl << "--- using reverse method ---" << std::endl;
  std::cout << std::endl << "--- before rotating ---" << std::endl;
  
  for(int i = 0 ; i < sizeof(B)/sizeof(char); i++) {
    std::cout << ' ' << B[i];
  }

  std::cout << std::endl << "--- after rotating ---" << std::endl;

  rotate_by_reverse(B, R);

  for(int i = 0 ; i < sizeof(B)/sizeof(char); i++) {
    std::cout << ' ' << B[i];
  }

}