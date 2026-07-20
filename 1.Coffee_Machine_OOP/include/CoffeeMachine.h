#ifndef   COFFEEMACHINE_H
#define   COFFEEMACHINE_H

class CoffeeMachine {
    private:
        int water;
        int milk;
        int coffeeBeans;
        int cups;
        int money;
    
    public:
        CoffeeMachine();

        void start();
        void fill();
        void buy();
        void take();
        void showStatus() const;
};

#endif
