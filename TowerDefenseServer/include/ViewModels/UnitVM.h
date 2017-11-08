#ifndef _UNITVM_
#define _UNITVM_

enum UnitType { uAbmonible, uDemonioVerde, uEspectro, uHalconSangriento, uHombreCabra, uNoMuerto }; 

struct UnitVM {
  UnitType unitType;
  int healthPoints;
  unsigned int xPos;
  unsigned int yPos;
  unsigned int nextXpos;
  unsigned int nextYpos;
  unsigned int stepDelay_ms;
  unsigned int id;
};

#endif