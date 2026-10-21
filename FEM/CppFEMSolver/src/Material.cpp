#include "Material.h"
#include <iostream>

Material::Material(int id, const std::string& name, double youngModulus, double area)
    : id(id), name(name), youngModulus(youngModulus), area(area) {}

int Material::getId() const {
    return id;
}

std::string Material::getName() const {
    return name;
}

double Material::getYoungModulus() const {
    return youngModulus;
}

double Material::getArea() const {
    return area;
}

void Material::print() const {
    std::cout << "Material " << id << ": " << name << std::endl;
    std::cout << "E = " << youngModulus << std::endl;
    std::cout << "A = " << area << std::endl;
}