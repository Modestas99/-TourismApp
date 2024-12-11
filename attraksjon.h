#ifndef ATTRAKSJON_H
#define ATTRAKSJON_H

#include <string>
#include <fstream>


class Attraksjon {
    
    private:
        std::string ID;
        std::string beskrivelse;
        std::string adresse;
        std::string webside;
    
    public:
        virtual void SkrivData();
        virtual void skrivTilFil(std::ofstream& utfil) const;
        virtual char getType() const;
        Attraksjon();
        Attraksjon(std::ifstream & inn);
        std::string getNavn();


       
    
};


#endif // ATTRAKSJON_H