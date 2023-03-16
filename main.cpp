#include "Node.h"
#include <iostream>
using namespace std;


void enqueue(Node* headQueue, char c);
int main() {
  char input[20];
  cout << "Enter equation: ";
  cin >> input;

  Node* headStack = NULL;
  Node* headQueue = NULL;
  int i = 0;
  Node* nQueue = headQueue;
  while (input[i] != '\0') {
    if (input[i] > 47 && input[i] < 58) {//number
      enqueue(headQueue, input[i]);
    }
    else if (input[i] == 40) {//left parenthesis
      

    }
    else if (input[i] == 41) {//right parenthesis

    }
    else if (input[i] == 43 || input[i] == 42 || input[i] == 45 || input[i] == 47) {//operator

    }
    ++i;
    nQueue = headQueue;
    while (nQueue != NULL) {
      cout << nQueue->num << endl;
      nQueue = nQueue->next;
      }
  }

}

void enqueue(Node* headQueue, char c) {
  Node* nQueue = headQueue;
  //convert it to a node
  //add to queue first in first out
  Node* newnode = new Node();
  newnode->num = (int)input[i];
  if (nQueue == NULL) {
    headQueue = newnode;
    nQueue = headQueue;
  }
  else {
    nQueue->next = newnode;
    nQueue = nQueue->next;
  }
  nQueue->next = newnode;
  newnode->next = NULL;
}
