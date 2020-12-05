#include "stdlib.h"
#include "stdio.h"
#include "LinkedList.h"

/*----------------------------------------------Linked List Implementation---------------------------*/



 node* getNode(node* head, void* d, COMPARE compare){
 
  node* ptr = head; // ptr to traverse the linked list
  while(ptr!=NULL){
   
   if(compare(ptr->d,d)==0)
    return ptr;
 
   ptr = ptr->next;
  }
  
  return NULL;
 }

 node* deleteNode(node* head, node* rm_node){
 
  if(rm_node == head){
  
   if(head->next == NULL)
    head = NULL;
   else
    head = head->next;
  
  }
  else{
  
    node* ptr = head;
    /*find the node that before rm_node*/
    while(ptr != NULL && ptr->next != rm_node)
      ptr = ptr->next;
    
    if(ptr!=NULL) 
      ptr->next = rm_node->next;
  
  }
  free(rm_node);
  
  return head;
  
 }
 
 
 void displayLinkedList(node* head, DISPLAY display){
 
   printf("\nLinked List\n");
   node* ptr = head;
   
   while(ptr!=NULL){
   
    display(ptr->d);
    ptr = ptr->next;
   
   }
 
 }
 
 
 
 node* push_front(node* head, void* d){
  
  if(head==NULL){
  
   node* new_node = (node*)malloc(sizeof(node));
   if(!new_node)
    return NULL;
  
   new_node -> d = d;
   new_node -> next = NULL;
   head = new_node;
    return head;
  
  }
  else{
   node* new_node = (node*)malloc(sizeof(node));
   if(!new_node)
    return NULL;
  
   new_node -> d = d;
   new_node -> next = head;
   head = new_node;
    return head;
  }
 
 }
 
 
 
 
 node* push_back(node* head, void* d){
  
  
  
  if(head==NULL){
  
   // create a memory space for the new node
   node* new_node = (node*)malloc(sizeof(node));
   if(!new_node){
    printf("An error occured!");
    return NULL;
   }
   new_node -> d = d;
   new_node -> next = NULL;
   
   head = new_node;
   
   return head;
  
  }
  else{
  
  
   // create a memory space for the new node
   node* new_node = (node*)malloc(sizeof(node));
   if(!new_node)
    return NULL;
  
   new_node -> d = d;
   new_node -> next = NULL;
  
   // search for the tail of the linked list
   node* ptr = head;
   while(ptr->next!=NULL)
    ptr = ptr->next;
 
  
   // link the tail to the new node
   ptr -> next = new_node;
   return head;
  }
 
 }
 

 
 node* pop_front(node* head){
  
  if(head==NULL){
  
   return NULL;
  
  }
  else{
   node* tmp = head;
   head = head->next;
   free(tmp);
  
   return head;
  }
 
 }
 
 
 node* pop_back(node* head){
    
   if(head==NULL){
    
    return head;
   }
   else if(head->next==NULL){
    node* tail = head;
    head = NULL;
    free(tail);
    return head;
   }
   else{
    // find the node that before the tail
    node* pre_tail = head;
    while((pre_tail->next)->next!=NULL)
     pre_tail = pre_tail->next;
   
    // modify the link and free memory     
    node* tail = pre_tail->next;
    pre_tail->next = NULL;
    free(tail);
   
    return head;
   }
 }

 node* clear(node* head){
 
  if(head==NULL){
   return head;
  }
  else{
  
   node* ptr;
  
   while(head!=NULL){
    ptr = head;
    head = head->next;
    free(ptr);
   }
 
  }
  
  return head;
 
 }

 void* front(node* head){
   return head->d;
  
 }
 
 void* back(node* head){
   
    // find the tail
    node* tail = head;
    while((tail->next)!=NULL)
     tail = tail->next;
     
    return tail->d;  
 
 }
 
 size_t sizeofList(node* head){
 
  size_t size = 0;
  
  node* ptr = head;
  while(ptr!=NULL){
     size++;
     ptr = ptr->next;
  }
  
  return size;
     
 }

/*----------------------------------------------Linked List Implementation---------------------------*/
