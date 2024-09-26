#include "../headers/Carte.h"

Carte::Carte():titlu(""), autor(""), tip(""), locatie(""), disponibila(0){

}

Carte::Carte(string t, string a, string ty, string l, int d):titlu(t), autor(a), tip(ty), locatie(l), disponibila(d){

}

string Carte::getTitlu() const{
    return titlu;
}

string Carte::getAutor() const{
    return autor;
}

string Carte::getTip() const{
    return tip;
}

string Carte::getLocatie() const{
    return locatie;
}

int Carte::getDisponibila() const{
    return disponibila;
}

void Carte::setDisponibila(int d){
    disponibila=d;
}
