#include <iostream>
#include "turoperatorer.h"
#include "byer.h"
#include "opplegg.h"
#include "funksjoner.h"
#include "LesData3.h"
using namespace std;


Turoperatorer gOperatorBase; ///<  Globalt container-objekt med ALLE turoperatørene.
Byer gByerBase;              ///<  Globalt container-objekt med ALLE byene.


int main() {
    gOperatorBase.lesFraFil();
    gByerBase.lesFraFil();

    string kommando; 
    skrivMeny();

    cout << "\nKommando: ";
    getline(cin, kommando); 

    char bokstav1 = toupper(kommando[0]);
    char bokstav2 = toupper(kommando[2]); 

    while (bokstav1 != 'Q') { 

        switch (bokstav1) { 
            case 'T':  gOperatorBase.OperatorHandling(bokstav2);   break;
            case 'B':  gByerBase.ByerHandling(bokstav2);           break;
            case 'A':  gByerBase.AttraksjonHandling(bokstav2);     break;
            default:   skrivMeny();                                break;   
        }

        cout << "\nKommando: ";
        getline(cin, kommando); 

        bokstav1 = toupper(kommando[0]);
        bokstav2 = toupper(kommando[2]);
    
    }

    cout << "\n\n";

    gOperatorBase.skrivTilFil();
    gByerBase.skrivTilFil();

    return 0;
}

