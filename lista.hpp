
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

template <class* tAtrb> class cLista {

  private:

	tAtrb atrb;
	cLista* prox;
  
	// Constructor function of a node on the list:
  cLista(tAtrb atrb);

	public:
  
  /* Functions */

	// Factory function of a node on the list:
  cLista* pLista(tAtrb atrb);
  
	// Function that returns the `tail` i.e. `l->prox`
  cLista* tail();
  
	// Returns the tAtrb file on the header cell of the list.
  tAtrb head();
  
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
  
  // Extrai e desaloca l->prox sem quebrar a lista, e retorna seu valor.
	// Extract and unalloc l->prox cell an returns its value.
	// Also links the header cell with l->prox->prox.
  tAtrb pop();
};

#endif
 
// Useful macros:

// For making an alias for the list:
#ifndef NOMELISTA
  #define NOMELISTA cLista;
#endif 
typedef cLista NOMELISTA;

// For iterating over the list:
#ifndef FORLISTA
  #define FORLISTA
  #define forLista(l,i) for(i=l->tail();i;i=i->tail())
  // The for below makes the same as the above, but keeps
	// track of the father node of the current loop node.
  #define forListaPai(l,i,f) for(f=l,i=l->tail();i;i=i->tail(),f=tail(f))
#endif
