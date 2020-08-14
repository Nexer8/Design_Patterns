#include <iostream>
#include <memory>
#include <vector>

using namespace std;

enum Role {
    EActor,
    EDirector,
    EGaffer
};

class Position {
public:
    //    factory method
    static shared_ptr<Position> createNewPerson(Role role);
    virtual void info() = 0;
};

class Actor : public Position {
public:
    void info() override { cout << "Actor plays a character\n"; }
};

class Director : public Position {
public:
    void info() override { cout << "Director directs the play\n"; }
};

class Gaffer : public Position {
public:
    void info() override { cout << "Gaffer takes care of the lights\n"; }
};

shared_ptr<Position> Position::createNewPerson(Role role) {
    switch (role) {
        case EActor:
            return make_shared<Actor>();
        case EDirector:
            return make_shared<Director>();
        case EGaffer:
            return make_shared<Gaffer>();
    }
}

int main() {
    vector<shared_ptr<Position>> roles;
    roles.emplace_back(Position::createNewPerson(EActor));
    roles.emplace_back(Position::createNewPerson(EDirector));
    roles.emplace_back(Position::createNewPerson(EGaffer));

    for (auto &role : roles) {
        role->info();
    }

    return 0;
}
