
#include "by.h"
#include "byer.h"
#include "LesData3.h"
#include "opplegg.h"
#include "turoperator.h"
#include "turoperatorer.h"
#include "funksjoner.h"
#include "const.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>

extern Byer gByerBase;

using namespace std;


/**
 * Endrer detaljer for en eksisterende turoperatør.
 *
 * @see Turoperatorer::skrivAlleTuroperatorer()
 * @see Turoperatorer::finnEntydigNavn()
 * @see Turoperatorer::endreEnTuroperatorMeny()
 * @see Turoperator::setGateAdresse()
 * @see Turoperator::setPostnrOgSted()
 * @see Turoperator::setKontaktpersonNavn()
 * @see Turoperator::setMailAdresse()
 * @see Turoperator::setWebside()
 * @see Turoperator::setTelefonNummer()
 */
void Turoperatorer::endreEnTuroperator() {
    string navn, fantNavn;
    char valg;

    //Sjekker om det er noen turoperatører i datastrukturen. Hvis ja fortsetter med funksjonen.
    if (turoperatorer.size()) {
        //Loopen fortsetter så lenge navnet ikke er entydig
        do {
            cout << "\n\tEndre noe om turoperator: ";  
            getline(cin, navn);

            fantNavn = finnEntydigNavn(navn); //Sjekker om navnet er entydig

            if (!fantNavn.empty()) {
                auto it = turoperatorer.find(fantNavn); //Finner turoperatøren i datastrukturen
                Turoperator* turoperator = it->second; //Henter pekeren til turoperatør-objektet

                cout << "\n\tENDRER TUROPERATOR '" << fantNavn << "'\n";

                endreEnTuroperatorMeny();
                valg = lesChar("Kommando");

                while (valg != 'Q') {
                    switch(valg) {
                        //Utfører handling basert på brukerens valg
                        case 'A':   turoperator->setGateAdresse();        break;
                        case 'B':   turoperator->setPostnrOgSted();       break;
                        case 'C':   turoperator->setKontaktpersonNavn();  break;
                        case 'D':   turoperator->setMailAdresse();        break;
                        case 'E':   turoperator->setWebside();            break;
                        case 'F':   turoperator->setTelefonNummer();      break;
                        default:    endreEnTuroperatorMeny();             break;
                    }

                    endreEnTuroperatorMeny();
                    valg = lesChar("\nKommando");
                } } 

        } while (fantNavn.empty()); 

        skrivMeny(); } 

    else { cout << "\n\tIngen turoperatorer finnes.\n"; }
}


/**
 * Viser en meny med alternativer for detaljer som kan endres for en turoperatør.
 * 
 */
void Turoperatorer::endreEnTuroperatorMeny() {

   cout << "\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:\n\n"
        << "\tA  \t - Endre gate-adresse\n"
        << "\tB  \t - Endre postnr og -sted\n"
        << "\tC  \t - Endre kontaktperson\n"
        << "\tD  \t - Endre mail-adresse\n"
        << "\tE  \t - Endre web-side\n"
        << "\tF  \t - Endre telefonnummer\n"
        << "\tQ  \t - Tilbake til hovedmenyen\n\n";
}


/**
 * Sikrer at turoperator navn som blir oppgitt er entydig. Hvis navnet som
 * blir oppgitt ikke er entydig blir en tom string returnert.
 * 
 * @param navn Navnet som skal matches mot turoperatørnavnene.
 */
string Turoperatorer::finnEntydigNavn(const string& innskrevetNavn) {

    string entydigNavn; 
    bool flereFunn = false; 
    bool uniktFunn = false; 

    // Gjør om navnet til små bokstaver
    string innskrevetNavnLiten = innskrevetNavn;
    transform(innskrevetNavnLiten.begin(), innskrevetNavnLiten.end(), innskrevetNavnLiten.begin(), ::tolower);

    // Går gjennom alle turoperatører og henter turoperatørnavnet
    for (const auto& it : turoperatorer) {
        string turoperatorNavnLiten = it.first;
        transform(turoperatorNavnLiten.begin(), turoperatorNavnLiten.end(), turoperatorNavnLiten.begin(), ::tolower);

        // Sjekker om det er en nøyaktig match
        if (turoperatorNavnLiten == innskrevetNavnLiten) {
            if (!entydigNavn.empty()) {
                flereFunn = true; 
            } else {
                entydigNavn = it.first;
                uniktFunn = true; // Merker at et unikt navn ble funnet 
            }
        } 
        // Sjekker om delvis match
        else if (turoperatorNavnLiten.find(innskrevetNavnLiten) != string::npos) {
            if (entydigNavn.empty()) {
                entydigNavn = it.first;
                uniktFunn = true; 
            } else {
                flereFunn = true; } }
    }

    if (flereFunn || !uniktFunn) {
        cout << "\n\tNAVNET ER IKKE ENTYDIG\n";
        return ""; }

    return entydigNavn;
}


