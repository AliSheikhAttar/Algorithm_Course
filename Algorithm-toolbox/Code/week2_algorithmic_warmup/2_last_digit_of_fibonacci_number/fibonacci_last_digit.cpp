#include <iostream>
#include <vector>

int get_fibonacci_last_digit_naive(int n)
{
    if (n <= 1)
        return n;

    int ctr = 1;
    std::vector<int> lasts = {0, 1};
    bool repeated = 0;
    while (ctr++ < n)
    {
        char last = (lasts[ctr - 1] + lasts[ctr - 2]) % 10;
        lasts.push_back(last);
        if (last == 1 && lasts[ctr - 1] == 0)
        {
            repeated = true;
            break;
        }
    }
    if (ctr != (n + 1) && repeated)
    {
        lasts.pop_back();
        lasts.pop_back();
        int idx = n % lasts.size();
        return lasts[idx];
    }

    return lasts[ctr - 1] % 10;
}

int main()
{
    int n;
    std::cin >> n;
    int c = get_fibonacci_last_digit_naive(n);
    std::cout << c << '\n';
}
