#include "BST.h"
#include <iostream>
#include <list>
#include<vector>

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
  Node<T>* ch;
  std::vector<Node<T>* > v1 = InOrderTraversal(root);
  bool other = false;
  for(unsigned int i=0; i<v1.size(); i++) {
    ch = v1[i];
    findB(&ch);
    if(ch->getBalance() == -2 || ch->getBalance() == 2) {
      other = true;
      break;
    }
  }
  while(other == true) {
    Node<T>* cn = ch;
    rotate(&cn);
    bool again = false;
    std::vector<Node<T>* > x = InOrderTraversal(root);
    for(unsigned int j=0; j<x.size(); j++) {
      Node<T>* cn = x[j];
      findB(&cn);
      if(ch->getBalance() == -2 || ch->getBalance() == 2) {
        again = true;
        break;
      }
    }
    if(again == false) {
      other = false;
    }
  }
}

template <typename T>
void BST<T>::remove(T v) {
  Node<T>** Node_to_remove = &root;
  Node<T>** temp = &root;
  Node<T>** removeRight = &root;
  Node<T>** removeLeft = &root;
  if(root->getValue() != v) {
    Node<T>**parent = &root;
    while((*Node_to_remove)->getValue() != v && *Node_to_remove != 0) {
      parent = Node_to_remove;
      if((*Node_to_remove)->getValue() < v) {
        Node_to_remove = (&((*Node_to_remove)->getRightChild()));
      }
      else if((*Node_to_remove)->getValue() > v) {
        Node_to_remove = &((*Node_to_remove)->getLeftChild());
      }
    }
    removeRight = &((*Node_to_remove)->getRightChild());
    removeLeft = &((*Node_to_remove)->getLeftChild());
    if(*removeLeft != 0) {
      Node<T>** replacement_parent = Node_to_remove;
      Node<T>** replacement = removeLeft;
      while((*replacement)->getRightChild() != 0) {
        replacement_parent = replacement;
        replacement = &((*replacement)->getRightChild());
      }
      if((*replacement)->getLeftChild() != 0) {
        temp = &((*replacement)->getLeftChild());
        if((*replacement_parent)->getValue() < (*replacement)->getValue()) {
          (*replacement_parent)->setRightChild(**temp);
        }     
      }
      if((*parent)->getValue() < v) {
        temp = &(*replacement);
        (*parent)->setRightChild(**temp);
      }
      else {
        temp = &(*replacement);
        (*parent)->setLeftChild(**temp);
      }
      if(removeLeft != replacement) {
        temp = &(*removeLeft);
        (*replacement)->setLeftChild(**temp);
      }
      if(*removeRight != 0) {
        temp = &(*removeRight);
        (*replacement)->setRightChild(**temp);
      }
    }
    else if(*removeLeft == 0) {
      if(*removeRight != 0) {
        temp = &(*removeRight);
        (*parent)->setRightChild(**temp);
      }
      else {
        if((*parent)->getRightChild() == *Node_to_remove) {
          temp = &(*removeRight);
          (*parent)->setRightChild(**temp);
        }
        else {
          temp = &(*removeLeft);
          (*parent)->setLeftChild(**temp);
        }
      }
    }
  }
  else {
    removeLeft = &((*Node_to_remove)->getLeftChild());
    removeRight = &((*Node_to_remove)->getRightChild());
    if(removeLeft != 0) {
      Node<T>** replacement = removeLeft;
      Node<T>** replacement_parent = Node_to_remove;
      while((*replacement)->getRightChild() != 0) {
        replacement_parent = replacement;
        replacement = &((*replacement)->getRightChild());
      }
      Node<T>* newNode = new Node<T>((*replacement)->getValue());
      temp = &(*removeLeft);
      newNode->setLeftChild(**temp);
      temp = &(*removeRight);
      newNode->setRightChild(**temp);
      root = &(*newNode);    
      temp = &((*replacement)->getLeftChild());
      if((*replacement_parent)->getValue() < (*replacement)->getValue()) {
        (*replacement_parent)->setRightChild(**temp);
      }
      else {
        (*replacement_parent)->setLeftChild(**temp);
      } 
    }
  }
}

template<typename T>
void BST<T>::rotate(Node<T>** cn) {
  short int d = (*cn)->getBalance();
  bool r;
  if(cn == &root) {
    r = true;
  }
  else {
    r = false;
  }
  if(d == 2) {
    Node<T>** tempRC = &((*cn)->getRightChild());
    Node<T>** tempLC;
    bool l = false;
    if(&((*tempRC)->getLeftChild()) != 0) {
      tempLC = &((*tempRC)->getLeftChild());
      l = true;
    }
    Node<T>** tempCN = &(*cn);
    (*tempRC)->setLeftChild(**tempCN);
    if(r == true) {
      root = *tempRC;
    }
    if(l == true) {
      (*cn)->setRightChild(**tempLC);
    }
  }
  if(d == -2) {
    Node<T>** tempLC = &((*cn)->getLeftChild());
    Node<T>** tempRC;
    bool R = false;
    if(&((*tempLC)->getRightChild()) != 0) {
      R = true;
      tempRC = &((*tempLC)->getRightChild());
    }
    Node<T>** tempCN = &(*cn);
    (*tempLC)->setRightChild(**tempCN);
    if(r == true) {
      root = *tempLC;
    }
    if(R == true) {
      (*cn)->setLeftChild(**tempRC);
    } 
  }
}

