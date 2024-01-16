#ifndef PATIENT_H
#define PATIENT_H

#include <string>
using namespace std;

class Patient{

public:
    Patient();

    //getters
    bool getIsHairy() const;       // Check if patient is hairy
    int getHeartRhythm() const;       // Check if patient's heartRhythm
    bool getIsResponsive() const;  // Check if patient is responsive
    bool getShockResult() const; // Check if shock result is available
    int getCurrentCPRDepth() const;



    //setters
    void setHairy(bool value);         // Set hairy status
    void setHeartRhythm(int value);         // Set patient's heartRhythm
    void setResponsive(bool value);    // Set responsive status
    void setShockResult(bool value);   // Set shock result status
    void setCurrentCPRDepth(int value);

private:
    bool isHairy;
    int heartRhythm;
    bool isResponsive;
    bool shockResult;

    int currentCPRDepth;

};

#endif // PATIENT_H
