#include "Fichier.h"
#include "Chaine.h"
#include <fstream>
#include <iostream>
#include "Resolution.h"
#include "ui_Resolution.h"
#include <QMessageBox>

Resolution::Resolution(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Resolution)
{
    ui->setupUi(this);
    connect(ui->newton , SIGNAL(clicked()) , this , SLOT(newton()));
    connect(ui->dichotomie , SIGNAL(clicked()) , this , SLOT(dichotomie()));
    connect(ui->rectangle , SIGNAL(clicked()) , this , SLOT(Mrectangle()));
    connect(ui->trapeze , SIGNAL(clicked()) , this , SLOT(Mtrapeze()));
    connect(ui->tracerGP , SIGNAL(clicked()) , this , SLOT(trace()));
}

Resolution::~Resolution()
{
    delete ui;
}
double Resolution::fprime(double x)
{
    double ret , h , epsilon;

    h = 1;
    ret = (f(x + h) - f(x)) / h;
    epsilon = ui->epsilon->value();
    while(h > epsilon)
    {
        ret = (f(x + h) - f(x)) / h;
        h = h / 2;
    }

    return (ret);
}
int Resolution::Ecritsolution(string fichier)
{
    // Pour pouvoir faire l'affichage avec gnuplot ; il faut le fichier.gnu
    ofstream fi;
    string fonction  , ordonnee;
    double a , b , tmp;
    int i;

    a = ui->a->value();
    b = ui->b->value();
    if(a > b)
    {
        tmp = a;
        a = b;
        b = tmp;
    }
    fonction = ui->fonction->text().toStdString();
    fi.open(fichier.c_str());
    if(fi)
    {
        fi << "set xzeroaxis" << endl;
        fi << "set yzeroaxis" << endl;
        fi << "set pointsize 0.2" << endl;

        fi << "set ylabel \"abscisses\"" << endl;
        fi << "set xlabel \"ordonnees\"" << endl;
        // ordonnee vers string
        ordonnee = to_string(a) + ":" + to_string(b);
        for(i=0 ; i<ordonnee.length() ; i++)
        {
            if(ordonnee[i] == ',')
            {
                // pour que gnuplot sait double ; il faut utiliser . comme virgule
                ordonnee[i] = '.';
            }
        }
        fi << "set xrange [" << ordonnee << "]" << endl;
        fi << "set yrange [-1:1]" << endl;

        fi << "plot " << fonction << " title \""  << fonction << "\" with lines" << endl;
        // s'il a calculé une approximation alors on ajoute les points dans solution.txt
        if(ui->approxim->text().length() != 0)
        {
            fi << "replot \"solution.txt\" using 1:2 title \"approxm\" with points pt 1 ps 1.2" << endl;
        }
        fi.close();
    }
    else
    {
        QMessageBox::information(this , "Pas de gnuplot" , "Impossible d'ecrire sur un fichier");
        cout << "Pas de gnuplot !" << endl;
        return (-1);
    }
    return (0);
}

void Resolution::Mrectangle()
{
    double resultat , tmp , n , a , b , epsilon;
    QString valeur;

    a = ui->a->value();
    b = ui->b->value();
    n = ui->Nsubdiv->value();
    if(a > b)
    {
        tmp = a;
        a = b;
        b = tmp;
    }

    resultat = 0;
    tmp = a;
    epsilon = ui->epsilon->value();
    while(fabs(b - tmp) > epsilon)
    {
        resultat = resultat + fabs((1/n) * f(tmp));
        tmp = tmp + (1 / n);
    }
    valeur = QString::fromStdString(to_string(resultat));
    ui->aire->setText(valeur);
}
void Resolution::Mtrapeze()
{
    double resultat , tmp , tmp1 , n , a , b , epsilon;
    QString valeur;

    a = ui->a->value();
    b = ui->b->value();
    n = ui->Nsubdiv->value();
    if(a > b)
    {
        tmp = a;
        a = b;
        b = tmp;
    }

    resultat = 0;
    tmp = a;
    tmp1 = tmp + (1 / n);
    epsilon = ui->epsilon->value();
    while(fabs(b - tmp1) > epsilon)
    {
        resultat = resultat + fabs((f(tmp) + f(tmp1)) * ((1/n)/2));
        tmp = tmp + (1 / n);
        tmp1 = tmp1 + (1 / n);
    }

    valeur = QString::fromStdString(to_string(resultat));
    ui->aire->setText(valeur);
}
void Resolution::trace()
{
    Ecritsolution("test.gnu");
    system("gnuplot \"test.gnu\" -persist");
}
void Resolution::dichotomie()
{
    double ret , i , s_n , s_n1 , a , b , epsilon;
    string coordonnees ;
    QString approxim , nbiteration;
    int iteration;
    Fichier solution;

    a = ui->a->value();
    b = ui->b->value();
    ret = f(a) * f(b);
    if(ret > 0)
    {
        QMessageBox::warning(this , "Erreur", "intervale invalide !");
        return;
    }

    iteration = 0;
    s_n = a;
    s_n1 = b;
    solution.setNom("solution.txt");
    coordonnees = to_string(s_n) + " 0\n" + to_string(s_n1) + " 0";
    solution.ajoutefin(coordonnees);
    epsilon = ui->epsilon->value();
    while( fabs(s_n1 - s_n) > epsilon )
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
    nbiteration = QString::fromStdString(to_string(iteration));
    ui->nbIteration->setText(nbiteration);

    approxim = QString::fromStdString(to_string(s_n));
    ui->approxim->setText(approxim);
}
double Resolution::f(double x)
{
    double resultat;
    string fonction;
    int i;
    Chaine fonc;

    i = 0;
    fonction = ui->fonction->text().toStdString();
    fonc.setLigne(&fonction);
    resultat = fonc.evaluer(i , x);
    fonction = *(fonc.getLigne());
    return (resultat);
}
void Resolution::newton()
{
    double ret , xn , xn1 , a , epsilon;
    int iteration;
    string coordonnees;
    QString resultat , nbiteration;
    Fichier solution;

    a = ui->a->value();
    iteration = 0;
    xn = a;
    solution.setNom("solution.txt");
    solution.vider();

    epsilon = ui->epsilon->value();
    while(fabs(distance(xn , 0 , xn , f(xn))) > epsilon)
    {
        coordonnees = to_string(xn) + " 0";
        solution.ajoutefin(coordonnees);
        xn1 = xn - (f(xn)/fprime(xn));
        xn = xn1;
        iteration++;
    }
    nbiteration = QString::fromStdString(to_string(iteration));
    ui->nbIteration->setText(nbiteration);

    ret = xn1;
    resultat = QString::fromStdString(to_string(ret));
    ui->approxim->setText(resultat);
}
double Resolution::distance(double x1 , double y1 , double x2 , double y2)
{
    double rep;
    rep = (double) sqrt(pow((x2-x1),2) + pow((y2-y1),2));
    return (rep);
}