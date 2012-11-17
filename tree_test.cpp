#include "BST.h"

int main() {
  BST<int>* avl = new BST<int>();

  avl->insert(5);
  avl->insert(6);
  avl->insert(7);

  //avl->visualRepPrint();

  avl->insert(3);
  avl->insert(4);
  avl->insert(2);

  //avl->visualRepPrint();

}
