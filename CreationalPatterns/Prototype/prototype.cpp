#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

enum Role {
    EActor,
    EDirector,
    EGaffer
};

class Person {
private:
    string prototypeName_;
    string name_;

public:
    Person() = default;
    explicit Person(string name) : prototypeName_(std::move(name)) {}
    virtual unique_ptr<Person> clone() const = 0;
    virtual void info(string name) {
        name_ = std::move(name);
        cout << "Call info from: " << prototypeName_ << " named: " << name_ << "\n";
    }
    virtual ~Person() = default;
};

class Actor : public Person {
public:
    explicit Actor(const string &prototypeName) : Person(prototypeName) {}
    unique_ptr<Person> clone() const override { return make_unique<Actor>(*this); }
};

class Director : public Person {
public:
    explicit Director(const string &prototypeName) : Person(prototypeName) {}
    unique_ptr<Person> clone() const override { return make_unique<Director>(*this); }
};

class Gaffer : public Person {
public:
    explicit Gaffer(const string &prototypeName) : Person(prototypeName) {}
    unique_ptr<Person> clone() const override { return make_unique<Gaffer>(*this); }
};

class PersonFactory {
private:
    unordered_map<Role, unique_ptr<Person>, hash<int>> prototypes_;

public:
    PersonFactory() {
        prototypes_[Role::EActor] = make_unique<Actor>("Actor");
        prototypes_[Role::EDirector] = make_unique<Director>("Director");
        prototypes_[Role::EGaffer] = make_unique<Gaffer>("Gaffer");
    }

    unique_ptr<Person> createPerson(Role type) { return prototypes_[type]->clone(); }
};

int main() {
    unique_ptr<PersonFactory> personFactory = make_unique<PersonFactory>();

    cout << "\nCreating first person...\n";
    unique_ptr<Person> person = personFactory->createPerson(Role::EActor);
    person->info("Victor");

    cout << "\nCreating second person...\n";
    person = personFactory->createPerson(Role::EDirector);
    person->info("Elisabeth");

    cout << "\nCreating third person...\n";
    person = personFactory->createPerson(Role::EGaffer);
    person->info("John");

    return 0;
}
