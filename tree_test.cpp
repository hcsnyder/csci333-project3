#include "BST.h"

int main() {
  BST<int>* bst = new BST<int>();

  bst->insert(5);
  bst->insert(6);
  bst->insert(3);
  bst->insert(4);
  bst->insert(2);
  bst->insert(7);


  bst->print();

  bst->visualRepPrint();

  bst->remove(6);

  bst->print();

  bst->visualRepPrint();

  bst->insert(1);
  bst->insert(6);
  bst->insert(8);

  bst->print();

  bst->visualRepPrint();

  bst->remove(5);

  bst->print();

  bst->visualRepPrint();
}
