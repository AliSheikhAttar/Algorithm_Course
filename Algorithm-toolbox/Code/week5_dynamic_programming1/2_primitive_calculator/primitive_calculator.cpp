#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<std::pair<int, int>> optimal_sequence(int n)
{
  std::vector<std::pair<int, int>> sequence = {{0, 0}, {0, 1}, {1, 1}, {1, 1}}; // 4 2 2,  8 4 3
  int i = 3;
  while (++i <= n)
  {
    int min = __INT_MAX__;
    int min_idx = 3;
    if (i % 3 == 0)
    {
      if (sequence[i / 3].first + 1 < min)
      {
        min = sequence[i / 3].first + 1;
        min_idx = i / 3;
      }
    }
    else if (i % 2 == 0)
    {
      if (sequence[i / 2].first + 1 < min)
      {
        min = sequence[i / 2].first + 1;
        min_idx = i / 2;
      }
    }
    if (sequence[i - 1].first + 1 < min)
    {
      min = sequence[i - 1].first + 1;
      min_idx = i - 1;
    }

    sequence.push_back({min, min_idx});
  }
  return sequence;
}

int main()
{
  int n;
  std::cin >> n;
  vector<std::pair<int, int>> sequence = optimal_sequence(n);
  vector<int> res = {n};
  int i = n;
  while (sequence[i].first > 0)
  {
    res.push_back(sequence[i].second);
    i = sequence[i].second;
  }
  std::cout << res.size()-1 << std::endl;
  reverse(res.begin(), res.end());
  for (size_t i = 0; i < res.size(); i++)
  {
    std::cout << res[i] << " ";
  }
}
