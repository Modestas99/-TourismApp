#include <iostream>
#include <string>
#include <iomanip>
#include "turoperator.h"
#include "LesData3.h"
#include "const.h"
using namespace std;

/**
 * Oppretter en ny turoperator objekt ved å lese inn nødvendig data fra brukeren.
 * 
 */
Turoperator::Turoperator() {
    cout << "\tGateadresse: "; getline(cin,gateAdresse);
    if (gateAdresse.empty()) {
        cout << "\tGate-adresse tom, setter default verdi \"----\"\n\n";
        gateAdresse = "----"; }
    
    cout << "\tPostnr og -sted: "; getline(cin,postnrOgSted);
    if (postnrOgSted.empty()) {
        cout << "\tPostnr og -sted tom, setter default verdi \"----\"\n\n";
        postnrOgSted = "----"; }

    cout << "\tKontaktperson: "; getline(cin,kontaktpersonNavn);
    if (kontaktpersonNavn.empty()) {
        cout << "\tKontaktperson tom, setter default verdi \"----\"\n\n";
        kontaktpersonNavn = "----"; }

    cout << "\tMail-adresse: "; getline(cin,mailAdresse);
    if (mailAdresse.empty()) {
        cout << "\tMail-adresse tom, setter default verdi \"----\"\n\n";
        mailAdresse = "----"; }

    cout << "\tWeb-side: "; getline(cin,webside);
    if (webside.empty()) {
        cout << "\tWeb-side tom, setter default verdi \"----\"\n\n";
        webside = "----"; }

    telefonNummer = lesInt("\tTelefon: ", MINTELEFONNUMMER, MAXTELEFONNUMMER);
    antallOpplegg = 0;
}


/**
 * Oppretter en ny turoperator objekt med oppgite parametre.
 * 
 * @param gateAdresse           Gateadresse for turoperatøren.
 * @param postnrOgSted          Postnummer og sted for turoperatøren.
 * @param kontaktpersonNavn     Navnet på kontaktpersonen for turoperatøren.
 * @param mailAdresse           E-postadressen til turoperatøren.
 * @param webside               Websiden til turoperatøren.
 * @param telefonNummer         Telefonnummeret til turoperatøren.
 * @param antallOpplegg         Antall opplegg hos turoperatøren.
 */
Turoperator::Turoperator(string gateAdresse, string postnrOgSted, string kontaktpersonNavn, string mailAdresse, string webside, int telefonNummer, int antallOpplegg) {
    this->gateAdresse = gateAdresse;
    this->postnrOgSted = postnrOgSted;
    this->kontaktpersonNavn = kontaktpersonNavn;
    this->mailAdresse = mailAdresse;
    this->webside = webside;
    this->telefonNummer = telefonNummer;
    this->antallOpplegg = antallOpplegg;
}


/**
 * Skriver ut turoperatør sitt navn, antall nåværende opplegg og hjemmeside-adressen. 
 * 
 */
void Turoperator::SkrivData1() {
    cout << antallOpplegg << " opplegg" << setw(5) << " " << webside;
}


/**
 * Skriver ut turoperatørens hele data. 
 * 
 */
void Turoperator::skrivData2() {

    cout << "\n\t" << antallOpplegg << " opplegg" << "  " << webside << "\n\t" 
         << gateAdresse << ", " << postnrOgSted << "\n\t"
         << kontaktpersonNavn << ", " << telefonNummer << ", "
         << mailAdresse << "\n";
}


/**
 * Setter ny gateadresse for en turoperatør.
 * 
 */
void Turoperator::setGateAdresse() {

    string nyGateAdresse;
    cout << "\n\tNy gate-adresse: "; 
    getline(cin, nyGateAdresse);
    if (nyGateAdresse.empty()) {
        cout << "\tNy gate-adresse tom, setter default verdi \"----\"\n\n";
        gateAdresse = "----"; 
    } else {
        gateAdresse = nyGateAdresse;
        cout << "\n\tNy gate-adresse lagret.\n";
    }
}


