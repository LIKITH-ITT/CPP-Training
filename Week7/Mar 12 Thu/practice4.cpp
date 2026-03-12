#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


class IDatabase
{
public:
    virtual bool connect() = 0;
    virtual ~IDatabase() = default;
};

class UserService
{
    IDatabase& db;

public:
    UserService(IDatabase& database) : db(database) {}

    bool login()
    {
        return db.connect();
    }
};

class Database : public IDatabase
{
    bool connect() override
    {
        return true;
    }
};

class MockDatabase : public IDatabase
{
public:
    MOCK_METHOD(bool, connect, (), (override));
};

TEST(UserServiceTest, LoginSuccess)
{
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, connect())
    .Times(1)
    .WillOnce(testing::Return(true));

    UserService service(mockDb);

    EXPECT_TRUE(service.login());
}

TEST(UserServiceTest, LoginFailure)
{
    MockDatabase mockDb;

    EXPECT_CALL(mockDb, connect())
        .Times(1)
        .WillOnce(testing::Return(false));

    UserService service(mockDb);

    EXPECT_FALSE(service.login());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}