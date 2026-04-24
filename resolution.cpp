#include "resolution.h"
#include <iostream>
#include "Fichier.h"
#include "Chaine.h"
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#define E 0.00001

double Resolution::fprime(double x)
{
    double ret , h;

    h = 1;
    while(h > E)
    {
        ret = (f(x + h) - f(x)) / h;
        h = h / 2;
    }
    
    return (ret);
}
Resolution::Resolution(){}
Resolution::~Resolution(){}
int Resolution::solution(string fichier)
{
    // Pour pouvoir faire l'affichage avec gnuplot ; il faut le fichier.gnu
    ofstream fi;
    fi.open(fichier.c_str());
    if(fi)
    {
        fi << "set xzeroaxis" << endl;
        fi << "set yzeroaxis" << endl;
        fi << "set pointsize 0.2" << endl;

        fi << "set ylabel \"abscisses\"" << endl;
        fi << "set xlabel \"ordonnees\"" << endl;
        fi << "set xrange [" << to_string(a) << ":" << to_string(b) << "]" << endl;
        fi << "set yrange [-1:1]" << endl;

        fi << "plot " << fonction << " title \""  << fonction << "\" with lines" << endl;
        fi << "replot \"solution.txt\" using 1:2 title \"approxm\" with points pt 1 ps 1.2" << endl;
        fi.close();
    }
    else
    {
        cout << "Pas de gnuplot !" << endl;
        return (-1);
    }
    return (0);
}
void Resolution::trace()
{
    solution("test.gnu");
    system("gnuplot \"test.gnu\" -persist");
}
string Resolution::getFonction()
{
    return (fonction);
}
void Resolution::setFonction(string f)
{
    fonction = f;
}
void Resolution::setA(double val)
{
    a = val;
}
double Resolution::getA()
{
    return (a);
}
void Resolution::demandeA()
{
    double tmp;
    cout << "entrez une valeur pour a : ";
    cin >> tmp;
    setA(tmp);
}
void Resolution::demandeB()
{
    double tmp;
    cout << "entrez une valeur pour b : ";
    cin >> tmp;
    setB(tmp);
}
void Resolution::setB(double val)
{
    b = val;
}
double Resolution::getB()
{
    return (b);
}
void Resolution::demandeFonction()
{
    string tmp;

    cout << "Entrez la fonction : ";
    cin.ignore();
    getline(cin , tmp);

    setFonction(tmp);
}
double Resolution::dichotomie()
{
    double ret , i , s_n , s_n1 ;
    string coordonnees;
    int iteration;
    Fichier solution;

    cout << "dichotomie : ";
    ret = f(a) * f(b);
    if(ret > 0)
    {
        cout << "intervale invalide !" << endl;
        exit(0);
    }
    
    iteration = 0;
    s_n = a;
    s_n1 = b;
    solution.setNom("solution.txt");
    coordonnees = to_string(s_n) + " 0\n" + to_string(s_n1) + " 0";
    solution.ajoutefin(coordonnees);
    while( fabs(s_n1 - s_n) > E )
    {
        i = ((s_n + s_n1) / 2);
        if((f(s_n) * f(i)) < 0)
        {
            s_n1 = i;
            coordonnees = to_string(s_n1) + " 0";
            solution.ajoutefin(coordonnees);
        }
        else if((f(i) * f(s_n1)) < 0)
        {
            s_n = i;
            coordonnees = to_string(s_n) + " 0";
            solution.ajoutefin(coordonnees);
        }
        iteration++;
    }
    
    cout << s_n << " ; " ;
    cout << "nb iteration : " << iteration << endl;
    
    return (ret);
}
double Resolution::f(double x)
{
    double resultat;
    int i;
    Chaine fonc;

    i = 0;
    fonc.setLigne(&fonction);
    resultat = fonc.evaluer(i , x);
    fonction = *(fonc.getLigne());
    return (resultat);
}
double Resolution::newton()
{
    double ret , xn , xn1;
    int iteration;
    string coordonnees;
    Fichier solution;

    cout << "newton : ";
    iteration = 0;
    xn = a;
    solution.setNom("solution.txt");
    solution.vider();
    while(fabs(distance(xn,0,xn,f(xn))) > E)
    {
        coordonnees = to_string(xn) + " 0";
        solution.ajoutefin(coordonnees);
        xn1 = xn - (f(xn)/fprime(xn));
        xn = xn1;
        iteration++;
    }
    
    cout << xn1 << " ; ";
    cout << "nb iteration : " << iteration << endl;

    ret = xn1;
    return (ret);
}
double Resolution::distance(double x1 , double y1 , double x2 , double y2)
{
    double rep;
    rep = (double) sqrt(pow((x2-x1),2) + pow((y2-y1),2));
    return (rep);
}