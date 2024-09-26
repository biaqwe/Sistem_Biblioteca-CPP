#include <iostream>
#include <fstream>
#include <cstring>
#include "../headers/Biblioteca.h"
using namespace std;

template<typename T>
T convertFromString(const string& str) {
    T value;
    stringstream ss(str);
    ss >> value;
    return value;
}

void help(){
    cout << "+-------------------------------------------------------------------------------------+\n";
    cout << "|                                       Help:                                         |\n";
    cout << "+-------------------------------------------------------------------------------------+\n";
    cout << "| Optiune    |                             Descriere                                  |\n";
    cout << "+------------+------------------------------------------------------------------------+\n";
    cout << "| adauga     | Adauga o carte.       <titlu> -a <autor> -t <tip> -l <locatie>         |\n";
    cout << "| cauta      | Cauta o carte.        <autor | tip> <nume autor | tip>                 |\n";
    cout << "| imprumuta  | Imprumuta o carte.    -t <titlu> -a <autor> -z <nr. zile imprumut>     |\n";
    cout << "| returneaza | Returneaza o carte.   -t <titlu> -a <autor>                            |\n";
    cout << "| afiseaza   | Afiseaza cartile disponibile                                           |\n";
    cout << "| help       | Afiseaza acest meniu                                                   |\n";
    cout << "+-------------------------------------------------------------------------------------+\n";
}

