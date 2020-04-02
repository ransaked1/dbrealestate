#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;

// Print bidimensional vector contents //
void print(vector<vector<string>> vec) {
  for (unsigned int i = 0; i < vec.size(); i++)
  {
    for (unsigned int j = 0; j < vec[i].size(); j++)
    {
      cout << vec[i][j];
    }
  }
}

// Print progress bar //
void printProgress(float progress, string message)
{
  int barWidth = 38; //size of the bar

  if (progress < 1.0)
  {
      cout << "[";
      int pos = barWidth * progress;
      for (int i = 0; i < barWidth; ++i)
      {
          if (i < pos)
          cout << "=";
          else if (i == pos)
          cout << ">";
          else cout << " ";
      }
      cout << "] " << int(progress * 100.0) << "% " << message  << "\r";
      cout.flush();
    }
    else
    {
      cout << "[";
      int pos = barWidth * progress;
      for (int i = 0; i <= barWidth; ++i)
      {
          if (i < pos)
          cout << "=";
          else cout << "]";
      }
      cout << " " << int(progress * 100.0) << "% " << message << "\r";
      cout.flush();
    }
}
