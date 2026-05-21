// Copyright 2021 NNTU-CS

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "bst.h"

bool isLatinLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char toLowerCase(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c + ('a' - 'A');
  }
  return c;
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Cannot open file: " << filename << std::endl;
    return;
  }

  std::string current;
  char ch;

  while (file.get(ch)) {
    char low = toLowerCase(ch);

    if (isLatinLetter(low)) {
      current.push_back(low);
    } else {
      if (!current.empty()) {
        tree.insert(current);
        current.clear();
      }
    }
  }

  if (!current.empty()) {
    tree.insert(current);
  }

  file.close();
}

bool compareByFreq(const std::pair<std::string, int>& a,
                   const std::pair<std::string, int>& b) {
  if (a.second != b.second) {
    return a.second > b.second;
  }
  return a.first < b.first;
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> items = tree.getAll();

  std::sort(items.begin(), items.end(), compareByFreq);

  std::ofstream out("freq.txt");
  if (!out.is_open()) {
    std::cerr << "Error: cannot create result/freq.txt" << std::endl;
    return;
  }

  for (const auto& entry : items) {
    std::cout << entry.first << " : " << entry.second << std::endl;
    out << entry.first << " : " << entry.second << std::endl;
  }

  out.close();
}
