#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <climits>

using std::max;
using std::min;
using std::string;
using std::vector;

long long eval(long long a, long long b, char op)
{
  if (op == '*')
  {
    return a * b;
  }
  else if (op == '+')
  {
    return a + b;
  }
  else if (op == '-')
  {
    return a - b;
  }
  else
  {
    assert(0);
  }
}
void min_max(const string &exp, int i, int j, vector<vector<long long>> &max_table, vector<vector<long long>> &min_table)
{
  long long min = LLONG_MAX;
  long long max = LLONG_MIN;
  for (int k = i; k < j; k += 1)
  {
    long long a = eval(max_table[i][k], max_table[k + 1][j], exp[2 * k + 1]);
    long long b = eval(max_table[i][k], min_table[k + 1][j], exp[2 * k + 1]);
    long long c = eval(min_table[i][k], max_table[k + 1][j], exp[2 * k + 1]);
    long long d = eval(min_table[i][k], min_table[k + 1][j], exp[2 * k + 1]);
    if (a > max)
      max = a;
    if (b > max)
      max = b;
    if (c > max)
      max = c;
    if (d > max)
      max = d;

    if (a < min)
      min = a;
    if (b < min)
      min = b;
    if (c < min)
      min = c;
    if (d < min)
      min = d;
  }
  max_table[i][j] = max;
  min_table[i][j] = min;
}

long long get_maximum_value(const string &exp)
{
  vector<vector<long long>> max_table(exp.size() / 2 + 1, vector<long long>(exp.size() / 2 + 1, 0));
  vector<vector<long long>> min_table(exp.size() / 2 + 1, vector<long long>(exp.size() * 2 + 1, 0));
  for (int i = 0; i < exp.size() / 2 + 1; i += 1)
  {
    max_table[i][i] = exp[i * 2] - '0';
    min_table[i][i] = exp[i * 2] - '0';
  }
  for (int s = 1; s < exp.size() / 2 + 1; s += 1)
  {
    for (int i = 0; i < exp.size() / 2 + 1 - s; i += 1)
    {
      min_max(exp, i, i + s, max_table, min_table);
    }
  }
  return max_table[0][exp.size() / 2];
}

int main()
{
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
