#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class IComponent {
public:
    virtual void traverse() const = 0;
};

class Leaf : public IComponent {
private:
    int value_;

public:
    explicit Leaf(int value) : value_(value) {}
    void traverse() const override { cout << "Value: " << value_ << "\n"; }
};

class Composite : public IComponent {
private:
    vector<shared_ptr<IComponent>> children;

public:
    void add(const shared_ptr<IComponent> &element) { children.emplace_back(element); }
    void traverse() const override {
        for (const auto &child : children) {
            child->traverse();
        }
    }
};

int main() {
    const int noOfContainers = 4;
    const int noOfLeaves = 3;
    vector<shared_ptr<Composite>> containers(noOfContainers);

    for (int i = 0; i < noOfContainers; i++) {
        containers[i] = make_shared<Composite>();
        for (int j = 0; j < noOfLeaves; j++) {
            containers[i]->add(make_shared<Leaf>(i * noOfLeaves + j));
        }
    }

    for (auto it = containers.begin(); it < containers.end(); it++) {
        cout << "Container: " << distance(containers.begin(), it) << "\n";
        it->get()->traverse();
        cout << "\n";
    }

    //    Add existing containers under one specific container
    for (int i = 1; i < noOfContainers; i++) {
        containers[0]->add(containers[i]);
    }

    cout << "Containers after the change\n";
    for (auto it = containers.begin(); it < containers.end(); it++) {
        cout << "Container: " << distance(containers.begin(), it) << "\n";
        it->get()->traverse();
        cout << "\n";
    }

    return 0;
}