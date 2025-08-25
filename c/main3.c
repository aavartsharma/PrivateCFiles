#include<stdio.h>
#include<stdlib.h>

struct ListNode { 
  int val;
  struct ListNode* next;
};

struct ListNode* createNode(int value) {
  struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
  newNode->val = value;
  newNode->next = NULL;
  return newNode;
}

void insertEnd(struct ListNode* node, int value) {
  struct ListNode* newNode = createNode(value);

  if(node->next == NULL){
    node->next = newNode;
    return;
  }
  struct ListNode* temp = node;
  while (temp->next != NULL){
    temp = temp-> next;
  }

  temp->next = newNode;
}

struct ListNode* linkedlist(int list[],int length) {
  struct ListNode* newNode = createNode(0);
  for (int i=0; i< length; i++)
  {
    insertEnd(newNode,list[i]);
  }
  return newNode;

}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) 
{
  int carry = 0;
  struct ListNode* dummy = createNode(0); // this is the haed of list
  struct ListNode* l3 = dummy;
  while(l1 || l2 || carry >0) {
    int x = l1 ? l1->val:0;
    int y = l2 ? l2->val:0;
    int sum = x+y+carry;
    carry = sum/10;
    l3->next = createNode(sum%10);
    l3 = l3-> next;
    printf("%d %d  sum: %d l3: %d\n",x,y,sum,l3->val);
    if(l1) l1 = l1->next;
    if(l2) l2 = l2->next;
  } 
  // printf("%d\n", dummy->next->val);
  return dummy->next;
  // return the a listnode
}

int main(void)
{
  int a[] = {1,2,3,3,3};
  int b[] = {4,5,6,6,7};
  struct ListNode num1 = *linkedlist(a,sizeof(a)/sizeof(a[0]));
  struct ListNode num2 = *linkedlist(b,sizeof(b)/sizeof(b[0]));
  struct ListNode* sum = addTwoNumbers(&num1, &num2);
  printf("%d\n", sum->next->next->next->val);
  while (sum != NULL){
    printf("%d ->", sum->val);
    if(sum->next != NULL){
      sum = sum->next;

    }
    else {
      sum = NULL;
    }
  }
  // printf("%d\n",sum->val);
  // printf("%d\n", 0==NULL && 0!=0);
  return 0;
}
