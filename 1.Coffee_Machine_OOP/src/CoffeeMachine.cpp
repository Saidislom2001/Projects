#include "../include/CoffeeMachine.h"
#include <iostream>
#include <string>

using namespace std;

CoffeeMachine::CoffeeMachine(){
    water = 400;
    milk = 540;
    coffeeBeans = 120;
    cups = 9;
    money = 550;
}

void CoffeeMachine::showStatus() const {
    cout << "The coffee machine has:" << endl;
    cout << water << " ml of water" << endl;
    cout << milk << " ml of milk" << endl;
    cout << coffeeBeans << " g of coffee beans" << endl;
    cout << cups << " disposable cups" << endl;
    cout << "$" << money << " of money" << endl;
}

void CoffeeMachine::buy()
{
    int choice;

    cout << "\nWhat do you want to buy?\n";
    cout << "1 - espresso\n";
    cout << "2 - latte\n";
    cout << "3 - cappuccino\n";
    cout << "0 - back to main menu\n";
    cout << "> ";
    cin >> choice;

    if (choice == 0) {
        return; // Return to main menu
    }

    if (choice == 1) {
        // Espresso
        if (water >= 250 && coffeeBeans >= 16 && cups >= 1) {
            water -= 250;
            coffeeBeans -= 16;
            cups -= 1;
            money += 4;
            cout << "I have enough resources, making you a coffee!" << endl;
        } else {
            cout << "Sorry, not enough resources to make an espresso." << endl;
        }
    } else if (choice == 2) {
        // Latte
        if (water >= 350 && milk >= 75 && coffeeBeans >= 20 && cups >= 1) {
            water -= 350;
            milk -= 75;
            coffeeBeans -= 20;
            cups -= 1;
            money += 7;
            cout << "I have enough resources, making you a coffee!" << endl;
        } else {
            cout << "Sorry, not enough resources to make a latte." << endl;
        }
    } else if (choice == 3) {
        // Cappuccino
        if (water >= 200 && milk >= 100 && coffeeBeans >= 12 && cups >= 1) {
            water -= 200;
            milk -= 100;
            coffeeBeans -= 12;
            cups -= 1;
            money += 6;
            cout << "I have enough resources, making you a coffee!" << endl;
        } else {
            cout << "Sorry, not enough resources to make a cappuccino." << endl;
        }
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }

}

void CoffeeMachine::fill()
{
    int addWater, addMilk, addCoffeeBeans, addCups;

    cout << "\nWrite how many ml of water you want to add: ";
    cin >> addWater;
    cout << "Write how many ml of milk you want to add: ";
    cin >> addMilk;
    cout << "Write how many grams of coffee beans you want to add: ";
    cin >> addCoffeeBeans;
    cout << "Write how many disposable cups you want to add: ";
    cin >> addCups;

    water += addWater;
    milk += addMilk;
    coffeeBeans += addCoffeeBeans;
    cups += addCups;

    cout << "\nResources added successfully!\n" ;
}

void CoffeeMachine::take()
{

}

void CoffeeMachine::start()
{
    string action;

    while (true) 
    {
    cout << "\nWrite action (buy, fill, take, remaining, exit): ";
    cin >> action;

    switch (action[0]) {
        case 'b':
            buy();
            break;
        case 'f':
            fill();
            break;
        case 't':
            take();
            break;
        case 'r':
            showStatus();
            break;
        case 'e':
            return;
        default:
            cout << "Invalid action. Please try again." << endl;
            break;
        }
    }

}

