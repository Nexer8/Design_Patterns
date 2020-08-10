#include <iostream>
#include <list>
#include <memory>

using namespace std;

class Resource {
public:
    int value = 0;
    void reset() { value = 0; }
};

class ObjectPool {
private:
    list<shared_ptr<Resource>> resources;
    static shared_ptr<ObjectPool> instance;

public:
    static shared_ptr<ObjectPool> getInstance() {
        if (!instance) {
            instance = make_shared<ObjectPool>();
        }

        return instance;
    }

    shared_ptr<Resource> getResource() {
        if (resources.empty()) {
            cout << "Creating a new resource\n";

            return make_shared<Resource>();
        } else {
            cout << "Reusing existing\n";
            shared_ptr<Resource> resource = resources.front();
            resources.pop_front();

            return resource;
        }
    }

    void returnResource(const shared_ptr<Resource> &res) {
        res->reset();
        resources.push_back(res);
    }
};

shared_ptr<ObjectPool> ObjectPool::instance = nullptr;

int main() {
    shared_ptr<ObjectPool> oPool = ObjectPool::getInstance();
    shared_ptr<Resource> rOne;
    shared_ptr<Resource> rTwo;

    rOne = oPool->getResource();
    rOne->value = 10;
    cout << "First resource value: " << rOne->value << "\n";

    rTwo = oPool->getResource();
    rTwo->value = 10;
    cout << "Second resource value: " << rTwo->value << "\n";

    oPool->returnResource(rOne);
    oPool->returnResource(rTwo);
    cout << "\n Object returned.\n\n";

    rOne = oPool->getResource();
    cout << "First resource value: " << rOne->value << "\n";

    rTwo = oPool->getResource();
    cout << "Second resource value: " << rTwo->value << "\n";

    return 0;
}
