#include <iostream>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iterator>
#include <numeric>
#include <omp.h>
#include <sstream>
#include <set>
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

//First with vectors, later with ordered sets
struct bingo {
  vector<int> numbers;
  vector<bool> hits = decltype(hits)(25,false);
};

vector<bingo> readBingoSquares(vector<string> rows) {
  vector<bingo> bingos;
  int bingocounter = 0;
  bingo b;

  // iterate all rows
  for (int r = 0; r < rows.size(); r++) {
    //Only actual rows
    if (rows.size() > 3) {

      auto currentrow = split(rows[r], " ");

      for (const auto &a : currentrow) {
        //cout<<a<<endl;
        b.numbers.push_back(std::stoi(a));
        bingocounter++;
        if (bingocounter==25) {

          cout<<"Bingo is full: counter at 25, bingo numbers size "<<b.numbers.size()<<endl;
          bingos.push_back(b);
          bingo a;
          b=a;
          r++;
          bingocounter=0;
          break;
        }
      }
    }


  }
  return bingos;
}

bool hasWon(bingo b) {
  //Possible wins: 0,1,2,3,4-> 5,6,7,8,9 =5*j+i
  //possible wins cols: 0 5 10 15 20 -> 1 6 11 16 21 = 

  //Check rows first
  for (int j=0;j<5;j++) {
      int hits=0;
      for (int i=0;i<5;i++) {
        if(b.hits[5*j+i]) {
          hits++;
        }


      }
      if (hits==5) {
        return true;
      }
      hits=0;
  }
  //Check cols 
  for (int i=0;i<5;i++) {
      int hits=0;
      for (int j=0;j<5;j++) {
        if(b.hits[5*j+i]) {
          hits++;
        }
      }
      if (hits==5) {
        return true;
      }
      hits=0;
  }

  return false;


}

void printBoard(bingo B) {
  for (int j=0;j<5;j++) {
    for (int i=0;i<5;i++) {
      cout<<B.numbers[j*5+i]<<' ';
    }
  cout<<"\n";
  }
  cout<<"\n";
}


void printHits(bingo B) {
  for (int j=0;j<5;j++) {
    for (int i=0;i<5;i++) {
      cout<<B.hits[j*5+i]<<' ';
    }
  cout<<"\n";
  }
  cout<<"\n";
}

void makeGuess(bingo &b, int guess) {
      auto v=b.numbers;
      auto it = find(v.begin(), v.end(), guess);
 
    // If element was found
    if (it != v.end())
    {
     
        // calculating the index
        // of K
        int index = it - v.begin();
        b.hits[index]=true;
    }

}


int calculateNumbers(bingo b, int victoryCall) {
  int summ=0;
  for (int a=0;a<25;a++) {
    if (!b.hits[a]) {
      summ+=b.numbers[a];
    }
  }
  return summ*victoryCall;
}

//Gotta do this with sets!
void playBingo(vector<bingo> bingos,vector<int> guesses) {
  std::set<int> winners;
  
  while(1) {
    for (const int g:guesses) {
      for (int bi=0;bi<bingos.size();bi++) {
        if (!winners.count(bi)){
        makeGuess(bingos[bi],g);
        if (hasWon(bingos[bi])) {
          printHits(bingos[bi]);
          printBoard(bingos[bi]);
          //cout<<calculateNumbers(bingos[bi],g)<<endl;
          winners.insert(bi);

          if (winners.size()==bingos.size()) {
            cout<<"Finished every board"<<endl;
            cout<<calculateNumbers(bingos[bi],g)<<endl;
            exit(0);
          }
        }
        }




      }
    }
  }


}



void analyse_contents(vector<string> stuff) {

  auto temp = split(stuff[0], ",");
  vector<int> guesses(temp.size());
  std::transform(temp.begin(), temp.end(), guesses.begin(),
                 [](string a) -> int { return std::stoi(a); });
  stuff.erase(stuff.begin());
  stuff.erase(stuff.begin());

  auto bingos=readBingoSquares(stuff);

  playBingo(bingos, guesses);
}

int main() {
  auto start_time = std::chrono::high_resolution_clock::now();
  auto stuff = readfile("data.txt");
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