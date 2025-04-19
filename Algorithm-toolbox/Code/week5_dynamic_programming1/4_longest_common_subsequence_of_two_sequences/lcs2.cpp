#include <iostream>
#include <vector>

using std::vector;

int lcs2(vector<int> &a, vector<int> &b)
{
  int n = a.size() + 1;
  int m = b.size() + 1;
  vector<vector<int>> arr(n, std::vector<int>(m, 0));
  for (size_t j = 1; j < m; j++)
  {
    for (size_t i = 1; i < n; i++)
    {
      int max_insert_del = std::max(arr[i][j - 1], arr[i - 1][j]);
      if (a[i - 1] == b[j - 1])
      {
        arr[i][j] = std::max(arr[i - 1][j - 1] + 1, max_insert_del);
      }
      else
      {
        arr[i][j] = std::max(arr[i - 1][j - 1], max_insert_del);
      }
    }
  }

  return arr[n - 1][m - 1];
}

int main()
{
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++)
  {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
