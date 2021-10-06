#ifndef LIST_H__
#define LIST_H__

#include "Node.h"

/*
 * linked list class
 */
class List{
  private:
    int length; //length variable
    Node* head; //head of linked list

  public:
    List(); //constructor
    int getLength(); //getter of length
    void addToList(double len1, double len2, double len3, int amount); //function to add to list
    Node* getElementRecursive(int index, int current, Node* n); //function to get element recursively
    Node* getElement(int i); //function to get element using getElementRecursive
    void removeFromList(); //function to remove from list
    ~List(); //destructor
};

#endif
