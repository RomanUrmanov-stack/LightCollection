#include "../inc/lgDetectorConstruction.hh"

//TODO: specify unified constants

//STATIC GEOMETRY DEFINITON BEGINING
G4double lgDetectorConstruction::world_x = 3.0*m, lgDetectorConstruction::world_y = 3.0*m, lgDetectorConstruction::world_z = 3.0*m;
G4double lgDetectorConstruction::crystal_x = 5.0*mm, lgDetectorConstruction::crystal_y = 5.0*mm, lgDetectorConstruction::crystal_z = 5.0*mm;
G4double lgDetectorConstruction::window_x = 5.0*mm,  lgDetectorConstruction::window_y = 10*mm, lgDetectorConstruction::window_z = 0.25*mm;
G4double lgDetectorConstruction::grease_x = 5.0*mm, lgDetectorConstruction::grease_y = 5.0*mm, lgDetectorConstruction::grease_z = 0.015*mm;
G4double lgDetectorConstruction::gap = 0.005*mm;
//STATIC GEOMETRY DEFINITION END

lgDetectorConstruction::lgDetectorConstruction():G4VUserDetectorConstruction()
{}

lgDetectorConstruction::~lgDetectorConstruction()
{}

G4VPhysicalVolume* lgDetectorConstruction::Construct()
{
    G4NistManager* nist_manager = G4NistManager::Instance();
    checkOverlaps = true;

    const G4int entries = 2;
    G4double photon_energy[entries] = {2.034*eV, 4.136*eV}; 

    //WORLD DESCRIPTION BEGINNING

    G4Box* solid_world = new G4Box("World", world_x, world_y, world_z);
    G4Material* air = nist_manager->FindOrBuildMaterial("G4_AIR");

    G4MaterialPropertiesTable* mp_table_air = new G4MaterialPropertiesTable();

    G4double air_refractive_index[entries] = {1.0003, 1.0003};
    mp_table_air->AddProperty("RINDEX", photon_energy, air_refractive_index, entries)->SetSpline(true);

    air->SetMaterialPropertiesTable(mp_table_air);

    G4LogicalVolume* logic_world = new G4LogicalVolume(solid_world, air, "World");
    G4VPhysicalVolume* phys_world = new G4PVPlacement (0, G4ThreeVector(), logic_world, "World", 0, false, 0, checkOverlaps);

    //WORLD DESCRIPTION END

    //CRYSTAL DESCRIPTION BEGINNING 

    G4Box *solid_crystal = new G4Box("Crystal", crystal_x, crystal_y, crystal_z);
    
    G4Element* elZn = new G4Element("Zinc"," Zn", 30, 65.38*g/mole);
    G4Element* elW = new G4Element("Tungsten", "W", 74, 183.84*g/mole);
    G4Element* elO = new G4Element("Oxygen", "O", 16, 16.0*g/mole);

    G4Material* ZnWO4 = new G4Material ("ZincTungstate", 7.620*g/cm3, 3);
    ZnWO4->AddElement(elZn, 1);
    ZnWO4->AddElement(elW, 1);
    ZnWO4->AddElement(elO, 4);

    G4double crystal_refrative_index[entries] = {2.32, 2.32};
    G4double crystal_absorption_length[entries] = {24.0*cm, 24.0*cm};

    G4MaterialPropertiesTable* mp_table_crystal = new G4MaterialPropertiesTable();
    mp_table_crystal->AddProperty("RINDEX", photon_energy, crystal_refrative_index, entries)->SetSpline(true);
    mp_table_crystal->AddProperty("ABSLENGTH", photon_energy, crystal_absorption_length, entries)->SetSpline(true);

    ZnWO4->SetMaterialPropertiesTable(mp_table_crystal);

    G4LogicalVolume* logic_crystal = new G4LogicalVolume(solid_crystal, ZnWO4, "Crystal");
    G4VPhysicalVolume* phys_crystal = new G4PVPlacement(0, G4ThreeVector(), logic_crystal, "Crystal", logic_world, false, 0, checkOverlaps); 

    //CRYSTAL DESCRIPTION END

    //PD WINDOW DESCRIPTION BEGINNING

    G4Box* solid_window = new G4Box("Window", window_x, window_y, window_z);
    G4Element* elH = new G4Element("Hydrogen", "H", 1, 1.008*g/mole);
    G4Element* elC = new G4Element("Carbon", "C", 6, 12.011*g/mole);

    G4Material* epoxy_resin = new G4Material("EpoxyResin", 1.2*g/cm3, 2);
    epoxy_resin->AddElement(elH, 2);
    epoxy_resin->AddElement(elC, 2);

    G4double window_refractive_index[entries] = {1.5, 1.5};
    G4double window_absorption_length[entries] = {0.0*cm, 0.0*cm};

    G4MaterialPropertiesTable* mp_table_window = new G4MaterialPropertiesTable();
    mp_table_window->AddProperty("RINDEX", photon_energy, window_refractive_index, entries)->SetSpline(true);
    mp_table_window->AddProperty("ABSLENGTH", photon_energy, window_absorption_length, entries)->SetSpline(true);

    epoxy_resin->SetMaterialPropertiesTable(mp_table_window);

    lgSensitiveDetector* sd_window = new lgSensitiveDetector("PhotoDiode", "lg_hits_collection");
    G4SDManager* sd_manager = G4SDManager::GetSDMpointer(); 
    sd_manager->AddNewDetector(sd_window);

    G4LogicalVolume* logic_window = new G4LogicalVolume(solid_window, epoxy_resin, "Window", 0, sd_window, 0, true);
    G4VPhysicalVolume* phys_window = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + 2 * grease_z + window_z), logic_window, "Window", logic_world, false, 0, checkOverlaps);
    
    //PD WINDOW DESCRIPTION END
    
    //GREASE DESCRPTION BEGINNING

    G4Box* solid_grease = new G4Box("Grease", grease_x, grease_y, grease_z);
    G4Material* si = nist_manager->FindOrBuildMaterial("G4_Si");

    G4double grease_refractive_index[entries] = {1.465, 1.465};

    G4MaterialPropertiesTable* mp_table_grease = new G4MaterialPropertiesTable();
    mp_table_grease->AddProperty("RINDEX", photon_energy, grease_refractive_index, entries)->SetSpline(true);

    si->SetMaterialPropertiesTable(mp_table_grease);

    G4LogicalVolume* logic_grease = new G4LogicalVolume(solid_grease, si, "SiliconGrease");
    G4VPhysicalVolume* phys_grease = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, crystal_z + grease_z), logic_grease, "SiGrease", logic_world, false, 0, checkOverlaps);

    //GREASE DESCRIPTION END

    //TEFLON DESCRIPTION BEGINNING

    G4double subtr_box_teflon_x = 6.0*mm, subtr_box_teflon_y = 6.0*mm, subtr_box_teflon_z = 5.5*mm;
    G4Box* subtr_box_teflon = new G4Box("SubtractionBoxTeflon", subtr_box_teflon_x, subtr_box_teflon_y, subtr_box_teflon_z);
    G4Box* mod_solid_crystal = new G4Box("IntersectionProblemSolver", crystal_x + 2 * gap, crystal_y + 2 * gap, crystal_z + 2 * gap);

    G4ThreeVector subtr_box_teflon_trans(0.0, 0.0, subtr_box_teflon_z - crystal_z);
    G4SubtractionSolid* solid_teflon = new G4SubtractionSolid("Teflon", subtr_box_teflon, mod_solid_crystal, 0, subtr_box_teflon_trans);
    
    G4Material* teflon = nist_manager->FindOrBuildMaterial("G4_TEFLON");

    G4double teflon_refractive_index[entries] = {1.35, 1.35};

    G4MaterialPropertiesTable* mp_table_teflon = new G4MaterialPropertiesTable();
    mp_table_teflon->AddProperty("RINDEX", photon_energy, teflon_refractive_index, entries)->SetSpline(true);

    teflon->SetMaterialPropertiesTable(mp_table_teflon);

    G4LogicalVolume* logic_teflon = new G4LogicalVolume(solid_teflon, teflon, "Teflon");
    G4VPhysicalVolume* phys_teflon = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, -subtr_box_teflon_z + crystal_z), logic_teflon, "Teflon", logic_world, false, 0, checkOverlaps);

    //TEFLON DESCRIPTION END

    //LAYERS OF AIR BETWEEN CRYSTAL AND TEFLON

    G4Box* solid_back_air = new G4Box("BackAir", crystal_x, crystal_y, gap);

    G4LogicalVolume* logic_back_air = new G4LogicalVolume(solid_back_air, air, "BackAir");
    G4VPhysicalVolume* phys_back_air = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, -crystal_z - gap), logic_back_air, "BackAir", logic_world, false, 0, checkOverlaps);

    G4Box* subtr_solid_side_air = new G4Box("SubtractionBoxSideAir", crystal_x + 2 * gap, crystal_y + 2 * gap, crystal_z);
    G4SubtractionSolid* solid_side_air = new G4SubtractionSolid("SideAir", subtr_solid_side_air, solid_crystal, 0, G4ThreeVector());

    G4LogicalVolume* logic_side_air = new G4LogicalVolume(solid_side_air, air, "SideAir");
    G4VPhysicalVolume* phys_side_air = new G4PVPlacement(0, G4ThreeVector(), logic_side_air, "SideAir", logic_world, false, 0, checkOverlaps); 

    //OPTICAL SURFACES
    G4OpticalSurface* op_surf_back_ac = new G4OpticalSurface("OpSurfaceBackAirCrystal");
    G4OpticalSurface* op_surf_side_ac = new G4OpticalSurface("OpSurfaceSidekAirCrystal");
    G4OpticalSurface* op_surf_back_at = new G4OpticalSurface("OpSurfaceBackAirTeflon");
    G4OpticalSurface* op_surf_side_at = new G4OpticalSurface("OpSurfaceSidekAirTeflon");

    G4LogicalBorderSurface* logic_op_surf_back_ac = new G4LogicalBorderSurface("OpSurfaceBackAirCrystal", phys_crystal, phys_back_air, op_surf_back_ac);
    G4LogicalBorderSurface* logic_op_surf_side_ac = new G4LogicalBorderSurface("OpSurfaceSideAirCrystal", phys_crystal, phys_side_air, op_surf_side_ac);
    G4LogicalBorderSurface* logic_op_surf_back_at = new G4LogicalBorderSurface("OpSurfaceBackAirTeflon", phys_back_air, phys_teflon, op_surf_back_at);
    G4LogicalBorderSurface* logic_op_surf_side_at = new G4LogicalBorderSurface("OpSurfaceSideAirTeflon", phys_side_air, phys_teflon, op_surf_side_at);

    G4double sigma_alpha_back_ac = 0.0;
    G4double specular_lobe_back_ac[entries] = {0.0, 0.0};
    G4double specular_spike_back_ac[entries] = {1.0, 1.0};
    G4double backscatter_back_ac[entries] = {0.0, 0.0};
    G4double reflectivity_back_ac[entries] = {1.0, 1.0};

    G4double sigma_alpha_side_ac = 0.0;
    G4double specular_lobe_side_ac[entries] = {0.0, 0.0};
    G4double specular_spike_side_ac[entries] = {1.0, 1.0};
    G4double backscatter_side_ac[entries] = {0.0, 0.0};
    G4double reflectivity_side_ac[entries] = {1.0, 1.0};

    G4double sigma_alpha_back_at = 0.0;
    G4double specular_lobe_back_at[entries] = {0.0, 0.0};
    G4double specular_spike_back_at[entries] = {0.0, 0.0};
    G4double backscatter_back_at[entries] = {0.0, 0.0};
    G4double reflectivity_back_at[entries] = {0.98, 0.98};

    G4double sigma_alpha_side_at = 0.0;
    G4double specular_lobe_side_at[entries] = {0.0, 0.0};
    G4double specular_spike_side_at[entries] = {0.0, 0.0};
    G4double backscatter_side_at[entries] = {0.0, 0.0};
    G4double reflectivity_side_at[entries] = {0.98, 0.98};

    op_surf_back_ac->SetType(dielectric_dielectric);
    op_surf_back_ac->SetModel(unified);
    op_surf_back_ac->SetFinish(ground);
    op_surf_back_ac->SetSigmaAlpha(sigma_alpha_back_ac);

    op_surf_side_ac->SetType(dielectric_dielectric);
    op_surf_side_ac->SetModel(unified);
    op_surf_side_ac->SetFinish(ground);
    op_surf_side_ac->SetSigmaAlpha(sigma_alpha_side_ac);

    op_surf_back_at->SetType(dielectric_metal);
    op_surf_back_at->SetModel(unified);
    op_surf_back_at->SetFinish(ground);
    op_surf_back_at->SetSigmaAlpha(sigma_alpha_back_at);

    op_surf_side_at->SetType(dielectric_metal);
    op_surf_side_at->SetModel(unified);
    op_surf_side_at->SetFinish(ground);
    op_surf_side_at->SetSigmaAlpha(sigma_alpha_side_at);

    G4MaterialPropertiesTable* mp_table_back_ac_surf =  new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable* mp_table_side_ac_surf =  new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable* mp_table_back_at_surf =  new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable* mp_table_side_at_surf =  new G4MaterialPropertiesTable();

    mp_table_back_ac_surf->AddProperty("SPECULARLOBECONSTANT", photon_energy, specular_lobe_back_ac, entries)->SetSpline(true);
    mp_table_back_ac_surf->AddProperty("SPECULARSPIKECONSTANT", photon_energy, specular_spike_back_ac, entries)->SetSpline(true);
    mp_table_back_ac_surf->AddProperty("BACKSCATTERCONSTANT", photon_energy, backscatter_back_ac, entries)->SetSpline(true);
    mp_table_back_ac_surf->AddProperty("REFLECTIVITY", photon_energy, reflectivity_back_ac, entries)->SetSpline(true);

    mp_table_side_ac_surf->AddProperty("SPECULARLOBECONSTANT", photon_energy, specular_lobe_side_ac, entries)->SetSpline(true);
    mp_table_side_ac_surf->AddProperty("SPECULARSPIKECONSTANT", photon_energy, specular_spike_side_ac, entries)->SetSpline(true);
    mp_table_side_ac_surf->AddProperty("BACKSCATTERCONSTANT", photon_energy, backscatter_side_ac, entries)->SetSpline(true);
    mp_table_side_ac_surf->AddProperty("REFLECTIVITY", photon_energy, reflectivity_side_ac, entries)->SetSpline(true);

    mp_table_back_at_surf->AddProperty("SPECULARLOBECONSTANT", photon_energy, specular_lobe_back_at, entries)->SetSpline(true);
    mp_table_back_at_surf->AddProperty("SPECULARSPIKECONSTANT", photon_energy, specular_spike_back_at, entries)->SetSpline(true);
    mp_table_back_at_surf->AddProperty("BACKSCATTERCONSTANT", photon_energy, backscatter_back_at, entries)->SetSpline(true);
    mp_table_back_at_surf->AddProperty("REFLECTIVITY", photon_energy, reflectivity_back_at, entries)->SetSpline(true);

    mp_table_side_at_surf->AddProperty("SPECULARLOBECONSTANT", photon_energy, specular_lobe_side_at, entries)->SetSpline(true);
    mp_table_side_at_surf->AddProperty("SPECULARSPIKECONSTANT", photon_energy, specular_spike_side_at, entries)->SetSpline(true);
    mp_table_side_at_surf->AddProperty("BACKSCATTERCONSTANT", photon_energy, backscatter_side_at, entries)->SetSpline(true);
    mp_table_side_at_surf->AddProperty("REFLECTIVITY", photon_energy, reflectivity_side_at, entries)->SetSpline(true);

    op_surf_back_ac->SetMaterialPropertiesTable(mp_table_back_ac_surf);
    op_surf_side_ac->SetMaterialPropertiesTable(mp_table_side_ac_surf);
    op_surf_back_at->SetMaterialPropertiesTable(mp_table_back_at_surf);
    op_surf_side_at->SetMaterialPropertiesTable(mp_table_side_at_surf);
    //OPTICAL SURFACES

    //LAYERS OF AIR BETWEEN CRYSTAL AND TEFLON

    return phys_world;
}

std::vector<G4double> lgDetectorConstruction::get_crystal_dimensions()
{
    std::vector<G4double> dim(3);
    dim[0] = crystal_x; 
    dim[1] = crystal_y;
    dim[2] = crystal_z;

    return dim;
}