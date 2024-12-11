#ifndef OPPLEGG_H
#define OPPLEGG_H

#include <string>
#include <vector>
#include <map>

class Opplegg {

private:
    std::string turoperatorNavn;
    std::string oppleggBeskrivelse;
    int antallDager;
    std::map<int, std::vector<std::pair<std::string, std::string>>> dagensAttraksjoner;

public:
    Opplegg(const std::string& turoperatorNavn, const std::string& oppleggBeskrivelse, int antallDager);
    void leggTilAttraksjon(int dagNummer, const std::string& attraksjonNavn, const std::string& byNavn);
    void skrivUtOpplegg() const;
    void skrivTilFil(const std::string& ut) const;
    void nullstillOpplegg();
};

#endif // OPPLEGG_H