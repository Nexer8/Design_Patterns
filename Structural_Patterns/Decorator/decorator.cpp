#include <iostream>

using namespace std;

class IBackpack {
public:
    virtual void assemble() = 0;
    virtual ~IBackpack() = default;
};

class PlainBackpack : public IBackpack {
public:
    void assemble() override { cout << "\n ShoulderStraps and mainCompartment"; }
};

class BackpackDecorator : public IBackpack {
private:
    IBackpack *m_decorator;

public:
    explicit BackpackDecorator(IBackpack *decorator) : m_decorator(decorator) {}
    ~BackpackDecorator() override { delete m_decorator; }
    void assemble() override { m_decorator->assemble(); }
};

class WithLaptopSlot : public BackpackDecorator {
public:
    explicit WithLaptopSlot(IBackpack *decorator) : BackpackDecorator(decorator) {}
    void assemble() override {
        BackpackDecorator::assemble();
        cout << " + LaptopSlot";
    }
};

class WithUSBCharge : public BackpackDecorator {
public:
    explicit WithUSBCharge(IBackpack *decorator) : BackpackDecorator(decorator) {}
    void assemble() override {
        BackpackDecorator::assemble();
        cout << " + USBCharge";
    }
};

class WithWaterBottle : public BackpackDecorator {
public:
    explicit WithWaterBottle(IBackpack *decorator) : BackpackDecorator(decorator) {}
    void assemble() override {
        BackpackDecorator::assemble();
        cout << " + WaterBottle";
    }
};

int main() {
    cout << "First example";
    IBackpack *pBackpack =
            new WithWaterBottle(
                    new WithUSBCharge(
                            new WithLaptopSlot(
                                    new BackpackDecorator(
                                            new PlainBackpack))));
    pBackpack->assemble();
    delete pBackpack;

    cout << "\n\nSecond example";
    pBackpack = new PlainBackpack;
    pBackpack = new BackpackDecorator(pBackpack);
    pBackpack = new WithLaptopSlot(pBackpack);
    pBackpack = new WithUSBCharge(pBackpack);
    pBackpack = new WithWaterBottle(pBackpack);
    pBackpack->assemble();

    delete pBackpack;

    return 0;
}