#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
   MySensitiveDetector(G4String);
   ~MySensitiveDetector();
   
private:
   G4bool ProcessHits(G4Step *step, G4TouchableHistory *ROhist);
};
#endif
