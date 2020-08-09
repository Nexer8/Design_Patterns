#include <iostream>
#include <string>

using namespace std;

class MoveLogic {
public:
    virtual ~MoveLogic() = default;
    virtual void move() = 0;
};

class Walk : public MoveLogic {
public:
    void move() override { cout << "Move alternating legs\n"; }
};

class Fly : public MoveLogic {
    void move() override { cout << "Flap wings\n"; }
};

class Animal {
public:
    virtual ~Animal() = default;
    virtual void howDoIMove() = 0;
};

class Person : public Animal {
private:
    MoveLogic *myMoveLogic_;

public:
    explicit Person(MoveLogic *moveLogic) : myMoveLogic_(moveLogic) {}
    void howDoIMove() override { myMoveLogic_->move(); }
};

class Bird : public Animal {
private:
    MoveLogic *myMoveLogic_;

public:
    explicit Bird(MoveLogic *moveLogic) : myMoveLogic_(moveLogic) {}
    void howDoIMove() override { myMoveLogic_->move(); }
};

int main() {
    MoveLogic *walk = new Walk();
    MoveLogic *fly = new Fly();

    Animal *animalA = new Person(walk);
    Animal *animalB = new Bird(fly);

    animalA->howDoIMove();
    animalB->howDoIMove();

    delete animalA;
    delete animalB;
    delete walk;
    delete fly;

    return 0;
}