#include <iostream>
#include <vector>
#include <algorithm>

long long MaxPairwiseProduct(const std::vector<int> &numbers)
{
    int n = numbers.size();

    auto maxIdx1 = 0;
    auto maxIdx2 = 1;
    bool firstbigger;
    for (int i = 2; i < n; ++i)
    {
        firstbigger = numbers[maxIdx1] >= numbers[maxIdx2];

        if (firstbigger)
            maxIdx2 = numbers[maxIdx2] < numbers[i] ? i : maxIdx2;
        else
            maxIdx1 = numbers[maxIdx1] < numbers[i] ? i : maxIdx1;
    }
    return (long long)numbers[maxIdx1] * numbers[maxIdx2];
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
