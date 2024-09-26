#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Carte.h"

using namespace std;

class Biblioteca
{
    private:
        static const int MAX_CARTI = 100;
        int nrCarti;
        string path;
        Carte carti[MAX_CARTI];
        void eliminareSpatii(string &str);
        int gaseste(const string &numeCarte, const string &numeAutor);

    public:
        Biblioteca(string path);
        void citire();
        void afisare();
        Biblioteca& operator+=(const Carte &carte);
        void cautaDupaAutor(const string &numeAutor);
        void cautaDupaTip(const string &numeTip);
        void imprumuta(const string &titlu, const string &autor, int nrZile);
        void returneaza(const string &titlu, const string &autor);
};
