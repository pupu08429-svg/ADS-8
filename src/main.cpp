// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>


void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> wordTree;
  const char* filePath = "src/war_peace.txt";

  std::cout << "Processing file: " << filePath << std::endl;
  makeTree(wordTree, filePath);

  std::cout << "Tree depth: " << wordTree.depth() << std::endl;
  std::cout << "Unique words count: " << wordTree.getAll().size() << std::endl;

  std::cout << "\nFrequency dictionary (sorted by frequency):" << std::endl;
  printFreq(wordTree);

  return 0;
}
