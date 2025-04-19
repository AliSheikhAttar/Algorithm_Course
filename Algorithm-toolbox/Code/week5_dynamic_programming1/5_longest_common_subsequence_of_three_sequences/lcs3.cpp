#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c)
{
  int n = a.size() + 1;
  int m = b.size() + 1;
  int p = c.size() + 1;
  std::vector<std::vector<std::vector<int>>> arr(n, std::vector<std::vector<int>>(m, std::vector<int>(p, 0)));
  for (size_t k = 1; k < p; k++)
  {
    for (size_t j = 1; j < m; j++)
    {
      for (size_t i = 1; i < n; i++)
      {
        int max_insert_del1 = std::max(arr[i][j - 1][k - 1], arr[i - 1][j][k - 1]);
        int max_insert_del2 = std::max(arr[i][j][k - 1], max_insert_del1);
        int max_insert_del3 = std::max(arr[i - 1][j][k], max_insert_del2);
        int max_insert_del4 = std::max(arr[i][j - 1][k], max_insert_del3);
        int max_insert_del5 = std::max(arr[i - 1][j - 1][k], max_insert_del4);

        if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1])
          arr[i][j][k] = std::max(arr[i - 1][j - 1][k - 1] + 1, max_insert_del5);
        else
          arr[i][j][k] = std::max(arr[i - 1][j - 1][k - 1], max_insert_del5);
      }
    }
  }
  return arr[n - 1][m - 1][p - 1];
}

int main()
{
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++)
  {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++)
  {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++)
  {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
