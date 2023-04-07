#include "node.h"
#include <iostream>

Node:: Node(int newnum, Node* newnext) {
    num = newnum;
    next = newnext;
    left = nullptr;
    right = nullptr;
}