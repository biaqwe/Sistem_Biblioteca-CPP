#include "../headers/Biblioteca.h"
#include <iomanip>

using namespace std;

Biblioteca::Biblioteca(string path):nrCarti(0),path(path){
    citire();
}

void Biblioteca::eliminareSpatii(string &str){
    size_t start=str.find_first_not_of(' ');
    size_t end=str.find_last_not_of(' ');
    str=(start==string::npos)?"":str.substr(start, end-start+1);
}

int Biblioteca::gaseste(const string &numeCarte, const string &numeAutor){
    for(int i=0; i<nrCarti; i++){
        string titlu=carti[i].getTitlu();
        string autor=carti[i].getAutor();
        eliminareSpatii(titlu);
        eliminareSpatii(autor);
        if(titlu==numeCarte && autor==numeAutor)
            return i;
    }
    return -1;
}

void Biblioteca::citire(){
    ifstream fisier;

    try {
        fisier.open(path);
    } catch(std::system_error& e) {
        std::cerr << e.code().message() << std::endl;
    }

    string line;
    while (nrCarti < MAX_CARTI && getline(fisier, line)){
        stringstream ss(line);
        string titlu, autor, tip, locatie;
        int disponibila;

        getline(ss, titlu, ',');
        getline(ss, autor, ',');
        getline(ss, tip, ',');
        getline(ss, locatie, ',');
        ss >> disponibila;

        eliminareSpatii(titlu);
        eliminareSpatii(autor);
        eliminareSpatii(tip);
        eliminareSpatii(locatie);

        carti[nrCarti] = Carte(titlu, autor, tip, locatie, disponibila);
        nrCarti++;
    }

    if (nrCarti == MAX_CARTI)
        cout << "Atentie: Numarul maxim de carti a fost atins." << endl;

    fisier.close();
}


void Biblioteca::afisare(){
    cout<<"Carti disponibile in biblioteca:"<<endl;
    cout<<setw(5)<<"ID."<<setw(40)<<"Titlu"<<setw(30)<<"Autor"<<setw(15)<<"Tip"<<setw(20)<<"Locatie"<<endl;
    for(int i=0; i<nrCarti; i++)
    {
        if(carti[i].getDisponibila())
            cout<<setw(5)<<i+1<<setw(40)<<carti[i].getTitlu()<<setw(30)<<carti[i].getAutor()<<setw(15)<<carti[i].getTip()<<setw(20)<<carti[i].getLocatie()<<endl;
    }
}

void Biblioteca::cautaDupaAutor(const string &numeAutor){
    cout<<"Cartile scrise de autorul "<<numeAutor<<" sunt:"<<endl;
    for(int i=0; i<nrCarti; i++)
        if(carti[i].getAutor()==numeAutor)
            cout<<i+1<<". "<<carti[i].getTitlu()<<", "<<carti[i].getAutor()<<", "<<carti[i].getTip()<<", "<<carti[i].getLocatie()<<endl;
}

void Biblioteca::cautaDupaTip(const string &numeTip){
    cout<<"Cartile de tipul "<<numeTip<<" sunt:"<<endl;
    for(int i=0; i<nrCarti; i++)
        if(carti[i].getTip()==numeTip)
            cout<<i+1<<". "<<carti[i].getTitlu()<<", "<<carti[i].getAutor()<<", "<<carti[i].getTip()<<", "<<carti[i].getLocatie()<<endl;
}

void Biblioteca::imprumuta(const string &titlu, const string &autor, int nrZile){
    int i=gaseste(titlu, autor);
    if(i!=-1){
        if(carti[i].getDisponibila()){
            cout<<"Cartea "<<titlu<<" a fost imprumutata pentru "<<nrZile<<" zile."<<endl;
            carti[i].setDisponibila(0);
            ofstream fisier(path);
            if(!fisier){
                cout<<"Eroare la deschiderea fisierului."<<endl;
                return;
            }
            for(int j=0; j<nrCarti; j++)
                fisier<<carti[j].getTitlu()<<","<<carti[j].getAutor()<<","<<carti[j].getTip()<<","<<carti[j].getLocatie()<<","<<carti[j].getDisponibila()<<endl;
            fisier.close();
        }
        else
            cout<<"Cartea nu este disponibila pentru imprumut."<<endl;
    }
    else
        cout<<"Cartea nu a fost gasita."<<endl;
}

void Biblioteca::returneaza(const string &titlu, const string &autor){
    int i=gaseste(titlu, autor);
    if(i!=-1){
        if(carti[i].getDisponibila())
            cout<<"Cartea este deja disponibila."<<endl;
        else{
            cout<<"Cartea "<<titlu<<" a fost returnata."<<endl;
            carti[i].setDisponibila(1);
            ofstream fisier(path);
            if(!fisier){
                cout<<"Eroare la deschiderea fisierului."<<endl;
                return;
            }
            for(int j=0; j<nrCarti; j++)
                fisier<<carti[j].getTitlu()<<","<<carti[j].getAutor()<<","<<carti[j].getTip()<<","<<carti[j].getLocatie()<<","<<carti[j].getDisponibila()<<endl;
            fisier.close();
        }
    }
    else
        cout<<"Cartea nu a fost gasita."<<endl;
}

Biblioteca& Biblioteca::operator+=(const Carte &carte) {
    if (nrCarti >= MAX_CARTI) {
        cout << "Nu se mai pot adauga carti. Capacitatea maxima a fost atinsa." << endl;
        return *this;
    }

    this->carti[nrCarti] = carte;
    nrCarti++;

    ofstream fisier(path, ios::app);
    if (!fisier) {
        cout << "Eroare la deschiderea fisierului." << endl;
        return *this;
    }

    fisier << carte.getTitlu() << "," << carte.getAutor() << "," << carte.getTip() << "," << carte.getLocatie() << "," << carte.getDisponibila() << endl;
    fisier.close();

    cout << "Cartea " << carte.getTitlu() << " a fost adaugata." << endl;
    return *this;
}