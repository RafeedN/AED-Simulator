#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMovie>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        ui->attachPadsButton->setEnabled(false);
        ui->detachPadsButton->setEnabled(false);
        ui->shockButton->setEnabled(false);
        ui->shaveButton->setEnabled(false);
        ui->cprButton->setEnabled(false);
        ui->CPRGoodButton->setEnabled(false);
        ui->CPRHardButton->setEnabled(false);
        ui->CPRLightButton->setEnabled(false);

        updateECG("/home/student/AED-3004-Final/ECGImages/Dead.gif");


        patient = new Patient();
        user = new User(patient);

        speaker = new AEDSpeaker();
        aed= new AED(speaker, user);

        aedThread = new QThread();
        aed->moveToThread(aedThread);

        //--------------------------------------------------------------------------------------------------------------------------------------------------------
        setTestCases(1); //--------------------------------------------CHANGE THIS TO CHANGE TEST CASE------------------------------------------------------------
        //--------------------------------------------------------------------------------------------------------------------------------------------------------



        connect(aed, &AED::updateECGDisplay, this, &MainWindow::updateECG);  //update ECG
        connect(aed, &AED::updateAEDDisplay, this, &MainWindow::updateAED);  //update AED
        connect(aed, &AED::updateBatteryCharge, this, &MainWindow::updateBattery);

        connect(user, &User::updateUserButtons, this, &MainWindow::updateUser);  //update User Screen
        connect(user, &User::updateAED, this, &MainWindow::updateAED);  //update User Screen


        connect(user, &User::updateCPRStatus, aed, &AED::updateCPR);



        //Call from buttons
        connect(ui->powerButton, &QPushButton::clicked, aed, &AED::powerOn);
        connect(ui->attachPadsButton, &QPushButton::clicked, aed, &AED::placeElectrodes);
        connect(ui->detachPadsButton, &QPushButton::clicked, aed, &AED::detachElectrodes);


        connect(ui->shockButton, &QPushButton::clicked, aed, &AED::Shock);
        connect(ui->shaveButton, &QPushButton::clicked, user, &User::shavePatient);
        connect(ui->cprButton, &QPushButton::clicked, user, &User::performCPR);
        connect(ui->CPRHardButton, &QPushButton::clicked, user, &User::HardCPR);
        connect(ui->CPRGoodButton, &QPushButton::clicked, user, &User::GoodCPR);
        connect(ui->CPRLightButton, &QPushButton::clicked, user, &User::LightCPR);



        aedThread->start();
    }

MainWindow::~MainWindow()
{
    delete patient;
    delete user;
    delete speaker;
    delete aed;
    delete ui;
    delete ECGgif;
}

void MainWindow::setTestCases(int caseNum){
    //aed->setTestCase(1, 1, true, 1, 1, false); Heart Rhythm Post shock, Heart rhythm post cpr, second shock?, post rhythm second shock, post rhythme second cpr,  low battery?
    if(caseNum==1){    //Start with shockable rhythm, shock and then use cpr to heal
        patient->setHairy(false);
        patient->setHeartRhythm(3);
        aed->setTestCase(1, 2, false, 1, 1, false);
    }
    else if(caseNum==2){    //Is Hairy, Start with shockable rhythm, shock, need a second shock, use cpr after to heal
        patient->setHairy(true);
        patient->setHeartRhythm(3);
        aed->setTestCase(3, 3, true, 1, 2, false);
    }
    else if(caseNum==3){    //Start with shockable rhythm, cannot shock becasue low battery, perform cpr
        patient->setHairy(false);
        patient->setHeartRhythm(4);
        aed->setTestCase(1, 2, false, 1,2, true);
    }
    else if(caseNum==4){    //Start with non shockable rhythm, perform cpr
        patient->setHairy(false);
        patient->setHeartRhythm(1);
        aed->setTestCase(1, 2, false, 1,1, false);
    }
}


void MainWindow::updateECG(const QString& gifPath){
    ECGgif = new QMovie(gifPath);
    ui->ECGLabel->setMovie(ECGgif);
    ECGgif->start();
}

