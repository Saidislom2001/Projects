#include "Load.h"
#include <iostream>

using namespace std;

Load::Load(int nodeId, double fx, double fy) : nodeId(nodeId), fx(fx), fy(fy) {}

int Load::getNodeId() const {
    return nodeId;
}

double Load::getFx() const {
    return fx;
}

double Load::getFy() const {
    return fy;
}

void Load::print() const {
    cout << "Load at Node " << nodeId 
    << ": Fx = " << fx 
    << ", Fy = " << fy << endl;
}