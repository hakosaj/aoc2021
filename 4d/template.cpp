#include <iostream>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iterator>
#include <numeric>
#include <omp.h>
#include <sstream>
#include <string>
#include <bitset>
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
    cout << i;
  }

  cout << "\n";
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
	splitt.push_back(token);
    s.erase(0, pos + delimiter.length());
	}
	splitt.insert(splitt.begin(),s);
	return splitt;
}

void analyse_contents(vector<string> stuff) {




}

int main() {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto stuff = readfile("test.txt");
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