#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

class HeapBuilder
{
private:
  vector<int> data_;
  vector<pair<int, int>> swaps_;

  void WriteResponse() const
  {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i)
    {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData()
  {
    int n;
    cin >> n;
    data_.resize(n);
    for (int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps()
  {
    swaps_.clear();
    int size = data_.size();
    for (int i = size / 2; i >= 0; i--)
    {
      sift_down(i);
    }
  }

  void sift_down(int i)
  {
    int size = data_.size();
    int minIdx = i;
    int l = 2 * i + 1;
    if (l < size && data_[l] < data_[minIdx])
      minIdx = l;

    int r = 2 * i + 2;
    if (r < size && data_[r] < data_[minIdx])
      minIdx = r;

    if (i != minIdx)
    {
      swaps_.push_back(pair<int, int>{i, minIdx});
      swap(data_[i], data_[minIdx]);
      sift_down(minIdx);
    }
  }

public:
  void Solve()
  {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
