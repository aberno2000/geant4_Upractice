#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name):
G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}
G4bool MySensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *ROhist)
{};

