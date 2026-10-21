#ifndef NODE_H
#define NODE_H

class Node {
    private:
        int id;
        double x;
        double y;

    public:
        Node(int id, double x, double y);

        int getId() const;
        double getX() const;
        double getY() const;

        void print() const;
};
#endif // NODE_H