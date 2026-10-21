#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

using namespace std;


class Material {
    private:
        string name;
        int id;
        double E; // Young's modulus
        double nu; // Poisson's ratio
    
    public:
        Material(const string& name, int id, double E, double nu);
        const string& getName() const;
        int getId() const;
        double getYoungsModulus() const;
        double getPoissonsRatio() const;
        void print() const;
};
#endif // MATERIAL_H
