#include <iostream>
#include <cmath>
#include <random>
#define TABLE_SIZE 15
using namespace std;

//for universal hashing, getting prime value bigger than max(key)
bool is_prime(int p) {
  for(int i = 2; i <= p/2; i++) {
    if(p % i == 0) return 0;
  }
  return true;
}

int get_prime(int min) {
  for(int i = min+1; ;i++) {
    if(is_prime(i))
      return i;
  }
}

typedef struct Node{
  int val;
  int key;
  struct Node *next;
} node;

class HashChain{
  int p;
  int a,b;
  int *h; // saving the universal hashing function
  node *hashTable[TABLE_SIZE];
public:
  HashChain(int prime) {
    p = prime;
    for(int i = 0; i < TABLE_SIZE; i++)
      hashTable[i] = NULL;
    h = new int[p];
    for(int i = 0; i< p; i++)
      h[i] = 0;
  }
  //universal hashing function
  void u_hash(int key) {
    get_random(a, b, p);
    h[key] = ((a*key+b) % p) % TABLE_SIZE;
  }
  void insert(int key, int value);
  int search (int key);
  bool deletion(int key);
  void get_random(int &a, int &b, int p);
  void displayHash() {
    for(int i = 0; i < TABLE_SIZE; i++) {
      cout << '\n' << i << "-->";
      while (hashTable[i] != NULL) {
        cout << "("<<hashTable[i] -> key << ", " << hashTable[i]->val <<")--> ";
        hashTable[i] = hashTable[i]->next;
      }
  }
  }
};
void HashChain ::insert(int key, int value) {
    node *t = new node;
    u_hash(key);
    t->key = key;
    t->next = hashTable[h[key]];
    t->val = value;
    hashTable[h[key]] = t;
    cout << value << "inserted ! \n";
  }
int HashChain :: search(int key){
    if(hashTable[h[key]] == NULL) {
      cout << "failed ! \n";
      return 0;
    }
    else if(hashTable[h[key]] -> key != key) {
      while(hashTable[h[key]]-> key == key)
        hashTable[h[key]] = hashTable[h[key]] -> next;
    }
    cout << hashTable[h[key]] -> val << "founded ! \n";
    return hashTable[h[key]] -> val;
  }
bool HashChain :: deletion(int key){
    node *cur;
    cur = hashTable[h[key]];
    node *prev;
    if(hashTable[h[key]] -> key == key) {
      node *first = hashTable[h[key]];
      hashTable[h[key]] = hashTable[h[key]] -> next;
      delete(first);
      return true; 
    }
    if(cur == NULL) {
      return false;
    } else if(cur -> key != key) {
      while(cur -> key != key) {
        prev = cur;
        cur = cur -> next;
      }
      if(cur == NULL) return false; 
    }
    prev -> next = cur->next;
    delete(cur);
    return true;
  }
void HashChain::get_random(int &a, int &b, int p) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(0, p-1);
  b = dis(gen);
  uniform_int_distribution<int> dis2(1, p-1);
  a = dis2(gen);
  };



int main() {
  int a[] = {24, 68, 78, 126, 73, 745, 122, 3, 8, 34, 756, 100, 32,4, 91};
  int p = get_prime(756);
  HashChain h(p);

  h.insert(24, 5);
  h.insert(68, 6);
  h.insert(78, 6);
  h.insert(126, 8);
  h.insert(73, 8);
  h.insert(745, 8);
  h.insert(122, 8);
  h.insert(123, 8);
  h.insert(3, 8);
  h.insert(8, 8);
  h.insert(34, 8);
  h.insert(756, 8);
  h.insert(100, 8);
  h.insert(32, 8);
  h.insert(4, 8);
  h.insert(91, 8);
  h.deletion(91);
  h.deletion(126);
  h.search(32);
  h.search(91);
  h.displayHash();
  
}