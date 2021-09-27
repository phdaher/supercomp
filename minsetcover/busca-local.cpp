#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

double fitness(vector<set<int, greater<int> > > subsets, set<int, greater<int> > cover)
{
  int n = 0;
  set<int, greater<int> >::iterator itr;
  for (itr = cover.begin(); itr != cover.end(); itr++)
  {
    n += subsets[*itr - 1].size();
  }
  return double(n) / double(cover.size());
}

set<int, greater<int> > complement(int m, set<int, greater<int> > cover)
{
  set<int, greater<int> > r;
  for (int i = 1; i <= m; i++)
  {
    r.insert(i);
  }
  set<int, greater<int> >::iterator itr;
  for (itr = cover.begin(); itr != cover.end(); itr++)
  {
    r.erase(*itr);
  }
  return r;
}

int random(int min, int max)
{
  static bool first = true;
  if (first)
  {
    srand(time(NULL));
    first = false;
  }
  return min + rand() % ((max + 1) - min);
}

int random_element(set<int, greater<int> > intset)
{
  return *std::next(intset.begin(), random(1, intset.size()) - 1);
}

void print_set(set<int, greater<int> > intset)
{
  set<int, greater<int> >::reverse_iterator itr;
  for (itr = intset.rbegin(); itr != intset.rend(); itr++)
  {
    cout << *itr << " ";
  }
  cout << endl;
}

set<int, greater<int> > intersection(set<int, greater<int> > set1, set<int, greater<int> > set2)
{
  set<int, greater<int> > r;
  set<int, greater<int> >::iterator itr;
  for (itr = set1.begin(); itr != set1.end(); itr++)
  {
    if (set2.count(*itr) == 1)
    {
      r.insert(*itr);
    }
  }
  return r;
}

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
      if (cover.count(i + 1) == 0 && (intersection(subsets[i], u).size() > max))
      {
        max = intersection(subsets[i], u).size();
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

  print_set(cover);
  double fit_cover = fitness(subsets, cover);
  cout << fit_cover << endl;
  cout << endl;

  // Cover complement
  set<int, greater<int> > cover_compl;
  cover_compl = complement(m, cover);

  // New Cover
  set<int, greater<int> > new_cover;
  new_cover = complement(m, cover_compl);

  // Cover clone
  set<int, greater<int> > cover_clone;
  cover_clone = complement(m, cover_compl);

  int r = 3;
  for (int i = 1; i <= r; i++)
  {
    int elem_del = random_element(cover_clone);
    cover_clone.erase(elem_del);
    int elem_ins = random_element(cover_compl);
    cover_compl.erase(elem_ins);

    cout << "del: " << elem_del << ", ins: " << elem_ins << endl;
    new_cover.erase(elem_del);
    new_cover.insert(elem_ins);
  }

  cout << endl;
  print_set(new_cover);
  double fit_new_cover = fitness(subsets, new_cover);
  cout << fit_new_cover << endl;
  cout << endl;

  if (fit_new_cover > fit_cover)
  {
    cout << "modificado" << endl;
    print_set(new_cover);
  }
  else
  {
    cout << "original" << endl;
    print_set(cover);
  }
}
