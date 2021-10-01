#include "Node.h"

Node::Node(int amount, double length1, double length2, double length3){
    this->amount = amount;
    this->length[0] = length1;
    this->length[1] = length2;
    this->length[2] = length3;
}

int Node::getAmount(){
    return amount;
}

void Node::setAmount(int amount){
    this->amount = amount;
}

double Node::getLength(int i){
    if(i >= 0 && i < 3){
        return length[i];
    }
    return -1;
}

void Node::setLength(int i, double length){
    if(i >= 0 && i < 3){
        this->length[i] = length;
    }
}
