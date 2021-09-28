#include <iostream>
#include <fstream>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

pair<vector<int>, int> bypassbranch(vector<int> subset, int i)
{
    for (int j = i - 1; j > -1; j--)
    {
        if (subset.at(j) == 0)
        {
            subset.at(j) = 1;
            return make_pair(subset, j + 1);
        }
    }
    return make_pair(subset, 0);
}

pair<vector<int>, int> nextvertex(vector<int> subset, int i, int m)
{
    if (i < m)
    {
        subset.at(i) = 0;
        return make_pair(subset, i + 1);
    }
    else
    {
        for (int j = m - 1; j > -1; j--)
        {
            if (subset.at(j) == 0)
            {
                subset.at(j) = 1;
                return make_pair(subset, j + 1);
            }
        }
    }
    return make_pair(subset, 0);
}

pair<int, vector<int> > BB(set<int> universe, vector<vector<int> > sets, vector<int> costs)
{
    vector<int> bestSubset;
    vector<int> subset(sets.size(), 1);
    subset.at(0) = 0;
    int bestCost = accumulate(costs.begin(), costs.end(), 0);
    int i = 1;
    while (i > 0)
    {
        if (i < sets.size())
        {
            int cost = 0;
            set<int> tSet;
            for (int k = 0; k < i; k++)
            {
                cost += subset.at(k) * costs.at(k);
                if (subset.at(k) == 1)
                {
                    tSet.insert(sets.at(k).begin(), sets.at(k).end());
                }
            }
            if (cost > bestCost)
            {
                pair<vector<int>, int> temp = bypassbranch(subset, i);
                subset = temp.first;
                i = temp.second;
                continue;
            }
            for (int k = i; k < sets.size(); k++)
            {
                tSet.insert(sets.at(k).begin(), sets.at(k).end());
            }
            if (tSet != universe)
            {
                pair<vector<int>, int> temp = bypassbranch(subset, i);
                subset = temp.first;
                i = temp.second;
            }
            else
            {
                pair<vector<int>, int> temp = nextvertex(subset, i, sets.size());
                subset = temp.first;
                i = temp.second;
            }
        }
        else
        {
            int cost = 0;
            set<int> fSet;
            for (int k = 0; k < i; k++)
            {
                cost += subset.at(k) * costs.at(k);
                if (subset.at(k) == 1)
                {
                    fSet.insert(sets.at(k).begin(), sets.at(k).end());
                }
            }
            if (cost < bestCost && fSet == universe)
            {
                bestCost = cost;
                bestSubset = subset;
            }
            pair<vector<int>, int> temp = nextvertex(subset, i, sets.size());
            subset = temp.first;
            i = temp.second;
        }
    }
    return make_pair(bestCost, bestSubset);
}

void printvector(vector<vector<int> > v)
{
    cout << "[";
    for (int i = 0; i < v.size(); i++)
    {
        cout << "[";
        vector<int> sv = v.at(i);
        for (int j = 0; j < sv.size(); j++)
        {
            cout << sv.at(j);
            if (j < sv.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]";
        if (i < v.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "]";
    cout << endl;
}

void exec(int m, vector<vector<int> > S, vector<int> C)
{
    chrono::system_clock::time_point z = chrono::system_clock::now();
    set<int> F;
    for (int x = 1; x < m + 1; x++)
    {
        F.insert(x);
    }
    pair<int, vector<int> > X = BB(F, S, C);
    int cost = X.first;
    vector<int> sets = X.second;
    vector<vector<int> > cover;
    for (int x = 0; x < sets.size(); x++)
    {
        if (sets.at(x) == 1)
        {
            cover.push_back(S.at(x));
        }
    }
    cout << "covering sets: ";
    printvector(cover);
    cout << "total cost: " << cost << " $" << endl;
    //
    chrono::system_clock::time_point end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - z;
    cout << "elapsed time: " << elapsed_seconds.count() << "s\n"
         << endl;
}

vector<vector<int> > vectorfromfile(ifstream *file)
{
    int n;
    string line;
    vector<vector<int> > r;
    while (getline(*file, line))
    {
        stringstream ss;
        ss.str(line);
        vector<int> v;
        while (ss >> n)
        {
            v.push_back(n);
        }
        r.push_back(v);
    }
    return r;
}

int main()
{
    int m1 = 5;
    ifstream f1("test-data/s1.txt");
    vector<vector<int> > S1 = vectorfromfile(&f1);
    vector<int> C1(S1.size(), 1);
    f1.close();
    //
    int m2 = 15;
    ifstream f2("test-data/s2.txt");
    vector<vector<int> > S2 = vectorfromfile(&f2);
    vector<int> C2(S2.size(), 1);
    f2.close();
    //
    int m3 = 5;
    ifstream f3("test-data/s3.txt");
    vector<vector<int> > S3 = vectorfromfile(&f3);
    vector<int> C3(S3.size(), 1);
    f3.close();
    //
    int m4 = 40;
    ifstream f4("test-data/s4.txt");
    vector<vector<int> > S4 = vectorfromfile(&f4);
    vector<int> C4(S4.size(), 1);
    f4.close();
    //
    int m5 = 30;
    // int n5 = 23;
    ifstream f5("test-data/s5.txt");
    vector<vector<int> > S5 = vectorfromfile(&f5);
    vector<int> C5(S5.size(), 1);
    f5.close();
    //
    cout << endl;
    exec(m1, S1, C1);
    exec(m2, S2, C2);
    exec(m3, S3, C3);
    exec(m4, S4, C4);
    exec(m5, S5, C5);
}
