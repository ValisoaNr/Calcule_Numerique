#ifndef RESOLUTION_H
#define RESOLUTION_H

#include <QMainWindow>
#include <string>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class Resolution;
}
QT_END_NAMESPACE

class Resolution : public QMainWindow
{
    Q_OBJECT

public:
    explicit Resolution(QWidget *parent = nullptr);
    ~Resolution() override;
    double f(double x);
    double fprime(double x);
    double distance(double x1 , double y1 , double x2 , double y2);
    int Ecritsolution(string fichier);
private slots:
    void newton();
    void dichotomie();
    void Mrectangle();
    void Mtrapeze();
    void trace();
private :
    Ui::Resolution *ui;
};
#endif // RESOLUTION_H
