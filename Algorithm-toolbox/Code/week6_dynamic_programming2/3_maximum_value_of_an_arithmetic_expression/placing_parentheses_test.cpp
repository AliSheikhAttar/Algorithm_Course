#include <cassert>
#include <string>
#include <iostream>
#include "placing_parentheses.h"

void test_get_maximum_value()
{
    // Test Case 1: Simple addition
    std::cout << "Testing 1+2: ";
    assert(get_maximum_value("1+2") == 3);
    std::cout << "Passed!" << std::endl;

    // Test Case 2: Simple multiplication
    std::cout << "Testing 2*3: ";
    assert(get_maximum_value("2*3") == 6);
    std::cout << "Passed!" << std::endl;

    // Test Case 3: Simple subtraction
    std::cout << "Testing 5-3: ";
    assert(get_maximum_value("5-3") == 2);
    std::cout << "Passed!" << std::endl;

    // Test Case 4: Three numbers
    std::cout << "Testing 1+2*3: ";
    assert(get_maximum_value("1+2*3") == 9); // (1+2)*3 = 9
    std::cout << "Passed!" << std::endl;

    // Test Case 5: More complex expression
    std::cout << "Testing 5-8+7*4-8+9: ";
    assert(get_maximum_value("5-8+7*4-8+9") == 200); // 5-(8+(7*(4-(8+9)))) = 200
    std::cout << "Passed!" << std::endl;

    // Test Case 6: Single digit
    std::cout << "Testing 5: ";
    assert(get_maximum_value("5") == 5);
    std::cout << "Passed!" << std::endl;

    // Test Case 7: All operations
    std::cout << "Testing 1+2-3*4: ";
    std::cout << "result: " << get_maximum_value("1+2-3*4") << std::endl;
    assert(get_maximum_value("1+2-3*4") == 0); // (1+2-3)*4 = 0
    std::cout << "Passed!" << std::endl;

    // Test Case 8: Large numbers
    std::cout << "Testing 9*9*9: ";
    assert(get_maximum_value("9*9*9") == 729); // (9*9)*9 = 729
    std::cout << "Passed!" << std::endl;

    std::cout << "\nAll tests passed!" << std::endl;
}

// int main()
// {
//     test_get_maximum_value();
//     return 0;
// }