/**
 * Leser turoperatørdata fra filen "TUROPERATORER.DTA" og oppretter turoperatører basert på dataene i filen.
 * 
 * @see Turoperator::Turoperator(string gateAdresse,string postnrOgSted,string kontaktpersonNavn,string mailAdresse,string webside,int telefonNummer,int antallOpplegg)
 * 
 */
void Turoperatorer::lesFraFil() {
    string navn, gateAdresse, postnrOgSted, kontaktpersonNavn, mailAdresse, webside;
    int telefonNummer, antallOpplegg;

     // Åpner filen "TUROPERATORER.DTA"
    ifstream innfil("TUROPERATORER.DTA");
    if (innfil) {
        cout << "LESER FRA FILEN 'TUROPERATORER.DTA'...\n";

        // Leser data fra filen så langt det er noe å lese
        while (getline(innfil, navn)) {
            getline(innfil, gateAdresse);
            getline(innfil, postnrOgSted);
            getline(innfil, kontaktpersonNavn);
            getline(innfil, mailAdresse);
            getline(innfil, webside);
            innfil >> telefonNummer >> antallOpplegg;
            innfil.ignore(); 
            
             // Oppretter en ny turoperatør med innlest data som parameter og legger den inn i datastrukturen
            Turoperator* nyTuroperator = new Turoperator(gateAdresse, postnrOgSted, kontaktpersonNavn, mailAdresse, webside, telefonNummer, antallOpplegg);
            turoperatorer.insert({navn, nyTuroperator}); } }
    else {
        cout << "\n\nFANT IKKE FILEN 'TUROPERATORER.DTA'.\n\n";
    }
}


/**
 * Oppretter en ny turoperatør. Hvis turoperatørnavnet som blir angitt finnes i datastrukturen,
 * bes brukeren om å velge et annet navn inntil et unikt navn er angitt. 
 * 
 * @see Turoperator::Turoperator()
 */
void Turoperatorer::nyTuroperator() {
    string navn;
    bool uniktNavnFunnet = false;

    while (!uniktNavnFunnet) {
        cout << "\n\tNy turoperators navn: ";
        getline(cin, navn);

        // Konverterer navnet til store bokstaver
        transform(navn.begin(), navn.end(), navn.begin(), ::toupper);

        if (turoperatorer.find(navn) != turoperatorer.end()) {
            cout << "\n\tTuroperatoren '" << navn << "' finnes allerede. Velg et annet navn.\n";
        } else {
            Turoperator* nyTuroperator = new Turoperator();
            turoperatorer.insert({navn, nyTuroperator});

            cout << "\n\tNy turoperator er lagt inn.\n\n";
            uniktNavnFunnet = true;
        }
    }
}


/**
 * Skriver ut informasjon om alle turoperatører i datastrukturen.
 * 
 * @see Turoperator::SkrivData1()
 */
void Turoperatorer::skrivAlleTuroperatorer() {
    if (turoperatorer.size()) {
        cout << "\n\tFolgende turoperatorer finnes:\n\n";
        for (const auto & val : turoperatorer)  {
            cout << "\t" << setw(15) << left << val.first;
            (val.second)->SkrivData1();
            cout << "\n";
        } }
    else { cout << "\n\tIngen turoperatorer finnes.\n"; }
}


/**
 * Skriver ut detaljert informasjon om en spesifikk turoperatør, basert på brukerens valg av navn.
 * Det blir også utført sjekk om navnet er entydig.
 * 
 * @see Turoperator::SkrivData2()
 */
void Turoperatorer::skrivEnTuroperator() {
    string navn, fantNavn;

    if (turoperatorer.size()) {
        bool navnFunnet = false;
        do {
            cout << "\n\tSkriv alt om turoperatoren: ";
            getline(cin, navn);

            fantNavn = finnEntydigNavn(navn);

            if (!fantNavn.empty()) {
                auto it = turoperatorer.find(fantNavn);
                cout << "\n\t" << it->first; 
                (it->second)->skrivData2(); 
                navnFunnet = true;
            } 
        } while (!navnFunnet);
    } else {
        cout << "\n\tIngen turoperatorer finnes.\n";
    }
}


