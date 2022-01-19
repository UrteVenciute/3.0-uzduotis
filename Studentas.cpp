#include "Studentas.h"

int sugeneruojami_sakiciai()
{
    return rand() % 10 + 1;
}

vector<int> auto_marks(int how_many_marks)
{
    vector<int> skaiciai;
    for (int i = 0; i < how_many_marks; i++)
    {
        skaiciai.push_back(sugeneruojami_sakiciai());
    }
    return skaiciai;
}

float studentas::galutBalas(vector<int> skaiciai)
{
    studentas grupe;
    grupe.galutinis_vidurkis = 0.4 * std::accumulate(skaiciai.begin(), skaiciai.end(), 0) / skaiciai.size() + 0.6 * sugeneruojami_sakiciai();
    return grupe.galutinis_vidurkis;
}

void failoNuskaitymas(vector <studentas>& grupe1, int& v1)
{
    double temp;
    double egzaminas;
    string temp2;
    int i = 0;
    std::stringstream out_data;
    int zodziuSk = 0;
    string zodis, vardas, pavarde;


    string pav = "Studentai " + to_string(v1) + ".txt";
    ifstream nuskaitymas(pav);

    getline(nuskaitymas, temp2);
    stringstream s(temp2);
    while (s >> zodis)
    {
        zodziuSk++;
    }
    int pazKiek = zodziuSk - 3;
    out_data << nuskaitymas.rdbuf();
    while (i < v1)
    {
        studentas stu;
        out_data >> vardas >> pavarde;
        stu.setVardas(vardas);
        stu.setPavarde(pavarde);

        stu.PazReserve(pazKiek);

        for (int k = 0; k < pazKiek; k++)
        {
            out_data >> temp;
            stu.PazPut(temp);
        }

        out_data >> egzaminas;

        stu.setEgz(egzaminas);

        stu.SetGalutinis_vidurkis();

        grupe1.push_back(stu);

        stu.PazClean();
        i++;
    }
    nuskaitymas.close();
}


void rusiavimas2(vector <studentas>& grupe_vector, vector <studentas>& vargsiukai_vector_2, vector <double>& time_vector, char& atsakymas)
{
    auto start = std::chrono::high_resolution_clock::now();
    vector<studentas>::iterator it1;
    std::partition(grupe_vector.begin(), grupe_vector.end(), [](studentas a)
        {
            return a.GetGalutinisVidurkis() >= 5;
        });
    auto itt = std::partition_point(grupe_vector.begin(), grupe_vector.end(), [](studentas a)
        {
            return a.GetGalutinisVidurkis() >= 5;
        });
    for (it1 = itt; it1 != grupe_vector.end(); it1++)
    {
        vargsiukai_vector_2.push_back(*it1);
    }
    grupe_vector.assign(grupe_vector.begin(), itt);
    grupe_vector.resize(grupe_vector.size());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    time_vector.push_back(diff.count());
}

void spausdinimas(int& v1, char& atsakymas, vector <studentas>& sarasas, vector <double>& laikas, string& pav)
{
    string failoPav = pav + "_Studentai " + to_string(v1) + ".txt";

    std::stringstream ss;

    auto start = std::chrono::high_resolution_clock::now();

    ofstream rz("Rezultatai_vector_" + failoPav);

    ss << setw(20) << left << "Pavarde" << setw(20) << left << "Vardas" << setw(20) << left << "Galutinis (Vid.)" << endl;
    ss << "-------------------------------------------------------------------------" << endl;

    for (const auto& stu : sarasas)
    {
        ss << setw(20) << left << stu.GetPavarde() << setw(20) << left << stu.GetVardas() << setw(20) << left << fixed << setprecision(2) << stu.GetGalutinisVidurkis() << endl;
    }

    rz << ss.str();

    rz.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    laikas.push_back(diff.count());
}

void spausdinimas(char& atsakymas, vector <studentas>& grupe1)
{
    ofstream rz("rezultatai.txt");

    rz << setw(20) << left << "Pavarde" << setw(20) << left << "Vardas" << setw(20) << left << "Galutinis (Vid.)" << setw(20) << left << "Galutinis (Med.)" << endl;
    rz << "--------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < grupe1.size(); i++)
    {
        rz << setw(20) << left << grupe1.at(i).GetPavarde() << setw(20) << left << grupe1.at(i).GetVardas() << setw(20) << left << fixed << setprecision(2) << grupe1.at(i).GetGalutinisVidurkis() << setw(20) << left << fixed << setprecision(2) << grupe1.at(i).GetGalutinisVidurkis() << endl;
    }
}