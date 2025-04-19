#include <iostream>


long long gcd(long long a, long long b)
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
long long lcm_naive(int a, int b) {
  int gcdVar = gcd(a, b);
  if (gcdVar == 1)
  {
    return (long long) a*b;
  }
  if (gcdVar == a || gcdVar == b)
  {
    int res = a == gcdVar ? b : a;
    return res;
  }

  int bigger = a <= b ? b : a;
  int smaller = a == bigger ? b : a;
  
  
  for (long l = smaller; l <= ((long long) a * b - smaller); l+=smaller)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_naive(a, b) << std::endl;
  return 0;
}
