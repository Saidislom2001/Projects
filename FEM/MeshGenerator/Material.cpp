#include "Material.h"
#include <iostream>

Material::Material(const string& name, int id, double E, double nu) : name(name), id(id), E(E), nu(nu) {}
const string& Material::getName() const {
    return name;
}

int Material::getId() const {
    return id;
}

double Material::getYoungsModulus() const {
    return E;
}

double Material::getPoissonsRatio() const {
    return nu;
}

void Material::print() const {
    std::cout << "Material Name: " << name << ", ID: " << id
              << ", Young's Modulus: " << E << ", Poisson's Ratio: " << nu << std::endl;
}