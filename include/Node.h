#ifndef NODE_H
#define NODE_H
#include <raylib.h>

class Node
{
    public:
        Node(Vector2 recPosition, float sizeRec);
        ~Node();

        float getSpeedX();
        float getSpeedY();
        void setSpeedX(float speedX);
        void setSpeedY(float speedY);

        Vector2 getPosition();
        void setPosition(Vector2 recPosition);

        Vector2 getSize();
        void setSize(Vector2 sizeRec);

        Node* getProx();
        void setProx(Node *p);

    private:

        Vector2 rectanglePosition;
        float speedRectangleX;
        float speedRectangleY;
        Vector2 sizeRectangle;
        Node* prox;
};

#endif // NODE_H
