#include "opplegg.h"
#include "byer.h"
#include "by.h"
#include <iostream>
#include <fstream>
#include <iomanip>

extern Byer gByerBase;

using namespace std;


/**
 * Opplegg constructor som opprettet et opplegg for en turoperatør
 * 
 * @param turoperatorNavn Turoperatørens navn
 * @param oppleggBeskrivelse Beskrivelse av opplegget
 * @param antallDager Antall dager oppleget varer i
 */
Opplegg::Opplegg(const string& turoperatorNavn, const string& oppleggBeskrivelse, int antallDager)
    : turoperatorNavn(turoperatorNavn), oppleggBeskrivelse(oppleggBeskrivelse), antallDager(antallDager) {}


/**
 * Legger inn attraksjon for dagen
 * 
 * @param dagNummer        Nummeret på dagen.
 * @param attraksjonNavn   Navnet på attraksjonen.
 * @param byNavn           Navnet på byen hvor attraksjonen er.
 */
void Opplegg::leggTilAttraksjon(int dagNummer, const string& attraksjonNavn, const string& byNavn) {

    // Legger inn et par med attraksjonNavn og byNavn i dagensAttraksjoner
    dagensAttraksjoner[dagNummer].push_back(make_pair(attraksjonNavn, gByerBase.finnEntydigByNavn(byNavn)));
};


/**
 * Skriver ut opplegg på skjermen
 */
void Opplegg::skrivUtOpplegg() const {
    cout << oppleggBeskrivelse << "\n";

    for (const auto& dag : dagensAttraksjoner) {
        cout << "\tDag nr " << dag.first << ":\n";
        string byNavn; // Variabel for å holde styr på hvilken by som ble utskrevet sist
        for (const auto& attraksjon : dag.second) {
            if (attraksjon.second != byNavn) { // Sjekker om attraksjonen tilhører en ny by.
                cout << "\t\t" << attraksjon.second << "\n"; // Hvis ja, skriver ut ny by navn
                byNavn = attraksjon.second; }

            cout << "\t\t\t" << attraksjon.first << "\n"; } } // Skriver ut navnet på attraksjonen.
}


/**
 * Skriver ut opplegg til fil. Alt er akkurat likt som i 
 * skrivUtOpplegg(), men alt skrives til fil i stedet.
 * 
 * 
 * @param ut Fil som skal skrives til
 */
void Opplegg::skrivTilFil(const string& ut) const {
    ofstream utfil(ut);
    if (utfil) {
        utfil << oppleggBeskrivelse << "\n";

        for (const auto& dag : dagensAttraksjoner) {
            utfil << "\tDag nr " << dag.first << ":\n";
            string byNavn;
            for (const auto& attraksjon : dag.second) {
                if (attraksjon.second != byNavn) {
                    utfil << "\t\t" << attraksjon.second << "\n";
                    byNavn = attraksjon.second; }

            utfil << "\t\t\t" << attraksjon.first << "\n"; } }

        utfil.close();
        cout << "\n\tSkrevet opplegget til filen: " << ut << "\n";
    } else { cout << "OPPLEGGET KUNNE IKKE LAGRES TIL FILEN\n"; }
}


/**
 * Frigjør memory ved å slette alle attraksjonene
 * 
 */
void Opplegg::nullstillOpplegg() { dagensAttraksjoner.clear(); }