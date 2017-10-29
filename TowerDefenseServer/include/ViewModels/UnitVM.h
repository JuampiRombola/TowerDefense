#ifndef _UNITVM_
#define _UNITVM_

enum UnitType { uAbmonible, uDemonioVerde, uEspectro, uHalconSangriento, uHombreCabra, uNoMuerto }; 

struct UnitVM {
  UnitType unitType;
  int healthPoints;
  uint xPos;
  uint yPos;
  uint stepDelay_ms;
  uint id;
};

#endif