int main(int argc, char *argv[]){
    string filePath = "../files/biblioteca.txt";
    Biblioteca biblioteca = Biblioteca(filePath);
    ofstream fisier(filePath, ios::app);
    if (argc > 1){
        string option = argv[1];
        if (option == "adauga"){
            bool hasAutor = false;
            bool hasTip = false;
            bool hasLocatie = false;

            for (int i = 2; i < argc; ++i){
                if (strcmp(argv[i], "-a") == 0) {
                    hasAutor = true;
                } else if (strcmp(argv[i], "-t") == 0) {
                    hasTip = true;
                } else if (strcmp(argv[i], "-l") == 0) {
                    hasLocatie = true;
                }
            }

            if (!hasAutor || !hasTip || !hasLocatie){
                cout << "Eroare: Trebuie sa specificati -a (autor), -t (tip), si -l (locatie)." << endl;
                help();
            }
            else {
                if (fisier.is_open()) {
                    string titlu = "";
                    string autor = "";
                    string tip = "";
                    string locatie = "";
                    bool nextIsAutor = false;
                    bool nextIsTip = false;
                    bool nextIsLocatie = false;
                    for (int i = 2; i < argc; ++i) {
                        if (strcmp(argv[i], "-a") == 0) {
                            nextIsAutor = true;
                            nextIsTip = false;
                            nextIsLocatie = false;
                            continue;
                        }
                        if (strcmp(argv[i], "-t") == 0) {
                            nextIsAutor = false;
                            nextIsTip = true;
                            nextIsLocatie = false;
                            continue;
                        }
                        if (strcmp(argv[i], "-l") == 0) {
                            nextIsAutor = false;
                            nextIsTip = false;
                            nextIsLocatie = true;
                            continue;
                        }
                        if (nextIsAutor) {
                            if (!autor.empty()) {
                                autor += " ";
                            }
                            autor += argv[i];
                        } else if (nextIsTip) {
                            if (!tip.empty()) {
                                tip += " ";
                            }
                            tip += argv[i];
                        } else if (nextIsLocatie) {
                            if (!locatie.empty()) {
                                locatie += " ";
                            }
                            locatie += argv[i];
                        } else {
                            if (!titlu.empty()) {
                                titlu += " ";
                            }
                            titlu += argv[i];
                        }
                    }
                    if (titlu.empty() || autor.empty() || tip.empty() || locatie.empty()) {
                        cout << "Eroare: Toate atributele (titlu, autor, tip, locatie) trebuie sa fie specificate."<< endl;
                        help();
                    } else {
                        biblioteca += Carte(titlu, autor, tip, locatie, 1);
                    }
                    fisier.close();
                } else {
                    cout << "Eroare la deschiderea fisierului." << endl;
                }
            }
        }
        else if (option == "cauta"){
            if (fisier.is_open()){
                string criteriu = argv[2];
                if (criteriu == "autor"){
                    string numeAutor = "";
                    for (int i = 3; i < argc; ++i){
                        if (!numeAutor.empty())
                            numeAutor += " ";
                        numeAutor += argv[i];
                    }
                    if (numeAutor.empty()){
                        cout << "Eroare: Trebuie sa specificati un nume de autor pentru cautare." << endl;
                        help();
                    }else{
                        biblioteca.cautaDupaAutor(numeAutor);
                    }
                }
                else if (criteriu == "tip"){
                    string numeTip = "";
                    for (int i = 3; i < argc; ++i){
                        if (!numeTip.empty())
                            numeTip += " ";
                        numeTip += argv[i];
                    }
                    if (numeTip.empty()){
                        cout << "Eroare: Trebuie sa specificati un tip pentru cautare." << endl;
                        help();
                    }else{
                        biblioteca.cautaDupaTip(numeTip);
                    }
                }
                else{
                    cout << "Criteriu de cautare invalid." << endl;
                }
                fisier.close();
            }else{
                cout << "Eroare la deschiderea fisierului." << endl;
            }
        }
        else if (option == "imprumuta"){
            bool hasTitlu = false;
            bool hasAutor = false;
            bool hasZile = false;
            for (int i = 2; i < argc; ++i){
                if (strcmp(argv[i], "-t") == 0){
                    hasTitlu = true;
                }
                else if (strcmp(argv[i], "-a") == 0){
                    hasAutor = true;
                }
                else if (strcmp(argv[i], "-z") == 0){
                    hasZile = true;
                }
            }
            if (!hasTitlu || !hasAutor || !hasZile){
                cout << "Eroare: Trebuie sa specificati -t (titlu), -a (autor), si -z (numar zile imprumut)." << endl;
                help();
            }
            else{
                if (fisier.is_open()) {
                    string titlu = "";
                    string autor = "";
                    int nrZile = 0;
                    bool nextIsTitlu = false;
                    bool nextIsAutor = false;
                    bool nextIsZile = false;

                    for (int i = 2; i < argc; ++i) {
                        if (strcmp(argv[i], "-t") == 0) {
                            nextIsTitlu = true;
                            nextIsAutor = false;
                            nextIsZile = false;
                            continue;
                        }
                        if (strcmp(argv[i], "-a") == 0) {
                            nextIsTitlu = false;
                            nextIsAutor = true;
                            nextIsZile = false;
                            continue;
                        }
                        if (strcmp(argv[i], "-z") == 0) {
                            nextIsTitlu = false;
                            nextIsAutor = false;
                            nextIsZile = true;
                            continue;
                        }
                        if (nextIsTitlu) {
                            if (!titlu.empty())
                                titlu += " ";
                            titlu += argv[i];
                        } else if (nextIsAutor) {
                            if (!autor.empty())
                                autor += " ";
                            autor += argv[i];
                        } else if (nextIsZile) {
                            nrZile = convertFromString<int>(argv[i]);
                        }
                    }
                    if (titlu.empty() || autor.empty() || nrZile == 0) {
                        cout << "Eroare: Toate atributele (titlu, autor, nrZile) trebuie sa fie specificate." << endl;
                        help();
                    } else {
                        biblioteca.imprumuta(titlu, autor, nrZile);
                    }
                    fisier.close();
                } else {
                    cout << "Eroare la deschiderea fisierului." << endl;
                }
            }
        }
        else if (option == "returneaza"){
            bool hasTitlu = false;
            bool hasAutor = false;

            for (int i = 2; i < argc; ++i){
                if (strcmp(argv[i], "-t") == 0){
                    hasTitlu = true;
                }
                else if (strcmp(argv[i], "-a") == 0){
                    hasAutor = true;
                }
            }
            if (!hasTitlu || !hasAutor){
                cout << "Eroare: Trebuie sa specificati -t (titlu) si -a (autor)." << endl;
                help();
            }
            else {
                if (fisier.is_open()) {
                    string titlu = "";
                    string autor = "";
                    bool nextIsTitlu = false;
                    bool nextIsAutor = false;

                    for (int i = 2; i < argc; ++i) {
                        if (strcmp(argv[i], "-t") == 0) {
                            nextIsTitlu = true;
                            nextIsAutor = false;
                            continue;
                        }
                        if (strcmp(argv[i], "-a") == 0) {
                            nextIsTitlu = false;
                            nextIsAutor = true;
                            continue;
                        }
                        if (nextIsTitlu) {
                            if (!titlu.empty())
                                titlu += " ";
                            titlu += argv[i];
                        } else if (nextIsAutor) {
                            if (!autor.empty())
                                autor += " ";
                            autor += argv[i];
                        }
                    }
                    if (titlu.empty() || autor.empty()) {
                        cout << "Eroare: Toate atributele (titlu, autor) trebuie sa fie specificate." << endl;
                        help();
                    } else {
                        biblioteca.returneaza(titlu, autor);
                    }
                    fisier.close();
                } else {
                    cout << "Eroare la deschiderea fisierului." << endl;
                }
            }
        }
        else if (option == "afiseaza"){
            biblioteca.afisare();
        }
        else if (option == "help"){
            help();
        }
        else{
            cout << "Optiune invalida." << endl;
        }
    }
    else{
        help();
    }
    return 0;
}
