#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "House.cpp"

using ::testing::Expectation;
using ::testing::Return;
using ::testing::_;

class MockDoor : public Door
{
public:
    explicit MockDoor() {}
    virtual ~MockDoor() {}

    MOCK_METHOD1(lock, void(bool));
    MOCK_METHOD0(open, std::string());
    MOCK_METHOD0(close, std::string());
};

TEST (HouseMockTest, dogOut)
{
    MockDoor door;
    // Expect that lock() will be called only once
    // with argument false.
    Expectation unlock = EXPECT_CALL(door, lock(false))
      .Times(1);

    // Expect that open() will be called only once
    // after calling lock(true)
    // returns "Dog Out"
    Expectation openDoor = EXPECT_CALL(door, open())
    .Times(1)
    .After(unlock)
    .WillOnce(Return("Door Opened"));

    // Expect that close() will be called only once
    // after calling open()
    Expectation closeDoor = EXPECT_CALL(door, close())
    .Times(1)
    .After(openDoor)
    .WillOnce(Return("Door Closed"));

    // Expect that lock() will be called only once
    // with argument false
    // after door.open()
    EXPECT_CALL(door, lock(true))
      .Times(1)
      .After(closeDoor);

    House* house = new House(&door);
    house->dogOut();
    EXPECT_FALSE(house->dogInside());
}

TEST (HouseMockTest, wrongOrder)
{
    MockDoor door;

    Expectation unlock = EXPECT_CALL(door, lock(false))
      .Times(1);

    Expectation openDoor = EXPECT_CALL(door, open())
    .Times(1)
    .After(unlock)
    .WillOnce(Return("Door Opened"));

    Expectation closeDoor = EXPECT_CALL(door, close())
    .Times(1)
    .After(openDoor)
    .WillOnce(Return("Door Closed"));

    EXPECT_CALL(door, lock(true))
      .Times(1)
      .After(closeDoor);

    House* house = new House_WrongOrder(&door);
    house->dogOut();
}

TEST (HouseMockTest, missingAction)
{
    MockDoor door;

    Expectation unlock = EXPECT_CALL(door, lock(false))
      .Times(1);

    Expectation openDoor = EXPECT_CALL(door, open())
    .Times(1)
    .After(unlock)
    .WillOnce(Return("Door Opened"));

    Expectation closeDoor = EXPECT_CALL(door, close())
    .Times(1)
    .After(openDoor)
    .WillOnce(Return("Door Closed"));

    EXPECT_CALL(door, lock(true))
      .Times(1)
      .After(closeDoor);

    House* house = new House_MissingAction(&door);
    house->dogOut();
}
