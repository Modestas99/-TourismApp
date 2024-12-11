
#include <iostream>
#include <string>
#include "funksjoner.h"
using namespace std;


/**
 * Skriver ut hovedmenyen.
 * 
 */
void skrivMeny() {

    cout << "\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:\n\n"
         << "\tT A\t - Skriv alle turoperatorer\n"
         << "\tT 1\t - Skriv alt om en turoperator\n"
         << "\tT N\t - Ny turoperator\n"
         << "\tT E\t - Endre noe om en turoperator\n"
         << "\tT O\t - Lag opplegg for en turoperator\n"
         << "\tT F\t - Fjern/slett en turoperator\n\n"

         << "\tB A\t - Skriv alle byer\n"
         << "\tB 1\t - Skriv alt om en by\n"
         << "\tB N\t - Ny By\n"
         << "\tB F\t - Fjern/slett en by\n\n"

         << "\tA N\t - Ny attraksjon i en by\n"
         << "\tA F\t - Fjern/slett attraksjon i by\n\n"

         << "\tQ  \t - Quit / avslutt\n"; 
};