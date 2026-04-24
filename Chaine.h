#include <iostream>
#include <string>
#include <cmath>

using namespace std;
class Chaine
{
    public:
        Chaine();
        ~Chaine();
        double evaluer(int& i, double x);
        void sauterEspaces();
        double lireNombre(int& i , double x);
        double element(int& i, double x);
        double terme(int& i, double x);
        void setLigne(string *l);
        string* getLigne();
    private:
        string* ligne;
};