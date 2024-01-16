#ifndef AEDSPEAKER_H
#define AEDSPEAKER_H

class AEDSpeaker{

public:
    AEDSpeaker();
    void powerOnWarning();
    void selfTestWarning();
    void analyzingHeartRhythm();
    void shockAdvisedWarning();

    void CPRHeavyWarning();
    void CPRLightWarning();
    void CPRGood();

private:
};

#endif // AEDSPEAKER_H
