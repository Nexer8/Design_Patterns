#include <iostream>
#include <memory>

using namespace std;

// Product
class Pizza {
private:
    string m_dough;
    string m_sauce;
    string m_topping;

public:
    void setDough(const string &dough) { m_dough = dough; }
    void setSauce(const string &sauce) { m_sauce = sauce; }
    void setTopping(const string &topping) { m_topping = topping; }

    void taste() const {
        cout << "Pizza with " << m_dough << " dough, "
             << m_sauce << " sauce and "
             << m_topping << " topping. Mmmmmmm." << endl;
    }
};

// Abstract builder
class PizzaBuilder {
protected:
    unique_ptr<Pizza> m_pizza;

public:
    virtual ~PizzaBuilder() = default;

    Pizza *getPizza() { return m_pizza.release(); }// this getter can be called only once
    void createNewPizza() {
        m_pizza = make_unique<Pizza>();
    }

    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTop() = 0;
};

// Concrete builder
class Margherita : public PizzaBuilder {
public:
    void buildDough() override { m_pizza->setDough("cross"); }
    void buildSauce() override { m_pizza->setSauce("tomato"); }
    void buildTop() override { m_pizza->setTopping("mozzarella+basil"); }
};

// Concrete builder
class Spicy : public PizzaBuilder {
public:
    void buildDough() override { m_pizza->setDough("pan baked"); }
    void buildSauce() override { m_pizza->setSauce("tomato+chilli"); }
    void buildTop() override { m_pizza->setTopping("pepperoni+salami"); }
};

// Director
class Cook {
private:
    PizzaBuilder *m_pizzaBuilder;

public:
    void makePizza(PizzaBuilder *pb) {
        m_pizzaBuilder = pb;
        m_pizzaBuilder->createNewPizza();
        m_pizzaBuilder->buildDough();
        m_pizzaBuilder->buildSauce();
        m_pizzaBuilder->buildTop();
    }
    void tastePizza() { m_pizzaBuilder->getPizza()->taste(); }
};

// Client
int main() {
    Cook cook{};
    Margherita margherita;
    Spicy spicy;

    cook.makePizza(&margherita);
    cook.tastePizza();

    cook.makePizza(&spicy);
    cook.tastePizza();

    return 0;
}