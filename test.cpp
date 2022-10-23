#include "gtest/gtest.h"
#include "dice.h"

using namespace DiceSpace;

TEST(Dice_vector, constructor) {
    ASSERT_ANY_THROW(Dice_vector vector1(-8));
    ASSERT_ANY_THROW(Dice_vector vector1(0));
    Dice_vector vector(100);
    ASSERT_EQ(vector.get_max_size(), 100);
    ASSERT_EQ(vector.get_amount(), 0);
    for (int i = 0; i < vector.get_max_size(); ++i) {
        ASSERT_EQ(vector.get_value(i), 0);
    }
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
    for (int i = 0 ; i < 4; ++i){
        vector.insert_dice();
    }
    ASSERT_EQ(vector.get_amount(), 4);
    ASSERT_EQ(vector.get_max_size(), 5);
    ASSERT_ANY_THROW(vector.remove_dice(5));
    vector.remove_dice(3);
    ASSERT_EQ(vector.get_amount(), 3);
    ASSERT_EQ(vector.get_max_size(), 5);
}

TEST(Dice_vector, throw_dices) {
    Dice_vector vector(5);
    for (int i = 0 ; i < 5; ++i){
        vector.insert_dice();
    }
    vector.throw_dice();
    for (int i = 0; i < vector.get_max_size(); ++i) {
        ASSERT_NEAR(vector.get_value(i), 3.5, 2.5);
    }
}

TEST(Dice_vector, find_dice) {
    Dice_vector vector(10);
    for (int i = 0 ; i < 7; ++i){
        vector.insert_dice();
    }
    ASSERT_ANY_THROW(vector.find_dice(9));
    ASSERT_EQ(vector[6], vector.get_value(6));
}

TEST(Dice_vector, sum_all_dices) {
    Dice_vector vector(4);
    for (int i = 0 ; i < 6; ++i){
        vector.insert_dice();
        vector.insert_value(i);
    }
    ASSERT_EQ(*vector, 15);
    vector.remove_all_dices();
    for (int i = 0 ; i < 4; ++i){
        vector.insert_dice();
    }
    ASSERT_EQ(*vector, vector.sum_all_dices());
}

TEST(Dice_vector, remove_all_dices) {
    Dice_vector vector(6);
    for (int i = 0 ; i < 6; ++i){
        vector.insert_dice();
    }
    vector.remove_all_dices();
    for (int i = 0; i < vector.get_max_size(); ++i) {
        ASSERT_EQ(vector.get_value(i), 0);
    }
    ASSERT_EQ(vector.get_amount(), 0);
    ASSERT_EQ(vector.get_max_size(), 6);
}

TEST(Dice_vector, insert_with_value) {
    Dice_vector vector(10);
    for (int i = 0 ; i < 6; ++i){
        vector.insert_dice();
    }
    vector += 5;
    ASSERT_EQ(vector.get_value(vector.get_amount() - 1), 5);
    vector += 2;
    ASSERT_EQ(vector.get_value(vector.get_amount() - 1), 2);
    ASSERT_ANY_THROW(vector += 9);
}


TEST(Dice_vector, copy_assignment){
    Dice_vector test(300);
    Dice_vector vector(13);
    for (int i = 0; i < vector.get_max_size(); ++i){
        vector.insert_dice();
    }
    test = vector;
    for (int i = 0; i < test.get_max_size(); ++i){
        ASSERT_EQ(test.get_value(i), vector.get_value(i));
    }
}

TEST(Dice_vector, sum_of_groups) {
    Dice_vector vector1(10);
    Dice_vector vector2(20);
    for (int i = 0; i < 6; ++i) {
        vector1.insert_dice();
        vector2.insert_dice();
    }
    Dice_vector sum(3);
    sum = vector1 + vector2;
    EXPECT_EQ(sum.get_max_size(), vector1.get_max_size() + vector2.get_amount());
    int j = 0;
    int i = 0;
    for (i = 0; i < vector1.get_amount() + vector2.get_amount(); ++i) {
        if (i < vector1.get_amount()) {
            ASSERT_EQ(sum.get_value(i), vector1.get_value(i));
        }
        else {
            ASSERT_EQ(sum.get_value(i), vector2.get_value(j));
            j++;
        }
    }
    for (; i < sum.get_max_size(); ++i){
        ASSERT_EQ(sum.get_value(i), 0);
    }
}

TEST(Dice_vector, move_assignment){
    Dice_vector test(300);
    Dice_vector vector(13);
    Dice_vector temp(200);
    for (int i = 0; i < vector.get_max_size(); ++i){
        vector.insert_dice();
    }
    temp = vector;
    test = std::move(vector);
    for (int i = 0; i < test.get_max_size(); ++i){
        ASSERT_EQ(test.get_value(i), temp.get_value(i));
    }
    ASSERT_EQ(vector.get_max_size(), 0);
    ASSERT_EQ(vector.get_amount(), 0);
    ASSERT_EQ(vector.get_dice_vector(), nullptr);
}

TEST(Dice_vector, copy_constructor){
    Dice_vector vector(13);
    for (int i = 0; i < vector.get_max_size(); ++i){
        vector.insert_dice();
    }
    Dice_vector test(vector);
    for (int i = 0; i < test.get_max_size(); ++i){
        ASSERT_EQ(test.get_value(i), vector.get_value(i));
    }
    ASSERT_EQ(test.get_max_size(), vector.get_max_size());
    ASSERT_EQ(test.get_amount(), vector.get_amount());
}

TEST(Dice_vector, move_constructor){
    Dice_vector vector(13);
    Dice_vector temp(200);
    for (int i = 0; i < vector.get_max_size(); ++i){
        vector.insert_dice();
    }
    temp = vector;
    Dice_vector test(std::move(vector));
    for (int i = 0; i < test.get_max_size(); ++i){
        ASSERT_EQ(test.get_value(i), temp.get_value(i));
    }
    ASSERT_EQ(vector.get_max_size(), 0);
    ASSERT_EQ(vector.get_amount(), 0);
    ASSERT_EQ(vector.get_dice_vector(), nullptr);
}


int test_main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}