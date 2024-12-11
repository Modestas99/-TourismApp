#ifndef TUROPERATOR_H
#define TUROPERATOR_H

#include <string>

class Turoperator {
private:
    int antallOpplegg;
    std::string gateAdresse;
    std::string kontaktpersonNavn;
    std::string mailAdresse;
    std::string postnrOgSted;
    int telefonNummer;
    std::string webside;

public:
    Turoperator();
    Turoperator(std::string gateAdresse, std::string postnrOgSted, std::string kontaktpersonNavn, std::string mailAdresse, std::string webside, int telefonNummer, int antallOpplegg);

    int getAntallOpplegg() const;
    std::string getGateAdresse() const;
    std::string getKontaktpersonNavn() const;
    std::string getMailAdresse() const;
    std::string getPostnrOgSted() const;
    int getTelefonNummer() const;
    std::string getWebside() const;

    void setGateAdresse();
    void setKontaktpersonNavn();
    void setMailAdresse();
    void setPostnrOgSted();
    void setTelefonNummer();
    void setWebside();
    
    void SkrivData1();
    void skrivData2();
    void leggTilOpplegg();
};

#endif // TUROPERATOR_H