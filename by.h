#ifndef BY_H
#define BY_H

#include "attraksjon.h"
#include <string>
#include <list>

class By {
    
    private:
        std::string land;
        std::list <Attraksjon*> attraksjoner;
    
    public:
        By();
        By(std::string land);
        void SkrivData1();
        void nyAttraksjon(Attraksjon* attraksjon);
        void skrivAttraksjoner(const std::string& byNavn);
        std::string getLand() const;
        void slettAttraksjonIBy(int nummer);
        const std::list<Attraksjon*>& getAttraksjoner() const;


       
    
};


#endif // BY_H