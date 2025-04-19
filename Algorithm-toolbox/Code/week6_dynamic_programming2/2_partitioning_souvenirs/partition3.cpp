#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

bool optimal_weight(long long W, vector<long long> &w)
{
  auto vals_2_del = vector<int>(w.size(), 0);
  vector<vector<int>> values(w.size() + 1, vector<int>((W + 1), 0));
  for (size_t i = w[0]; i < (W + 1); i++)
  {
    values[1][i] = w[0];
  }
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
  if (values[w.size()][W] != W)
  {
    return 0;
  }
  int i = w.size();
  int j = W;
  int weight_remaining = W;
  while (i > 0 and j > 0)
  {
    if (w[i - 1] + values[i - 1][j - w[i - 1]] == weight_remaining)
    {
      vals_2_del.at(i - 1) = 1;
      weight_remaining -= w[i - 1];
      j = j - w[i - 1];
      i = i - 1;
    }
    else if (values[i - 1][j] == weight_remaining)
    {
      i = i - 1;
    }
  }
  for (int x = (vals_2_del.size() - 1); x >= 0; x--)
  {
    if (vals_2_del[x] == 1)
    {
      w.erase(w.begin() + x);
    }
  }
  return 1;
}

int partition3(vector<long long> &A)
{
  long long sum = 0;
  for (size_t i = 0; i < A.size(); i++)
  {
    sum += A[i];
  }
  if (sum % 3 != 0)
  {
    return 0;
  }
  sort(A.begin(), A.end());
  auto knapsack = optimal_weight(sum / 3, A);
  if (knapsack == 0)
  {
    return 0;
  }

  return optimal_weight(sum / 3, A);
}

int main()
{
  long long n;
  std::cin >> n;
  vector<long long> A(n);
  for (size_t i = 0; i < A.size(); ++i)
  {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
