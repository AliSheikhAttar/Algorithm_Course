#include <iostream>
#include <vector>

using std::vector;

vector<long long> optimal_summands(long long n)
{
  vector<long long> summands;
  long long sum = 0;
  for (int i = 1; i <= static_cast<int>(n / 2) && sum < n; i++)
  {
    summands.push_back(i);
    sum += i;
  }
  if (sum != n)
  {
      while (!summands.empty() && (n - sum) <= static_cast<long long>(summands.size())){
        sum -= summands.back();
        summands.pop_back();
      }
      summands.push_back(n-sum);
      
  }

  return summands;
}

int main()
{
  long long n;
  std::cin >> n;
  vector<long long> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i)
  {
    std::cout << summands[i] << ' ';
  }
}
