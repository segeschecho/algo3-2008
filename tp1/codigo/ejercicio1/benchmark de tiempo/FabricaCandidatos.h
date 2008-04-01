#ifndef _FabricaCandidatos_H
#define _FabricaCandidatos_H

class FabricaCandidatos {
    private:
        unsigned long long numeroActual;
        unsigned long long k;
        bool turno;

    public:
        FabricaCandidatos();
        unsigned long long int siguiente();
};
#endif /*_FabricaCandidatos_H*/

