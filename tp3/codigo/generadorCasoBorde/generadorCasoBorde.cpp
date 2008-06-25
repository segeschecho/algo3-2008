void armarCasoBordeConstructiva(vector<nodo>& fijos1, vector<nodo>& fijos2, vector<nodo>& todos1, vector<nodo>& todos2, list<eje>& listaEjes, unsigned int size) {
    try {
        if (size % 2 == 0) {
            throw "La cantidad de nodos es par. Debe ser impar!";
        }

        nodo v = 0;

        while (v < (size - 3)/2) {
            todos1.push_back(v);
            fijos1.push_back(v);
            v++;
        }

        while (v < (size - 3)/2 + 2) {
            todos2.push_back(v);
            fijos2.push_back(v);
            v++;
        }

        // hay 1 solo movil en la particion 1
        todos1.push_back(v);
        v++;

        while (v < size) {
            todos2.push_back(v);
            v++;
        }

        // ahora armo la lista de ejes
        vector<nodo>::const_iterator it1 (todos1.begin());
        vector<nodo>::const_iterator it2 (todos2.begin());
        // salteo los 2 fijos de p2
        it2++;
        it2++;

        for (unsigned int i = 0; i < todos1.size() - 1; i++) {
            eje e;
            e.primero = *it1;
            e.segundo = *it2;
            listaEjes.push_back(e);
            it1++;
            it2++;
        }

        eje e;
        e.primero = *it1;
        e.segundo = *(todos2.begin());
        listaEjes.push_back(e);
        e.segundo = *(todos2.begin() + 1);
        listaEjes.push_back(e);
        e.segundo = *(todos2.begin() + 2);
        listaEjes.push_back(e);
    }
    catch(char * str){
        cout << "Excepcion: " << str;
    }
}