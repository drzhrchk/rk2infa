#include <iostream>
#include <string>

class BankAccount {
public:

    BankAccount(const std::string& accountNumber, const std::string& ownerName, double initialBalance)
        : accountNumber(accountNumber), ownerName(ownerName), balance(initialBalance) {}

 
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Пополнено: $" << amount << ". Новый баланс: $" << balance << std::endl;
        } else {
            std::cout << "Сумма пополнения должна быть положительной." << std::endl;
        }
    }


    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Снято: $" << amount << ". Новый баланс: $" << balance << std::endl;
        } else {
            std::cout << "Ошибка: недостаточно средств или неверная сумма." << std::endl;
        }
    }


    void displayAccountInfo() const {
        std::cout << "Номер счета: " << accountNumber << std::endl;
        std::cout << "Владелец счета: " << ownerName << std::endl;
        std::cout << "Баланс: $" << balance << std::endl;
    }

protected:
    std::string accountNumber;
    std::string ownerName;     
    double balance;            
};

class SavingsAccount : public BankAccount {
public:

    SavingsAccount(const std::string& accountNumber, const std::string& ownerName, double initialBalance, double interestRate)
        : BankAccount(accountNumber, ownerName, initialBalance), interestRate(interestRate) {}


    void applyInterest() {
        double interest = balance * (interestRate / 100);
        balance += interest;
        std::cout << "Начислены проценты: $" << interest << ". Новый баланс: $" << balance << std::endl;
    }

private:
    double interestRate; 
};

int main() {

    BankAccount myAccount("123456", "Иван Иванов", 1000.0);
    

    myAccount.displayAccountInfo();
    

    myAccount.deposit(500.0);
    myAccount.withdraw(200.0);
    
 
    SavingsAccount mySavings("654321", "Мария Петрова", 2000.0, 5.0);
    
 
    mySavings.displayAccountInfo();
    
 
    mySavings.deposit(300.0);
    mySavings.withdraw(100.0);
    
    
    mySavings.applyInterest();
    
    return 0;
}
