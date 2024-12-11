#include "museumgalleri.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


/**
 * Skriver ut museums data, inkludert type og høydepunkt.
 * 
 * @see Attraksjon::SkrivData()
 * 
 */
void MuseumGalleri::SkrivData() {

    cout << "Museum/Galleri";
    Attraksjon::SkrivData(); //Skriver ut dataene fra 'Attraksjon'-klassen.
    cout << "\t" << hoydepunkt << "\n\n";
}


/**
 * MuseumGalleri constructor som leser inn data fra fil.
 * Attraksjon constructor blir kjørt først for å lese inn opprinelig data.
 * 
 * @param inn Fil som skal leses fra.
 * @see Attraksjon::Attraksjon(innfil)
 */
MuseumGalleri::MuseumGalleri(ifstream &inn) : Attraksjon(inn) {
    getline(inn,hoydepunkt);
}


/**
 * MuseumGalleri constructor som ber brukeren om å oppgi dens data.
 * Attraksjon constructor blir kjørt først for å lese inn opprinelig data.
 * Hvis brukeren ikke oppgir noe blir en default value av "----" satt.
 * 
 * @see Attraksjon::Attraksjon()
 */
MuseumGalleri::MuseumGalleri() : Attraksjon() {
    cout << "\tHoydepunkt: "; 
    getline(cin, hoydepunkt);
    if (hoydepunkt.empty()) {
        cout << "\tHoydepunkt tom, setter default verdi \"----\"\n\n";
        hoydepunkt = "----"; }
}


/**
 * Skriver dataene til museum til fil.
 * 
 * @param utfil Fil som skal skrives til
 * @see Attraksjon::skrivTilFil()
 */
void MuseumGalleri::skrivTilFil(ofstream& utfil) const {

    Attraksjon::skrivTilFil(utfil);
    utfil << hoydepunkt << "\n";
}


/**
 *  Returnerer bokstav 'M' for typen Museum/Galleri.
 * 
 * @return Objekttype
 */
char MuseumGalleri::getType() const { return 'M'; }

