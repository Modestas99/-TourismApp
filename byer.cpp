#include "byer.h"
#include "by.h"
#include "museumgalleri.h"
#include "kirke.h"
#include "severdighet.h"
#include "LesData3.h"
#include "funksjoner.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;


/**
 * Ber brukeren om et unikt navn for byen/stedet,
 * sjekker om navnet allerede eksisterer i datastrukturen,
 * hvis navnet er unikt legger den inn i datastrukturen.
 * 
 */
void Byer::nyBy() {
    string navn;
    bool uniktNavnFunnet = false; //Bool variabel som blir brukt til å loope gjennom funksjonen mens det oppgite navn ikke er entydig

    while (!uniktNavnFunnet) {
        cout << "\n\tNy bys/steds navn: ";
        getline(cin, navn);

        transform(navn.begin(), navn.end(), navn.begin(), ::toupper); // Konverterer navnet til store bokstaver før sammenligning

        if (byer.find(navn) != byer.end()) { // Sjekker om navnet allerede finnes i datastrukturen
            cout << "\n\tByen '" << navn << "' finnes allerede. Velg et annet by.\n";  }
        else {
            By* nyBy = new By();
            byer.insert({navn, nyBy}); // Legger inn by med unikt navn inn i datastrukturen

            cout << "\n\tNy by/sted er lagt inn\n\n";
            uniktNavnFunnet = true; }
    }
}


/**
 * Skriver ut alle byer/steder i datastrukturen.
 * 
 * Hvis det finnes byer/steder i databasen, skrives de ut sammen med deres detaljer.
 * Hvis det ikke finnes noen byer/steder i databasen, skrives en melding om det.
 */
void Byer::skrivAlleByer() {

    if (byer.size()) {
    cout << "\n\tFolgende " << byer.size() << " byer/steder finnes:\n\n";

    for (const auto & it : byer)  {
        cout << "\t" << setw(15) << left << it.first;
        (it.second)->SkrivData1();
        cout << "\n"; }; } 

    else { cout << "\n\tIngen byer finnes.\n"; }
}


/**
 * Sletter en by/sted fra datastrukturen.
 * 
 * Ber brukeren om navnet på byen/stedet som skal slettes,
 * sjekker om byen med det oppgitte navnet eksisterer i
 * datastrukturen og sletter den hvis det gjør det.
 *
 * @see Byer::finnEndytigByNavn()
 */
void Byer::slettEnBy() {
    string navn, valg;

    if (byer.size()) {

    bool entydigNavnFunnet = false;
    while (!entydigNavnFunnet) {
        cout << "\n\tSlett by/sted: ";
        getline(cin, navn);

        string entydigNavn = finnEntydigByNavn(navn); // Finner det entydige navnet på byen/stedet
        if (!entydigNavn.empty()) {
    
            auto it = byer.find(entydigNavn);
            cout << "\n\tEr du SIKKER at du vil slette byen/stedet '" << it->first << "'? (J/N)";
            valg = lesChar("");

            if (valg == "J") {
                delete it->second; // Sletter byen/stedet
                byer.erase(it); // Fjerner byen/stedet fra datastrukturen
                cout << "\n\tByen/stedet '" << entydigNavn << "' ble slettet.\n";
            } else { cout << "\n\tOK, ingen by/sted blir slettet likevel.\n"; }
            entydigNavnFunnet = true;
        } } }
        else { cout << "\n\tIngen byer finnes.\n"; }
}


/**
 * Legger inn en attraksjon i en by/sted.
 * 
 * Ber brukeren om navnet på byen/stedet der attraksjonen skal
 * legges til. Om byen med det oppgitte navnet eksisterer i
 * datastrukturen bes brukeren om å oppgi detaljer for attraksjonen
 * hen vil legge til i byen/stedet
 * 
 * @see Byer::finnEndytigByNavn()
 * @see By:NyAttraksjon()
 * @see MuseumGalleri::MuseumGalleri()
 * @see Severdighet::Severdighet()
 * @see Kirke::Kirke()
 */
void Byer::leggTilAttraksjonIBy() {
    bool fantBy = false;

    if (byer.size()) { // Sjekker om det noen byer finnes i datastrukturen

    while (!fantBy) {
        string navn;
        cout << "\n\tNy attraksjon i byen/stedet: ";
        getline(cin, navn);

        string entydigBy = finnEntydigByNavn(navn);

        if (!entydigBy.empty()) {
            auto it = byer.find(entydigBy);
            cout << "\n\t" << entydigBy << "\n";

            char type;
            bool riktigAttraksjonsType = false;
            while (!riktigAttraksjonsType) {
                type = lesChar("\tAttraksjonstype M(useum/Galleri), K(irke), S(everdighet)");
                if (type == 'M' || type == 'K' || type == 'S') { // Sjekker om brukerens valg er gyldig
                    riktigAttraksjonsType = true; }
                else { cout << "\n\tUGYLDIG ATTRAKSJONSTYPE\n\n"; } // Gir beskjed om et ugyldig valg
            }

            Attraksjon* nyAttraksjon = nullptr;

            switch (type) {
                case 'M': nyAttraksjon = new MuseumGalleri();   break; // Oppretter et nytt 'MuseumGalleri'-objekt
                case 'K': nyAttraksjon = new Kirke();           break; // Oppretter et nytt 'Kirke'-objekt
                case 'S': nyAttraksjon = new Severdighet();     break; // Oppretter et nytt 'Severdighet'-objekt
            }

            if (nyAttraksjon) { 
                it->second->nyAttraksjon(nyAttraksjon); // Legger til attraksjonen i byen/stedet
                cout << "\n\tAttraksjon lagt til i " << entydigBy << "\n";
                fantBy = true; }  //Avslutter loopen når attraksjonen er lagt inn
        }
    } }

    else { cout << "\n\tIngen byer finnes.\n"; }
}


