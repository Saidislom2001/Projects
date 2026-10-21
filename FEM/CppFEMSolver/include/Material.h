#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

class Material {
private:
    int id;
    std::string name;
    double youngModulus;
    double area;

public:
    Material(int id, const std::string& name, double youngModulus, double area);

    int getId() const;
    std::string getName() const;
    double getYoungModulus() const;
    double getArea() const;

    void print() const;
};

#endif