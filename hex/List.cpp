#include "List.h"
#include <stdlib.h>

/*
 * linked list class
 */

//constructor
List::List(){
    this->head = NULL;
    this->length = -1;
}

//getter of length
int List::getLength(){
    return this->length;
}

//function to add item to list
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

//getter of element recursively
Node* List::getElementRecursive(int index, int current, Node* n){
    if(index == current){
        return n;
    }
    else{
        return getElementRecursive(index, current+1, n->next);
    }
}

//getter of element
Node* List::getElement(int i){
    if(i > this->length || i < 0){
        return NULL;
    }
    return getElementRecursive(i, 0, this->head);
}

//function to remove item from list
void List::removeFromList(){
    if(this->head == NULL){
        return;
    }
    Node* n = this->head;
    this->head = n->next;
    delete n;
    this->length--;
}  

//destructor
List::~List(){
    int l = this->length;
    for(int i = 0; i < l; i++){
        removeFromList();
    }
}
