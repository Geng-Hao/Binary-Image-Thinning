#ifndef LinkedList_H
#define LinkedList_H


/* ------------------------------Linked List Function Prototype----------------------------*/
 

 
 typedef struct node{
 
  void* d; // data section
 
  struct node* next; // point to the next node
 
 }node;
 
 typedef void(*DISPLAY)(void*); // function pointer
 typedef int(*COMPARE)(void*, void*); // function pointer
 
 node* getNode(node*, void*, COMPARE);
 node* deleteNode(node*, node*);
 void displayLinkedList(node*, DISPLAY);
 
 node* push_front(node*, void*);
 node* push_back(node*, void*);
 node* pop_front(node*);
 node* pop_back(node*);
 node* clear(node*);
 void* front(node*);
 void* back(node*);
 size_t sizeofList(node*);
 
 

/* ------------------------------Linked List Function Prototype----------------------------*/



#endif 

