#include "Mesh.h"
#include "Material.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Function declarations
int getPositiveInt(const string& prompt);
double getPositiveDouble(const string& prompt);

int main()
{
    int nx = getPositiveInt("Enter the number of elements in the x-direction (nx): ");
    int ny = getPositiveInt("Enter the number of elements in the y-direction (ny): ");

    double width = getPositiveDouble("Enter the width of the mesh: ");
    double height = getPositiveDouble("Enter the height of the mesh: ");

    cout << "Enter the material properties:" << endl;
    string materialName;
    cout << "Material name: ";
    getline(cin, materialName);
    int materialId = getPositiveInt("Material ID: ");
    double youngsModulus = getPositiveDouble("Young's modulus (E): ");
    double poissonsRatio = getPositiveDouble("Poisson's ratio (nu): ");



    Material material(materialName, materialId, youngsModulus, poissonsRatio);
    Mesh mesh(nx, ny, width, height, material);

    mesh.generateNodes();
    mesh.generateElements();

    mesh.printMesh();
    mesh.saveToFile("mesh.csv");

    return 0;
}

int getPositiveInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value <= 0) {
            cout << "Invalid input. Please enter a positive integer." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any extra input
            return value;
        }
    }
}

double getPositiveDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value <= 0) {
            cout << "Invalid input. Please enter a positive double." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any extra input
            return value;
        }
    }
}       

