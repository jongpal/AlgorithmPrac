#include <iostream>
#include <vector>

using namespace std;

void upheap(int from, vector <int> &h2) {
  h2.insert(h2.end(), from);
  if (h2.size() > 2) {
    int ind = h2.size()-1;
    //loop until the last element who has leaf(child)
    while ((ind/2 >=1) && (h2[ind/2] < h2[ind])) {
      int temp = h2[ind];
      h2[ind] = h2[ind/2];
      h2[ind/2] = temp;
      ind = ind / 2;
    }
  }
}

//making a heap from unordered array
void build_max_heap(vector<int> from, vector<int> &h){
  for(int i = 0; i < from.size(); i++) {
    upheap(from[i], h);
  }
}
// deleting the top node for sorting process
void downheap(int top, vector <int> &heap) {
  int ind = top;
  while((ind <= (heap.size()-1)/2) && ((heap[ind] < (heap[2*ind])) || (heap[ind] < heap[2*ind+1]))) {
    int bigger = heap[2*ind] >= heap[2*ind+1] ? heap[2*ind] : heap[2*ind+1];
    if(heap[ind] <= bigger) {
      if(bigger == heap[2*ind]) {
        int temp = heap[ind];
        heap[ind] = heap[2*ind];
        heap[2*ind] = temp;
        ind *=2;
      } else {
        int temp = heap[ind];
        heap[ind] = heap[2*ind+1];
        heap[2*ind+1] = temp;
        ind = 2*ind +1;
      }
    }
  }
}
//for heap sort
int extract_max(vector <int> &heap) {
    int max = heap[1];
    heap[1] = heap[heap.size()-1];
    heap.pop_back();
    downheap(1, heap);
    return max;
}

int main() {
  vector <int> heap;
  vector <int> A = {1,9,5,7,21,11,50,3,18,5,8,4,40,41,42,43,44,45,46,47,48};
  heap.insert(heap.begin(), 0);
  build_max_heap(A, heap);
  //heap sort
  while(heap.size() > 1) {
    cout << extract_max(heap) <<'\n';
  }
}