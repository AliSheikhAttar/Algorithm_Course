#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Answer
{
	size_t i, j, len;
};

// Hash computation variables
vector<long long> shashes1;
vector<long long> shashes2;
vector<long long> thashes1;
vector<long long> thashes2;
vector<long long> powers1;
vector<long long> powers2;
const int m1 = 1000000007;
const int m2 = 1000000009;
const int x = 263;

void precompute_hashes(const string &s, const string &t)
{
	int ns = s.size();
	int nt = t.size();
	int max_size = max(ns, nt);

	shashes1.clear();
	shashes1.resize(ns + 1, 0);
	shashes2.clear();
	shashes2.resize(ns + 1, 0);
	thashes1.clear();
	thashes1.resize(nt + 1, 0);
	thashes2.clear();
	thashes2.resize(nt + 1, 0);
	powers1.clear();
	powers1.resize(max_size + 1, 0);
	powers2.clear();
	powers2.resize(max_size + 1, 0);

	powers1[0] = 1;
	powers2[0] = 1;
	for (int i = 1; i <= max_size; i++)
	{
		powers1[i] = (powers1[i - 1] * x) % m1;
		powers2[i] = (powers2[i - 1] * x) % m2;
	}

	for (int i = 0; i < ns; i++)
	{
		shashes1[i + 1] = (shashes1[i] * x + s[i]) % m1;
		shashes2[i + 1] = (shashes2[i] * x + s[i]) % m2;
	}

	for (int i = 0; i < nt; i++)
	{
		thashes1[i + 1] = (thashes1[i] * x + t[i]) % m1;
		thashes2[i + 1] = (thashes2[i] * x + t[i]) % m2;
	}
}

pair<long long, long long> get_hash_pair(int start, int length, bool is_first_string)
{
	vector<long long> &hashes1 = is_first_string ? shashes1 : thashes1;
	vector<long long> &hashes2 = is_first_string ? shashes2 : thashes2;

	long long hash1 = (hashes1[start + length] - (hashes1[start] * powers1[length]) % m1 + m1) % m1;
	long long hash2 = (hashes2[start + length] - (hashes2[start] * powers2[length]) % m2 + m2) % m2;

	return {hash1, hash2};
}

bool check_length(const string &s, const string &t, int length, int &s_pos, int &t_pos)
{
	unordered_map<long long, vector<int>> hash_positions;

	for (int i = 0; i + length <= s.size(); i++)
	{
		auto hash_pair = get_hash_pair(i, length, true);
		long long combined_hash = hash_pair.first * m2 + hash_pair.second;
		hash_positions[combined_hash].push_back(i);
	}

	for (int j = 0; j + length <= t.size(); j++)
	{
		auto hash_pair = get_hash_pair(j, length, false);
		long long combined_hash = hash_pair.first * m2 + hash_pair.second;

		if (hash_positions.count(combined_hash))
		{
			s_pos = hash_positions[combined_hash][0];
			t_pos = j;
			return true;
		}
	}

	return false;
}

Answer solve(const string &s, const string &t)
{
	Answer ans = {0, 0, 0};

	if (s.size() == 0 || t.size() == 0)
		return ans;

	precompute_hashes(s, t);

	int high = min(s.size(), t.size());
	int low = 0;
	int s_pos = 0, t_pos = 0;

	while (low <= high)
	{
		int mid = (low + high) / 2;

		if (check_length(s, t, mid, s_pos, t_pos))
		{
			ans = {s_pos, t_pos, mid};
			low = mid + 1;
		}
		else
			high = mid - 1;
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t)
	{
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