/**
 * Skriver informasjon om alle turoperatører til filen 'TUROPERATORER.DTA'.
 * 
 */
void Turoperatorer::skrivTilFil() {

    ofstream utfil("TUROPERATORER.DTA"); // Åpner filen for skriving

    if (utfil) {
        cout << "SKRIVER TIL FILEN 'TUROPERATORER.DTA'...\n";
         // For loop som går gjennom hver turoperatør i datastrukturen og skriver deres informasjon til filen
        for (const auto& it : turoperatorer) {
            utfil << it.first << "\n"; //Skriver turoperator navnet til filen først og fremst
            utfil << it.second->getGateAdresse() << "\n";
            utfil << it.second->getPostnrOgSted() << "\n";
            utfil << it.second->getKontaktpersonNavn() << "\n";
            utfil << it.second->getMailAdresse() << "\n";
            utfil << it.second->getWebside() << "\n";
            utfil << it.second->getTelefonNummer() << "\n";
            utfil << it.second->getAntallOpplegg() << "\n"; } }
    
    else { cout << "\n\nKUNNE IKKE AAPNE FILEN 'TUROPERATORER.DTA' FOR UTSKRIVING!\n\n";}
};


/**
 * Alle turoperatorer blir skrevet ut. Brukeren spørres om hvilken turoperator hen vil slette og bes om
 * å oppgi turoperatørensnavn. Hvis navnet er entydig blir brukeren bedt om å bekrefte slettingen.
 * 
 * @see Turoperatorer::finnEntydigNavn()
 * @see Turoperatorer::skrivAlleTuroperatorer();
 */
void Turoperatorer::slettEnTuroperator() {
    string navn, valg;
    string fantNavn;

    if (turoperatorer.size()) {
        do {
            cout << "\n\tSlett/fjern turoperator: ";
            getline(cin, navn);
            fantNavn = finnEntydigNavn(navn);

            if (!fantNavn.empty()) {
                auto it = turoperatorer.find(fantNavn);
                cout << "\n\tEr du SIKKER at du vil slette turoperatoren '" << it->first; 
                valg = lesChar("'? (J/N)");

                if (valg == "J") {
                    delete it->second;
                    turoperatorer.erase(it);
                    cout << "\n\tTuroperatoren '" << fantNavn << "' ble slettet.\n";  } 
                
                else if (valg == "N") { cout << "\n\tOK, turoperatoren blir ikke slettet.\n"; } }
        } while (fantNavn.empty());
    } else { cout << "\n\tIngen turoperatorer finnes.\n"; }
}


/**
 * Lar brukeren lage et opplegg for en turoperator.
 * Brukeren blir bedt om å oppgi turoperatørens navn, beskrivelse av opplegget og antall dager for opplegget.
 * Deretter blir brukeren bedt om å legge til attraksjoner for hver dag i opplegget.
 * 
 * @see Byer::getByNavn()
 * @see By::skrivAttraksjoner()
 * @see By::getAttraksjoner()
 * @see Opplegg:Opplegg()
 * @see Opplegg:skrivUtOpplegg()
 * 
 */
