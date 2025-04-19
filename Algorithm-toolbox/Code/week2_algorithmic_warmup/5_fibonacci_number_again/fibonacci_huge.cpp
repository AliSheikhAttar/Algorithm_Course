#include <iostream>
#include <vector>

long long get_fibonacci_huge_naive(long long n, long long m)
{
    if (n <= 1)
        return n;

    int ctr = 1;
    std::vector<int> lasts = {0, 1};
    bool repeated = 0;
    while (ctr++ < n)
    {
        long long last = (lasts[ctr - 1] + lasts[ctr - 2]);
        last %= m;
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
        return lasts[idx] % m;
    }

    return lasts[ctr - 1] % m;
}

int main()
{
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_naive(n, m) << '\n';
}
