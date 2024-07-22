#include "BankAccount.h"

// constructor and destructor
BankAccount::BankAccount(/* args */)
{
    balance = 0;
    accountNumber = "";
    accountHolder = "";
}

BankAccount::~BankAccount()
{
}

// setter
void BankAccount::setBalance(double balance)
{
    this->balance = balance;
}
void BankAccount::setAccountNumber(std::string accountNumber)
{
    this->accountNumber = accountNumber;
}
void BankAccount::setAccountHolder(std::string accountHolder)
{
    this->accountHolder = accountHolder;
}
// getter
double BankAccount::getBalance()
{
    return balance;
}
std::string BankAccount::getAccountNumber()
{
    return accountNumber;
}
std::string BankAccount::getAccountHolder()
{
    return accountHolder;
}

// deposit and withdraw
void BankAccount::deposit(double amount)
{
    balance += amount;
}
void BankAccount::withdraw(double amount)
{
    balance -= amount;
}
// checking balance
bool BankAccount::checkBalance(double amount)
{
    if (balance >= amount)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// display balance
void BankAccount::displayBalance()
{
    std::cout << "================================\n";
    std::cout << "Account Holder : " << accountHolder << std::endl;
    std::cout << "Account Number : " << accountNumber << std::endl;
    std::cout << "Balance : " << balance << std::endl;
    std::cout << "================================\n";
}
