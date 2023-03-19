#include "node.h"
#include <iostream>
#include <string.h>
#include <cstring>
#include <vector>
using namespace std;

/*
Author: Min Kim
Program Description: This is a program that will create the prefix, infix, and postfix notations of an 
inputted equation from the binary tree made from the equation. 
Date: 3/19/23
*/

void enqueue(Node* &headQueue, Node* & tailQueue, Node* token);
void dequeue(Node* &headQueue);
void push(Node* &tailStack, int operation);
Node* pop(Node* &tailStack);
int peek(Node* tailStack);
int prescedence(int op);
void infix(Node* root);
void prefix(Node* root);
void postfix(Node* root);

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
        if (tailStack->next == NULL) {
        }
        enqueue(headQueue, tailQueue, pop(tailStack));
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
      while ((tailStack != NULL) && (prescedence(peek(tailStack)) >= prescedence(peek(token)))) {
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

  //build binary tree
  Node* root = NULL;
  Node* token = headQueue;
  vector<Node*>tree;
  while(token != NULL) {
    if (token->num > 47 && token->num < 58) {//number
    tree.push_back(token);
    }
    else {//operator
      token->right = tree.back();
      tree.pop_back();
      token->left = tree.back();
      tree.pop_back();
      tree.push_back(token);
    }
    token = token->next;
  }
  root = tree[0];

  bool cont = true;
  char notation[20];
  while (cont == true) {//print from binary tree
    cout << "Infix, prefix, postfix, or quit (infix, prefix, postfix, quit)?: ";
    cin >> notation;
    cin.ignore();
    if (strcmp(notation, "infix") == 0) {
      infix(root);
      cout << endl;
    }
    else if (strcmp(notation, "prefix") == 0) {
      prefix(root);
      cout << endl;
    }
    else if (strcmp(notation, "postfix") == 0) {
      postfix(root);
      cout << endl;
    }
    else if (strcmp(notation, "quit") == 0) {
      cont = false;
    }
    else {
      cout << "Invalid input" << endl;
    }
  }
}
/*
prefix, infix, postfix psuedocode from https://en.wikipedia.org/wiki/Binary_expression_tree
*/
void prefix(Node* root) {//print in prefix notation
  if (root != NULL) {
    cout << char(root->num);
    prefix(root->left);
    prefix(root->right);
  }
}

void infix(Node* root) {//print in infix notation
  if (root != NULL) {
    if (root->num < 48) {//if its an operator
      cout << "(";
    }
    infix(root->left);
    cout << char(root->num);
    infix(root->right);
    if(root->num < 48) {
      cout << ")";
    }
  }
}

void postfix(Node* root) {//print in postfix notation
  if (root != NULL) {
    postfix(root->left);
    postfix(root->right);
    cout << char(root->num);
  }
}

int prescedence(int op) {//find prescedence of operator
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

int peek(Node* tailStack) {
  return tailStack->num;
}