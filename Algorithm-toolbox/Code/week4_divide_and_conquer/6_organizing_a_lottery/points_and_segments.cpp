#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points)
{
  vector<int> cnt;

  vector<std::pair<int, int>> axis;
  unordered_map<int, int> point_values;

  axis.reserve(starts.size() * 2 + points.size());
  point_values.reserve(points.size());

  for (size_t i = 0; i < starts.size(); i++)
  {
    axis.push_back(make_pair(starts[i], 0));
    axis.push_back(make_pair(ends[i], 2));
  }
  for (auto point : points)
  {
    axis.push_back(make_pair(point, 1));
  }

  sort(axis.begin(), axis.end());
  int counter = 0;
  for (auto data_point : axis)
  {
    if (data_point.second == 0)
    {
      counter++;
    }
    else if (data_point.second == 1)
    {
      point_values[data_point.first] = counter;
    }
    else
    {
      counter--;
    }
  }
  for (auto point : points)
  {
    cnt.push_back(point_values[point]);
  }

  return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points)
{
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++)
  {
    for (size_t j = 0; j < starts.size(); j++)
    {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++)
  {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++)
  {
    std::cin >> points[i];
  }
  // use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++)
  {
    std::cout << cnt[i] << ' ';
  }
}
