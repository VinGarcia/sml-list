#include <stdlib.h>
#include "lista.hpp"

// Build a node of the list.
cLista::cLista(tAtrb atrb)
{
  this->atrb = atrb;
  this->prox = NULL;
}

// Build a node of the list.
cLista* cLista::cLista(tAtrb atrb)
{
	return new cLista(atrb);
}

cLista* cLista::tail()
{
  return this->prox;
}

tAtrb cLista::head()
{
  return this->atrb;
}

// Return this->tail() and make this->prox = NULL.
cLista* cLista::cuttail()
{
  cLista* aux = this->tail();
  
  this->prox = NULL;
  
  return aux;
}

// Returns this->head() and free the header cell memory space.
tAtrb cLista::rmhead()
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
int cLista::cat(cLista* list)
{
	cLista* aux = this;

  // find the last item from head:
  while(aux->tail()) aux = aux->tail();
  
  // Concatenate the two lists if head!=NULL:
  if(aux) aux->prox = list;
  
  return 0;
}

// Link the this node with the tail node. (this->prox = tail)
// Beware: If this have a tail, the tail pointer will be overwrited.
int cLista::link(cLista* tail)
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
cLista* cLista::push(tAtrb atrb)
{
  cLista* aux = new cLista(atrb);
  aux->link(this->tail());
  this->link(aux);
  return this;
}

// Remove and free the item in front of the header cell of l.
// Also links the header to the removed cell tail.
// (extract the item on the top of the stack)
tAtrb cLista::pop()
{
  cLista* aux = this->tail();
  this->link(aux->tail());
  return aux->rmhead();
}

