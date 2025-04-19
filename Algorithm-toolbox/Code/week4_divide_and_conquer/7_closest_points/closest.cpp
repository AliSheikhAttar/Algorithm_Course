#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

using std::min;
using std::pair;
using std::string;
using std::vector;

constexpr double distance(const pair<long long, long long> &a,
                          const pair<long long, long long> &b)
{
  return sqrt((b.first - a.first) * (b.first - a.first) +
              (b.second - a.second) * (b.second - a.second));
}

double minimal_distance_sectors(vector<pair<long long, long long>> &points, long long l, long long r, long long pivot, pair<long long, long long> mid_point, double d)
{
  long long i = l;
  long long j = pivot;
  vector<pair<long long, long long>> y_sorted;
  while (i < pivot && j <= r)
  {
    if (points[i].second <= points[j].second)
    {
      y_sorted.push_back(points[i]);
      i++;
    }
    else
    {
      y_sorted.push_back(points[j]);
      j++;
    }
  }
  while (i < pivot)
  {
    y_sorted.push_back(points[i]);
    i++;
  }
  while (j <= r)
  {
    y_sorted.push_back(points[j]);
    j++;
  }
  std::copy(y_sorted.begin(), y_sorted.end(), points.begin() + l);

  vector<pair<long long, long long>> valids;

  for (long long i = l; i <= r; i++)
  {
    if (abs(points[i].first - mid_point.first) < d)
    {
      valids.emplace_back(points[i].first, points[i].second);
    }
  }

  double best_d = d;
  for (long long i = 0; i < valids.size(); i++)
  {
    for (long long j = 1; j <= 7 && (i + j) < valids.size(); j++)
    {
      best_d = min(best_d, distance(valids[i], valids[i + j]));
    }
  }
  return best_d;
}

double minimal_distance(vector<pair<long long, long long>> &points, long long l, long long r)
{
  if (r == l)
  {
    return std::numeric_limits<double>::max();
  }

  long long pivot = (l + r) / 2;
  auto mid_point = points.at(pivot);
  double d = min(minimal_distance(points, l, pivot),
                 minimal_distance(points, pivot + 1, r));
  double d1 = minimal_distance_sectors(points, l, r, pivot + 1, mid_point, d);

  return min(d, d1);
}

int main()
{
  size_t n;
  std::cin >> n;
  vector<std::pair<long long, long long>> points(n);
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> points[i].first >> points[i].second;
  }
  sort(points.begin(), points.end());

  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(points, 0, points.size() - 1) << "\n";
}
