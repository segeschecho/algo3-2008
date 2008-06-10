#ifndef _GRAFOBIPARTITO_H_
#define _GRAFOBIPARTITO_H_
#include <list>

using namespace std;

#define nodo unsigned

struct eje{
  nodo primero;
  nodo segundo;
};

class GrafoBipartito {
  public:
      GrafoBipartito(unsigned int cardinalV1, unsigned int cardinalV2, const list< eje > & ejes);
      GrafoBipartito(const GrafoBipartito& g);
      ~GrafoBipartito();

      bool perteneceAV1(nodo v) const;
      unsigned int grado(nodo v) const;
      GrafoBipartito operator = (const GrafoBipartito& g);

  private:
      unsigned int cantNodosV1, cantNodosV2;
      unsigned int cantEjes;
      nodo* gradoDe;
      list<nodo>* _ejes;
};

#endif
