// hash table using open addressing
// especially using double hash to avoid clustering problem
#include <iostream>

using namespace std;
// choose m(the heap table size) to a odd number
// and choosing h2(k) according to that is traditional
#define TABLE_SIZE 17 

class DoubleHash {
  int *hashTable;
  int curr_size;
public:
  DoubleHash() {
    hashTable = new int[TABLE_SIZE];
    curr_size = 0;
    //empty state : -1
    for(int i = 0; i < TABLE_SIZE; i++) {
      hashTable[i] = -1;
    };
  };
//h1 and h2 are two hash functions 
// (h1 + i*h2) % TABLE_SIZE
  int h1(int k) {
    return k % TABLE_SIZE;
  };
  int h2(int k) {
    return 1 + (k % (TABLE_SIZE -1));
  };
  int preHash (int i, int k) {
    return (h1(k)+ i*h2(k)) % TABLE_SIZE;
  };
  bool isFull() {
    return curr_size == TABLE_SIZE;
  };
  int insert(int key) {
    if(isFull()) {
      cout << "the table is full \n";
      return 0; 
    };
    int a = preHash(0, key);
    int cur = 1;
    if(hashTable[a] == -1) {
      hashTable[a] = key;
      cout << "\n insert "<< key << " success\n";
    } else {
      while (1) {
        a = preHash(cur, key);
        if(hashTable[a] == -1) {
          hashTable[a] = key;
          cout << "\n insert " << key <<" success" << cur+1 << " trial";
          break;
        };
        cur ++;
      };
    };
    curr_size++;
    return key;
  };
  int search (int key) {
    int trial = 0;
    int phash;
    while (1) {
      phash = preHash(trial, key);
      if(hashTable[phash] == -1) {
        cout << "fail";
        return 0;
      } else if (hashTable[phash] == key) {
        int value = hashTable[phash];
        cout << "\nsuccess, found " << key << "in array index: " << phash <<" trial: "<< trial<< '\n';
        return key;
      };
      trial ++;
    };
  };
  int deletion (int key){
    int trial = 0;
    int phash;
    while (1) {
      phash = preHash(trial,key);
      if(hashTable[phash] == key) {
        int k = hashTable[phash];
        hashTable[phash] = -2; 
        cout << "delete success\n";
        return k;
      } else if(hashTable[phash] == -1) {
        cout <<"delete fail";
        return 0;
      }
      trial++;
    }    
  }
  void displayTable() 
    { 
        for (int i = 0; i < TABLE_SIZE; i++) { 
            if (hashTable[i] != -1) 
                cout << i << " --> "
                     << hashTable[i] << endl; 
            else
                cout << i << endl; 
        } 
    } 
};
int main() {
  int a[] = { 19, 27, 36, 10, 64, 86, 182};
  int n = sizeof(a) / sizeof(a[0]);

  DoubleHash h;
  for(int i = 0; i< n; i++) {
    h.insert(a[i]);
  }
  //  h.displayHash();
  h.search(19);
  h.search(86);
  h.deletion(19);
  h.deletion(27);
  h.deletion(36);
  h.deletion(10);
  h.deletion(64);
  h.deletion(86);
  h.deletion(182);
  h.displayHash();
  for(int i = 0; i< n; i++) {
    h.insert(a[i]);
  }
  
  h.displayTable();
  return 0;
}