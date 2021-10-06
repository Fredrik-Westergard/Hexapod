#ifndef NODE_H__
#define NODE_H__

/*
 * class for a node for the linked list
 */
class Node{
    private:
        int amount; //amount of steps
        double length[3]; //length of steps

    public:
        int getAmount(); //getter of amount
        void setAmount(int amount); //setter of amount
        double getLength(int i); //getter of length
        void setLength(int i, double length); //setter of length

        Node(int amount, double length1, double length2, double length3); //constructor

        Node* next; //pointer to the next element
};

#endif
