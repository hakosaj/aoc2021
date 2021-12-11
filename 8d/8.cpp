#include <iostream>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iterator>
#include <map>
#include <numeric>
#include <omp.h>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <typeinfo>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

bool isprime(int n) {
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;

  if (n % 2 == 0 || n % 3 == 0)
    return false;

  for (int i = 5; i * i <= n; i = i + 6)
    if (n % i == 0 || n % (i + 2) == 0)
      return false;

  return true;
}

void printVector(vector<int> digits) {

  cout << "\n";
  for (int i : digits) {
    cout << i << ',';
  }

  // cout<<"sum: "<< std::accumulate(digits.begin(),digits.end(),0);
}

vector<string> readfile(string filename) {
  string myText;
  vector<string> contents;

  std::fstream fileToRead(filename, std::ios::in);

  while (std::getline(fileToRead, myText)) {
    contents.push_back(myText);
  }

  fileToRead.close();
  return contents;
}

vector<string> split(string s, string delimiter) {
  size_t pos = 0;
  vector<string> splitt;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    if (token.size() > 0) {

      splitt.push_back(token);
    }
    s.erase(0, pos + delimiter.length());
  }
  splitt.insert(splitt.end(), s);
  return splitt;
}

string eraseCharacter(string str, char token) {
  str.erase(std::remove(str.begin(), str.end(), token), str.end());
  return str;
}
std::set<char> setminus(std::set<char> a, std::set<char> b) {
  string result;
  std::set<char> d;
  set_difference(a.begin(), a.end(), b.begin(), b.end(),
                 inserter(result, result.begin()));
  for (char c : result) {
    d.insert(c);
  }
  return d;
}

std::set<char> setintersect(std::set<char> a, std::set<char> b) {
  string result;
  std::set<char> d;
  set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                   inserter(result, result.begin()));
  for (char c : result) {
    d.insert(c);
  }
  return d;
}

// Segments,number
std::map<int, int> nmb = {{6, 0}, {2, 1}, {5, 2}, {5, 3}, {4, 4},
                          {5, 5}, {6, 6}, {3, 7}, {7, 8}, {6, 9}};
// segments vs number
std::map<int, int> unmb = {{2, 1}, {4, 4}, {3, 7}, {7, 8}};

std::map<int, std::set<char>> strs;
std::set<char> full{'a', 'b', 'c', 'd', 'e', 'f', 'g'};


void analyse_contents(vector<string> stuff) {
  long totalsum=0;
  for (int i = 0; i < stuff.size(); i++) {
  std::set<std::set<char>> sixes;
  std::set<std::set<char>> fives;
    auto d = split(stuff[i], " ");
    for (int a = 0; a < d.size(); a++) {
      if (d[a].size() == 1) {
        continue;
      }
      auto wrd = d[a];
      std::set<char> d;
      std::sort(wrd.begin(), wrd.end());
      for (char c : wrd) {
        d.insert(c);
      }
      if (wrd.size() == 2) {
        strs[1] = d;
      } else if (wrd.size() == 4) {
        strs[4] = d;
      } else if (wrd.size() == 3) {
        strs[7] = d;
      } else if (wrd.size() == 7) {
        strs[8] = d;
      } else if (wrd.size() == 5) {
        fives.insert(d);
      } else if (wrd.size() == 6) {
        sixes.insert(d);
      }
    }

    // If something in six and intersect with not fours len one, then nine
    auto notfours = setminus(full, strs[4]);
    auto tempsixes = sixes;
    for (const auto &d : tempsixes) {
      if (setintersect(notfours, setminus(full, d)).size()) {
        strs[9] = d;
        sixes.erase(d);
        break;
      }
    }

    // If something is six and intersect with not seven len one, then six
    auto notsevens = setminus(full, strs[7]);
    tempsixes = sixes;
    for (const auto &d : sixes) {
      if (setintersect(notsevens, setminus(full, d)).size()) {
        strs[0] = d;
        sixes.erase(d);
        break;
      }
    }

    // last element of sixes is zero
    tempsixes = sixes;
    for (const auto &d : tempsixes) {
      strs[6] = d;
      sixes.erase(d);
      break;
    }

    auto tempfives = fives;
    // If something is five and intersect with not seven is two, then three
    notsevens = setminus(full, strs[7]);
    for (const auto &d : tempfives) {
      if (setintersect(notsevens, setminus(full, d)).size() == 2) {
        strs[3] = d;
        fives.erase(d);
        break;
      }
    }

    // If something is five and intersect with not four is one, then five
    auto notfour = setminus(full, strs[7]);
    tempfives = fives;
    for (const auto &d : tempfives) {
      if (setintersect(notfour, setminus(full, d)).size() == 1) {
        strs[2] = d;
        fives.erase(d);
        break;
      }
    }
    // last element of fives is two
    tempfives = fives;
    for (const auto &d : tempfives) {
      strs[5] = d;
      fives.erase(d);
      break;
    }


    auto r = split(stuff[i], " ");
      vector<int> sm;
    for (int a = r.size()-4; a < r.size(); a++) {
      std::set<char> cm;
      std::sort(r[a].begin(), r[a].end());
      for (char c : r[a]) {
        cm.insert(c);
      }
      for (const auto& [key, value] : strs) {
      if (value == cm){
        sm.push_back((int)key);
      }

    }
    }
    long summ=0;
    int tens=1000;
    for (const auto &gd:sm) {
      summ+=gd*tens;
      tens/=10;
    }
    totalsum+=summ;

    
  }



cout<<totalsum<<endl;
}

int main() {
  auto stuff = readfile("data.txt");
  auto start_time = std::chrono::high_resolution_clock::now();
  analyse_contents(stuff);

  auto end_time = std::chrono::high_resolution_clock::now();
  cout << "\nElapsed: "
       << std::chrono::duration_cast<std::chrono::seconds>(end_time -
                                                           start_time)
              .count()
       << ".";
  cout << std::chrono::duration_cast<std::chrono::microseconds>(end_time -
                                                                start_time)
              .count()
       << " seconds." << endl;
}