void MainWindow::updateAED(const QString& AEDText){
    ui->AEDDisplayLabel->setText(AEDText);


    //Change  button visibillity conditions
    if(AEDText == "Self Test Succesful!"){
        ui->attachPadsButton->setEnabled(true);
        ui->cprButton->setEnabled(false);
        ui->CPRGoodButton->setEnabled(false);
        ui->CPRHardButton->setEnabled(false);
        ui->CPRLightButton->setEnabled(false);
    }
    else if(AEDText =="Power off!"){
        ui->attachPadsButton->setEnabled(false);
        ui->detachPadsButton->setEnabled(false);
        ui->shockButton->setEnabled(false);
        ui->shaveButton->setEnabled(false);
        ui->cprButton->setEnabled(true);
        ui->CPRGoodButton->setEnabled(true);
        ui->CPRHardButton->setEnabled(true);
        ui->CPRLightButton->setEnabled(false);
        ui->batteryLabel->setText("0%");
    }
    else if(AEDText=="Shockable Rhythm Detected."){
        ui->attachPadsButton->setEnabled(false);
        ui->detachPadsButton->setEnabled(true);
        ui->shockButton->setEnabled(true);
    }
    else if(AEDText=="Not a shockable Rhythm."){
        ui->attachPadsButton->setEnabled(false);
        ui->detachPadsButton->setEnabled(true);
        ui->cprButton->setEnabled(true);
        ui->CPRGoodButton->setEnabled(true);
        ui->CPRHardButton->setEnabled(true);
        ui->CPRLightButton->setEnabled(false);
    }
    else if(AEDText=="Shock Administered"){
        ui->shaveButton->setEnabled(false);

    }
    else if(AEDText=="Perform CPR"){
        ui->cprButton->setEnabled(true);
        ui->CPRGoodButton->setEnabled(true);
        ui->CPRHardButton->setEnabled(true);
        ui->CPRLightButton->setEnabled(false);
    }
    else if(AEDText=="CPR Complete"){
        aed->ECGDisplay(aed->getPostCPRRhythm());

            ui->powerButton->setEnabled(false);
            ui->attachPadsButton->setEnabled(false);
            ui->detachPadsButton->setEnabled(false);
            ui->shockButton->setEnabled(false);
            ui->shaveButton->setEnabled(false);
            ui->cprButton->setEnabled(false);
            ui->CPRGoodButton->setEnabled(false);
            ui->CPRHardButton->setEnabled(false);
            ui->CPRLightButton->setEnabled(false);

    }else if(AEDText=="Electrodes were detached"){
        ui->attachPadsButton->setEnabled(true);
        ui->detachPadsButton->setEnabled(false);
        ui->shockButton->setEnabled(false);
        ui->shaveButton->setEnabled(false);
        aed->ECGDisplay(0);


    }else if(AEDText=="Not succuesful, prepare for second shock"){
        ui->detachPadsButton->setEnabled(true);
        ui->shockButton->setEnabled(true);
        aed->chargeBattery();
    }

}

void MainWindow::updateBattery(const QString& newBattery){
    ui->batteryLabel->setText(newBattery);
}

void MainWindow::updateUser(const QString& Text){
    if(Text == "Shave"){
        ui->shaveButton->setEnabled(true);
    }
    else if(Text == "Shaven"){
        ui->shaveButton->setEnabled(false);
    }
    else if(Text == "Good"){
        ui->CPRGoodButton->setEnabled(false);
        ui->CPRHardButton->setEnabled(true);
        ui->CPRLightButton->setEnabled(true);
    }
    else if(Text == "Hard"){
        ui->CPRGoodButton->setEnabled(true);
        ui->CPRHardButton->setEnabled(false);
        ui->CPRLightButton->setEnabled(true);
    }
    else if(Text == "Light"){
        ui->CPRGoodButton->setEnabled(true);
        ui->CPRHardButton->setEnabled(true);
        ui->CPRLightButton->setEnabled(false);
    }
}
