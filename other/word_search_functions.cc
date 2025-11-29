// Copyright Madison Byrd 2025
#include "/mnt/classes/programming/project3/word_search_functions.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// The first line of some functions in this file will make cpplint angry because
// of lines over 80 characters long, non-constant references, and because of its 
// insistence on the use of absolute paths for header files.

// open a file containing characters for a word search and store them
bool ReadWordSearch(string file_name, char word_search[][kSize]) {
  // we make a backup in case we find invalid data in the file
  char word_search_temp[kSize][kSize];
  for (int i = 0; i < kSize; i++)
    for (int j = 0; j < kSize; j++)
      word_search_temp[i][j] = word_search[i][j];
  // open the file
  std::ifstream puzzle_file;
  puzzle_file.open(file_name);
  if (!puzzle_file.is_open())
    return false;

  // load the data into the array
  string line;
  int i = 0;
  int j = 0;
  bool valid = true;
  for (i = 0; i < kSize; i++) {
    for (j = 0; j < kSize && !puzzle_file.eof(); j++) {
      char ch = puzzle_file.get();
      // if we get a newline, go to the next character
      if (ch == '\n')
        ch = puzzle_file.get();
      word_search[i][j] = ch;
    }
  }

  // make sure we got the right amount of rows and columns
  if (i != kSize || j != kSize)
    valid = false;

  // close the file
  puzzle_file.close();

  // if we didn't get valid data, restore the array we were passed
  if (!valid) {
    for (int j = 0; j < kSize; j++)
      for (int k = 0; k < kSize; k++)
        word_search[j][k] = word_search_temp[j][k];
  }
  return valid;
}

// print out all the characters in a grid of kSize by kSize characters
void PrintWordSearch(const char puzzle[][kSize]) {
  for (int i = 0; i < kSize; i++) {
    for (int j = 0; j < kSize; j++)
      cout << puzzle[i][j];
    cout << endl;
  }
}

// find a given string in the puzzle at given coordinates to the right
bool FindWordRight(const char w_search[][kSize], string to_find, int& row, int& col) {
  bool found_it = false;
  unsigned int i, j;
  for (i = 0; i < kSize; i++) {
    for (j = 0; j < kSize; j++) {
      // if the string exceeds the bounds of the puzzle, return false
      // check the first character
      if (w_search[i][j] == to_find.at(0) && to_find.length() <= kSize - j) {
        for (unsigned int k = 0; k < to_find.length(); k++) {
          // check the remaining characters
          if (w_search[i][j++] != to_find.at(k))
            break;
          if (k == to_find.length()-1) {
            found_it = true;
            row = i;
            col = j - to_find.length();
            return true;
          }
        }
      }
    }
  }
  return found_it;
}

// find a given string in the puzzle at given coordinates to the left
bool FindWordLeft(const char w_search[][kSize], string to_find, int& row, int& col) {
  bool found_it = false;
  unsigned int i, j;
  for (i = 0; i < kSize; i++) {
    for (j = 0; j < kSize; j++) {
      // keep track of the first character
      int tmp = j;
      // if the string exceeds the bounds of the puzzle, return false
      // check the first character
      if (w_search[i][j] == to_find.at(0) && to_find.length() <= j) {
        for (unsigned int k = 0; k < to_find.length(); k++) {
          if (w_search[i][tmp--] != to_find.at(k))
            break;
          if (k == to_find.length()-1) {
            found_it = true;
            row = i;
            col = tmp + to_find.length();
            return true;
          }
        }
      }
    }
  }
  return found_it;
}

// find a given string in the puzzle at given coordinates downward
bool FindWordDown(const char w_search[][kSize], string to_find, int& row, int& col) {
  bool found_it = false;
  unsigned int i, j;
  for (i = 0; i < kSize; i++) {
    for (j = 0; j < kSize; j++) {
      // if the string exceeds the bounds of the puzzle, return false
      // check the first character
      if (w_search[i][j] == to_find.at(0) && to_find.length() <= kSize - i) {
        for (unsigned int k = 0; k < to_find.length(); k++) {
          if (w_search[i++][j] != to_find.at(k))
            break;
          if (k == to_find.length()-1) {
            found_it = true;
            row = i - to_find.length();
            col = j;
            return true;
          }
        }
      }
    }
  }
  return found_it;
}

// find a given string in the puzzle at given coordinates upward
bool FindWordUp(const char w_search[][kSize], string to_find, int& row, int& col) {
  bool found_it = false;
  unsigned int i, j;
  for (i = 0; i < kSize; i++) {
    for (j = 0; j < kSize; j++) {
      // keep track of the first character
      int tmp = i;
      // if the string exceeds the bounds of the puzzle, return false
      // check the first character
      if (w_search[i][j] == to_find.at(0) && to_find.length() <= i) {
        for (unsigned int k = 0; k < to_find.length(); k++) {
          if (w_search[tmp--][j] != to_find.at(k))
            break;
          if (k == to_find.length()-1) {
            found_it = true;
            row = tmp + to_find.length();
            col = j;
            return true;
          }
        }
      }
    }
  }
  return found_it;
}

// find a given string in the puzzle at given coordinates down and to the right
bool FindWordDiagonal(const char w_search[][kSize], string to_find, int& row, int& col) {
  bool found_it = false;
  unsigned int i, j;
  for (i = 0; i < kSize; i++) {
    for (j = 0; j < kSize; j++) {
      // keep track of the first character
      int tmprow = i;
      int tmpcol = j;
      // if the string exceeds the bounds of the puzzle, return false
      // check the first character
      if (w_search[i][j] == to_find.at(0) &&
          to_find.length() <= kSize - j &&
          to_find.length() <= kSize - i) {
        for (unsigned int k = 0; k < to_find.length(); k++) {
          if (w_search[tmprow++][tmpcol++] != to_find.at(k))
            break;
          if (k == to_find.length()-1) {
            found_it = true;
            row = tmprow - to_find.length();
            col = tmpcol - to_find.length();
            return true;
          }
        }
      }
    }
  }
  return found_it;
}
