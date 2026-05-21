// Copyright 2021 NNTU-CS

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <vector>

template<typename Key>
class BST {
 private:
  struct Vertex {
    Key label;
    int counter;
    Vertex* leftVertex;
    Vertex* rightVertex;

    explicit Vertex(const Key& key)
        : label(key), counter(1), leftVertex(nullptr), rightVertex(nullptr) {}
  };

  Vertex* rootVertex;

  Vertex* addVertex(Vertex* v, const Key& key, bool& newFlag) {
    if (v == nullptr) {
      newFlag = true;
      return new Vertex(key);
    }

    if (key < v->label) {
      v->leftVertex = addVertex(v->leftVertex, key, newFlag);
    } else if (key > v->label) {
      v->rightVertex = addVertex(v->rightVertex, key, newFlag);
    } else {
      v->counter++;
      newFlag = false;
    }
    return v;
  }

  Vertex* locateVertex(Vertex* v, const Key& key) const {
    if (v == nullptr || v->label == key) {
      return v;
    }
    if (key < v->label) {
      return locateVertex(v->leftVertex, key);
    } else {
      return locateVertex(v->rightVertex, key);
    }
  }

  int computeHeight(Vertex* v) const {
    if (v == nullptr) {
      return -1;
    }
    return 1+ std::max(computeHeight(v->leftVertex),
                        computeHeight(v->rightVertex));
  }

  void collectPairs(Vertex* v, std::vector<std::pair<Key, int>>* out) const {
    if (v == nullptr) {
      return;
    }
    collectPairs(v->leftVertex, out);
    out->push_back({v->label, v->counter});
    collectPairs(v->rightVertex, out);
  }

  void eraseSubtree(Vertex* v) {
    if (v == nullptr) {
      return;
    }
    eraseSubtree(v->leftVertex);
    eraseSubtree(v->rightVertex);
    delete v;
  }

 public:
  BST() : rootVertex(nullptr) {}

  ~BST() {
    eraseSubtree(rootVertex);
  }

  void insert(const Key& key) {
    bool flag = false;
    rootVertex = addVertex(rootVertex, key, flag);
  }

  int search(const Key& key) const {
    Vertex* found = locateVertex(rootVertex, key);
    return found ? found->counter : 0;
  }

  int depth() const {
    return computeHeight(rootVertex);
  }

  std::vector<std::pair<Key, int>> getAll() const {
    std::vector<std::pair<Key, int>> result;
    collectPairs(rootVertex, &result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
