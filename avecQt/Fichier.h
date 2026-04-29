#include <string>
using namespace std;

class Fichier
{
    public:
        Fichier();
        ~Fichier();
        void setNom(string n);
        string getNom();
        void vider();
        void ajoutefin(string chaine);
    private:
        string nom;
};