/**
 * Ber brukeren om navnet på byen/stedet som skal skrives
 * ut. Om byen med det oppgitte navnet eksisterer i
 * datastrukturen skriver ut alle attraksjonene som er 
 * registrert i dette byet.
 * 
 * @see Byer::finnEntydigByNavn()
 * @see By:skrivAttraksjoner()
 */
void Byer::skrivEnBy() {
    string byNavn;

    if (byer.size()) {
        bool entydigNavnFunnet = false;
        do {
            cout << "\n\tSkriv alt om byen/stedet: ";
            getline(cin, byNavn);

            string entydigBy = finnEntydigByNavn(byNavn); // Finner entydig navnet på byen/stedet

            if (!entydigBy.empty()) {
                auto it = byer.find(entydigBy); // Finner byen/stedet i datastrukturen
                if (it != byer.end()) {
                    it->second->skrivAttraksjoner(entydigBy); // Skriver ut alle attraksjonene i byen/stedet
                    entydigNavnFunnet = true; } } 
        } while (!entydigNavnFunnet);
    } else { cout << "\n\tIngen byer finnes.\n"; }
}


/**
 * Leser data fra filen "BYER.DTA" og oppretter nye byer basert på dataene i filen.
 *
 * @see By::By()
 * @see By::nyAttraksjon()
 * @see Kirke::Kirke(innfil)
 * @see MuseumGalleri::MuseumGalleri(innfil)
 * @see Severdighet::Severdighet(innfil)
 */
void Byer::lesFraFil() {
    char objektType;
    
    ifstream innfil("BYER.DTA"); // Åpner filen for lesing 
    if (innfil) { // Sjekker om filen ble åpnet
        cout << "LESER FRA FILEN 'BYER.DTA'...\n";
        
        bool harAttraksjoner = true; // Variabel som holder styr på om det forrige objektet hadde attraksjoner
        
        while (innfil >> objektType) {  // Leser objekttypen fra filen
            innfil.ignore(); // Ignorerer space som kommer etter objekttypen
            
            string byNavn, land;
            getline(innfil, byNavn); // Leser inn byens navn
            getline(innfil, land); // Leser inn landet byen ligger i

            auto it = byer.find(byNavn);
            if (it == byer.end()) { 
                By* nyBy = new By(land); //Oppretter en ny by og legger den inn i datastrukturen
                byer.insert({byNavn, nyBy});
                it = byer.find(byNavn); }

            if (objektType == '-') { harAttraksjoner = false; }  // Sjekker om byen har noen attraksjoner
            
            else {
                if (!harAttraksjoner) { harAttraksjoner = true; } // Bytter flagget hvis byen har attraksjoner
                Attraksjon* nyAttraksjon = nullptr;
                switch (objektType) {
                    case 'K': nyAttraksjon = new Kirke(innfil);           break; //Oppretter ny Kirke-objekt og leser inn dens data
                    case 'M': nyAttraksjon = new MuseumGalleri(innfil);   break; //Samme som kirke
                    case 'S': nyAttraksjon = new Severdighet(innfil);     break; //Samme som kirke
                    default: cout << "";                                  break; //"Dummy" default value, blir ikke brukt for noen ting
                }
                it->second->nyAttraksjon(nyAttraksjon);  // Legger til attraksjon i byen
            } }

        innfil.close(); 
    } else { cout << "FANT IKKE FILEN 'BYER.DTA'.\n"; }
}


/**
 * Skriver alle byenes data til fil, 
 * inkludert deres attraksjoner. Hvis ingen
 * attraksjoner finnes i byen er det kun dens
 * navn og land den ligger i skrevet til filen
 * 
 * @see By::getAttraksjoner()
 * @see By::getLand()
 * @see Attraksjon::GetType()
 * @see Attraksjon::skrivTilFil()
 */