void Turoperatorer::lagEtOpplegg() {
    string turoperatorNavn, oppleggBeskrivelse;
    int antallDager;

    if (turoperatorer.size()) {
        bool uniktNavnFunnet = false;
        while (!uniktNavnFunnet) {
            cout << "\n\tLag et opplegg for turoperatoren: ";
            getline(cin, turoperatorNavn);

            string entydigNavn = finnEntydigNavn(turoperatorNavn);
            if (!entydigNavn.empty()) {
                uniktNavnFunnet = true;
                turoperatorNavn = entydigNavn; } }

        cout << "\n\t" << turoperatorNavn << "\n";
        cout << "\tBeskrivelse av opplegget: ";
        getline(cin, oppleggBeskrivelse);

        antallDager = lesInt("\tOpplegg for antall dager: ", MINOPPLEGGDAGER, MAXOPPLEGGDAGER);

         // Oppretter et opplegg-objekt
        Opplegg opplegg(turoperatorNavn, oppleggBeskrivelse, antallDager);

        if (turoperatorer.find(turoperatorNavn) != turoperatorer.end()) {
            turoperatorer[turoperatorNavn]->leggTilOpplegg(); }

        // Variabler for å holde styre på dagnummer og om attraksjonen finnes for hver dag
        int dagNr = 1;
        map<int, bool> attraksjonFinnes;

         // Looper gjennom alle dager i opplegget
        while (dagNr <= antallDager) {
            cout << "\n\tDag nr." << dagNr << ":\n";

            string byNavn;
            bool uniktByNavnFunnet = false; 
            while (!uniktByNavnFunnet) { 
                cout << "\tLag opplegg for byen/stedet: ";
                getline(cin, byNavn);

                // Finner et entydig navn for byen/stedet
                string entydigByNavn = gByerBase.finnEntydigByNavn(byNavn);
                if (!entydigByNavn.empty()) {
                    uniktByNavnFunnet = true;
                    //Returnerer en pointer til byen/stedet
                    By* by = gByerBase.getBy(entydigByNavn); 
                    
                    // Skriver ut attraksjoner for byen/stedet
                    if (by != nullptr) {
                        by->skrivAttraksjoner(entydigByNavn);
                        bool sammeDag = true; //Variabel for å holde styr om det er samme dag eller ikke

                        while (sammeDag) {
                            int attraksjonsNr = lesInt("\tLegg til attraksjon nr", 0, by->getAttraksjoner().size());
                            
                            //Hvis brukeren ønsker å slutte med å legge inn nye attraksjoner
                            if (attraksjonsNr == 0) {
                                char valg;

                                //Sjekker om det er siste dag eller ikke. Skriver ut melding basert på det.
                                if (dagNr == antallDager) { valg = lesChar("\n\tS(amme) dag, Q(uit)"); }
                                    else { valg = lesChar("\n\tS(amme) dag, N(este) dag, Q(uit)"); }

                                //Sjekker om noen attraksjoner finnes for nåværende dagen, før brukeren kan gå videre til neste dag   
                                if (valg == 'N') { 
                                    if (attraksjonFinnes[dagNr]) {
                                        dagNr++; 
                                        attraksjonFinnes[dagNr] = false; } // Sørger for at neste dag ikke har noen attraksjoner
                                    else { cout << "\n\tIngen attraksjoner for denne dagen registrert. Registrer minst en attraksjon.\n";  } }

                                //Sjekker om noen attraksjoner finnes for nåværende dagen, før brukeren kan avslutte  
                                else if (valg == 'Q') {
                                    if (attraksjonFinnes[dagNr]) {
                                        opplegg.skrivUtOpplegg();
                                        char lagringsValg;
                                        lagringsValg = lesChar("\n\tLagre dette paa fil? (J/N)");

                                        // Lagre opplegget på fil hvis brukeren ønsker det
                                        if (lagringsValg == 'J') {
                                            //Oppretter ny fil med riktige parametre
                                            stringstream oppleggFilen;
                                            oppleggFilen << turoperatorNavn << "-" << setw(3) << setfill('0') << turoperatorer[turoperatorNavn]->getAntallOpplegg() << "-" << dagNr << "dg.dta";
                                            string filnavn = oppleggFilen.str();
                                            opplegg.skrivTilFil(filnavn); }

                                        //Nullstiller opplegget og frigjør memory.
                                        opplegg.nullstillOpplegg();
                                        return; } 

                                    else { cout << "\n\tIngen attraksjoner for denne dagen registrert. Registrer minst en attraksjon.\n"; } }
                                
                            sammeDag = false; }
                            
                            else { //Loop som blir brukt for å legge inn nye attraksjoner og holde styre på om attraksjoner for nåværende dag finnes.
                                auto it = next(by->getAttraksjoner().begin(), attraksjonsNr - 1);
                                Attraksjon* attraksjon = *it;
                                cout << "\t\tLegger inn: " << attraksjon->getNavn() << "\n\n";
                                opplegg.leggTilAttraksjon(dagNr, attraksjon->getNavn(), byNavn);
                                attraksjonFinnes[dagNr] = true; } 
                         } }
                } 
            }
        }
    } else { cout << "\n\tIngen turoperatorer finnes.\n";}
}


/**
 * Meny til turoperatørens handlinger
 * 
 * @param valg Brukerens valg
 */
void Turoperatorer::OperatorHandling(char valg) {
    switch(valg)  {

        case 'A':  skrivAlleTuroperatorer();    break;
        case '1':  skrivEnTuroperator();        break;
        case 'N':  nyTuroperator();             break;
        case 'E':  endreEnTuroperator();        break;
        case 'O':  lagEtOpplegg();              break;
        case 'F':  slettEnTuroperator();        break;
        default:   skrivMeny();                 break;
    }
}

















