#include "Fichier.h"
#include <fstream>
#include <iostream>

Fichier::Fichier()
{}
Fichier::~Fichier()
{}
void Fichier::setNom(string n)
{
    nom = n;
}
string Fichier::getNom()
{
    return (nom);
}
void Fichier::vider()
{
    ofstream fic;

    fic.open(nom.c_str());
    if(fic)
    {
        fic << "";
        fic.close();
    }
    else
    {
        cout << "Erreur ouverture de GNU fichier !" << endl;
    }
}
void Fichier::ajoutefin(string chaine)
{
    ofstream fic;
    int i;
    for(i=0 ; i<chaine.length() ; i++)
    {
        if(chaine[i] == ',')
        {
            // pour que gnuplot sait double ; il faut utiliser . comme virgule
            chaine[i] = '.';
        }
    }
    fic.open(nom.c_str()  , ios::app);
    if(fic)
    {
        fic << chaine << endl;
        fic.close();
    }
    else
    {
        cout << "Erreur ouverture de GNU fichier !" << endl;
    }
}