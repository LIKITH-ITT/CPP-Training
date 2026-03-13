#include <gtest/gtest.h>
class BankAccount
{
    int balance;

public:
    BankAccount(int initialBalance) : balance(initialBalance) {}

    void deposit(int amount)
    {
        balance += amount;
    }

    bool withdraw(int amount)
    {
        if (amount > balance)
            return false;

        balance -= amount;
        return true;
    }

    int getBalance()
    {
        return balance;
    }
};

class GivenFixtureName : public ::testing::Test
{
    protected:
    BankAccount* account;
    void SetUp() override
    {
        account = new BankAccount(100);
    }
};

TEST_F(GivenFixtureName, WithPositiveDeposit_SuccessDeposit){
    account->deposit(200);
    EXPECT_EQ(account->getBalance(), 300);
}

TEST_F(GivenFixtureName, WithPositiveWithdraw_SuccesWithdraw){
    EXPECT_EQ(account->withdraw(50), true);
}

TEST_F(GivenFixtureName, WithPositiveWithdraw_FailWithdraw){
    EXPECT_EQ(account->withdraw(150), false);
}