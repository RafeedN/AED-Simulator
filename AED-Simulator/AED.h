#ifndef AED_H
#define AED_H

#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QMovie>
#include <QTimer>

#include <QThread>
#include <unistd.h>
#include "AEDSpeaker.h"
#include "User.h"




class AED : public QObject  {
    Q_OBJECT

public:
    explicit AED(AEDSpeaker* speaker, User* user, QObject *parent = nullptr);

    void setTestCase(int rhythm1, int rhythm2, bool shock2, int rhythm3, int rhythm4, bool battLow);

    int getPostCPRRhythm();
    bool getNumShocks();

    void ECGDisplay(int heartRhythm);
    void initiateSelfTest();
    void placeElectrodes();
    void detachElectrodes();
    void analyzeHeartRhythm(Patient* patient);
    void chargeBattery();
    void Shock();

    void updateCPR(const QString& CPRStatus);

signals:
    void updateECGDisplay(const QString &gifPath);
    void updateAEDDisplay(const QString &aedText);
    void updateBatteryCharge(const QString &batteryCharge);



public slots:
    void powerOn();


private:
    bool isOn;
    bool electrodesPlaced;
    bool shockAdvised;
    int currentCharge;

    int postShockRhythm;
    int postCPRRhyythm;
    bool multipleShocks;
    int postSecondShockRhythm;
    int postSecondCPRRhythm;

    bool isBatteryLow;

    AEDSpeaker* speaker;
    User* user;


};

#endif // AED_H
