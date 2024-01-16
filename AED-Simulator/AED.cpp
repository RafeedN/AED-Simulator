#include "AED.h"

AED::AED(AEDSpeaker *s, User* u, QObject *parent) : QObject(parent) {
    isOn = false;
    electrodesPlaced = false;
    shockAdvised = false;
    currentCharge=0;
    speaker = s;
    user = u;
}

void AED::setTestCase(int rhythm1, int rhythm2, bool shock2, int rhythm3, int rhythm4, bool battLow){
    postShockRhythm=rhythm1;
    postCPRRhyythm=rhythm2;
    multipleShocks=shock2;
    postSecondShockRhythm=rhythm3;
    postSecondCPRRhythm=rhythm4;
    isBatteryLow=battLow;
}


void AED::powerOn() {
    if(isOn==false){
        user->setIsOn(true);
        isOn = true;
        emit updateAEDDisplay("Power On!");
        speaker->powerOnWarning();
        ECGDisplay(0);
        initiateSelfTest();
    }
    else if(isOn==true){
           user->setIsOn(false);
          isOn = false;
          emit updateAEDDisplay("Power off!");
          ECGDisplay(0);
    }
}

void AED::initiateSelfTest(){
    usleep(2000000);
    emit updateAEDDisplay("Running self test!");
    speaker->selfTestWarning();
    usleep(2000000);
    emit updateAEDDisplay("Self Test Succesful!");
    chargeBattery();
}




void AED::placeElectrodes() {
    if(user->placeElectrodes() == true){
        emit updateAEDDisplay("Electrodes were Attached");
        usleep(2000000);
        analyzeHeartRhythm(user->getPatient());
        user->setElectrodesPlaced(true);
    }
}

void AED::detachElectrodes(){
    emit updateAEDDisplay("Electrodes were detached");
    user->setElectrodesPlaced(false);
    usleep(2000000);
}

void AED::analyzeHeartRhythm(Patient* patient){
    emit updateAEDDisplay("Stand Clear");
    usleep(2000000);
    emit updateAEDDisplay("Analyzing Heart Rhythm");
    speaker->analyzingHeartRhythm();
    usleep(2000000);

    int heartRhythm = patient->getHeartRhythm();
    ECGDisplay(heartRhythm);


    if(heartRhythm==1 || heartRhythm==2){
        emit updateAEDDisplay("Not a shockable Rhythm.");
        usleep(2000000);
        emit updateAEDDisplay("Please Perform CPR!");
    }
    if(heartRhythm==3 || heartRhythm==4){
        emit updateAEDDisplay("Shockable Rhythm Detected.");
        speaker->shockAdvisedWarning();
    }
}

void AED::chargeBattery(){
    if(isBatteryLow==true){
        for(int i=0; i<=14; i++){
            QString s = QString::number(i);
            emit updateBatteryCharge(s+"%");
            usleep(25000);
        }
        currentCharge=14;
    }else{
        for(int i=0; i<=100; i++){
            QString s = QString::number(i);
            emit updateBatteryCharge(s+"%");
            usleep(25000);
        }
        currentCharge=100;
    }

}

void AED::Shock(){
    if (currentCharge==100){
        emit updateAEDDisplay("Shock Administered");
        ECGDisplay(postShockRhythm);
        usleep(1000000);
        currentCharge=0;
        QString s = QString::number(currentCharge);
        emit updateBatteryCharge(s+"%");

        usleep(1000000);

        if(multipleShocks==true){
            emit updateAEDDisplay("Prepare for second shock");
            multipleShocks=false;
            postShockRhythm=postSecondShockRhythm;
            postCPRRhyythm=postSecondCPRRhythm;
        }else{
            emit updateAEDDisplay("Perform CPR");
        }

        chargeBattery();

    }else{
        emit updateAEDDisplay("Not enough power!");
        usleep(2000000);
        emit updateAEDDisplay("Perform CPR");
    }

}

void AED::updateCPR(const QString& CPRStatus){
    if(CPRStatus=="Light"){
        emit updateAEDDisplay("Do Harder Compressions");
        speaker->CPRLightWarning();
    }
    else if(CPRStatus=="Good"){
        emit updateAEDDisplay("Good Compressions!");
        speaker->CPRGood();
    }
    else{
        emit updateAEDDisplay("Do Lighter Compressions");
        speaker->CPRHeavyWarning();
    }
}

int AED::getPostCPRRhythm(){ return postCPRRhyythm; }
bool AED::getNumShocks(){ return multipleShocks; }



void AED::ECGDisplay(int heartRhythm) {
    switch (heartRhythm){
        case 0:{ emit updateECGDisplay("/home/student/AED-3004-Final/ECGImages/Dead.gif"); break; }
        case 1:{ emit updateECGDisplay("/home/student/AED-3004-Final/ECGImages/Asystole.gif"); break; }
        case 2:{ emit updateECGDisplay("/home/student/AED-3004-Final/ECGImages/Sinus.gif"); break; }
        case 3:{ emit updateECGDisplay("/home/student/AED-3004-Final/ECGImages/VF.gif"); break; }
        case 4:{ emit updateECGDisplay("/home/student/AED-3004-Final/ECGImages/VT.gif"); break; }
    }
}

