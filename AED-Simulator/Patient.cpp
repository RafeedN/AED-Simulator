#include "Patient.h"
#include <iostream>

Patient::Patient() : isHairy(false), heartRhythm(false), isResponsive(false), shockResult(false), currentCPRDepth(1) {}

//getters
bool Patient::getIsHairy() const { return isHairy; }
int Patient::getHeartRhythm() const { return heartRhythm; }
bool Patient::getIsResponsive() const { return isResponsive; }
bool Patient::getShockResult() const { return shockResult; }
int Patient::getCurrentCPRDepth() const { return currentCPRDepth; }

//setters
void Patient::setHairy(bool value) { isHairy = value; }
void Patient::setHeartRhythm(int value) { heartRhythm = value; }
void Patient::setResponsive(bool value) { isResponsive = value; }
void Patient::setShockResult(bool value) { shockResult = value; }
void Patient::setCurrentCPRDepth(int value) { currentCPRDepth = value; }
