#include "kirke.h"
#include "LesData3.h"
#include "const.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


/**
 * Skriver ut kirkens data, inkludert type, byggeår og kapasitet
 * 
 * @see Attraksjon::SkrivData()
 */
void Kirke::SkrivData() {
    
    switch (kirkeType) {
        case KirkeType::KATEDRAL: cout << "Katedral";   break;
        case KirkeType::KIRKEE:   cout << "Kirke";      break;
        case KirkeType::KAPELL:   cout << "Kapell";     break;
        default: cout << "Kirke"; // Blir ikke brukt, da kirkene må ha en av enum verdiene
    }

    Attraksjon::SkrivData(); // Skriver ut dataene fra 'Attraksjon'-klassen.
    cout << "\tBygget ca. aar: " << byggeaar << "\tKapasitet: " << kapasitet << "\n\n";
}



/**
 * Kirke constructor som leser inn data fra fil.
 * Attraksjon constructor blir kjørt først for å lese inn opprinelig data.
 * 
 * @param inn Filen som skal leses fra.
 */
Kirke::Kirke(ifstream &inn) : Attraksjon(inn) {
    int kirkeTypeValg;
    inn >> kirkeTypeValg;

    switch (kirkeTypeValg) {
        case 1: kirkeType = KirkeType::KATEDRAL;    break;
        case 2: kirkeType = KirkeType::KIRKEE;      break; 
        case 3: kirkeType = KirkeType::KAPELL;      break;
        default: kirkeType = KirkeType::KIRKEE;
    }   
        
    inn >> kapasitet;
    inn.ignore();  
    inn >> byggeaar;
}


/**
 * Kirke constructor som ber brukeren om å oppgi dens data.
 * Attraksjon constructor blir kjørt først for å lese inn opprinelig data.
 * 
 */
Kirke::Kirke() : Attraksjon() {
    int kirkeTypeValg;
    kirkeTypeValg = lesInt("\tKirke type (1 - KATEDRAL, 2 - KIRKE, 3 - KAPELL)",1,3);
    
    switch (kirkeTypeValg) {
        case 1: kirkeType = KirkeType::KATEDRAL;    break;
        case 2: kirkeType = KirkeType::KIRKEE;      break; 
        case 3: kirkeType = KirkeType::KAPELL;      break;
        default: kirkeType = KirkeType::KIRKEE;
    }

    byggeaar = lesInt("\tBygge aar: ", MINKIRKEAAR, MAXKIRKEAAR);
    kapasitet = lesInt("\tMaksimum kapasitet: ", MINKIRKEKAPASITET, MAXKIRKEKAPASITET);
}



/**
 * Skriver dataene til kirken til fil.
 * 
 * @see Attraksjon::skrivTilFil()
 * @param utfil Fil som skal skrives til
 */
void Kirke::skrivTilFil(ofstream& utfil) const {
    Attraksjon::skrivTilFil(utfil);
    utfil << static_cast<int>(kirkeType) + 1 << "\n"; //Gjør om enum verdien til int
    utfil << kapasitet << "\n";
    utfil << byggeaar << "\n"; 
}

/**
 * Returnerer typen 'K' for Kirke.
 * 
 * @return Typen til objektet.
 */
char Kirke::getType() const { return 'K'; }

