#include <stdlib.h>
#include "lista.hpp"

// Build a node of the list.
template <class tAtrb>
cLista<tAtrb>::cLista(tAtrb atrb)
{
  this->atrb = atrb;
  this->prox = NULL;
}

template <class tAtrb>
cLista<tAtrb>* cLista<tAtrb>::tail()
{
  return this->prox;
}

template <class tAtrb>
tAtrb cLista<tAtrb>::head()
{
  return this->atrb;
}

// Return this->tail() and make this->prox = NULL.
template <class tAtrb>
cLista<tAtrb>* cLista<tAtrb>::cuttail()
{
  cLista<tAtrb>* aux = this->tail();
  
  this->prox = NULL;
  
  return aux;
}

// Returns this->head() and free the header cell memory space.
template <class tAtrb>
tAtrb cLista<tAtrb>::rmhead()
{
  tAtrb aux = this->head();
  
  delete this;
  
  return aux;
}

// Concatenate two lists into one -- Complexity O(list1.length).
// Beware this function may create a circular list thus: infinit loop.
// To insert a list inside another list do:
//   aux = list1->cuttail();
//   list1->link(list2);
//   list2->cat(aux);
template <class tAtrb>
int cLista<tAtrb>::cat(cLista<tAtrb>* list)
{
	cLista<tAtrb>* aux = this;

  // find the last item from head:
  while(aux->tail()) aux = aux->tail();
  
  // Concatenate the two lists if head!=NULL:
  if(aux) aux->prox = list;
  
  return 0;
}

// Link the this node with the tail node. (this->prox = tail)
// Beware: If this have a tail, the tail pointer will be overwrited.
template <class tAtrb>
int cLista<tAtrb>::link(cLista<tAtrb>* tail)
{
  // Link the head to the tail
  this->prox = tail;
  
  return 0;
}

/* * * * * Stack Operations * * * * */

// This operations assumes the header cell contains no value.
// The stack is built as the tail of the this cell.

// Insert an item in front of the header cell of l.
// (insert it on the top of the stack)
template <class tAtrb>
cLista<tAtrb>* cLista<tAtrb>::push(tAtrb atrb)
{
  cLista<tAtrb>* aux = new cLista(atrb);
  aux->link(this->tail());
  this->link(aux);
  return this;
}

// Remove and free the item in front of the header cell of l.
// Also links the header to the removed cell tail.
// (extract the item on the top of the stack)
template <class tAtrb>
tAtrb cLista<tAtrb>::pop()
{
  cLista<tAtrb>* aux = this->tail();
  this->link(aux->tail());
  return aux->rmhead();
}

