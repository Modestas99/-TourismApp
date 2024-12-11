#include "by.h"
#include <iostream>
#include <string>
#include <iomanip>


using namespace std;

/**
 * By constructor som ber brukeren om å oppgi
 * landet den ligger i.
 * 
 */
By::By() { cout << "\tLand: "; getline(cin,land); }


/**
 * By constructor som oppretter en ny by med det angitte landet.
 * 
 * @param land Det angitte landet for 'By'-objektet
 */
By::By(string land) { this->land = land; }


/**
 * Skriver ut dataene til byen, inkludert landet og antall attraksjoner.
 * Brukes i Byer::skrivAlleByer()
 * 
 */
void By::SkrivData1() {

    cout << setw(15) << left << land
    << attraksjoner.size() << " attraksjoner";
}


/**
 * Henter landet byen ligger i.
 * 
 * @return Landet byen ligger i
 */
string By::getLand() const { return land; }



/**
 * Legger inn ny attraksjon til "attraksjoner" listen.
 * 
 * @param attraksjon Peker til den nye attraksjonen som skal legges til.
 */
void By::nyAttraksjon(Attraksjon* attraksjon) {

    attraksjoner.push_back(attraksjon);
}


/**
 * Skriver ut alle attraksjonene i et by.
 * 
 * @param byNavn Byens navn.
 */
void By::skrivAttraksjoner(const string& byNavn) {

    if (attraksjoner.empty()) { //Sjekker om byen har noen attraksjoner
        cout << "\n\tIngen attraksjoner registrert i " << byNavn << ",  " << land << "\n"; }
    else {
        int counter = 1;
        cout << "\n\t" << byNavn << ",  " << land << " har folgende " << attraksjoner.size() << " attraksjoner:" << "\n\n";
            for (const auto &it : attraksjoner) { //Går gjennom attraksjonene
                cout << "\t" << counter++ << ": ";
                it->SkrivData(); } }
}


/**
 * Sletter en attraksjon fra "attraksjoner" listen basert på det oppgitte nummeret.
 * 
 * @param nummer Nummeret til attraksjonen som skal slettes.
 */
void By::slettAttraksjonIBy(int nummer) {

    if (nummer >= 1 && nummer <= attraksjoner.size()) { // Sjekker om det angitte nummeret er gyldig
        auto it = next(attraksjoner.begin(), nummer - 1); // Finner iterator til attraksjonen som skal slettes
        delete *it; // Sletter attraksjonen
        attraksjoner.erase(it); // Sletter attraksjonen fra listen
        cout << "\n\tAttraksjon nummer " << nummer << " ble slettet.\n";
    } else { cout << "Ugyldig attraksjons nummer.\n"; }; //Melding om ugyldig attraksjonsnummer
}


/**
 * Returnerer liste med attraksjoner i et by
 * 
 * @return Listen med attraksjoner i byen
 */
const list<Attraksjon*>& By::getAttraksjoner() const { return attraksjoner; }