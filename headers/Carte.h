#pragma once

#include <iostream>
#include <string>
using namespace std;

class Carte
{
    string titlu;
    string autor;
    string tip;
    string locatie;
    int disponibila;
    public:
        Carte();
        Carte(string t, string a, string ty, string l, int d);
        string getTitlu() const;
        string getAutor() const;
        string getTip() const;
        string getLocatie() const;
        int getDisponibila() const;
        void setDisponibila(int d);
};

