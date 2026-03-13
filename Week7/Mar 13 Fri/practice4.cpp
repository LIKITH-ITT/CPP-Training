#include <string>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class IDatabase
{
public:
    virtual bool connect() = 0;
    virtual bool checkUser(const std::string& username, const std::string& password) = 0;
    virtual ~IDatabase() = default;
};

class UserService
{
    IDatabase& db;

public:
    UserService(IDatabase& database) : db(database) {}

    bool login(const std::string& username, const std::string& password)
    {
        if (!db.connect())
        {
            return false;
        }

        return db.checkUser(username, password);
    }
};
class MockIDatabase : public IDatabase
{
    public:
    MOCK_METHOD(bool, connect, (),(override));
    MOCK_METHOD(bool, checkUser, (const std::string&, const std::string&), (override));
};

TEST(DatabaseTest, GivenConnect){
    MockIDatabase mock;
    EXPECT_CALL(mock, connect()).Times(1).WillOnce(::testing::Return(true));
    EXPECT_CALL(mock, checkUser(::testing::_,::testing::_))
    .Times(1)
    .WillOnce(::testing::Return(false));

    UserService service(mock);
    EXPECT_FALSE(service.login("user","pass"));
}