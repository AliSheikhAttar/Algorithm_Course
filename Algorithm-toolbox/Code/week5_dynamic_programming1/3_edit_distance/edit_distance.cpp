#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

long long edit_distance(const string &str1, const string &str2)
{
  long long n = str1.size() + 1;
  long long m = str2.size() + 1;
  vector<vector<long long>> arr(n, std::vector<long long>(m, 0));
  for (size_t i = 0; i < n; i++)
  {
    arr[i][0] = i;
  }
  for (size_t i = 0; i < m; i++)
  {
    arr[0][i] = i;
  }
  for (size_t j = 1; j < m; j++)
  {
    for (size_t i = 1; i < n; i++)
    {
      int min_insert_del = std::min(arr[i][j - 1], arr[i - 1][j]);
      if (str2[j - 1] == str1[i - 1])
      {
        arr[i][j] = arr[i - 1][j - 1] < (min_insert_del + 1) ? arr[i - 1][j - 1] : (min_insert_del + 1);
      }
      else
      {
        arr[i][j] = (arr[i - 1][j - 1] + 1) < (min_insert_del + 1) ? (arr[i - 1][j - 1] + 1) : (min_insert_del + 1);
      }
    }
  }

  return arr[n - 1][m - 1];
}

int main()
{
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
