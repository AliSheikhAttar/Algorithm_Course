#include <iostream>
#include <vector>
#include <cstdlib>
#include <tuple> // Required for std::tuple

using std::swap;
using std::vector;

std::tuple<int, int> partition2(vector<int> &a, int l, int r)
{
  std::tuple<int, int> res;
  int x = a[l];
  int j = l, k = l;
  for (int i = l + 1; i <= r; i++)
  {
    if (a[i] <= x)
    {
      j++;
      swap(a[i], a[j]);
    }
  }
  for (int i = l + 1; i <= j; i++)
  {
    if (a[i] < x)
    {
      k++;
      swap(a[i], a[k]);
    }
  }
  swap(a[l], a[k]);
  return std::make_tuple(k, j);
}

void randomized_quick_sort(vector<int> &a, int l, int r)
{
  if (l >= r)
  {
    return;
  }
  std::tuple<int, int> myTuple;
  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  myTuple = partition2(a, l, r);

  randomized_quick_sort(a, l, std::get<0>(myTuple) - 1);
  randomized_quick_sort(a, std::get<1>(myTuple) + 1, r);
}

int main()
{
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i)
  {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i)
  {
    std::cout << a[i] << ' ';
  }
}
