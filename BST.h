#ifndef __BST_H__
#define __BST_H__

#include "Node.h"
#include <string>
#include <vector>

template <typename T>
class BST {
 private:
  Node<T>* root;
  std::vector<Node<T> * > InOrderTraversal(Node<T>* root);
  std::vector<Node<T> * > PostOrderTraversal(Node<T>* root);
  void rotate(Node<T>** cn, short int d);
  short int findB(Node<T>** n);

 public:
  BST<T>();
  ~BST<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void InOrderTraversalPrint();
  void PostOrderTraversalPrint();
  void visualRepPrint();
};


#endif
