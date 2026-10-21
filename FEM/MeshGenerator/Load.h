#ifndef LOAD_H
#define LOAD_H

class Load
{
private:
    int nodeId;
    double fx;
    double fy;
public:
    Load(int nodeId, double fx, double fy);

    int getNodeId() const;
    double getFx() const;
    double getFy() const;

    void print() const;
};



#endif