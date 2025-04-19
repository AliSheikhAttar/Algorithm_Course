#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment
{
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments)
{
  vector<int> points;
  while (segments.size() > 0)
  {
    int minRight = 0;
    for (int i = 1; i < segments.size(); i++)
    {
      if (segments[i].end < segments[minRight].end)
      {
        minRight = i;
      }
    }
    vector<int> interSegments = {};
    int bestPoint = segments[minRight].end;
    points.push_back(bestPoint);
    for (int j = 0; j < segments.size(); j++)
    {
      if (segments[j].start <= bestPoint)
      {
        interSegments.push_back(j);
      }
    }
    for (int z = interSegments.size() - 1; z >= 0; z--)
    {
      segments.erase(segments.begin() + interSegments[z]);
    }
  }

  return points;
}

int main()
{
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i)
  {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i)
  {
    std::cout << points[i] << " ";
  }
}
