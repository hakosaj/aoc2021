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

std::map<string,long> performSwaps(string polymer, std::map<string, string> swaps,  int rounds) {
  std::map<string,long> pairs;
  rounds=10;
  //First, add all pairs to the map
  for (int i = 0; i < polymer.size() - 1; i++) {
    string ss = polymer.substr(i, 2);
    if (pairs.count(ss)) {
      pairs[ss]+=1;
    }
    else {
      pairs[ss]=1;
    }
  }

  // For each round
std::map<string,long> otherpairs=pairs;
  while (rounds) {
    rounds--;
    //Iterate through all current different pairs in the polymer
    for (auto const& [key,value]: pairs) {
      //If this pair is in the swaps
      if (swaps.count(key)) {
        //The count of the old 
        int paircount=swaps.count(key);

        //Then we find the new two pairs
        string np1{key[0],swaps[key][0]};
        string np2{swaps[key][0],key[1]};


        //We add the two new pairs to the pairs
        if (pairs.count(np1)) {
          otherpairs[np1]+=paircount;
        }else {
          otherpairs[np1]=paircount;
        }

        if (pairs.count(np2)) {
          otherpairs[np2]+=paircount;
        }else {
          otherpairs[np2]=paircount;
        }
        //And we remove the old pair from the original pairs
        otherpairs[key]-=paircount;
        if (otherpairs[key]<1) {
          otherpairs.erase(key);
        }
      }
      
    }
    pairs=otherpairs;
  }
  return otherpairs;

}

std::map<char, long long> occurrences(std::map<string,long> pairs) {


  std::map<char,long long> counts;

  for (auto const &[key, value] : pairs) {
    if (counts.count(key[0])) {
      counts[key[0]]+=1;
    }else {
      counts[key[0]]=1;
    }

    if (counts.count(key[1])) {
      counts[key[1]]+=1;
    }else {
      counts[key[1]]=1;
  }
  }

  for (auto const &[key, value] : counts) {
    counts[key]=ceil(value/2.0);
    cout<<key<<": "<<value<<endl;
  }
    return counts;

}


void analyse_contents(vector<string> stuff) {

  int rounds = 10;
  stuff.erase(stuff.begin() + 1);
  string polymer = stuff[0];
  stuff.erase(stuff.begin());

  std::map<string, string> swaps;

  for (const auto &a : stuff) {
    auto g = split(a, " -> ");
    swaps.insert({g[0], g[1]});
  }
    auto pairs= performSwaps(polymer, swaps, rounds);
  occurrences(pairs);
}

int main() {
  auto stuff = readfile("test.txt");
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