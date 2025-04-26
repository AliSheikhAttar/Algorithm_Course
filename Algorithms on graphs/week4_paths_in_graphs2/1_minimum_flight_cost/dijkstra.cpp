#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <climits> 

using ll = long long;
typedef std::vector<ll> vec;
using std::vector;

ll distance(vector<vec> &adj, vector<vec> &cost, int s, int t)
{
  int n = adj.size();
  vec dist(n, LLONG_MAX);
  vector<bool> visited(n, false);

  std::priority_queue<
      std::pair<ll, int>,
      std::vector<std::pair<ll, int>>,
      std::greater<std::pair<ll, int>>>
      pq;

  dist[s] = 0;
  pq.push(std::make_pair(0LL, s));

  while (!pq.empty())
  {
    std::pair<ll, int> top = pq.top();
    pq.pop();

    ll d = top.first;
    int u = top.second;

    if (visited[u])
      continue;
    visited[u] = true;
    if (u == t)
      break;

    for (size_t i = 0; i < adj[u].size(); ++i)
    {
      int v = static_cast<int>(adj[u][i]);
      ll w = cost[u][i];
      if (!visited[v] && dist[v] > d + w)
      {
        dist[v] = d + w;
        pq.push(std::make_pair(dist[v], v));
      }
    }
  }

  return (dist[t] == LLONG_MAX ? -1LL : dist[t]);
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  vector<vec> adj(n, vec());
  vector<vec> cost(n, vec());

  for (int i = 0; i < m; i++)
  {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }

  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t) << "\n";

  return 0;
}