/**
 * Setter ny post nr og sted for en turoperatør.
 * 
 */
void Turoperator::setPostnrOgSted() {

    string nyPostnrOgSted;
    cout << "\n\tNy postnr og -sted: "; 
    getline(cin, nyPostnrOgSted);
    if (nyPostnrOgSted.empty()) {
        cout << "\tNy postnr og -sted tom, setter default verdi \"----\"\n\n";
        gateAdresse = "----"; 
    } else {
        postnrOgSted = nyPostnrOgSted;
        cout << "\n\tNy postnr og -sted lagret.\n"; }
}


/**
 * Setter ny kontakt person navn for en turoperatør.
 * 
 */
void Turoperator::setKontaktpersonNavn() {

    string nyKontaktPerson;
    cout << "\n\tNy kontaktperson: "; 
    getline(cin, nyKontaktPerson);
    if (nyKontaktPerson.empty()) {
        cout << "\tNy kontaktperson tom, setter default verdi \"----\"\n\n";
        kontaktpersonNavn = "----"; 
    } else {
        kontaktpersonNavn = nyKontaktPerson;
        cout << "\n\tNy kontaktperson lagret.\n";
    }
}
        

/**
 * Setter ny mail adresse for en turoperatør.
 * 
 */
void Turoperator::setMailAdresse() {

    string nyMailAdresse;

    cout << "\n\tNy mail-adresse: "; 
    getline(cin, nyMailAdresse);
    if (nyMailAdresse.empty()) {
        cout << "\tNy mail-adresse tom, setter default verdi \"----\"\n\n";
        mailAdresse = "----"; 
    } else {
        mailAdresse = nyMailAdresse;
        cout << "\n\tNy mail-adresse lagret.\n";
    }
}
           

/**
 * Setter ny webside for en turoperatør.
 * 
 */
void Turoperator::setWebside() {

    string nyWebside;

    cout << "\n\tNy web-side: "; 
    getline(cin, nyWebside);
    if (nyWebside.empty()) {
        cout << "\tNy web-side tom, setter default verdi \"----\"\n\n";
        nyWebside = "----"; 
    } else {
        webside = nyWebside;
        cout << "\n\tNy web-side lagret.\n";
    }
}


/**
 * Setter ny telefonnummer for en turoperatør.
 * 
 */
void Turoperator::setTelefonNummer() {

    int telefonNummer;
    
        telefonNummer = lesInt("\n\tNy telefonnummer", MINTELEFONNUMMER, MAXTELEFONNUMMER);
        this->telefonNummer = telefonNummer;
        cout << "\n\tNy telefonnummer lagret.\n";
};      


/**
 * Henter turoperatørens gata adresse.
 * 
 */
string Turoperator::getGateAdresse() const {return gateAdresse; }


/**
 * Henter turoperatørens post sted og nr.
 * 
 */
string Turoperator::getPostnrOgSted() const {return postnrOgSted; }


/**
 * Henter turoperatørens kontaktperson navn.
 * 
 */
string Turoperator::getKontaktpersonNavn() const {return kontaktpersonNavn; }


/**
 * Henter turoperatørens mail adresse.
 * 
 */
string Turoperator::getMailAdresse() const {return mailAdresse; }


/**
 * Henter turoperatørens webside.
 * 
 */
string Turoperator::getWebside() const {return webside; }


/**
 * Henter turoperatørens telefonnummer.
 * 
 */
int Turoperator::getTelefonNummer() const {return telefonNummer; }


/**
 * Henter turoperatørens antall opplegg.
 * 
 */
int Turoperator::getAntallOpplegg() const {return antallOpplegg; }


/**
 * Øker antall opplegg hos en turoperator
 * 
 */
void Turoperator::leggTilOpplegg() { antallOpplegg++; }