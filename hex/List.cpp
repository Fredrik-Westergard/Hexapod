#include "List.h"
#include <stdlib.h>


List::List(){
    this->head = NULL;
    this->length = -1;
}

int List::getLength(){
    return this->length;
}

void List::addToList(double len1, double len2, double len3, int amount){
    Node* n = new Node(amount, len1, len2, len3);
    n->next = NULL;

    if(this->head == NULL){
        this->head = n;
    }
    else{
        Node* m = getElement(this->length);
        m->next = n;
    }
    this->length++;
}

Node* List::getElementRecursive(int index, int current, Node* n){
    if(index == current){
        return n;
    }
    else{
        return getElementRecursive(index, current+1, n->next);
    }
}

Node* List::getElement(int i){
    if(i > this->length || i < 0){
        return NULL;
    }
    return getElementRecursive(i, 0, this->head);
}

void List::removeFromList(){
    if(this->head == NULL){
        return;
    }
    Node* n = this->head;
    this->head = n->next;
    delete n;
    this->length--;
}  

List::~List(){
    int l = this->length;
    for(int i = 0; i < l; i++){
        removeFromList();
    }
}
