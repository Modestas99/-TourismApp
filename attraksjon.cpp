#include "attraksjon.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


/**
 * Skriver ut dataene til attraksjonen, inkludert navn, adresse, beskrivelse og webside.
 * 
 */
void Attraksjon::SkrivData() {
    cout << "\t" << ID << ",  \t" << adresse << "\n"
         << "\t" << beskrivelse << "\n"
         << "\t" << webside << "\n";
}


/**
 * Attraksjon constructor som leser inn data fra fil.
 * 
 * @param inn Fil som skal leses fra.
 */
Attraksjon::Attraksjon(ifstream & inn) {
    getline(inn,ID);
    getline(inn,beskrivelse);
    getline(inn,adresse);
    getline(inn,webside);
}


/**
 * Attraksjon constructor som ber brukeren om å oppgi dens data.
 * Hvis brukeren ikke oppgir noe blir en default value av "----" satt.
 * 
 */
Attraksjon::Attraksjon() {
    cout << "\tNavn: "; 
    getline(cin, ID);
    if (ID.empty()) {
        cout << "\tNavn tom, setter default verdi \"----\"\n\n";
        ID = "----"; }

    cout << "\tBeskrivelse: "; 
    getline(cin, beskrivelse);
    if (beskrivelse.empty()) {
        cout << "\tBeskrivelse tom, setter default verdi \"----\"\n\n";
        beskrivelse = "----"; }

    cout << "\tAdresse: "; 
    getline(cin, adresse);
    if (adresse.empty()) {
        cout << "\tAdresse tom, setter default verdi \"----\"\n\n";
        adresse = "----"; }

    cout << "\tWeb-side: "; 
    getline(cin, webside);
    if (webside.empty()) {
        cout << "\tWeb-side tom, setter default verdi \"----\"\n\n";
        webside = "----"; }
}


/**
 * Returnerer navnet til attraksjonen.
 * 
 * @return Navnet til attraksjonen.
 */
string Attraksjon::getNavn() { return ID; }


/**
 * Skriver attraksjonens data til fil.
 * 
 * @param utfil Filen som skal skrives til
 */
void Attraksjon::skrivTilFil(ofstream& utfil) const {
    utfil << ID << "\n";
    utfil << beskrivelse << "\n";
    utfil << adresse << "\n";
    utfil << webside << "\n";
}


/**
 * Returnerer "dummy" typen til attraksjon som videre blir overskrevet.
 * Blir ikke brukt for noen ting
 * 
 * @return Attraksjons type
 */
char Attraksjon::getType() const {return 'A'; }
