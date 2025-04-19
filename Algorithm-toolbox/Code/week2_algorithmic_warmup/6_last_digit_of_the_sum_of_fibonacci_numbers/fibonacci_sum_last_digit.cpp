#include <iostream>
#include <vector>
int fibonacci_sum_naive(long long n)
{
    if (n <= 1)
        return n;

    int ctr = 1;
    std::vector<char> lasts = {0, 1};
    long long sum = 0;
    bool repeated = 0;
    char last;
    while (ctr++ < n)
    {
        last = (lasts[ctr - 1] + lasts[ctr - 2]) % 10;
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
        long long iterations = (long long)n / lasts.size();
        for (int i = 0; i < lasts.size(); i++)
        {
            sum = (sum +lasts[i]) %10;
        }
        sum = (sum * iterations) % 10;

        int idx = n % lasts.size();
        for (int i = 0; i <= idx; i++)
        {
            sum = (sum + lasts[i]) % 10;
        }
    }else{
        for (int i = 0; i < lasts.size(); i++)
        {
            sum = (sum +lasts[i]) %10;
        }
        
    }

    return sum % 10;
}

int main()
{
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_naive(n);
}
