#ifndef _GRAFOBIPARTITO_H_
#define _GRAFOBIPARTITO_H_
#include <list>
#include <vector>

using namespace std;

#define nodo unsigned int

struct eje{
    nodo primero;
    nodo segundo;
};

nodo maxElem(const vector<nodo>& p);

class GrafoBipartito {
    friend class Dibujo;
  public:
      GrafoBipartito(const list<nodo>& Part1, const list<nodo>& Part2, const list<eje> & ejes);
      GrafoBipartito(const GrafoBipartito& g);
      ~GrafoBipartito();

      unsigned int cantNodos(void) const;
      unsigned int cantEjes(void) const;
      unsigned int grado(nodo v) const;
      void operator = (const GrafoBipartito& g);

  //private:
      vector<nodo> V1, V2;
      unsigned int m, n;
      vector< vector<nodo> > diccEjes;
};

#endif
