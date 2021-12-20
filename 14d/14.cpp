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

string performSwaps(string polymer, std::map<string, string> swaps) {
  int extraindex = 0;
  auto polymer2 = polymer;
  for (int i = 0; i < polymer.size() - 1; i++) {
    string ss = polymer.substr(i, 2);
    if (swaps.count(ss)) {
      polymer2.insert(polymer2.begin() + i + 1 + extraindex, swaps[ss][0]);
      extraindex++;
    }
  }
  return polymer2;
}

std::map<char, long long> occurrences(string polymer) {
  std::map<char, long long> occs;
  for (const char c : polymer) {
    if (occs.count(c)) {
      occs[c] += 1;
    } else {
      occs[c] = 1;
    }
  }
  long long mx=0;
  long long mn=INT32_MAX;
  for (auto const &[key, value] : occs) {
    if (value>mx) {
      mx=value;
    }
    if (value<mn) {
      mn=value;
    }
    cout << key << ": " << value << endl;
  }
  cout<<"max: "<<mx<<", and min: "<<mn<<", and their subs: "<<mx-mn<<endl;
  return occs;
}

void analyse_contents(vector<string> stuff) {

  int rounds = 15;
  stuff.erase(stuff.begin() + 1);
  string polymer = stuff[0];
  stuff.erase(stuff.begin());

  std::map<string, string> swaps;

  for (const auto &a : stuff) {
    auto g = split(a, " -> ");
    swaps.insert({g[0], g[1]});
  }
  while (rounds) {
    rounds--;
    polymer = performSwaps(polymer, swaps);
  }
  occurrences(polymer);
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