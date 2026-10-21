#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>

using namespace std;

class Element {
    private:
        int id;
        vector<int> nodeIDs; // Store node IDs for the element
        int materialId;

    public:
        Element(int id, const vector<int>& nodeIDs, int materialId);

        int getId() const;
        const vector<int>& getNodeIDs() const;
        int getMaterialId() const;

        void print() const;
};

#endif // ELEMENT_H        






