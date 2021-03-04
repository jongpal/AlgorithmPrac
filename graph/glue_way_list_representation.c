#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define offsetof(struct_name, field_name) (unsigned int)&((struct_name *)0)->field_name

/*
 Glue way of linked list : saving ptr inside of data structure. this way we can utilize memorize way better than traditional way(less call of dynamic memory allocation)
 -> if various linked list will save one common data, then this way will be more efficient than traditional way which saves pointer to the data with its right,left pointer
*/

typedef struct glthread_node_ {

  struct glthread_node_ *right;
  struct glthread_node_ *left;
}glthread_node_t;

typedef struct glthread_{
  glthread_node_t *head;
  unsigned int offset;
} glthread_t;
glthread_t *emp_list;

typedef struct emp_{
  char name[30];
  unsigned int salary;
  char designation[30];
  unsigned int emp_id;
  glthread_node_t glnode;
}emp_t;


void init_glthread(glthread_node_t* glnode){
  glnode->right = NULL;
  glnode->left = NULL;
}

void init_emp(emp_t *emp, char *name, unsigned int salary, char *designation, unsigned int id){
  strncpy(emp->name, name, strlen(name));
  emp->salary = salary;
  strncpy(emp->designation, designation, strlen(designation));
  emp-> emp_id = id;
}

// 추가: 왼쪽에서 append
void add_glnode(glthread_node_t* glnode){
  if(emp_list->head == NULL){
    emp_list->head = glnode;
    return;
  }
  glthread_node_t *prev = emp_list->head;
  
  prev->left = glnode;
  glnode->right = prev;
  emp_list->head = glnode;
}

void remove_glnode(glthread_node_t* glnode){
  char isHead = 0;
  if(emp_list->head == glnode) isHead = 1;

  // if right is NULL, it's gotta be head or not (no need to check left) 
  if(!glnode->right){ 
    if(isHead) {
      emp_list->head = NULL;
      return;
    } 
    // if not, it will be the end element of the list
    glnode->left->right = glnode->right;
  }
  //no left case + existing right would be head
  else if(!glnode->left){
    glnode->right->left = glnode->left;
    emp_list->head = glnode->right;
  }
  //elements in the middle
  else {
    glnode->right->left =glnode->left;
    glnode->left->right = glnode->right;
  }
}

void print_emp_list(glthread_t *e_l){
  glthread_node_t *saved = e_l -> head;
  
  while(e_l->head){
    printf("\n\n");
    emp_t *cur = (emp_t *)((char *)e_l->head - e_l->offset);
    printf("name : %s\n", cur->name);
    printf("salary : %d\n", cur->salary);
    printf("designation : %s\n", cur->designation);
    printf("emp_id : %d\n", cur->emp_id);
    e_l->head = e_l->head->right;
    // break;
  }
  // back to original head
  emp_list->head = saved;
}
int main(void) {
  //init head
  emp_list = (glthread_t *) calloc(1, sizeof(glthread_t));
  emp_list->head = NULL;
  emp_list->offset = offsetof(emp_t, glnode);

  emp_t *emp1;
  emp1 = (emp_t *)calloc(1, sizeof(emp_t));
  init_emp(emp1, "jong", 10, "seoul", 1);
  init_glthread(&emp1->glnode);
  add_glnode(&emp1->glnode);

  emp_t *emp2;
  emp2 = (emp_t *)calloc(1, sizeof(emp_t));
  init_emp(emp2, "hi", 13, "seoul", 2);
  init_glthread(&emp2->glnode);
  add_glnode(&emp2->glnode);

  emp_t *emp3;
  emp3 = (emp_t *)calloc(1, sizeof(emp_t));
  init_emp(emp3, "you", 20, "busan", 3);
  init_glthread(&emp3->glnode);
  add_glnode(&emp3->glnode);

  print_emp_list(emp_list);

  remove_glnode(&emp2->glnode);
  free(emp2);
  printf("%s\n", (char*)emp_list->head - offsetof(emp_t, glnode));
  remove_glnode(&emp3->glnode);
  free(emp3);
  remove_glnode(&emp1->glnode);
  free(emp1);
  free(emp_list);
  return 0;
}