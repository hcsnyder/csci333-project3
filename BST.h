#ifndef __BST_H__
#define __BST_H__

#include "Node.h"
#include <string>

template <typename T>
class BST {
 private:
  Node<T>* root;
  void InOrderTraversalPrint(Node<T>* root);
  void PostOrderTraversalPrint(Node<T>* root);
  void rotate(Node<T>** cn, int d);

 public:
  BST<T>();
  ~BST<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void InOrderTraversal();
  void PostOrderTraversal();
  void visualRepPrint();
};


#endif
