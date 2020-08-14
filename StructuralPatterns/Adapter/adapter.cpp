#include <iostream>
#include <memory>
#include <utility>

using namespace std;

typedef int Cable;

class EuropeanSocketInterface {
public:
    virtual int voltage() = 0;
    virtual Cable live() = 0;
    virtual Cable neutral() = 0;
    virtual Cable earth() = 0;
};

class USASocketInterface {
public:
    virtual int voltage() = 0;
    virtual Cable live() = 0;
    virtual Cable neutral() = 0;
};

class Socket : public EuropeanSocketInterface {
public:
    int voltage() override { return 230; }
    Cable live() override { return 1; }
    Cable neutral() override { return -1; }
    Cable earth() override { return 0; }
};

class Adapter : public USASocketInterface {
private:
    shared_ptr<EuropeanSocketInterface> socket_;

public:
    int voltage() override { return 110; }
    Cable live() override { return socket_->live(); }
    Cable neutral() override { return socket_->neutral(); }
    void plugIn(shared_ptr<EuropeanSocketInterface> outlet) { socket_ = move(outlet); }
};

class ElectricDevice {
private:
    shared_ptr<USASocketInterface> power_;

public:
    void plugIn(shared_ptr<USASocketInterface> supply) { power_ = move(supply); }
    void powerOn() {
        if (power_->live() == 1 && power_->neutral() == -1) {
            cout << "Working great!\n";
        }
    }
};

int main() {
    shared_ptr<Socket> socket = make_unique<Socket>();
    shared_ptr<Adapter> adapter = make_unique<Adapter>();
    ElectricDevice kettle;

    adapter->plugIn(socket);
    kettle.plugIn(adapter);
    kettle.powerOn();

    return 0;
}
