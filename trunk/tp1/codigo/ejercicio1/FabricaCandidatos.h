#ifndef _FabricaCandidatos_H
#define _FabricaCandidatos_H

using namespace std;

class FabricaCandidatos {
    private:
        unsigned numeroActual;
        unsigned int k;
        short int turno;

    public:
        FabricaCandidatos();
        int siguiente();
};
#endif /*_FabricaCandidatos_H*/

