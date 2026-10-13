#ifndef SNAKE_H
#define SNAKE_H
#include "Node.h"

class Snake
{
    public:
        Snake();
        ~Snake();

        int getSize();
        void addNode();
        void removeNode();
        Node* getHead();
        Node* getTail();

    private:
        Node *headSnake = nullptr;
        Node *tailSnake = nullptr;
        int sizeSnake = 0;
};

#endif // SNAKE_H
