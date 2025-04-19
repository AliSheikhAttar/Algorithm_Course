#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

long long max_dot_product(vector<long long> a, vector<long long> b)
{
  // write your code here
  long long result = 0;
  while (a.size() > 0)
  {
    int maxi = 0;
    int maxj = 0;
    for (int i = 1; i < a.size(); i++)
    {
      if (a[i] > a[maxi])
      {
        maxi = i;
      }
    }
    for (int i = 1; i < b.size(); i++)
    {
      if (b[i] > b[maxj])
      {
        maxj = i;
      }
    }
    result += a[maxi] * b[maxj];
    a.erase(a.begin() + maxi);
    b.erase(b.begin() + maxj);
  }
  return result;
}

int main()
{
  size_t n;
  std::cin >> n;
  vector<long long> a(n), b(n);
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}
