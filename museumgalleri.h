#ifndef MUSEUMGALLERI_H
#define MUSEUMGALLER_H

#include <string>
#include "attraksjon.h"


class MuseumGalleri : public Attraksjon {
    
    private:
        std::string hoydepunkt;
    
    public:
        virtual void SkrivData();
        virtual void skrivTilFil(std::ofstream& utfil) const;
        virtual char getType() const;
        MuseumGalleri(std::ifstream &inn);
        MuseumGalleri();

       
    
};


#endif // MUSEUMGALLERI_H