#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>

using namespace std;

struct CarSharedState {
    string brand_;
    string model_;
    string color_;

    CarSharedState(string brand, string model, string color) : brand_(move(brand)),
                                                               model_(move(model)),
                                                               color_(move(color)) {}

    void info() const {
        cout << "Car: " << brand_ << " " << model_ << " " << color_ << "\n";
    }
};

struct CarUniqueState {
    string owner_;
    string plates_;

    void info() const {
        cout << "Car: " << owner_ << " " << plates_ << "\n";
    }
};

class Flyweight {
private:
    shared_ptr<CarSharedState> sharedState_;

public:
    explicit Flyweight(shared_ptr<CarSharedState> sharedState) : sharedState_(move(sharedState)) {}
    void printInfo(const CarUniqueState &uniqueState) const {
        sharedState_->info();
        uniqueState.info();
    }
    explicit Flyweight(const CarSharedState &sharedState) : sharedState_(make_shared<CarSharedState>(sharedState)){};
};

class FlyweightFactory {
private:
    unordered_map<string, Flyweight> flyweights_;
    static string getKey(const CarSharedState &sharedState) {
        return sharedState.brand_ + "_" + sharedState.model_ + "_" + sharedState.color_;
    }

public:
    FlyweightFactory(initializer_list<CarSharedState> sharedStates) {
        for (const CarSharedState &sharedState : sharedStates) {
            flyweights_.insert(make_pair<string, Flyweight>(getKey(sharedState), Flyweight(sharedState)));
        }
    }

    Flyweight getFlyweight(const CarSharedState &sharedState) {
        const string key = getKey(sharedState);
        if (flyweights_.find(key) == flyweights_.end()) {
            cout << "FlyweightFactory: Can't find a flyweight, creating a new one.\n";
            flyweights_.insert(make_pair(key, Flyweight(sharedState)));
        } else {
            cout << "FlyweightFactory: Reusing existing flyweight.\n";
        }

        return flyweights_.at(key);
    }

    void listFlyweights() const {
        cout << "\nFlyweightFactory: I have " << flyweights_.size() << " flyweights\n";
        for (const auto &flyweight : flyweights_) {
            cout << flyweight.first << "\n";
        }
    }
};

void addCarToPoliceDatabase(FlyweightFactory &flyweightFactory, string plates, string owner, string brand, string model, string color) {
    cout << "\nClient: Adding a car to database.\n";
    const Flyweight &flyweight = flyweightFactory.getFlyweight({move(brand), move(model), move(color)});
    flyweight.printInfo({move(plates), move(owner)});
}

int main() {
    FlyweightFactory factory(
            {{"Chevrolet", "Camaro2018", "pink"},
             {"Mercedes Benz", "C300", "black"},
             {"Mercedes Benz", "C500", "red"},
             {"BMW", "M5", "red"},
             {"BMW", "X6", "white"}});
    factory.listFlyweights();

    addCarToPoliceDatabase(factory,
                           "CL234IR",
                           "James Doe",
                           "BMW",
                           "M5",
                           "red");

    addCarToPoliceDatabase(factory,
                           "CL234IR",
                           "James Doe",
                           "BMW",
                           "X1",
                           "red");
    factory.listFlyweights();

    return 0;
}