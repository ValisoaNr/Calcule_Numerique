#include <iostream>
#include <string>
#include <cmath>
#include "Chaine.h"

using namespace std;

Chaine::Chaine()
{}
Chaine::~Chaine()
{}
void Chaine::setLigne(string* l)
{
    ligne = l;
}
string* Chaine::getLigne()
{
    return (ligne);
}
void Chaine::sauterEspaces()
{
    int i;

    i = 0;
    while(i < (ligne->length()))
    {
        if(((*ligne)[i] == ' ') || ((*ligne)[i] == '\t'))
        {
            ligne->erase(i , 1);
        }
        else
        {
            i++;
        }
    }
}
double Chaine::lireNombre(int& i , double x)
{
    double resultat , decimal , facteur;
    bool apresVirgule;
    char c ;
    
    resultat = 0;
    decimal = 0;
    apresVirgule = false;
    facteur = 0.1;
    while(i < ligne->length())
    {
        c = (*ligne)[i];
        if(c >= '0' && c <= '9')
        {
            if(apresVirgule)
            {
                resultat = resultat + ((c - '0') * facteur);
                facteur *= 0.1;
            }
            else
            {
                resultat = (resultat * 10) + (c - '0');
            }
            i++;
        }
        else if(c == '.')
        {
            apresVirgule = true;
            i++;
        }
        else if(isalpha(c))
        {
            resultat *= element(i , x);
            i++;
        }
        else
        {
            break;
        }
    }
    return resultat;
}
double Chaine::element(int& i, double x)
{
    char c;
    double nombre , contenu;
    string fonction;
 
    nombre = 0;
    if(i >= ligne->length())
    {
        return (nombre);
    }
    
    c = (*ligne)[i];
    
    // Si c'est un nombre
    if((c >= '0' && c <= '9') || c == '.')
    {
        nombre = lireNombre(i , x);
        return nombre;
    }
    
    // Si c'est la variable x
    if(c == 'x')
    {
        i++;
        return (x);
    }
    
    // Si c'est une parenthèse ouvrante
    if(c == '(')
    {
        i++;
        nombre = evaluer(i, x);
        if(i < ligne->length() && (*ligne)[i] == ')')
        {
            i++;
        }
        return nombre;
    }
    
    // Sinon, c'est une fonction (sin, cos, log, sqrt)
    fonction = "";
    while(i < ligne->length() && isalpha((*ligne)[i]))
    {
        fonction = fonction + (*ligne)[i];
        i++;
    }
    contenu = 0;
    
    if(i < ligne->length() && (*ligne)[i] == '(')
    {
        i++;
        contenu = evaluer(i, x);
        if((i < ligne->length()) && ((*ligne)[i] == ')'))
        {
            i++;
        }
    }
    
    if(fonction == "sin")
    {
        return sin(contenu);
    }
    else if(fonction == "cos")
    {
        return cos(contenu);
    }
    else if(fonction == "log")
    {
        return log(contenu);
    }
    else if(fonction == "sqrt")
    {
        return sqrt(contenu);
    }
    
    return (0);
}
double Chaine::terme(int& i, double x)
{
    double resultat , val;
    char op;
    
    resultat = element(i, x);
    while (i < ligne->length())
    {
        op = (*ligne)[i];
        if (op == '*' || op == '/')
        {
            i++;
            val = element(i, x);
            if (op == '*')
            {
                resultat = resultat * val;
            }
            else
            {
                resultat = resultat / val;
            }
        }
        else
        {
            break;
        }
    }
    return resultat;
}
double Chaine::evaluer(int& i, double x)
{
    double resultat , val;
    char op;
    
    sauterEspaces();
    resultat = terme(i, x);
    while(i < (ligne->length()))
    {
        op = (*ligne)[i];
        if(op == '+' || op == '-')
        {
            i++;
            val = terme(i, x);
            if(op == '+')
            {
                resultat = resultat + val;
            }
            else
            {
                resultat = resultat - val;
            }
        }
        else 
        {
            break;
        }
    }
    return resultat;
}
