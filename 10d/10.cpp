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
#include <stack>
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


int isCorrupt(string st) {
  std::stack<char> que;
  for (char s:st) {
    if (s=='(') {
      que.push(s);
    }
    if (s=='[') {
      que.push(s);
    }
    if (s=='{') {
      que.push(s);
    }
    if (s=='<') {
      que.push(s);
    }

    if (s==')') {
      if (que.top()!='(') {
        return 3;
      }else {
        que.pop();
      }
    }
    if (s==']') {
      if (que.top()!='[') {
        return 57;
      }else {
        que.pop();
      }
    }
    if (s=='}') {
      if (que.top()!='{') {
        return 1197;
      }else {
        que.pop();
      }
    }
    if (s=='>') {
      if (que.top()!='<') {
        return 25137;
      }else {
        que.pop();
      }
    }



  }
  return 0;

}




string fixit(string st) {
  std::stack<char> que;
  for (char s:st) {
    if (s=='(') {
      que.push(s);
      continue;
    }
    if (s=='[') {
      que.push(s);
      continue;
    }
    if (s=='{') {
      que.push(s);
      continue;
    }
    if (s=='<') {
      que.push(s);
      continue;
    }
    que.pop();
    



  }
  string fixstring;
  while (!(que.empty())) {
    if (que.top()=='(') {
      fixstring.push_back(static_cast<char>(que.top()+1));
      que.pop();
    }else {
    fixstring.push_back(static_cast<char>(que.top()+2));
    que.pop();
    }
  }
  return fixstring;

}





bool isComplete(string st) {
  int brflag=0;
  int sqflag=0;
  int curflag=0;
  int eqflag=0;

  for (char s:st) {
    if (s=='(') {
      brflag++;
    }
    if (s=='[') {
      sqflag++;
    }
    if (s=='{') {
      curflag++;
    }
    if (s=='<') {
      eqflag++;
    }
    if (s==')') {
      brflag--;
    }
    if (s==']') {
      sqflag--;
    }
    if (s=='}') {
      curflag--;
    }
    if (s=='>') {
      eqflag--;

  }
  }
  if (sqflag || brflag || curflag || eqflag) {
    return 0;
  }
  return 1;

}



long calculateScore(string g) {
  long score=0;

  for (char a:g) {
    score*=5;
    if (a==')') {
      score+=1;
    }
    else if (a==']') {
      score+=2;
    }
    else if (a=='}') {
      score+=3;
    }
    else{
      score+=4;
    }
  }
  return score;

}
void analyse_contents(vector<string> stuff) {

  auto stuff2=stuff;

  vector<long> totalscore;
  for (int i=0;i<stuff.size();i++) {
    //cout<<isComplete(stuff2[i])<<endl;
    if (!isCorrupt(stuff[i])) {
      //stuff[i]=stuff[i]+fixit(stuff[i]);
      auto fixer=fixit(stuff[i]);
      totalscore.push_back(calculateScore(fixer));
    }

  }
  std::sort(totalscore.begin(),totalscore.end());
  cout<<totalscore[(totalscore.size()-1)/2]<<endl;



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