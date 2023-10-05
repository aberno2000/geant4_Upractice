#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    
    G4Element* C = nist->FindOrBuildElement("C");
    
    G4Material* SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    SiO2 -> AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2 -> AddElement(nist->FindOrBuildElement("O"), 2);
    
    G4Material* H2O = new G4Material("H2O", 1.000*g/cm3, 2);
    H2O -> AddElement(nist->FindOrBuildElement("H"), 2);
    H2O -> AddElement(nist->FindOrBuildElement("O"), 1);
    
    G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    Aerogel->AddMaterial(SiO2, 0.625);
    Aerogel->AddMaterial(H2O, 0.374);
    Aerogel->AddElement(C, 0.001);
    

    G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);

    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
    
    G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicRadiator");

    G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);
    
    G4Box *matrix_unit = new G4Box("matrix_unit", 0.005*m, 0.005*m, 0.01*m);

    MU_logic = new G4LogicalVolume(matrix_unit, worldMat,"MU_logic");
    
    for(int i=0; i<100; i++)
    {
    	for(int j=0; j<100; j++)
    	{
    	G4VPhysicalVolume *phys_vol_UM = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100,-0.5*m+(j+0.5)*m/100, 0.49*m), MU_logic, "phys_vol_UM", logicWorld, false, i+j*100, true);
    	}
    }
    
       	 
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandFill(){
  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  logicDetector->SetSensitiveDetector(sensDet);
      };
