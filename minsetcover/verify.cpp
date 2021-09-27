#include <iostream>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

int main()
{
  int n, m;
  int number;
  string line;
  vector<set<int, greater<int> > > subsets;
  
  // Reads n and m
  getline(cin, line);
  stringstream ss;
  ss.str(line);
  ss >> n;
  ss >> m;

  // Reads subsets
  for (int i = 0; i < m; i++)
  {
    getline(cin, line);
    stringstream ss;
    ss.str(line);
    set<int, greater<int> > subset;
    while (ss >> number)
    {
      subset.insert(number);
    }
    subsets.push_back(subset);
  }

  // Reads cover
  getline(cin, line);
  stringstream ss_c;
  ss_c.str(line);
  set<int, greater<int> > cover;
  while (ss_c >> number)
  {
    cover.insert(number);
  }
  
  // Generates u
  set<int, greater<int> > u;
  for (int i = 0; i < n; i++)
  {
    u.insert(i);
  }

  set<int, greater<int> >::reverse_iterator itr_c;
  for (itr_c = cover.rbegin(); itr_c != cover.rend(); itr_c++)
  {
    int i = *itr_c - 1;
    set<int, greater<int> >::iterator itr_s;
    for (itr_s = subsets[i].begin(); itr_s != subsets[i].end(); itr_s++)
    {
      u.erase(*itr_s);
    }
  }

  if (u.size() == 0)
  {
    cout << "Cobertura atendida";
    cout << endl;
  }
  else
  {
    cout << "Cobertura não atendida";
    cout << endl;
  }
}
