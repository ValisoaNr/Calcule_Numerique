#include <string>
#include <vector>
using namespace std;

class Resolution
{
    public:
        Resolution();
        ~Resolution();
        double f(double x);
        double fprime(double x);
        void trace();
        double distance(double x1 , double y1 , double x2 , double y2);
        double newton();
        double dichotomie();
        void demandeA();
        void demandeB();
        void demandeFonction();
        void setA(double val);
        void setB(double val);
        void setFonction(string f);
        double getA();
        double getB();
        int solution(string fichier);
        string getFonction();
    private :
        string fonction;
        double a , b;
};