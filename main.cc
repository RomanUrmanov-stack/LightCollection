#include "G4RunManager.hh"
#include "G4UImanager.hh" 

#include "inc/lgDetectorConstruction.hh"
#include "inc/lgPhysicsList.hh"
#include "inc/lgPrimaryGeneratorAction.hh"
#include "inc/lgRunAction.hh"
#include "inc/lgEventAction.hh"

#define G4VIS_USE
#define G4UI_USE

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

int main(int argc, char *argv[])
{
    G4RunManager *run_manager = new G4RunManager;

    run_manager->SetUserInitialization(new lgDetectorConstruction());
    run_manager->SetUserInitialization(new lgPhysicsList());
    run_manager->SetUserAction(new lgPrimaryGeneratorAction());
    run_manager->SetUserAction(new lgRunAction());
    run_manager->SetUserAction(new lgEventAction());

    run_manager->Initialize();

    #ifdef G4VIS_USE
        G4VisManager* vis_manager = new G4VisExecutive();
        vis_manager->Initialize();
    #endif

    #ifdef G4UI_USE
        G4UImanager* ui_man = G4UImanager::GetUIpointer();
        G4UIExecutive* ui_ex = new G4UIExecutive(argc, argv);
    #ifdef G4VIS_USE
        ui_man->ApplyCommand("/control/execute init_vis.mac");
    #endif

        ui_ex->SessionStart();

        delete ui_ex;
    #else
        int noe = 2000;
        run_manager->BeamOn(noe);
    #endif    

    #ifdef G4VIS_USE
        delete vis_manager;
    #endif 

    delete run_manager;
    return 0;
}