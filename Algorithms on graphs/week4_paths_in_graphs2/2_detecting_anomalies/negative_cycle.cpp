#include <iostream>
#include <vector>
#include <functional>
#include <climits>
#include <limits>
#include <queue>

using ll = long long;
typedef std::vector<ll> vec;
using std::queue;
using std::vector;

static const ll INF = std::numeric_limits<int>::max();

struct Edge
{
  int u, v;
  ll w;
};

bool bellmanFord(
    int n,
    const std::vector<Edge> &edges)
{
  std::vector<ll> dist(n, INF);
  dist[0] = 0;

  for (int i = 1; i < n; ++i)
  {
    bool any = false;
    for (auto &e : edges)
    {
      if ( dist[e.v] > dist[e.u] + e.w)
      {
        dist[e.v] = dist[e.u] + e.w;
        any = true;
      }
    }
    if (!any)
      break;
  }

  for (auto &e : edges)
  {
    if (dist[e.v] > dist[e.u] + e.w)
      return true;
  }
  return false;
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  std::vector<Edge> edges(m);

  for (int i = 0; i < m; i++)
  {
    std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
  }
  std::cout << bellmanFord(n, edges);
}
