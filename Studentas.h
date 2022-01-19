#pragma once
#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <iomanip> 
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>    
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <chrono>
#include <list>
#include <iterator>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;
using std::sort;
using std::vector;
using std::ifstream;
using std::cerr;
using std::getline;
using std::ofstream;
using std::stringstream;
using std::to_string;
using std::list;
using std::advance;

class Zmogus
{
protected:
    string vardas_;
    string pavarde_;
public:
    Zmogus() : vardas_(""), pavarde_("") {};
    ~Zmogus() {};
    virtual string GetVardas() const = 0;
    virtual string GetPavarde() const = 0;
};

class studentas : public Zmogus
{
private:
    //string vardas_, pavarde_;
    vector <double> paz_;
    double egz_;
    double galutinis_vidurkis;
public:
    ~studentas() { paz_.clear(); } //destruktorius
    studentas() : egz_(0), galutinis_vidurkis(0) {}; //default konstruktorius
    studentas(const studentas& s)  //kopijavimo konstruktorius
    {
        vardas_ = s.vardas_;
        pavarde_ = s.pavarde_;
        egz_ = s.egz_;
        paz_ = s.paz_;
        galutinis_vidurkis = s.galutinis_vidurkis;
    }
    studentas& operator=(const studentas& s) //copy priskyrimas
    {
        if (&s == this) return *this;

        vardas_ = s.vardas_;
        pavarde_ = s.pavarde_;
        egz_ = s.egz_;
        paz_ = s.paz_;
        galutinis_vidurkis = s.galutinis_vidurkis;

        return *this;
    }

    inline std::string GetVardas() const { return vardas_; }
    inline std::string GetPavarde() const { return pavarde_; }

    inline double GetEgzamina() const { return egz_; }
    inline int GetNdDydi() const { return paz_.size(); }
    inline double GetNdElementa(int i) const { return paz_.at(i); }

    void  setVardas(string vardas) { vardas_ = vardas; }
    void  setPavarde(string pavarde) { pavarde_ = pavarde; }
    void setEgz(double egz) { egz_ = egz; };

    void PazReserve(int pazKiek) { paz_.reserve(pazKiek); }
    void PazPut(double pazymys) { paz_.push_back(pazymys); }
    void PazClean() { paz_.clear(); }

    void SetGalutinis_vidurkis() {
        double sum = 0.;
        double kiekis = 0.;
        double vid = 0.;
        for (int i = 0; i < paz_.size(); i++)
        {
            sum += paz_.at(i);
            kiekis++;
        }
        vid = sum / kiekis;
        galutinis_vidurkis = 0.4 * vid + 0.6 * egz_;
    }
    inline double GetGalutinisVidurkis() const { return galutinis_vidurkis; }
    float galutBalas(std::vector<int>);

};

int sugeneruojami_sakiciai();
void failoNuskaitymas(vector <studentas>& grupe1, int& v1);
void rusiavimas2(vector <studentas>& grupe_vector, vector <studentas>& vargsiukai_vector_2, vector <double>& time_vector, char& atsakymas);
void spausdinimas(int& v1, char& atsakymas, vector <double>& laikas, vector <studentas>& sarasas, string& pav);
void spausdinimas(char& atsakymas, vector <studentas>& grupe1);
void spausdinimas(int& v1, char& atsakymas, vector <studentas>& sarasas, vector <double>& laikas, string& pav);


#endif
