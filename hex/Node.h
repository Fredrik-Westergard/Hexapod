#ifndef NODE_H__
#define NODE_H__

class Node{
    private:
        int amount;
        double length[3];

    public:
        int getAmount();
        void setAmount(int amount);
        double getLength(int i);
        void setLength(int i, double length);

        Node(int amount, double length1, double length2, double length3);

        Node* next;
};

#endif