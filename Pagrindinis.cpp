#include "Funkcija.h"
#include "Studentas.h"
#include <sstream>

int uzklausakiekpaz()
{
    int pazSkaicius;
    cout << "Namu darbu skaicius" << endl;
    cin >> pazSkaicius;
    while (cin.fail() || pazSkaicius < 1 || pazSkaicius > 10)
    {
        cin.clear();
        cout << "Namu darbu skaicius yra netinkamas, iveskite skaiciu didesni uz 0" << endl;
        cin.ignore(256, '\n');
        cin >> pazSkaicius;
    }
    return pazSkaicius;
}

void darbasSuFailu(vector <int>& v1, char& atsakymas)
{
    string failoPav;
    vector <double> laikas_vector;
    vector <studentas> vargsiukai_vector;
    vector <studentas> grupe_vector;
    string pavP = "Protingi";
    string pavV = "Vargsiukai";

    cout << setw(46) << left << " Atliktas darbas " << setw(25) << left << "| Laikas su vektoriu " << "|" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    for (int i = 0; i < (v1.size()); i++)
    {
        laikas_vector.reserve(4);

        auto start = std::chrono::high_resolution_clock::now();
        failoNuskaitymas(grupe_vector, v1.at(i));
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        laikas_vector.push_back(diff.count());


        int vieta = 40 - i;

        cout << v1.at(i) << setw(vieta) << " studentu nuskaitymas " << "| " << setw(23) << left << laikas_vector.at(0) << "| " << endl;

        rusiavimas2(grupe_vector, vargsiukai_vector, laikas_vector, atsakymas);

        cout << v1.at(i) << setw(vieta) << " studentu surusiavimas 2 strategija " << "| " << setw(23) << left << laikas_vector.at(1) << "| " << endl;

        spausdinimas(v1.at(i), atsakymas, grupe_vector, laikas_vector, pavP);
        spausdinimas(v1.at(i), atsakymas, vargsiukai_vector, laikas_vector, pavV);

        grupe_vector.clear();
        vargsiukai_vector.clear();
        laikas_vector.clear();

    }
}