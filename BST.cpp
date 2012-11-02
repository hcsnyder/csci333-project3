#include "BST.h"
#include <iostream>
#include <list>

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
    if(Node_to_remove != &root) {
      if((*parent)->getValue() < v) {
        temp = &((*replacement_parent)->getRightChild());
        (*parent)->setRightChild(**temp);
      }
      else {
        temp = &((*replacement_parent)->getRightChild());
        (*parent)->setLeftChild(**temp);
      }
    }
    if(Node_to_remove == &root) {
      root = *replacement;
    }
    if((*Node_to_remove)->getLeftChild() != 0) {
      temp = &((*Node_to_remove)->getLeftChild());
      (*replacement)->setLeftChild(**temp);
    }
    if((*Node_to_remove)->getRightChild() != 0) {
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

template<typename T>
void BST<T>::visualRepPrint() {
  std::string space = " ";
  std::string LeftChildLine = "//";
  std::string RightChildLine = "\\";
  int row = 1;
  int middle = 70;
  std::list<Node<T>* > parentQueue;
  std::list<Node<T>* > childQueue;
  std::list<int> spacing;
  childQueue.push_back(root);
  Node<T>* pop;
  Node<T>* parent;
  int rowSize = childQueue.size();
  while(childQueue.size > 0) {
    int sp_row = 0;
    int gap = 0;
    for(int i=0; i<rowSize; i++) {
      pop = childQueue.front();
      childQueue.pop_front();
      if(pop == root) {
      std::cout << space*middle << pop.getValue();
      spacing.push_back(middle);
      }
      else if(pop != root) {
        bool p = false;
        int side = 0;
        int sp_p = 0;
        int sp_c = 0;
        int sp_row = 0;
        while(p == false) {
          if(parentQueue.front()->getLeftChild() == pop) {
            side = 0;
            p = true;
            sp_p = spacing.front();
            parent = parentQueue.front();
          }
          else if(parentQueue.front()->getRightChild() == pop) {
            side = 1;
            p = true;
            parent = parentQueue.front();
            parentQueue.pop_front();
            sp_p = spacing.front();
            spacing.pop_front();
          }
          else {
            p = false;
            parentQueue.pop_front();
            spacing.pop_front();
          }
        }
        if(side == 0) {
          sp_c = sp_p-6;
        }
        else if(side == 1) {
          sp_c = sp_p+6;
        }
        gap = sp_c - sp_row;
        std::cout << space*gap << pop.getValue();
        sp_row = gap;
        spacing.push_back(sp_c);
      }
      parentQueue.push_back(pop);
      if(pop->getLeftChild() != 0) {
        ChildQueue.push_back(pop->getLeftChild());
      }
      if(pop->getRightChild() != 0) {
        ChildQueue.push_back(pop->getRightChild());
      }
    }
    std::cout << std::endl;
    rowSize = childQueue.size();
    gap = 0;
    for(int j=0; j<rowSize; i++) {
      pop = childQueue.front();
      childQueue.pop_front();
      childQueue.push_back(pop);
      int sp_p = spacing.front();
      int sp_c = 0;
      sp_row = 0;
      spacing.pop_front();
      spacing.push_back(sp_p);
      if(pop->getLeftChild() != 0) {
        sp_c = sp_p-3;
        gap = sp_c - sp_row;
        std::cout << space*gap << LeftChildLine;
        sp_row = gap;
      }
      if(pop->getRightChild() != 0) {
        sp_c = sp_p+3;
        gap = sp_c - sp_row;
        std::cout << space*gap << RightChildLine;
        sp_row = gap; 
      }
    }
    std::cout <<std::endl;
  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
