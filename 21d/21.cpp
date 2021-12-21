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


void analyse_contents(vector<string> stuff) {

}

struct player {
  int score=0;
  int position=0;
  int id=0;
};

  int mindie=1;
  int maxdie=100;
  int currentdie=mindie;

void play_turn( player& a) {
      int rolls=0;
      for (int i=0;i<3;i++) {
        if (currentdie==100) {
          currentdie=1;
        }
        rolls+=currentdie;
        cout<<currentdie<<" ";
        currentdie++;
      }
      cout<<"\n";

      rolls=rolls%10;
      a.position+=rolls;
      if (a.position>10) {
        a.position=a.position-10;
        if (a.position==0) {
          cout<<"nolla!"<<endl;
          exit(0);
        }
      }
      int score=a.position;
      a.score+=score;
      cout<<"player: "<<a.id<<" and we add "<<score<<" for a total of: "<<a.score<<endl;
  
}
void analyse_contents_nopar() {
  player p1;
  p1.position=4;
  p1.id=1;
  player p2;
  p2.id=2;
  p2.position=8;
  bool turnp1=true;
  //int turns=200;
  while (p1.score<1000 && p2.score<1000) {
  //while (turns) {
    //turns--;
    if (turnp1) {
      play_turn(p1);
      turnp1=false;
    }else{
      play_turn(p2);
      turnp1=true;
    }


  }

}

int main() {
  //auto stuff = readfile("test.txt");
  auto start_time = std::chrono::high_resolution_clock::now();
  //analyse_contents(stuff);
  analyse_contents_nopar();

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