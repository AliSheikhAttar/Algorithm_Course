#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::cin;
using std::string;
using std::vector;
using std::map;

struct Query
{
    string type, name;
    int number;
};

vector<Query> read_queries()
{
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string> &result)
{
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query> &queries)
{
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    map<int, string> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add"){
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            if (contacts.find(queries[i].number) != contacts.end()){
                contacts[queries[i].number] = queries[i].name;
                was_founded = true;
            }
            // otherwise, just add it
            if (!was_founded)
                contacts[queries[i].number] = queries[i].name;
        }
        else if (queries[i].type == "del"){
            if (contacts.find(queries[i].number) != contacts.end())
                contacts.erase(queries[i].number);
        }
        else {
            string response = "not found";
            if (contacts.find(queries[i].number) != contacts.end()){
                response = contacts[queries[i].number];
            }
            result.push_back(response);
        }
    return result;
}

int main()
{
    write_responses(process_queries(read_queries()));
    return 0;
}
