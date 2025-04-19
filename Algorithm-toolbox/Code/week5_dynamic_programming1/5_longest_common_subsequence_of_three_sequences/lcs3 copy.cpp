#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c)
{

  int n = a.size() + 1;
  int m = b.size() + 1;
  int p = c.size() + 1;
  vector<vector<vector<int>>> arr(n, std::vector<vector<int>>(m, std::vector<int>(p, 0)));
  for (size_t k = 1; k < p; k++)
  {
    for (size_t j = 1; j < m; j++)
    {
      for (size_t i = 1; i < n; i++)
      {

        auto insert_del = std::vector<int>{
            arr[i - 1][j][k],
            arr[i - 1][j][k - 1],
            arr[i][j - 1][k],
            arr[i][j - 1][k - 1],
            arr[i - 1][j - 1][k],
        };
        auto max_insert_del_iterator = std::max_element(insert_del.begin(), insert_del.end());
        int max_insert_del = *max_insert_del_iterator;
        if (a[i - 1] == b[j - 1] == c[k - 1])
        {
          arr[i][j][k] = std::max(arr[i - 1][j - 1][k - 1] + 1, max_insert_del);
        }
        else
        {
          arr[i][j][k] = std::max(arr[i - 1][j - 1][k - 1], max_insert_del);
        }
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
