#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class IProductRepository
{
public:
    virtual int getPrice(const std::string& product) = 0;
    virtual ~IProductRepository() = default;
};

class PriceService
{
    IProductRepository& repo;

public:
    PriceService(IProductRepository& r) : repo(r) {}

    int getFinalPrice(const std::string& product)
    {
        int price = repo.getPrice(product);
        return price + 10;   
    }
};

class MockIProductRepository : public IProductRepository
{
    public:
    MOCK_METHOD(int, getPrice, (const std::string&), (override));
};

TEST(FixtureName, GivenPrice_SuccessGetPrice)
{
    MockIProductRepository mock;
    EXPECT_CALL(mock, getPrice(::testing::_))
    .Times(1)
    .WillOnce(::testing::Return(500));

    PriceService service(mock);
    EXPECT_EQ(service.getFinalPrice("Github"),510);

}
