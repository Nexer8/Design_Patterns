#include <iostream>
#include <vector>

using namespace std;

class Subject {
private:
    vector<class Observer *> observers;
    bool scored = false;

public:
    // register observers
    void attach(Observer *obs) { observers.push_back(obs); }
    bool getScored() const { return scored; }

    // an EVENT
    // sets if scored and notifies all observers
    void setScored(bool score) {
        scored = score;
        notify();
    }

    void notify();
};

class Observer {
private:
    Subject *subj;

public:
    int excitementLevel;// state
    Observer(Subject *mod, int excLevel) {
        subj = mod;
        excitementLevel = excLevel;
        subj->attach(this);//  Observers attaches themselves to the Subject
    }

    virtual void update() = 0;

protected:
    Subject *getSubject() { return subj; }
};

// a concrete Observer
class OldObserver : public Observer {
public:
    OldObserver(Subject *mod, int div) : Observer(mod, div) {}
    void update() override {
        bool scored = getSubject()->getScored();
        excitementLevel++;

        if (scored && excitementLevel > 150) {
            cout << "Old Observer's team scored!!"
                 << " His excitement level is "
                 << excitementLevel
                 << " watch out of heart attacks!" << endl;
        } else {
            cout << "Team didn't score. Yeeeih nothing to worry about"
                 << endl;
        }
    }
};

class YoungObserver : public Observer {
public:
    YoungObserver(Subject *mod, int div) : Observer(mod, div) {}
    void update() override {
        bool scored = getSubject()->getScored();
        excitementLevel++;

        if (scored && excitementLevel > 100) {
            cout << "Young Observer's team scored!!"
                 << " His excitement level is "
                 << excitementLevel
                 << " don't drink and drive!!" << endl;
        } else {
            cout << "Team scored! Yeeh, the excitement level is "
                 << excitementLevel
                 << " so there is nothing to worry about" << endl;
        }
    }
};

void Subject::notify() {
    for (auto observer : observers) {
        observer->update();
    }
}

int main() {
    Subject subj;
    (YoungObserver(&subj, 100));
    (OldObserver(&subj, 150));
    (YoungObserver(&subj, 52));

    subj.setScored(true);

    return 0;
}
