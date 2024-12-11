#ifndef BYER_H
#define BYER_H

#include "by.h"
#include <map>
#include <string>

class Byer {

    private:
        std::map <std::string,By*> byer;
    
    public:
        void nyBy();
        void skrivAlleByer();
        void skrivEnBy();
        void slettEnBy();
        void skrivTilFil();
        void leggTilAttraksjonIBy();
        void lesFraFil();
        void slettAttraksjonIBy();
        By* getBy(const std::string& byNavn);
        std::string finnEntydigByNavn(const std::string& navn);
        void ByerHandling(char valg);
        void AttraksjonHandling(char valg);
        
};



#endif // BYER_H