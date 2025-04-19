#include <iostream>
#include <vector>
using std::vector;

double get_optimal_value(long long capacity, vector<long long> weights, vector<long long> values)
{
  double value = 0.0;

  while (capacity > 0 && !weights.empty())
  {
    double mvp = -1;
    int mvpIdx = -1;
    for (int i = 0; i < weights.size(); i++)
    {
      if (weights[i] > 0)
      {
        if (static_cast<double>(values[i]) / weights[i] > mvp)
        {
          mvp = static_cast<double>(values[i]) / weights[i];
          mvpIdx = i;
        }
      }
    }
    if (mvpIdx == -1)
    {
      break;
    }
    
    int amount = std::min(weights[mvpIdx], capacity);
    value += static_cast<double>(amount) * values[mvpIdx]/weights[mvpIdx];
    capacity -= amount;
    values.erase(values.begin() + mvpIdx);
    weights.erase(weights.begin() + mvpIdx);
  }

  return value;
}

int main()
{
  int n;
  long long capacity;
  std::cin >> n >> capacity;
  vector<long long> values(n);
  vector<long long> weights(n);
  for (int i = 0; i < n; i++)
  {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
