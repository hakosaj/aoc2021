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

int brysearch(int bot,int top, vector<int> spots) {
  std::cin.ignore();
  cout<<bot<<" "<<top<<endl;
  if (top==bot) {
      int findist=0;
    for (const auto &g:spots) {
      findist+=abs(top-g);
    }
    return findist;
  }
  long botdist=0;
  long topdist=0;
  long middist=0;
  int midi=bot+(top-bot)/2;
    for (const auto &g:spots) {
      topdist+=abs(top-g);
      botdist+=abs(bot-g);
      middist+=abs(midi-g);
    }
    cout<<"botdist :"<<botdist<<endl;
    cout<<"middist :"<<middist<<endl;
    cout<<"topdist :"<<topdist<<endl;

    if (middist>botdist) {
      return brysearch(bot,midi-1,spots);
    }else {
      return brysearch(midi+1,top,spots);


    }


}

int fuelspent(int difference) {
  int ind=0;
  int fuel=0;
  for (int f=0;f<difference+1;f++) {
    fuel+=ind;
    ind++;

  }
  return fuel;
}

void analyse_contents(vector<string> stuff) {
  double avg=0;
  int mx=0;
  vector<int> spots;
  for (const auto &g: split(stuff[0],",")) {
    int nmb=std::stoi(g);
    spots.push_back(nmb);
    if (mx<nmb) {
      mx=nmb;
    }
  }
  
  long long totalfuel=0;
  long long min=INT32_MAX;
  long long besttry=0;
  for (int tre=0;tre<mx;tre++) {
    for (const auto &g:spots) {
      totalfuel+=fuelspent(abs(tre-g));
    }
    if(totalfuel<min) {
      min=totalfuel;
      besttry=tre;
    }else {
      break;
    }
    totalfuel=0;

  }


  
  //cout<<brysearch(0,mx,spots)<<endl;
  cout<<besttry<< " "<<min<<endl;



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