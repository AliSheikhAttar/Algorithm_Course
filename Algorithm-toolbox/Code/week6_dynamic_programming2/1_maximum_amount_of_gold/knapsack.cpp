#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w)
{
  vector<vector<int>> values(w.size() + 1, vector<int>((W + 1), 0));
  for (size_t i = w[0]; i < (W + 1); i++){ values[1][i] = w[0];}
  for (size_t i = 2; i < (w.size() + 1); i++)
  {
    for (size_t j = 1; j < (W + 1); j++)
    {
      values[i][j] = values[i - 1][j];
      if (w[i - 1] <= j)
      {
        int val = values[i - 1][j - w[i - 1]] + w[i - 1];
        if (val > values[i][j])
          values[i][j] = val;
      }
    }
  }
  return values[w.size()][W];
}

int main()
{
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++)
  {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
