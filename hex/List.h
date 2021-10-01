#ifndef LIST_H__
#define LIST_H__

#include "Node.h"

class List{
  private:
    int length;
    Node* head;

  public:
    List();
    int getLength();
    void addToList(double len1, double len2, double len3, int amount);
    Node* getElementRecursive(int index, int current, Node* n);
    Node* getElement(int i);
    void removeFromList();
    ~List();
};

#endif
