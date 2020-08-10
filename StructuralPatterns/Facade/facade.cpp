#include <iostream>

using namespace std;

class Waiter {
public:
    void writeOrder() { cout << " Waiter writes client's order\n"; }
    void sendToKitchen() { cout << " Send order to kitchen\n"; }
    void serveCustomer() { cout << " Yeeei customer is served!!!\n"; }
};

class Kitchen {
public:
    void prepareFood() { cout << " Cook food\n"; }
    void callWaiter() { cout << " Call Waiter\n"; }
    void washDishes() { cout << " Wash the dishes\n"; }
};

class OrderFacade {
private:
    Waiter waiter;
    Kitchen kitchen;

public:
    void orderFood() {
        cout << "A series of interdependent calls on various subsystems:\n";
        waiter.writeOrder();
        waiter.sendToKitchen();
        kitchen.prepareFood();
        kitchen.callWaiter();
        waiter.serveCustomer();
        kitchen.washDishes();
    }
};

int main() {
    OrderFacade orderFacade{};
    orderFacade.orderFood();

    return 0;
}
