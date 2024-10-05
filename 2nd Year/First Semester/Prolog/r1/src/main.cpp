// Teacher's model
#include "lista.h"

#include <iostream>

/*
   Flow model:
      (p == NULL) -> []
      (p->urm == NULL) -> [p]
      else -> last + [p]
*/
PNod reverse_rec(Lista &l, PNod p)
{
   if(p == NULL)
      return NULL;

   if(p->urm == NULL) {
      l._prim = p;
      return p;
   }

   PNod last = reverse_rec(l, p->urm);
   last->urm = p;
   p->urm = NULL;
   return p;
}

void reverse(Lista &l)
{
   reverse_rec(l, l._prim);
}

/*
   Flow model:
      (p == NULL) -> 0
      (p->urm == NULL) -> p->e
      else -> max(last, p->e)
*/
TElem maximum_rec(PNod p)
{
   if(p == NULL)
      return 0;

   if(p->urm == NULL)
      return p->e;

   TElem last = maximum_rec(p->urm);
   if(last > p->e)
      return last;

   return p->e;
}

TElem maximum(Lista l)
{
   return maximum_rec(l._prim);
}

int main()
{
   Lista l = creare();
   std::cout << "Lista initiala: \n";
   tipar(l);
   std::cout << "Lista inversata: \n";
   reverse(l);
   tipar(l);
   std::cout << "Maximul listei: " << maximum(l) << "\n";
}
