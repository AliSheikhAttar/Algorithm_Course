#include <cassert>
#include <vector>
#include <iostream>
#include <climits> // for INT_MAX

using std::vector;

// Function declarations (copy from original file)
vector<vector<int>> optimal_weight(int W, const vector<int> &w);
int partition3(vector<int> &A);

void test_partition3()
{
    // Test Case 1: Simple case that should return 0
    vector<int> test1 = {3, 3, 3, 3};
    std::cout << "Testing {3, 3, 3, 3}: ";
    assert(partition3(test1) == 0);
    std::cout << "Passed!" << std::endl;

    // Test Case 2: Valid partition with equal numbers
    vector<int> test2 = {3, 3, 3, 3, 3, 3}; // Can be split into {3,3}, {3,3}, {3,3}
    std::cout << "Testing {3, 3, 3, 3, 3, 3}: ";
    assert(partition3(test2) == 1);
    std::cout << "Passed!" << std::endl;

    // Test Case 3: Single number
    vector<int> test3 = {3};
    std::cout << "Testing {3}: ";
    assert(partition3(test3) == 0);
    std::cout << "Passed!" << std::endl;

    // Test Case 4: Empty array
    vector<int> test4 = {};
    std::cout << "Testing empty array: ";
    assert(partition3(test4) == 1); // Empty array sum is 0, which is divisible by 3
    std::cout << "Passed!" << std::endl;

    // Test Case 5: Negative numbers
    vector<int> test5 = {-3, -3, 3, 3, 0, 0}; // Can be split into {-3,3}, {-3,3}, {0,0}
    std::cout << "Testing {-3, -3, 3, 3, 0, 0}: ";
    assert(partition3(test5) == 1);
    std::cout << "Passed!" << std::endl;

    // Test Case 6: Large numbers
    vector<int> test6 = {1000000, 1000000, 1000000, 1000000, 1000000, 1000000};
    std::cout << "Testing large equal numbers: ";
    assert(partition3(test6) == 1);
    std::cout << "Passed!" << std::endl;

    // Test Case 7: Complex case that looks possible but isn't
    vector<int> test7 = {2, 3, 4, 3, 3, 3}; // Can be split into {2,4}, {3,3}, {3,3}
    std::cout << "Testing {2, 3, 4, 3, 3, 3}: ";
    assert(partition3(test7) == 1); // Changed from 0 to 1
    std::cout << "Passed!" << std::endl;

    // Let's add a new truly impossible case
    vector<int> test7b = {2, 3, 4, 3, 3, 4}; // Sum is 19, not divisible by 3
    std::cout << "Testing {2, 3, 4, 3, 3, 4}: ";
    assert(partition3(test7b) == 0);
    std::cout << "Passed!" << std::endl;

    // Test Case 8: All zeros
    vector<int> test8 = {0, 0, 0, 0};
    std::cout << "Testing all zeros: ";
    assert(partition3(test8) == 1);
    std::cout << "Passed!" << std::endl;

    // Test Case 9: Complex valid partition
    vector<int> test9 = {1, 2, 3, 2, 2, 2, 3}; // Can be split into {1,2,2}, {2,3}, {2,3}
    std::cout << "Testing {1, 2, 3, 2, 2, 2, 3}: ";
    assert(partition3(test9) == 1);
    std::cout << "Passed!" << std::endl;

    // Test Case 10: Simple case of three equal numbers
    vector<int> test10 = {1, 1, 1};
    std::cout << "Testing {1, 1, 1}: ";
    assert(partition3(test10) == 1); // Changed from 0 to 1 as {1}, {1}, {1} is valid
    std::cout << "Passed!" << std::endl;

    // Let's add a new test case that truly can't be partitioned
    vector<int> test10b = {1, 1, 2}; // Sum is 4, not divisible by 3
    std::cout << "Testing {1, 1, 2}: ";
    assert(partition3(test10b) == 0);
    std::cout << "Passed!" << std::endl;

    // Test Case 11: Case with repeated numbers
    vector<int> test11 = {4, 4, 4, 4, 4, 4, 4, 4, 4}; // Can be split into three groups of three 4s
    std::cout << "Testing nine 4s: ";
    assert(partition3(test11) == 1); // Changed from 0 to 1 as it can be split into {4,4,4}, {4,4,4}, {4,4,4}
    std::cout << "Passed!" << std::endl;

    // Test Case 12: Large but safe values
    vector<int> test12 = {1000, 1000, 1000, 1000, 1000, 1000}; // Can be split into {1000,1000}, {1000,1000}, {1000,1000}
    std::cout << "Testing large values: ";
    assert(partition3(test12) == 1);
    std::cout << "Passed!" << std::endl;

    // Test Case 13: Complex case with multiple numbers that can be split into {3,6,4}, {9,1,3}, {9,1,3}
    vector<int> test13 = {3, 6, 4, 1, 9, 6, 9, 1};
    std::cout << "Testing 3 6 4 1 9 6 9 1: ";
    assert(partition3(test13) == 1);
    std::cout << "Passed!" << std::endl;

    // Test Case 14: Simple case with sum not divisible by 3 (sum = 31)
    vector<int> test14 = {1, 30};
    std::cout << "Testing 1 30: ";
    assert(partition3(test14) == 0);
    std::cout << "Passed!" << std::endl;

    // Test Case 15: Large test case with many numbers that can be split into {25,7}, {19,12,1}, {10,8,7,5,2}
    vector<int> test15 = {1, 2, 3, 4, 5, 5, 7, 7, 8, 10, 12, 19, 25};
    std::cout << "Testing 1 2 3 4 5 5 7 7 8 10 12 19 25: ";
    assert(partition3(test15) == 1);
    std::cout << "Passed!" << std::endl;

    std::cout << "\nAll tests passed!" << std::endl;
}

// int main()
// {
//     test_partition3();
//     return 0;
// }