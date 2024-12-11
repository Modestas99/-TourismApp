#ifndef SEVERDIGHET_H
#define SEVERDIGHET_H

#include "attraksjon.h"


class Severdighet : public Attraksjon {
    
    private:
        std::string aktivitet;
    
    public:
        virtual void SkrivData();
        virtual void skrivTilFil(std::ofstream& utfil) const;
        virtual char getType() const;
        Severdighet(std::ifstream &inn);
        Severdighet();


       
    
};


#endif // SEVERDIGHET_H