void Byer::skrivTilFil() {
    ofstream utfil("BYER.DTA"); // Åpner filen for skriving

    if (utfil) { // Sjekker om filen ble åpnet
        cout << "SKRIVER TIL FILEN 'BYER.DTA'...\n";

        for (const auto& it : byer) { // Går gjennom alle byene i datastrukturen
            if (it.second->getAttraksjoner().empty()) { // Sjekker om byen har ingen attraksjoner
                utfil << "- " << it.first << "\n"; //Hvis byen ikke har noen attraksjoner så skrives bare '-'
                utfil << it.second->getLand() << "\n";
            } else { // Hvis byen har attraksjoner
                for (const auto& attraksjon : it.second->getAttraksjoner()) { // Går gjennom alle attraksjonene i byen
                    utfil << attraksjon->getType() << " ";  
                    utfil << it.first << "\n"; 
                    utfil << it.second->getLand() << "\n"; 
                    attraksjon->skrivTilFil(utfil); 
                } }
        }
    } else { cout << "\n\nKUNNE IKKE AAPNE FILEN 'BYER.DTA' FOR UTSKRIVING!\n\n";  }    
}


/**
 * Sletter en attraksjon i et by/sted.
 * Hvis ingen attraksjoner finnes i denne byen
 * skrives en melding om det.
 * 
 * @see Byer::finnEntydigByNavn()
 * @see By::getAttraksjoner()
 * @see By::skrivAttraksjoner()
 * @see By::slettAttraksjonIBy()
 * 
 */
void Byer::slettAttraksjonIBy() {
    string byNavn;

    if (byer.size()) {
        do {
            cout << "\n\tFjern/slett attraksjon i by: "; 
            getline(cin, byNavn);
            byNavn = finnEntydigByNavn(byNavn);
        } while (byNavn.empty()); //Looper inntil entydig navn er oppgitt

        auto it = byer.find(byNavn); // Finner byen i datastrukturen
        auto& attraksjoner = it->second->getAttraksjoner(); // Henter listen over alle attraksjonene i byen

        if (!attraksjoner.empty()) { // Sjekker om noen attraksjoner ble hentet, hvis ja - fortsetter.
            it->second->skrivAttraksjoner(byNavn);
            int valg;
            valg = lesInt("\n\tSlett attraksjon:", 0, attraksjoner.size());
            
            it->second->slettAttraksjonIBy(valg); // Sletter attraksjon basert på brukerens valg
        } else { cout << "\n\tIngen attraksjoner registrert i '" << it->first << "'\n"; }
    } 
    else { cout << "\n\tIngen byer finnes.\n"; }
}

/**
 * Returnerer peker til en spesifikk by
 * 
 * @param byNavn Byens navn
 * @return Pointer til byen
 * 
 */
By* Byer::getBy(const string& byNavn) {
    
        auto it = byer.find(byNavn);
        if (it != byer.end()) { // Sjekker om byen ble funnet
            return it->second; // Returnerer pekeren til byen
        } else { return nullptr; } // Returnerer nullptr hvis byen ble ikke funnet
}


/**
 * Finner og returnerer et entydig by navn.
 * 
 * @param byNavn Bynavn innskrevet av brukeren
 * @return Byens fulle navn / tom string hvis ingen entydig navn ble funnet
 */
string Byer::finnEntydigByNavn(const string& innskrevetBy) {
    string entydigBy; 
    bool flereFunn = false; 
    bool uniktFunn = false;  

    string innskrevetByLiten = innskrevetBy;
    // Gjør om navnet til små bokstaver
    transform(innskrevetByLiten.begin(), innskrevetByLiten.end(), innskrevetByLiten.begin(), ::tolower);

    for (const auto& it : byer) { // Går gjennom alle bynavnene i datastrukturen
        string byNavnLiten = it.first;
        transform(byNavnLiten.begin(), byNavnLiten.end(), byNavnLiten.begin(), ::tolower);

        if (byNavnLiten == innskrevetByLiten) { // Sjekker om bynavnet matcher nøyaktig det som brukeren skrev inn
            if (!entydigBy.empty()) {
                flereFunn = true; } 
            else { 
                entydigBy = it.first; 
                uniktFunn = true; } } 
       
        else if (byNavnLiten.find(innskrevetByLiten) != string::npos) { // Sjekker om bynavnet delvis matcher det som brukeren skrev inn
            if (entydigBy.empty()) {
                entydigBy = it.first;
                uniktFunn = true; }
            else { flereFunn = true;} } }

    if (flereFunn || !uniktFunn) { // Hvis det er flere funn eller ingen unike funn
        cout << "\n\tNAVNET ER IKKE ENTYDIG\n";
        return ""; }

    return entydigBy;
}



/**
 * Meny til byer handlinger
 * 
 * @param valg Brukerens valg
 */
void Byer::ByerHandling(char valg) {

    switch(valg)  {
        case 'A': skrivAlleByer();  break;
        case '1': skrivEnBy();      break;
        case 'N': nyBy();           break;
        case 'F': slettEnBy();      break;
        default:  skrivMeny();      break; 
    }
}


/**
 * Meny til attraksjons handlinger
 * 
 * @param valg Brukerens valg
 */
void Byer::AttraksjonHandling(char valg) {

    switch(valg)  {
        case 'N': leggTilAttraksjonIBy();     break;
        case 'F': slettAttraksjonIBy();       break;
        default:  skrivMeny();                break;  
    }
}
