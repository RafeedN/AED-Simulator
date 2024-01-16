#include "User.h"
#include <iostream>
using namespace  std;

User::User(Patient* patient1, QObject *parent) : QObject(parent), patient(patient1), currentGoodCompressions(0) {}

void User::shavePatient() {
    patient->setHairy(false);
    emit updateUserButtons("Shaven");
    cout << "USER:[ Has SUCCESSFULLY shaved the victim's chest!]"<< endl;
}

bool User::placeElectrodes() {
    if(patient->getIsHairy() == false){
        cout << "USER:[ Has SUCCESSFULLY placed the electrode!]"<< endl;
        return true;
    }else{
        cout << "USER:[ Victim's Chest is too hairy please shave and REATTACH THE ELECTRODE!]"<< endl;
        emit updateUserButtons("Shave");
        return false;
    }
}

void User::setElectrodesPlaced(bool value){
    electrodesPlaced=value;
}

void User::setIsOn(bool value){ isOn=value; }

void User::performCPR() {
    if(patient->getCurrentCPRDepth()==1 && electrodesPlaced==true && isOn==true){
        emit updateCPRStatus("Light");
    }
    else if(patient->getCurrentCPRDepth()==2 && electrodesPlaced==true  && isOn==true){
        currentGoodCompressions++;

        if(currentGoodCompressions==20){
            emit updateAED("CPR Complete");
            continueEvaluation();
        }else{
            emit updateCPRStatus("Good");
        }
        cout << "USER:Succesfully Completed "<<currentGoodCompressions<<"/20 compressions"<< endl;

    }
    else if(patient->getCurrentCPRDepth()==3 && electrodesPlaced==true  && isOn==true){
        emit updateCPRStatus("Hard");
    }
    else{
        cout << "I don't know if the compressions are good but gosh darnit I am trying."<< endl;
    }
}

void User::continueEvaluation() {
    cout << "USER:[ -------------------Continous Evaluation-----------------------]"<< endl;
}

Patient* User::getPatient() {
    return patient;
}

void User::LightCPR(){
    patient->setCurrentCPRDepth(1);
    emit updateUserButtons("Light");
}
void User::GoodCPR(){
    patient->setCurrentCPRDepth(2);
    emit updateUserButtons("Good");
}
void User::HardCPR(){
    patient->setCurrentCPRDepth(3);
    emit updateUserButtons("Hard");
}

