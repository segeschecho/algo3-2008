#ifndef _GRAFOBIPARTITO_H_
#define _GRAFOBIPARTITO_H_
#include <list>

using namespace std;

#define nodo unsigned int
class GrafoBipartito {
  public:
      struct eje{
          nodo primero;
          nodo segundo;
      };
      GrafoBipartito(unsigned int cardinalV1, unsigned int cardinalV2, const list< eje > & ejes);
      GrafoBipartito(const GrafoBipartito& g);
      ~GrafoBipartito();

      unsigned int gradoDe(nodo v) const;
      void operator = (const GrafoBipartito& g);

  private:
      unsigned int cantNodosV1, cantNodosV2;
      unsigned int cantEjes;
      list<nodo>* diccEjes;
};

#endif
