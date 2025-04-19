#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::swap;
using std::vector;

class JobQueue
{
private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;
  vector<long long> next_free_time_;
  vector<long long> workers_;

  void WriteResponse() const
  {
    for (int i = 0; i < jobs_.size(); ++i)
    {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData()
  {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for (int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs()
  {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    next_free_time_.resize(num_workers_);
    workers_.resize(num_workers_);

    for (size_t i = 0; i < num_workers_; i++)
      workers_[i] = i;

    for (int i = 0; i < jobs_.size(); ++i)
    {
      int duration = jobs_[i];
      int next_worker = workers_[0];
      start_times_[i] = next_free_time_[next_worker];
      assigned_workers_[i] = next_worker;
      next_free_time_[next_worker] += duration;
      sift_down(0);
    }
  }

  void sift_down(int i)
  {
    int size = num_workers_;
    int minIdx = i;
    int l = 2 * i + 1;
    if (l < size &&
        (next_free_time_[workers_[l]] < next_free_time_[workers_[minIdx]] ||
         (next_free_time_[workers_[l]] == next_free_time_[workers_[minIdx]]) && workers_[l] < workers_[minIdx]))
      minIdx = l;

    int r = 2 * i + 2;
    if (r < size &&
        (next_free_time_[workers_[r]] < next_free_time_[workers_[minIdx]] ||
         (next_free_time_[workers_[r]] == next_free_time_[workers_[minIdx]]) && workers_[r] < workers_[minIdx]))
      minIdx = r;

    if (i != minIdx)
    {
      swap(workers_[i], workers_[minIdx]);
      sift_down(minIdx);
    }
  }

public:
  void Solve()
  {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
