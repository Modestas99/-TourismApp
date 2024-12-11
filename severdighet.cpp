#include "severdighet.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


/**
 * Skriver ut severdighetens data, inkludert type og aktivitet
 * 
 * @see Attraksjon::SkrivData()
 */
void Severdighet::SkrivData() {

    cout << "Severdighet";
    Attraksjon::SkrivData(); //Skriver ut dataene fra 'Attraksjon'-klassen.
    cout << "\t" << aktivitet << "\n\n";
}


/**
 * Severdighet constructor som leser inn data fra fil.
 * 
 * @param inn Fil som skal leses fra.
 * @see Attraksjon::Attraksjon(infil)
 */
Severdighet::Severdighet(ifstream &inn) : Attraksjon(inn) {
    getline(inn,aktivitet);
}


/**
 * Severdighet constructor som ber brukeren om å oppgi dens data.
 * Attraksjon constructor blir kjørt først for å lese inn opprinelig data.
 * Hvis brukeren ikke oppgir noe blir en default value av "----" satt.
 * 
 * @see Attraksjon::Attraksjon()
 */
Severdighet::Severdighet() : Attraksjon() {

    cout << "\tSpesielt: "; 
    getline(cin, aktivitet);
    if (aktivitet.empty()) {
        cout << "\tIngenting spesielt, setter default verdi \"----\"\n\n";
        aktivitet = "----"; }
}


/**
 * Skriver severdighetens data til fil.
 * 
 * @see Attraksjon::skrivTilFil()
 * @param utfil Fil som skal skrives til
 */
void Severdighet::skrivTilFil(ofstream& utfil) const {

    Attraksjon::skrivTilFil(utfil);
    utfil << aktivitet << "\n";
}


/**
 * Returnerer bokstav 'S' for typen Severdighet.
 * 
 * @return Objekttype
 */
char Severdighet::getType() const { return 'S'; } 