#include "node.h"
#include <iostream>
using namespace std;

void enqueue(Node* &headQueue, Node* & tailQueue, Node* token);
void dequeue(Node* &headQueue);
void push(Node* &tailStack, int operation);
int prescedence(int op);
Node* pop(Node* &tailQueue);

int main() {
  char input[80];
  cout << "Enter equation: ";
  cin >> input;

  Node* tailStack = NULL;
  Node* headQueue = NULL;
  Node* tailQueue = NULL;
  int i = 0;
  while (input[i] != '\0') {
    Node* token = new Node(int(input[i]), NULL);
    if (token->num > 47 && token->num < 58) {//number: automatically goes to queue
      enqueue(headQueue, tailQueue, token);//
    }
    else if (token->num == 41) {//right parenthesis
      while(tailStack->num != 40) {
        cout << tailStack->num << endl;
        if (tailStack->next == NULL) {
        }
        cout << tailStack->next->num << endl;
        enqueue(headQueue, tailQueue, pop(tailStack));
        cout << tailStack->num << endl;
        if (tailStack == NULL) {
          break;
        }
      }
      pop(tailStack);//pop left parenthesis
    }

    else if (token->num == 40) {//left parenthesis: stack
      push(tailStack, int(input[i]));
    }
    else if (token->num == 43 || token->num == 42 || token->num == 45 || token->num == 47 || token->num == 94) {//operator
      while ((tailStack != NULL) && (prescedence(tailStack->num) >= prescedence(token->num))) {
        enqueue(headQueue, tailQueue, pop(tailStack));
      }
      push(tailStack, token->num);
    }
    ++i;
  }
  //now that there are no more tokens to go through, pop remaining operators off stack and shift them to queue
  while(tailStack != NULL) {
    enqueue(headQueue, tailQueue, pop(tailStack));//
  }
  Node* nQueue = headQueue;
  cout << "Shunting yard output: ";
  while (nQueue != NULL) {
    cout << char(nQueue->num);
    nQueue = nQueue->next;
  }
  cout << endl;
  bool cont = true;
  while (cont == true) {
    cout << "Infix, prefix, or postfix notation (infix, prefix, postfix)?: ";
    cin
  }
  //binary tree

}

int prescedence(int op) {
  if (op == 94) {//^
    return 3;
  }
  else if (op == 47 || op == 42) {//*/
    return 2;
  }
  else if (op == 43 || op == 45) {//+-
    return 1;
  }
  else {//(
    return 0;
  }
}

void enqueue(Node* &headQueue, Node* &tailQueue, Node* newnode) {
  if (newnode == NULL) {
    return;
  }
  tailQueue = headQueue;
  //convert it to a node, add to queue first in first out
  if (tailQueue == NULL) {//if it's the first one
    headQueue = newnode;
    tailQueue = headQueue;
  }
  else {
    while (tailQueue->next != NULL) {
      tailQueue = tailQueue->next;
    }
    tailQueue->next = newnode;
  }
  newnode->next = NULL;
}

void dequeue(Node* &headQueue) {//delete head
  Node* temp = headQueue->next;
  delete headQueue;
  headQueue = temp;
}

void push(Node* &tailStack, int operation) {
  Node* newnode = new Node(operation, NULL);
  if (tailStack == NULL) {
    tailStack = newnode;
    tailStack->next = NULL;
  }
  else {//make newnode the tail and put next as previous tail
    Node* temp = tailStack;
    newnode->next = temp;
    tailStack = newnode;
  }
}

Node* pop(Node* &tailStack) {//remove tail of stack
  if (tailStack->next == NULL) {
    Node* returnvalue = tailStack;
    tailStack = NULL;
    return returnvalue;
  }
  Node* temp = tailStack->next;
  Node* move = tailStack;
  move->next = NULL;
  tailStack = temp;
  return move;
}

void peek() {

}