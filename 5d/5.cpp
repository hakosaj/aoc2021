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

// mapped by y

struct gridline {
  // If true, vertical
  int id;
  std::set<std::pair<int, int>> memb;
  // = decltype(hits)(25,false);
};

void addSpatial(int x,int y, std::map<std::pair<int,int>,int> &spatialMap) {
        auto pt = std::pair<int, int>(x,y);
        if (spatialMap.count(pt)) {
          spatialMap[pt] += 1;
        } else {
          spatialMap[pt] = 1;
        }

}


void indexPoints(vector<string> p1, vector<string> p2,
                 std::map<std::pair<int, int>, int> &spatialMap) {
  auto xs = std::stoi(p1[0]);
  auto ys = std::stoi(p1[1]);
  auto xe = std::stoi(p2[0]);
  auto ye = std::stoi(p2[1]);

  if (xs == xe) {
    if (ye > ys) {
      for (int a = ys; a < ye + 1; a++) {
        addSpatial(xs,a,spatialMap);

      }
    } else {
      for (int a = ye; a < ys + 1; a++) {
        addSpatial(xs,a,spatialMap);
      }
    }

  } else if (ys == ye) {
    if (xe > xs) {
      for (int a = xs; a < xe + 1; a++) {
        addSpatial(a,ys,spatialMap);
      }
    } else {
      for (int a = xe; a < xs + 1; a++) {
        addSpatial(a,ys,spatialMap);
      }
    }


  }else {
    //diagonal
    //left top->right bottom
    if (ys<ye && xs<xe) {
      for (int a=0;a<(ye-ys)+1;a++) {
        addSpatial(xs+a,ys+a,spatialMap);
      }

     // right top->left fottom 
    }else if (ys < ye && xe<xs){
      for (int a=0;a<(ye-ys)+1;a++) {
        addSpatial(xs-a,ys+a,spatialMap);
      }

    //left bottom->right top
    }else if (ys>ye && xs<xe) {
      for (int a=0;a<(ys-ye)+1;a++) {
        addSpatial(xs+a,ys-a,spatialMap);
      }

    }else {
      for (int a=0;a<(ys-ye)+1;a++) {
        addSpatial(xs-a,ys-a,spatialMap);
      }

    }
    



  }
}
// return g;

void analyse_contents(vector<string> stuff) {
  vector<std::pair<std::pair<int, int>, std::pair<int, int>>> points;
  std::map<std::pair<int, int>, int> spatialMap;


  for (int i=0;i<stuff.size();i++){

    auto points = split(stuff[i], "->");
    auto p1 = split(points[0], ",");
    auto p2 = split(points[1], ",");
    indexPoints(p1, p2, spatialMap);
  }
  int sm=0;
  for (auto const &pair : spatialMap) {
    if (pair.second > 1) {
      sm++;
    }
  }
  cout<<sm<<endl;
}

int main() {
  auto stuff = readfile("myfile.txt");
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