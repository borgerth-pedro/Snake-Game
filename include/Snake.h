#ifndef SNAKE_H
#define SNAKE_H


class Snake
{
    public:
        Snake();
        ~Snake();

        int getSize();
        void addNode();
        void removeNode();

    private:
        int sizeSnake;
        int* body;
};

#endif // SNAKE_H
