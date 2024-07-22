#if !defined(BANKACCOUNTS_H_)
#define BANKACCOUNTS_H_
#include <iostream>
class BankAccount
{
private:
    double balance;
    std::string accountNumber;
    std::string accountHolder;

public:
//constructor and destructor
    BankAccount(/* args */);
    ~BankAccount();

    //setter
    void setBalance(double balance);
    void setAccountNumber(std::string accountNumber);
    void setAccountHolder(std::string accountHolder);
    //getter
    double getBalance();
    std::string getAccountNumber();
    std::string getAccountHolder();

    //deposit and withdraw
    void deposit(double amount);
    void withdraw(double amount);
    //checking balance
    bool checkBalance(double amount);
    //display balance
    void displayBalance();
};




#endif // BANKACCOUNTS_H_
