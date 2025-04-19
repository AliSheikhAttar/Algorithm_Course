#include <iostream>
#include <vector>

int get_change(int m)
{
  auto a = std::vector<int>(m+1);
  a[0] = 0;
  a[1] = 1;
  for (size_t i = 2; i < m + 1; i++)
  {
    int min = __INT_MAX__;
    for (auto coin : {1, 3, 4})
    {
      if (i >= coin)
      {
        if (a[i - coin] + 1 < min)
        {
          min = a[i - coin] + 1;
        }
      }
    }
    a[i] = min;
  }
  return a[m];
}

int main()
{
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