template<typename T>
void BST<T>::findB(Node<T>** n) {
  short int leftH = 0;
  short int rightH = 0;
  bool noL = false;
  bool noR = false;
  if((*n)->getLeftChild() == 0) {
    leftH = 0;
    noL = true;
  }
  if((*n)->getRightChild() == 0) {
    rightH = 0;
    noR = true;
  }
  else if(noL == false || noR == false) {
    std::vector<Node<T>* > v = InOrderTraversal(&(**n));
    for(unsigned int i=0; i<v.size(); i++) {
      Node<T>* nlow = v[i-1];
      Node<T>* npar = v[i];
      Node<T>* nhigh = v[i+1];
      if(npar == *n) {
        if(nlow != 0) {
          leftH = nlow->getBalance() - 1;
        }
        if(nhigh != 0) {
          rightH = nhigh->getBalance() + 1;;
        } 
      }
    }
  }
  short int bal = rightH - leftH;
  (*n)->setBalance(bal);
}

template <typename T>
void BST<T>::InOrderTraversalPrint() {
  std::vector<Node<T>* > v = InOrderTraversal(root);
  for(unsigned int i=0; i<v.size(); i++) {
    Node<T>* n = v[i];
    std::cout << n->getValue() << std::endl;
  }
}

template <typename T>
void BST<T>::PostOrderTraversalPrint() {
  std::vector<Node<T>* > v = PostOrderTraversal(root);
  for(unsigned int i=0; i<v.size(); i++) {
    Node<T>* n = v[i];
    std::cout << n->getValue() << std::endl;
  }
}

template <typename T>
std::vector<Node<T>* > BST<T>::InOrderTraversal(Node<T>* n) {
  std::vector<Node<T>* > v;
  if(n != 0) {
    InOrderTraversal(n->getLeftChild());
    v.push_back(n);
    InOrderTraversal(n->getRightChild());
  }
  return v;
}

template<typename T>
std::vector<Node<T>* > BST<T>::PostOrderTraversal(Node<T>* n) {
 std::vector<Node<T>* > v; 
 if(n != 0) {
    PostOrderTraversal(n->getLeftChild());
    PostOrderTraversal(n->getRightChild());
    v.push_back(n);
  }
  return v;
}

template<typename T>
void BST<T>::visualRepPrint() {
  std::string space = " ";
  std::string LeftChildLine = "L";
  std::string RightChildLine = "R";
  int middle = 70;
  std::list<Node<T>* > parentQueue;
  std::list<Node<T>* > childQueue;
  std::list<int> spacing;
  childQueue.push_back(root);
  Node<T>* pop;
  Node<T>* parent;
  int crowSize = childQueue.size();
  while(crowSize > 0) {
    int sp_row = 0;
    int gap = 0;
    for(int i=0; i<crowSize; i++) {
      pop = childQueue.front();
      childQueue.pop_front();
      if(pop == root) {
      for(int x=0; x<middle; x++) {
        std::cout << space;
      }
      std::cout << pop->getValue();
      spacing.push_back(middle);
      }
      else if(pop != root) {
        bool p = false;
        int side = 0;
        int sp_p = 0;
        int sp_c = 0;
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
        for(int x=0; x<gap; x++) {
          std::cout << space;
        }
        std::cout << pop->getValue();
        sp_row = sp_row+gap;
        spacing.push_back(sp_c);
      }
      parentQueue.push_back(pop);
      if(pop->getLeftChild() != 0) {
        childQueue.push_back(pop->getLeftChild());
      }
      if(pop->getRightChild() != 0) {
        childQueue.push_back(pop->getRightChild());
      }
    }
    std::cout << std::endl;
    int prowSize = parentQueue.size();
    gap = 0;
    sp_row = 0;
    if(childQueue.size() > 0) {
      for(int a=0; a<prowSize; a++) {
        pop = parentQueue.front();
        parentQueue.pop_front();
        parentQueue.push_back(pop);
        int sp_p = spacing.front();
        int sp_c = 0;
        spacing.pop_front();
        spacing.push_back(sp_p);
        if(pop->getLeftChild() != 0) {
          sp_c = sp_p-3;
          gap = sp_c - sp_row;
          for(int x=0; x<gap; x++) {
            std::cout << space;
          }
          std::cout << LeftChildLine;
          sp_row = sp_row+gap;
        }
        if(pop->getRightChild() != 0) {
          sp_c = sp_p+3;
          gap = sp_c - sp_row;
          for(int y=0; y<gap; y++) {
            std::cout << space;
          }
          std::cout << RightChildLine;
          sp_row = sp_row+gap; 
        }
      }
    }
    crowSize = childQueue.size();
    std::cout << std::endl;
  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
