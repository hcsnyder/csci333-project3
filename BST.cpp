#include "BST.h"
#include <iostream>

template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  
}


template <typename T>
bool BST<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;

  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }
  *curr = temp;
}

template <typename T>
void BST<T>::remove(T v) {
  Node<T>** parent = &root;
  Node<T>** Node_to_remove = &root;
  Node<T>** temp = &root;
  while((*Node_to_remove)->getValue() != v && *Node_to_remove != 0) {
    parent = Node_to_remove;
    if((*Node_to_remove)->getValue() < v) {
      Node_to_remove = (&((*Node_to_remove)->getRightChild()));
    }
    else if((*Node_to_remove)->getValue() > v) {
      Node_to_remove = &((*Node_to_remove)->getLeftChild());
    }
  }
  if((*Node_to_remove)->getLeftChild() != 0) {
    Node<T>** replacement_parent = parent;
    Node<T>** replacement = Node_to_remove;
    replacement = &((*replacement)->getLeftChild());
    while((*replacement)->getRightChild() != 0) {
      replacement_parent = replacement;
      replacement = &((*replacement)->getRightChild());
    }
    if((*replacement)->getLeftChild() != 0) {
      temp = &((*replacement)->getLeftChild());
      (*replacement_parent)->setRightChild(**temp);
    }
    else if(Node_to_remove != &root) {
      if((*parent)->getValue() < v) {
        temp = &((*replacement_parent)->getRightChild());
        (*parent)->setRightChild(**temp);
      }
      else {
        temp = &((*replacement_parent)->getRightChild());
        (*parent)->setLeftChild(**temp);
      }
    }
    else if(Node_to_remove == &root) {
      root = *replacement;
    }
    else if((*Node_to_remove)->getLeftChild() != 0) {
      temp = &((*Node_to_remove)->getLeftChild());
      (*replacement)->setLeftChild(**temp);
    }
    else if((*Node_to_remove)->getRightChild() != 0) {
      temp = &((*Node_to_remove)->getRightChild());
      (*replacement)->setRightChild(**temp);
    }
  }
  else if((*Node_to_remove)->getLeftChild() == 0) {
    if((*Node_to_remove)->getRightChild() != 0) {
      if(Node_to_remove != &root) {
        temp = &((*Node_to_remove)->getRightChild());
        (*parent)->setRightChild(**temp);
      }
      else {
        root = (*Node_to_remove)->getRightChild();
      }
    }
    else {
      if((*parent)->getRightChild() == *Node_to_remove) {
        temp = &((*Node_to_remove)->getRightChild());
        (*parent)->setRightChild(**temp);
      }
      else {
        temp = &((*Node_to_remove)->getLeftChild());
        (*parent)->setLeftChild(**temp);
      }
      if(Node_to_remove == &root) {
        root = root->getRightChild();
      }
    }
  }
}

template <typename T>
void BST<T>::print() {
  traversalPrint(root);
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
