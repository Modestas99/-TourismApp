#ifndef KIRKE_H
#define KIRKE_H

#include "attraksjon.h"
#include "enum.h"
#include <fstream>


class Kirke : public Attraksjon {
    
    private:
        int byggeaar;
        int kapasitet;
        KirkeType kirkeType;

    
    public:
        virtual void SkrivData();
        virtual void skrivTilFil(std::ofstream& utfil) const;
        virtual char getType() const;
        Kirke(std::ifstream &inn);
        Kirke();
    
};


#endif // KIRKE_H