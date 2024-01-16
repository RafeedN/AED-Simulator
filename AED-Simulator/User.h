#ifndef USER_H
#define USER_H

#include <QObject>
#include <QPushButton>
#include "Patient.h"


class User : public QObject  {
    Q_OBJECT

public:
    explicit User(Patient* patient, QObject *parent = nullptr);
    void shavePatient();
    bool placeElectrodes();
    void setElectrodesPlaced(bool value);
    void setIsOn(bool value);

    void performCPR();

    void LightCPR();
    void HardCPR();
    void GoodCPR();

    void continueEvaluation();

    Patient* getPatient();

signals:
    void updateUserButtons(const QString &text);
    void updateCPRStatus(const QString& text);
    void updateAED(const QString& text);


public slots:


private:
    Patient* patient;
    int currentGoodCompressions;
    bool electrodesPlaced;
    bool isOn;

};

#endif // USER_H
