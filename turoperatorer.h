#ifndef TUROPERATORER_H
#define TUROPERATORER_H

#include "turoperator.h"
#include <string>
#include <vector>
#include <map>

class Turoperatorer {
private:
    std::map<std::string, Turoperator*> turoperatorer;

public:
    void endreEnTuroperator();
    void endreEnTuroperatorMeny();
    std::string finnEntydigNavn(const std::string& navn);
    void lagEtOpplegg();
    void lesFraFil();
    void nyTuroperator();
    void skrivAlleTuroperatorer();
    void skrivEnTuroperator();
    void skrivTilFil();
    void slettEnTuroperator();
    void OperatorHandling(char valg);
};

#endif