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


int rows=0;
int cols=0;

void printGrid(vector<vector<int>> d) {
  for (int j = 1; j < rows + 1; j++) {
    for (int i = 1; i < cols + 1; i++) {
      cout << d[j][i]<<" ";
    }
    cout << "\n";
  }
  cout << "\n";
}

bool checkNeighbors(int y, int x, vector<vector<int>> grid) {
  if (grid[y-1][x]<=grid[y][x]) {
    if (grid[y-1][x]!=-1){
    return false;
    }
  }
  if (grid[y+1][x]<=grid[y][x]) {
    if (grid[y+1][x]!=-1){
    return false;
    }
  }
  if (grid[y][x-1]<=grid[y][x]) {
    if (grid[y][x-1]!=-1){
    return false;
    }
  }
  if (grid[y][x+1]<=grid[y][x]) {
    if (grid[y][x+1]!=-1){
    return false;
    }
  }

  return true;
}


void getLows(vector<vector<int>> grid) {
  int lowsums=0;
  int points=0;
  for (int j=1;j<rows+1;j++) {
    for (int i=1;i<cols+1;i++) {
      if (checkNeighbors(j,i,grid)) {
        cout<<"low pt: "<< i<<","<<j<<endl;
        lowsums+=grid[j][i]+1;
        points++;
      }

    }
  }  
  cout<<lowsums<<endl;
  cout<<points<<endl;
}


int wall = 9;
int floodarea=0;
vector<vector<int>> ggrid;

void flood_fill(int y, int x, int color)
{
  if (x==0 || y==0 || y==rows+1 || x==cols+1) {
    return;
  }
  
   if(ggrid[y][x] == wall || ggrid[y][x] == color)
      return;                                              
   
   
   ggrid[y][x] = color;
   floodarea++;
   
   flood_fill(y, x+1, color);  
   flood_fill(y,x-1, color);  
   flood_fill(y-1,x, color);  
   flood_fill(y+1,x, color);  
   
   return;

}


void analyse_contents(vector<string> stuff) {
  vector<vector<int>> grid;
  rows=stuff.size();
  cols=stuff[0].size();

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
  ggrid=grid;
  vector<int> basins;

  for (int j = 1; j < rows + 1; j++) {
    for (int i = 1; i < cols + 1; i++) {
      if (ggrid[j][i]!= 11 || ggrid[j][i]!=9) {
      flood_fill(j,i,11);
      if (floodarea>0) {
        cout<<floodarea<<endl;
        basins.push_back(floodarea);
      }
      floodarea=0;
      }
    }
  }
  //getLows(grid);
  std::sort(basins.begin(),basins.end(),std::greater<>());
  cout<<basins[0]<<"*"<<basins[1]<<"*"<<basins[2]<<"= "<<basins[0]*basins[1]*basins[2]<<endl;


}



int main() {
  //1830 too high
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