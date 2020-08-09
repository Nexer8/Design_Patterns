#include <iostream>

using namespace std;

// abstract product
class DoorHandle {
public:
    virtual ~DoorHandle() = default;
    //    a pure virtual function
    virtual void printSerialNumber() = 0;
};

// a concrete factory
class BMWDoorHandle : public DoorHandle {
public:
    void printSerialNumber() override {
        cout << " DoorHandle_Product: BMW123 \n";
    }
};

// a concrete factory
class FordDoorHandle : public DoorHandle {
public:
    void printSerialNumber() override {
        cout << " DoorHandle_Product: Ford123 \n";
    }
};

// an abstract factory
class Car {
public:
    virtual ~Car() = default;
    virtual DoorHandle *createDoorHandle() = 0;
};

// a concrete factory
class BMWCar : public Car {
public:
    DoorHandle *createDoorHandle() override {
        return new BMWDoorHandle;
    }
};

// a concrete factory
class FordCar : public Car {
public:
    DoorHandle *createDoorHandle() override {
        return new FordDoorHandle;
    }
};

int main() {
    Car *car;
    DoorHandle *doorHandle;

    //    Create a door handle for a Ford car
    car = new FordCar;
    doorHandle = car->createDoorHandle();
    doorHandle->printSerialNumber();

    delete car;
    delete doorHandle;

    //    Create a door handle for a Ford car
    car = new BMWCar;
    doorHandle = car->createDoorHandle();
    doorHandle->printSerialNumber();

    delete car;
    delete doorHandle;

    return 0;
}