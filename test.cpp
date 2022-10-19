#include "gtest/gtest.h"
#include "dice.h"

using namespace DiceSpace;

TEST(Dice_vector, constructor) {
    Dice_vector vector(100);
    ASSERT_EQ(vector.get_max_size(), 100);
    ASSERT_EQ(vector.get_amount(), 0);
    for (int i = 0; i < vector.get_max_size(); ++i) {
        ASSERT_EQ(vector.get_value(i), 0);
    }
    ASSERT_ANY_THROW(Dice_vector vector1(-8));
    ASSERT_ANY_THROW(Dice_vector vector1(0));
}

TEST(Dice_vector, insert_dice) {
    Dice_vector vector(5);
    vector.insert_dice();
    ASSERT_EQ(vector.get_amount(), 1);
    ASSERT_EQ(vector.get_max_size(), 5);
    ASSERT_NEAR(vector.get_value(0), 3.5, 2.5);
    vector.insert_dice();
    vector.insert_dice();
    ASSERT_EQ(vector.get_amount(), 3);
    ASSERT_EQ(vector.get_max_size(), 5);
    ASSERT_NEAR(vector.get_value(1), 3.5, 2.5);
    ASSERT_NEAR(vector.get_value(2), 3.5, 2.5);

}

TEST(Dice_vector, remove_dice) {
    Dice_vector vector(5);
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    ASSERT_EQ(vector.get_amount(), 4);
    ASSERT_EQ(vector.get_max_size(), 5);
    vector.remove_dice(3);
    ASSERT_EQ(vector.get_amount(), 3);
    ASSERT_EQ(vector.get_max_size(), 5);
}

TEST(Dice_vector, throw_dices) {
    Dice_vector vector(5);
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.throw_dice();
    for (int i = 0; i < vector.get_max_size(); ++i) {
        ASSERT_NEAR(vector.get_value(i), 3.5, 2.5);
    }
}

TEST(Dice_vector, find_dice) {
    Dice_vector vector(10);
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    ASSERT_EQ(vector[6], vector.get_value(6));
}

TEST(Dice_vector, sum_all_dices) {
    Dice_vector vector(4);
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    ASSERT_EQ(*vector, vector.sum_all_dices());
    vector.remove_all_dices();
    vector.insert_dice();
    vector.insert_value(3);
    vector.insert_dice();
    vector.insert_value(6);
    vector.insert_dice();
    vector.insert_value(1);
    vector.insert_dice();
    vector.insert_value(2);
    ASSERT_EQ(*vector, 12);
}

TEST(Dice_vector, remove_all_dices) {
    Dice_vector vector(6);
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.remove_all_dices();
    for (int i = 0; i < vector.get_max_size(); ++i) {
        ASSERT_EQ(vector.get_value(i), 0);
    }
}

TEST(Dice_vector, insert_with_value) {
    Dice_vector vector(10);
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector.insert_dice();
    vector += 5;
    ASSERT_EQ(vector.get_value(4), 5);
    vector += 2;
    ASSERT_EQ(vector.get_value(5), 2);
    ASSERT_ANY_THROW(vector += 9);
}

int test_main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}