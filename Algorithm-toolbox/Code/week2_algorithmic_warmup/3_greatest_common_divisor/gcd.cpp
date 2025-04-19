#include <iostream>

long long gcd_naive(long long a, long long b)
{
  bool smallerOne;
  while (a != 0 && b != 0)
  {
    smallerOne = a <= b;
    if (smallerOne)
      b %= a;
    else
      a %= b;
  }
  if (a == 0)
  {
    return b;
  }
  return a;
}

int main()
{
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd_naive(a, b) << std::endl;
  return 0;
}
