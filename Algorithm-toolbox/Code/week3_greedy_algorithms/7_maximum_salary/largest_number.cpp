#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

string largest_number(vector<string> a)
{

  struct
  {
    bool operator()(string a, string b) const
    {
      return a + b > b + a;
      if (a == b)
        return false;

      int len = 0;
      if (a.size() > b.size())
        len = b.size();
      else
        len = a.size();
      int i;
      for (i = 0; i < len; i++)
      {
        if (a[i] > b[i])
          return true;
        else if (a[i] < b[i])
          return false;
      }
      if (a.size() < b.size())
        return b[i] < b[0];
      return a[i] > a[0];
    }
  } biggerComb;
  std::sort(a.begin(), a.end(), biggerComb);
  std::stringstream ret;
  for (size_t i = 0; i < a.size(); i++)
  {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main()
{
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++)
  {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
