#include <iostream>
#include <fstream>
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
  ifstream readFile("teste.txt");

  // Reads n and m
  getline(readFile, line);
  stringstream ss;
  ss.str(line);
  ss >> n;
  ss >> m;

  // Reads subsets
  while (getline(readFile, line))
  {
    stringstream ss;
    ss.str(line);
    set<int, greater<int> > subset;
    while (ss >> number)
    {
      subset.insert(number);
    }
    subsets.push_back(subset);
  }
  readFile.close();

  // Generates u
  set<int, greater<int> > u;
  for (int i = 0; i < n; i++)
  {
    u.insert(i);
  }

  // Initializes cover with empty set
  int k = 0;
  set<int, greater<int> > cover;
  while (u.size() > 0)
  {
    // Selects max subset from subsets
    int max = 0;
    int i_max = 0;
    for (int i = 0; i < subsets.size(); i++)
    {
      if (cover.count(i + 1) == 0 && subsets[i].size() > max)
      {
        max = subsets[i].size();
        i_max = i;
      }
    }
    // Removes elements of max subset from u
    set<int, greater<int> >::iterator itr;
    for (itr = subsets[i_max].begin(); itr != subsets[i_max].end(); itr++)
    {
      u.erase(*itr);
    }
    // Adds index of max subset to cover
    cover.insert(i_max + 1);
    if (k++ > m)
    {
      break;
    }
  }

  // Prints cover
  set<int, greater<int> >::reverse_iterator itr_c;
  for (itr_c = cover.rbegin(); itr_c != cover.rend(); itr_c++)
  {
    cout << *itr_c << " ";
  }
  cout << endl;
}