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

int rows = 10;
int cols = 10;
long totalFlashes=0;
bool allFlash=false;

void printGrid(vector<vector<int>> d) {
  for (int j = 1; j < rows + 1; j++) {
    for (int i = 1; i < cols + 1; i++) {
      cout << d[j][i];
    }
    cout << "\n";
  }
  cout << "\n";
}

int increaseNeighbors(int row, int col, vector<vector<int>> &grid) {
  int newovernines;
  for (int j = row - 1; j < row + 2; j++) {
    for (int i = col - 1; i < col + 2; i++) {
      if (!(j == row && i == col)) {
        if (grid[j][i] != -1) {

          grid[j][i] += 1;
          if (grid[j][i] == 10) {
            newovernines++;
          }
        }
      }
    }
  }
  return newovernines;
}
void step(vector<vector<int>> &grid) {

  bool flashgrid[rows][cols];
  for (int i = 0; i < rows+1; i++) {
    for (int j = 0; j < cols+1; j++) {
      flashgrid[i][j] = false;
    }
  }


  int overnines = 0;
  // increase
  for (int j = 1; j < rows + 1; j++) {
    for (int i = 1; i < cols + 1; i++) {
      grid[j][i] += 1;
      if (grid[j][i] > 9) {
        overnines++;
      }
    }
  }

  while (overnines > 0) {
    for (int j = 1; j < rows + 1; j++) {
      for (int i = 1; i < cols + 1; i++) {
        if (grid[j][i] > 9 && !flashgrid[j][i]) {
          overnines += increaseNeighbors(j, i, grid);
          flashgrid[j][i] = true;
          overnines--;
        }
      }
    }
  }
int tots=0;
  for (int j = 1; j < rows + 1; j++) {
    for (int i = 1; i < cols + 1; i++) {
      if (flashgrid[j][i]) {
        grid[j][i]=0;
        tots++;
        totalFlashes++;
      }

  }
  }
  if (tots==rows*cols) {
    allFlash=true;
  }

  
}

void analyse_contents(vector<string> stuff) {

  vector<vector<int>> grid;

  grid.push_back(vector<int>(cols + 2, -1));
  for (int j = 0; j < rows; j++) {
    vector<int> row;
    row.push_back(-1);
    for (int i = 0; i < cols; i++) {
      row.push_back((int)(stuff[j][i] - '0'));
    }
    row.push_back(-1);
    grid.push_back(row);
  }
  grid.push_back(vector<int>(cols + 2, -1));

//int steps=100;
//for (int i=0;i<steps;i++) {
  int steps=0;
while (!allFlash) {
  step(grid);
  steps++;
}
cout<<steps<<endl;
  //printGrid(grid);
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