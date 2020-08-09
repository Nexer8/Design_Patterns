#include <iostream>

using namespace std;

class Singleton {
public:
    static Singleton *getInstance();

private:
    Singleton() = default;
    static Singleton *s_instance;
};

Singleton *Singleton::s_instance = nullptr;

Singleton *Singleton::getInstance() {
    if (!s_instance) {
        s_instance = new Singleton();
        cout << "There is no instance so we created one.\n";

        return s_instance;
    }

    else {
        cout << "Hey this is the same instance!\n";

        return s_instance;
    }
}

int main() {
    Singleton::getInstance();
    Singleton::getInstance();

    return 0;
}
