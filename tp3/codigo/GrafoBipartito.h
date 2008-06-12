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

class GrafoBipartito {
  public:
      GrafoBipartito(const list<nodo>& Part1, const list<nodo>& Part2, const list<eje> & ejes);
      GrafoBipartito(const GrafoBipartito& g);
      ~GrafoBipartito();

      unsigned int gradoDe(nodo v) const;
      void operator = (const GrafoBipartito& g);

  private:
      vector<nodo> P1, P2;
      unsigned int m, n;
      vector< vector<nodo> > diccEjes;
};

#endif
