
/* Simple SML List */

// This list have only basic abstractions leaving the rest up to the
// programmer. All functions threat NULL parameters so they
// don't cause segmentation fault.
//
// All functions return value is tAtrb or cLista* in normal cases,
// and NULL or tAtrbInval when an error hapens.
//
// Read more about tAtrb and tAtrbInval below.

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SML_LISTA
#define SML_LISTA
  
// Below is the error return value for functions that should return
// an tAtrb, by default its NULL:
// Change it if tAtrb is not a pointer.
#define tAtrbInval NULL

#define hd(l) l->head()
#define tl(l) l->tail()
#define rmhd(l) l->rmhead()
#define cuttl(l) l->cuttail()

template <class tAtrb> class cLista {

  private:

	tAtrb atrb;
	cLista* prox;

	public:

	// len keeps the number of cells on this->tail().
	//
	// If you call any state change function on the list tail cells
	// the len value will not be updated.
	//
	// The only functions you can use on the tail safely are:
	//   hd() and tail().
	//
	// Or len will contain an incorrect value.
	int len=0;

  /* Functions */
  
	// Constructor function of a node on the list:
  cLista<tAtrb>(tAtrb atrb);
  cLista<tAtrb>();

	// Function that returns the `tail` i.e. `l->prox`
  cLista*& tail();
  
	// Returns the tAtrb file on the header cell of the list.
  tAtrb& head();
  
	// Returns the tail(l) and makes l->prox = NULL;
  cLista* cuttail();
  
	// Returns head(l) and call free(l);
  tAtrb rmhead();
  
	// Concatenates the two lists into one.
  int cat(cLista* tl);
  
  // link the head node to the list l (head->prox = l)
  int link(cLista* l);
  
  /* * * * * Stack Operations: * * * * */
  
	// Insert an item atrb right after the header cell of l.
  cLista* push(tAtrb atrb);
	// Insert a node right after the header cell of l.
  cLista* push(cLista* node);
  
  // Extrai e desaloca l->prox sem quebrar a lista, e retorna seu valor.
	// Extract and unalloc l->prox cell an returns its value.
	// Also links the header cell with l->prox->prox.
  tAtrb pop();
};

// Build a node of the list.
template <class tAtrb>
cLista<tAtrb>::cLista(tAtrb atrb)
{
  this->atrb = atrb;
  this->prox = NULL;
}

// Build a node of the list.
template <class tAtrb>
cLista<tAtrb>::cLista()
{
  this->atrb = NULL;
  this->prox = NULL;
}

template <class tAtrb>
cLista<tAtrb>*& cLista<tAtrb>::tail()
{
  return this->prox;
}

template <class tAtrb>
tAtrb& cLista<tAtrb>::head()
{
  return this->atrb;
}

// Return this->tail() and make this->prox = NULL.
template <class tAtrb>
cLista<tAtrb>* cLista<tAtrb>::cuttail()
{
  cLista<tAtrb>* aux = this->tail();
  
  this->prox = NULL;

	// Update length:
	this->len = 0;
  
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

	// Update length:
	this->len += list->len+1;

  // find the last item from head:
  while(aux->tail()) {
		// Update length:
		aux->len += list->len+1;

		aux = aux->tail();
	}
  
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

	// Update length:
  this->len += tail->len+1;
  
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
	// Create and insert a new attribute:
  cLista<tAtrb>* aux = new cLista(atrb);
  aux->prox = this->tail();
  this->prox = aux;

	// Update length:
  this->prox->len = this->len;
	this->len++;
  return this;
}

// Insert a node in front of the header cell of l.
// (insert it on the top of the stack)
template <class tAtrb>
cLista<tAtrb>* cLista<tAtrb>::push(cLista* node)
{
  node->link(this->tail());
  this->link(node);

	// Update length:
  this->prox->len = this->len;
	this->len++;
  return this;
}

// Remove and free the item in front of the header cell of l.
// Also links the header to the removed cell tail.
// (extract the item on the top of the stack)
template <class tAtrb>
tAtrb cLista<tAtrb>::pop()
{
  cLista<tAtrb>* aux = this->tail();
  this->prox = aux->tail();

	// Update length:
	this->len--;
  return aux->rmhead();
}


#endif
 
// Useful macros:

// For iterating over the list:
#ifndef FORLISTA
  #define FORLISTA
  #define forLista(l,i) for(i=l->tail();i;i=i->tail())
  // The for below makes the same as the above, but keeps
	// track of the father node of the current loop node.
  #define forLista3(l,i,f) for(f=l,i=l->tail();i;i=i->tail(),f=f->tail())
#endif
