#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <list>

using std::cin;
using std::list;
using std::map;
using std::string;
using std::vector;

struct Query
{
    string type, s;
    size_t ind;
};

class QueryProcessor
{
    int bucket_count;
    // Changed to use size_t keys instead of string
    map<size_t, list<string>> elems;
    size_t hash_func(const string &s) const
    {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {}

    Query readQuery() const
    {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const
    {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query &query)
    {
        if (query.type == "check")
        {
            // use reverse order, because we append strings to the end
            size_t idx = query.ind;
            if (elems.find(idx) != elems.end())
            {
                for (auto it = elems[idx].rbegin(); it != elems[idx].rend(); ++it)
                {
                    std::cout << *it << " ";
                }
            }
            std::cout << "\n";
        }
        else
        {
            size_t hash = hash_func(query.s);

            if (query.type == "find")
            {
                bool found = false;
                if (elems.find(hash) != elems.end())
                {
                    for (const auto &str : elems[hash])
                    {
                        if (str == query.s)
                        {
                            found = true;
                            break;
                        }
                    }
                }
                writeSearchResult(found);
            }
            else if (query.type == "add")
            {
                if (elems.find(hash) != elems.end())
                {
                    // Check if string already exists in the chain
                    bool exists = false;
                    for (const auto &str : elems[hash])
                    {
                        if (str == query.s)
                        {
                            exists = true;
                            break;
                        }
                    }
                    // Add only if it doesn't exist
                    if (!exists)
                    {
                        elems[hash].push_back(query.s);
                    }
                }
                else
                {
                    // Create new chain with this string
                    list<string> chain;
                    chain.push_back(query.s);
                    elems[hash] = chain;
                }
            }
            else if (query.type == "del")
            {
                if (elems.find(hash) != elems.end())
                {
                    for (auto it = elems[hash].begin(); it != elems[hash].end(); ++it)
                    {
                        if (*it == query.s)
                        {
                            elems[hash].erase(it);
                            break;
                        }
                    }
                }
            }
        }
    }

    void processQueries()
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
