#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QObject>
#include <QThread>
#include <QMovie>

#include "AED.h"
#include "User.h"
#include "Patient.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setTestCases(int caseNum);

    void updateECG(const QString& gifPath);
    void updateAED(const QString& AEDText);
    void updateBattery(const QString& AEDText);
    void updateUser(const QString& AEDText);



private:
    Ui::MainWindow *ui;
    AED *aed;
    User *user;
    Patient *patient;

    AEDSpeaker *speaker;
    QThread *aedThread;
    QMovie *ECGgif;

};
#endif // MAINWINDOW_H
