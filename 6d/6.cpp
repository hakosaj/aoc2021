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


std::map<int,long long> emptygen(){
  std::map<int, long long> newgen;
  for (int i=8;i>-1;i--) {
    newgen.insert(std::pair(i,0));
  }
  return newgen;
}

void grow(std::map<int,long long> fish) {
  int days = 256;
  for (int d = 0; d < days; d++) {
    auto ng=emptygen();

    for (int i=8;i>0;i--) {
      ng[i-1]=fish[i];
    }
    ng[6]=ng[6]+fish[0];
    ng[8]=fish[0];
    fish=ng;


  }
  long long sm=0;
  for (int i=8;i>-1;i--) {
    //cout<<fish[i]<<endl;
    sm+=fish[i];
  }
  cout<<sm<<endl;
}
void analyse_contents(vector<string> stuff) {
  // 9 elems; first is days, second is fish
  std::map<int,long long> fish;
  auto rar = split(stuff[0], ",");

  for (int i = 0; i < 9; i++) {
    fish.insert(std::pair(i, 0));
  }
  for (const auto &a : rar) {
    long r = a[0] - '0';
    fish[r] = fish[r] += 1;
    //fish2.push_back(r);
  }
  grow(fish);
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