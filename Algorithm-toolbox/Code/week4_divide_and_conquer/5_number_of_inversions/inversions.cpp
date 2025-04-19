#include <iostream>
#include <vector>

using std::vector;

int counter = 0;
long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right)
{
  long long number_of_inversions = 0;
  if (right <= left + 1)
    return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);
  // write your code here
  return number_of_inversions;
}

void merge(vector<int> &a, int l, int pivot, int r)
{
  vector<int> merged = {};
  int i = l;
  int j = pivot;
  while (i < pivot && j <= r)
  {
    if (a[i] <= a[j])
    {
      merged.push_back(a[i]);
      i++;
    }
    else if (a[j] < a[i])
    {
      merged.push_back(a[j]);
      counter += (pivot - i);
      j++;
    }
  }
  while (i < pivot)
  {
    merged.push_back(a[i]);
    i++;
  }
  while (j <= r)
  {
    merged.push_back(a[j]);
    j++;
  }

  for (size_t i = 0; i < merged.size(); i++)
  {
    a[i + l] = merged[i];
  }
}

void merge_sort(vector<int> &a, int l, int r)
{
  if (l - r >= 0)
    return;

  int pivot = (l + r) / 2;

  merge_sort(a, l, pivot);
  merge_sort(a, pivot + 1, r);
  merge(a, l, pivot + 1, r);
}

int main()
{
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++)
  {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  merge_sort(a, 0, a.size() - 1);
  std::cout << counter << '\n';
}
