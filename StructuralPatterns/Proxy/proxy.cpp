#include <iostream>
#include <memory>

using namespace std;

class FundsPaidFromAccount {
private:
    float balance_ = 500.0;

public:
    void execute(float amount) {
        if (amount > balance_) {
            cout << "No sufficient funds!\n";
        } else {
            balance_ -= amount;
            cout << "Spent: " << amount << "$ , current balance: " << balance_ << "$\n";
        }
    }
};

class Check {
private:
    shared_ptr<FundsPaidFromAccount> funds_;

public:
    explicit Check(shared_ptr<FundsPaidFromAccount> funds) : funds_(move(funds)){};
    void execute(float amount) {
        funds_->execute(amount);
    }
};

int main() {
    shared_ptr<FundsPaidFromAccount> payment = make_shared<FundsPaidFromAccount>();
    payment->execute(500.0);

    shared_ptr<Check> checkPayment = make_shared<Check>(payment);
    checkPayment->execute(2.0);

    return 0;
}
