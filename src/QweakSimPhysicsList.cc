//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimPhysicsList.cc

   $Revision: 1.3 $	
   $Date: 2006/05/05 21:20:32 $

   \author Klaus Hans Grimm   

*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimPhysicsList.hh"

// geant4 includes
#include "G4Version.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4Decay.hh"

#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#if G4VERSION_NUMBER < 940
#include "G4MultipleScattering.hh"
#else
#include "G4eMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#endif
#include "G4eBremsstrahlung.hh"
#include "G4eIonisation.hh"
#include "G4PAIModel.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuonMinusCaptureAtRest.hh"
#include "G4hIonisation.hh"
#include "G4HadronElasticProcess.hh"
#include "G4LElastic.hh"
#include "G4CascadeInterface.hh"
#include "G4LEKaonZeroLInelastic.hh"
#include "G4LEKaonZeroSInelastic.hh"
#include "G4TheoFSGenerator.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4ExcitationHandler.hh"
#include "G4PreCompoundModel.hh"
#include "G4QGSMFragmentation.hh"
#include "G4ExcitedStringDecay.hh"
#include "G4QGSModel.hh"
#include "G4RegionStore.hh"
#include "G4RunManager.hh"
#include "G4eplusAnnihilation.hh"
#include "G4PionPlusInelasticProcess.hh"
#include "G4PiNuclearCrossSection.hh"
#include "G4LEPionPlusInelastic.hh"
#include "G4PionMinusInelasticProcess.hh"
#include "G4LEPionMinusInelastic.hh"
#include "G4PionMinusAbsorptionAtRest.hh"
#include "G4KaonPlusInelasticProcess.hh"
#include "G4LEKaonPlusInelastic.hh"
#include "G4KaonMinusInelasticProcess.hh"
#include "G4LEKaonMinusInelastic.hh"
#include "G4KaonMinusAbsorption.hh"
#include "G4KaonZeroLInelasticProcess.hh"
#include "G4KaonZeroSInelasticProcess.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4ProtonInelasticCrossSection.hh"
#include "G4LEProtonInelastic.hh"
#include "G4AntiProtonInelasticProcess.hh"
#include "G4LEAntiProtonInelastic.hh"
#include "G4HEAntiProtonInelastic.hh"
#include "G4AntiProtonAnnihilationAtRest.hh"
#include "G4AntiNeutronInelasticProcess.hh"
#include "G4LEAntiNeutronInelastic.hh"
#include "G4HEAntiNeutronInelastic.hh"
#include "G4AntiNeutronAnnihilationAtRest.hh"
#include "G4LambdaInelasticProcess.hh"
#include "G4LELambdaInelastic.hh"
#include "G4HELambdaInelastic.hh"
#include "G4AntiLambdaInelasticProcess.hh"
#include "G4LEAntiLambdaInelastic.hh"
#include "G4HEAntiLambdaInelastic.hh"
#include "G4SigmaMinusInelasticProcess.hh"
#include "G4LESigmaMinusInelastic.hh"
#include "G4HESigmaMinusInelastic.hh"
#include "G4AntiSigmaMinusInelasticProcess.hh"
#include "G4LEAntiSigmaMinusInelastic.hh"
#include "G4HEAntiSigmaMinusInelastic.hh"
#include "G4SigmaPlusInelasticProcess.hh"
#include "G4LESigmaPlusInelastic.hh"
#include "G4HESigmaPlusInelastic.hh"
#include "G4AntiSigmaPlusInelasticProcess.hh"
#include "G4LEAntiSigmaPlusInelastic.hh"
#include "G4HEAntiSigmaPlusInelastic.hh"
#include "G4XiMinusInelasticProcess.hh"
#include "G4LEXiMinusInelastic.hh"
#include "G4HEXiMinusInelastic.hh"
#include "G4AntiXiMinusInelasticProcess.hh"
#include "G4LEAntiXiMinusInelastic.hh"
#include "G4HEAntiXiMinusInelastic.hh"
#include "G4XiZeroInelasticProcess.hh"
#include "G4LEXiZeroInelastic.hh"
#include "G4HEXiZeroInelastic.hh"
#include "G4AntiXiZeroInelasticProcess.hh"
#include "G4LEAntiXiZeroInelastic.hh"
#include "G4HEAntiXiZeroInelastic.hh"
#include "G4OmegaMinusInelasticProcess.hh"
#include "G4LEOmegaMinusInelastic.hh"
#include "G4HEOmegaMinusInelastic.hh"
#include "G4AntiOmegaMinusInelasticProcess.hh"
#include "G4LEAntiOmegaMinusInelastic.hh"
#include "G4HEAntiOmegaMinusInelastic.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronHPInelasticData.hh"
#include "G4NeutronInelasticCrossSection.hh"
#include "G4HadronFissionProcess.hh"
#include "G4LFission.hh"
#include "G4NeutronHPFission.hh"
#include "G4NeutronHPFissionData.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4LCapture.hh"
#include "G4NeutronHPCapture.hh"
#include "G4NeutronHPCaptureData.hh"
#include "G4GammaNuclearReaction.hh"
#include "G4PhotoNuclearProcess.hh"
#include "G4ElectroNuclearReaction.hh"
#include "G4ElectronNuclearProcess.hh"
#include "G4PositronNuclearProcess.hh"
#include "G4NeutronInelasticProcess.hh"

// user includes
#include "QweakSimPhysicsListMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPhysicsList::QweakSimPhysicsList() : G4VUserPhysicsList()
{
  defaultCutValue = 1.0*cm;

  // defaultCutValue     = 1.0*micrometer;

  //********************************************
  //Added for low energy hadronic tests 04/27/06
  //but may not be necessary or work well
//   cutForGamma         = defaultCutValue;
//   cutForElectron      = 1.0*nanometer;
//   cutForPositron      = defaultCutValue;
  //********************************************

  theCerenkovProcess           = 0;
  //theScintillationProcess      = 0;
  theAbsorptionProcess         = 0;
  theRayleighScatteringProcess = 0;
  theBoundaryProcess           = 0;

  pMessenger = new QweakSimPhysicsListMessenger(this);
  SetVerboseLevel(2);

//   hadPhyics = new HadronPhysicsLHEP_PRECO_HP("hadron");
//   RegisterPhysics(hadPhyics);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPhysicsList::~QweakSimPhysicsList()
{
  if (pMessenger)                    delete pMessenger; 

  if (theCerenkovProcess)            delete theCerenkovProcess;
  if (theAbsorptionProcess)          delete theAbsorptionProcess;
  if (theRayleighScatteringProcess)  delete theRayleighScatteringProcess;
  if (theBoundaryProcess)            delete theBoundaryProcess;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
  ConstructShortLiveds();
  ConstructIons();
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructProcess()
{
  AddTransportation();

  ConstructEMProcess();
  ConstructOpticalPhotonProcess();
  //ConstructHadronProcess();
  //ConstructNeutronProcess();
  //ConstructPhotonNuclearProcess();
  //ConstructElectronNuclearProcess();
  //ConstructDecayProcess();
}

void QweakSimPhysicsList::ConstructBosons()
{
    //  Construct all bosons
    G4BosonConstructor pConstructor;
    pConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructLeptons()
{
    //  Construct all leptons
    G4LeptonConstructor pConstructor;
    pConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructMesons()
{
    //  Construct all mesons
    G4MesonConstructor pMesonConstructor;
    pMesonConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructBaryons()
{
    //  Construct all baryons
    G4BaryonConstructor pBaryonConstructor;
    pBaryonConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructShortLiveds()
{
    //  Construct resonaces and quarks
    G4ShortLivedConstructor pShortLivedConstructor;
    pShortLivedConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructIons()
{
  // Construct all ions
  G4IonConstructor pConstructor;
  pConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::AddTransportation()
{
    G4VUserPhysicsList::AddTransportation();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructEMProcess()
{
    G4ProcessManager*   pManager = 0;

    /////////////////////
    //                 //
    //  Gamma physics  //
    //                 //
    /////////////////////
    //
    pManager = G4Gamma::Gamma()->GetProcessManager();
    pManager->AddDiscreteProcess(new G4PhotoElectricEffect);
    pManager->AddDiscreteProcess(new G4ComptonScattering);
    pManager->AddDiscreteProcess(new G4GammaConversion);


    ////////////////////////
    //                    //
    //  Electron physics  //
    //                    //
    ////////////////////////
    //
    pManager = G4Electron::Electron()->GetProcessManager();
    #if G4VERSION_NUMBER < 940
    pManager->AddProcess(new G4MultipleScattering,  -1, 1,1);
    #else
    pManager->AddProcess(new G4eMultipleScattering, -1, 1,1);
    #endif
    pManager->AddProcess(new G4eBremsstrahlung,     -1, 3,3);
    pManager->AddProcess(new G4eIonisation,         -1, 2,2);

/*
    const G4RegionStore* theRegionStore = G4RegionStore::GetInstance();

    G4Region* DriftCellRegion_VDC = theRegionStore->GetRegion("DriftCellRegion_VDC");

    // see http://geant4.home.cern.ch/geant4/G4UsersDocuments/UsersGuides/PhysicsReferenceManual/html/node38.html
    // The Photoabsorption Ionization (PAI) model describes the ionization energy loss of a relativistic charged particle in matter.
    G4eIonisation* eion = new G4eIonisation();
    //eion -> SetVerboseLevel(3);

    G4PAIModel*     paiVDC = new G4PAIModel(G4Electron::ElectronDefinition(),"PAIModel");

    // set energy limits where 'pai' is active
    paiVDC->SetLowEnergyLimit(0.1*keV);
    paiVDC->SetHighEnergyLimit(100.0*TeV);

    // here 0 is the highest priority in region 'gas'
    eion->AddEmModel(0,paiVDC,paiVDC,DriftCellRegion_VDC);


    // G4Region* DriftCellRegion_GEM = theRegionStore->GetRegion("DriftCellRegion_GEM");

    // G4PAIModel*     paiGEM = new G4PAIModel(G4Electron::ElectronDefinition(),"PAIModel");
    // set energy limits where 'pai' is active
    // paiGEM->SetLowEnergyLimit(0.1*keV);
    // paiGEM->SetHighEnergyLimit(100.0*TeV);

    // here 0 is the highest priority in region 'gas'
    // eion->AddEmModel(0,paiGEM,paiGEM,DriftCellRegion_GEM);

    //eion->DumpInfo()
    //eion->PrintInfo()

    pManager->AddProcess(eion,-1, 2, 2); 
*/

    ////////////////////////
    //                    //
    //  Positron physics  //
    //                    //
    ////////////////////////
    //
    pManager = G4Positron::Positron()->GetProcessManager(); 
    #if G4VERSION_NUMBER < 940
    pManager->AddProcess(new G4MultipleScattering,  -1, 1,1);
    #else
    pManager->AddProcess(new G4eMultipleScattering, -1, 1,1);
    #endif
    pManager->AddProcess(new G4eIonisation,         -1, 2,2);
    pManager->AddProcess(new G4eBremsstrahlung,     -1, 3,3);
    pManager->AddProcess(new G4eplusAnnihilation,    0,-1,4);


    ////////////////////////
    //                    //
    //   Muon- physics    //
    //                    //
    ////////////////////////
    //
    pManager = G4MuonMinus::MuonMinus()->GetProcessManager(); 
    #if G4VERSION_NUMBER < 940
    pManager->AddProcess(new G4MultipleScattering(),    -1, 1, 1);
    #else
    pManager->AddProcess(new G4MuMultipleScattering(),  -1, 1, 1);
    #endif
    pManager->AddProcess(new G4MuIonisation(),          -1, 2, 2);
    pManager->AddProcess(new G4MuBremsstrahlung(),      -1,-1, 3);  
    pManager->AddProcess(new G4MuPairProduction(),      -1,-1, 4);
    pManager->AddProcess(new G4MuonMinusCaptureAtRest(), 0,-1,-1);


    ////////////////////////
    //                    //
    //   Muon+ physics    //
    //                    //
    ////////////////////////
    //
    pManager = G4MuonPlus::MuonPlus()->GetProcessManager(); 
    #if G4VERSION_NUMBER < 940
    pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
    #else
    pManager->AddProcess(new G4MuMultipleScattering(),-1, 1, 1);
    #endif
    pManager->AddProcess(new G4MuIonisation(),        -1, 2, 2);
    pManager->AddProcess(new G4MuBremsstrahlung(),    -1,-1, 3);
    pManager->AddProcess(new G4MuPairProduction(),    -1,-1, 4);


    ////////////////////////
    //                    //
    //    Tau- physics    //
    //                    //
    ////////////////////////
    //
    pManager = G4TauMinus::TauMinus()->GetProcessManager();
    #if G4VERSION_NUMBER < 940
    pManager->AddProcess(new G4MultipleScattering(),   -1, 1, 1);
    #else
    pManager->AddProcess(new G4MuMultipleScattering(), -1, 1, 1);
    #endif
    pManager->AddProcess(new G4hIonisation(),          -1, 2, 2);


    ////////////////////////
    //                    //
    //    Tau+ physics    //
    //                    //
    ////////////////////////
    //
    pManager = G4TauPlus::TauPlus()->GetProcessManager();
    #if G4VERSION_NUMBER < 940
    pManager->AddProcess(new G4MultipleScattering(),   -1, 1, 1);
    #else
    pManager->AddProcess(new G4MuMultipleScattering(), -1, 1, 1);
    #endif
    pManager->AddProcess(new G4hIonisation(),          -1, 2, 2);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructOpticalPhotonProcess()
{
  theCerenkovProcess            = new G4Cerenkov("Cerenkov");
  //theScintillationProcess     = new G4Scintillation("Scintillation");
  theAbsorptionProcess          = new G4OpAbsorption();
  //theRayleighScatteringProcess  = new G4OpRayleigh();
  theBoundaryProcess            = new G4OpBoundaryProcess();

  // does not exist yet
//  theCerenkovProcess->DumpPhysicsTable();
//  theScintillationProcess->DumpPhysicsTable();
//  theAbsorptionProcess->DumpPhysicsTable();
//  theRayleighScatteringProcess->DumpPhysicsTable();

  theCerenkovProcess->SetMaxNumPhotonsPerStep(300);
  theCerenkovProcess->SetTrackSecondariesFirst(true);

  //theScintillationProcess->SetScintillationYieldFactor(1.);
  //theScintillationProcess->SetTrackSecondariesFirst(true);

  theParticleIterator->reset();

  while( (*theParticleIterator)() )
    {
      G4ParticleDefinition* particle     = theParticleIterator->value();
      G4ProcessManager*     pManager     = particle->GetProcessManager();
      G4String              particleName = particle->GetParticleName();     

      #if G4VERSION_NUMBER < 910
      if (theCerenkovProcess->IsApplicable(*particle)) {
	  pManager->AddContinuousProcess(theCerenkovProcess); // here: disable Cerenkov (part 2 of 2)
      }
      #else
      if (theCerenkovProcess->IsApplicable(*particle)) {
	  pManager->AddProcess(theCerenkovProcess);
	  pManager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
      }
      #endif

//      if (theScintillationProcess->IsApplicable(*particle)) {
//          pManager->AddProcess(theScintillationProcess);
//          pManager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
//          pManager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
//      }

      if (particleName == "opticalphoton") {

	  G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
	  pManager->AddDiscreteProcess(theAbsorptionProcess);

	// accoring to some threads in Geant4 HyperNews theRayleighScatteringProcess
	// is only defined/valid for the medium water
	//pManager->AddDiscreteProcess(theRayleighScatteringProcess);
	pManager->AddDiscreteProcess(theBoundaryProcess);
      }
    }
}

void QweakSimPhysicsList::ConstructHadronProcess()
{

  G4ProcessManager*   pManager = 0;

  //========================
  // Hadronic elastic model
  //========================

  G4HadronElasticProcess* theElasticProcess = new G4HadronElasticProcess();
  G4LElastic*             theElasticModel   = new G4LElastic();

  theElasticProcess->RegisterMe(theElasticModel);

  //==========================
  // Hadronic inelastic models
  //==========================

  // Bertini cascade model: use for p,n,pi+,pi- between 0 and 9.9 GeV
  G4CascadeInterface* bertiniModel = new G4CascadeInterface();
  bertiniModel->SetMaxEnergy(9.9*GeV);

  // Low energy parameterized models : use between 9.5 and 25 GeV
  G4double LEPUpperLimit = 25.0*GeV;
  G4double LEPpnpiLimit  =  9.5*GeV;

  G4LEKaonZeroLInelastic* LEPk0LModel = new G4LEKaonZeroLInelastic();
  LEPk0LModel->SetMaxEnergy(LEPUpperLimit);

  G4LEKaonZeroSInelastic* LEPk0SModel = new G4LEKaonZeroSInelastic();
  LEPk0SModel->SetMaxEnergy(LEPUpperLimit);

  // Quark-Gluon String Model: use for p,n,pi+,pi- between 15 GeV and 100 TeV

  G4TheoFSGenerator*               QGSPModel   = new G4TheoFSGenerator();
  G4GeneratorPrecompoundInterface* theCascade  = new G4GeneratorPrecompoundInterface();
  G4ExcitationHandler*             exHandler   = new G4ExcitationHandler();
  G4PreCompoundModel*              preCompound = new G4PreCompoundModel(exHandler);

  theCascade->SetDeExcitation(preCompound);
  QGSPModel->SetTransport(theCascade);

  G4QGSMFragmentation*             frag        = new G4QGSMFragmentation();
  G4ExcitedStringDecay*            stringDecay = new G4ExcitedStringDecay(frag);
  G4QGSModel<G4QGSParticipants>*   stringModel = new G4QGSModel<G4QGSParticipants>();

  stringModel->SetFragmentationModel(stringDecay);

  QGSPModel->SetHighEnergyGenerator(stringModel);
  QGSPModel->SetMinEnergy( 15*GeV);
  QGSPModel->SetMaxEnergy(100*TeV);


  ///////////////////
  //               //
  //  pi+ physics  //
  //               //
  ///////////////////
  //
  pManager = G4PionPlus::PionPlus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4PionPlusInelasticProcess* pipinelProc = new G4PionPlusInelasticProcess();
  G4PiNuclearCrossSection*    pion_XC     = new G4PiNuclearCrossSection();
                              pipinelProc->AddDataSet(pion_XC);
                              pipinelProc->RegisterMe(bertiniModel);

  G4LEPionPlusInelastic*      LEPpipModel = new G4LEPionPlusInelastic();
                              LEPpipModel->SetMinEnergy(LEPpnpiLimit);
                              LEPpipModel->SetMaxEnergy(LEPUpperLimit);

			      pipinelProc->RegisterMe(LEPpipModel);
                              pipinelProc->RegisterMe(QGSPModel);

  pManager->AddDiscreteProcess(pipinelProc);

  ///////////////////
  //               //
  //  pi- physics  //
  //               //
  ///////////////////
  //
  pManager = G4PionMinus::PionMinus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4PionMinusInelasticProcess* piminelProc = new G4PionMinusInelasticProcess();
  piminelProc->AddDataSet(pion_XC);
  piminelProc->RegisterMe(bertiniModel);

  G4LEPionMinusInelastic* LEPpimModel = new G4LEPionMinusInelastic();
  LEPpimModel->SetMinEnergy(LEPpnpiLimit);
  LEPpimModel->SetMaxEnergy(LEPUpperLimit);
  piminelProc->RegisterMe(LEPpimModel);

  piminelProc->RegisterMe(QGSPModel);
  pManager->AddDiscreteProcess(piminelProc);

  // pi- absorption at rest
  G4PionMinusAbsorptionAtRest* pimAbsorb = new G4PionMinusAbsorptionAtRest();
  pManager->AddRestProcess(pimAbsorb);

  ///////////////////
  //               //
  //  K+ physics   //
  //               //
  ///////////////////
  //
  pManager = G4KaonPlus::KaonPlus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4KaonPlusInelasticProcess* kpinelProc = new G4KaonPlusInelasticProcess();
  G4LEKaonPlusInelastic*      LEPkpModel = new G4LEKaonPlusInelastic();
                              LEPkpModel->SetMaxEnergy(LEPUpperLimit);
                              kpinelProc->RegisterMe(LEPkpModel);
                              kpinelProc->RegisterMe(QGSPModel);
  pManager->AddDiscreteProcess(kpinelProc);

  ///////////////////
  //               //
  //  K- physics   //
  //               //
  ///////////////////
  //
  pManager = G4KaonMinus::KaonMinus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4KaonMinusInelasticProcess* kminelProc = new G4KaonMinusInelasticProcess();
  G4LEKaonMinusInelastic*      LEPkmModel = new G4LEKaonMinusInelastic();
                               LEPkmModel->SetMaxEnergy(LEPUpperLimit);
                               kminelProc->RegisterMe(LEPkmModel);
                               kminelProc->RegisterMe(QGSPModel);
  pManager->AddDiscreteProcess(kminelProc);

  // K- absorption at rest
  G4KaonMinusAbsorption* kmAbsorb = new G4KaonMinusAbsorption();
  pManager->AddRestProcess(kmAbsorb);

  ///////////////////
  //               //
  //  K0L physics  //
  //               //
  ///////////////////
  //
  pManager = G4KaonZeroLong::KaonZeroLong()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4KaonZeroLInelasticProcess* k0LinelProc = new G4KaonZeroLInelasticProcess();
                               k0LinelProc->RegisterMe(LEPk0LModel);
                               k0LinelProc->RegisterMe(QGSPModel);
  pManager->AddDiscreteProcess(k0LinelProc);

  ///////////////////
  //               //
  //  K0S physics  //
  //               //
  ///////////////////
  //
  pManager = G4KaonZeroShort::KaonZeroShort()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4KaonZeroSInelasticProcess* k0SinelProc = new G4KaonZeroSInelasticProcess();
                               k0SinelProc->RegisterMe(LEPk0SModel);
                               k0SinelProc->RegisterMe(QGSPModel);
  pManager->AddDiscreteProcess(k0SinelProc);

  ///////////////////
  //               //
  //    Proton     //
  //               //
  ///////////////////
  //
  pManager = G4Proton::Proton()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4ProtonInelasticProcess*      pinelProc = new G4ProtonInelasticProcess();
  G4ProtonInelasticCrossSection* proton_XC = new G4ProtonInelasticCrossSection();
                                 pinelProc->AddDataSet(proton_XC);
                                 pinelProc->RegisterMe(bertiniModel);

  G4LEProtonInelastic* LEPpModel = new G4LEProtonInelastic();
                       LEPpModel->SetMinEnergy(LEPpnpiLimit);
                       LEPpModel->SetMaxEnergy(LEPUpperLimit);

		       pinelProc->RegisterMe(LEPpModel);
                       pinelProc->RegisterMe(QGSPModel);

  pManager->AddDiscreteProcess(pinelProc);

  ///////////////////
  //               //
  //  Anti-Proton  //
  //               //
  ///////////////////
  //
  pManager = G4AntiProton::AntiProton()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4AntiProtonInelasticProcess* apinelProc = new G4AntiProtonInelasticProcess();
  G4LEAntiProtonInelastic*      LEPapModel = new G4LEAntiProtonInelastic();
                                apinelProc->RegisterMe(LEPapModel);

  G4HEAntiProtonInelastic*      HEPapModel = new G4HEAntiProtonInelastic();
                                apinelProc->RegisterMe(HEPapModel);

  pManager->AddDiscreteProcess(apinelProc);

  // anti-proton annihilation at rest
  G4AntiProtonAnnihilationAtRest* apAnnihil = new G4AntiProtonAnnihilationAtRest();
  pManager->AddRestProcess(apAnnihil);

  ///////////////////
  //               //
  // Anti-Neutron  //
  //               //
  ///////////////////
  //
  pManager = G4AntiNeutron::AntiNeutron()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4AntiNeutronInelasticProcess* aninelProc = new G4AntiNeutronInelasticProcess();

  G4LEAntiNeutronInelastic*      LEPanModel = new G4LEAntiNeutronInelastic();
                                 aninelProc->RegisterMe(LEPanModel);

  G4HEAntiNeutronInelastic*      HEPanModel = new G4HEAntiNeutronInelastic();
                                 aninelProc->RegisterMe(HEPanModel);

  pManager->AddDiscreteProcess(aninelProc);

  // anti-neutron annihilation at rest
  G4AntiNeutronAnnihilationAtRest* anAnnihil = new G4AntiNeutronAnnihilationAtRest();

  pManager->AddRestProcess(anAnnihil);

  ///////////////////
  //               //
  //    Lambda     //
  //               //
  ///////////////////
  //
  pManager = G4Lambda::Lambda()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4LambdaInelasticProcess* linelProc = new G4LambdaInelasticProcess();

  G4LELambdaInelastic*      LEPlModel = new G4LELambdaInelastic();
                            linelProc->RegisterMe(LEPlModel);

  G4HELambdaInelastic*      HEPlModel = new G4HELambdaInelastic();
                            linelProc->RegisterMe(HEPlModel);

  pManager->AddDiscreteProcess(linelProc);

  ///////////////////
  //               //
  //  Anti-Lambda  //
  //               //
  ///////////////////
  //
  pManager = G4AntiLambda::AntiLambda()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4AntiLambdaInelasticProcess* alinelProc = new G4AntiLambdaInelasticProcess();

  G4LEAntiLambdaInelastic*      LEPalModel = new G4LEAntiLambdaInelastic();
                                alinelProc->RegisterMe(LEPalModel);

  G4HEAntiLambdaInelastic*      HEPalModel = new G4HEAntiLambdaInelastic();
                                alinelProc->RegisterMe(HEPalModel);

  pManager->AddDiscreteProcess(alinelProc);

  ///////////////////
  //               //
  //    Sigma-     //
  //               //
  ///////////////////
  //
  pManager = G4SigmaMinus::SigmaMinus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4SigmaMinusInelasticProcess* sminelProc = new G4SigmaMinusInelasticProcess();

  G4LESigmaMinusInelastic*      LEPsmModel = new G4LESigmaMinusInelastic();
                                sminelProc->RegisterMe(LEPsmModel);

  G4HESigmaMinusInelastic*      HEPsmModel = new G4HESigmaMinusInelastic();
                                sminelProc->RegisterMe(HEPsmModel);

  pManager->AddDiscreteProcess(sminelProc);

  ///////////////////
  //               //
  //  Anti-Sigma-  //
  //               //
  ///////////////////
  //
  pManager = G4AntiSigmaMinus::AntiSigmaMinus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4AntiSigmaMinusInelasticProcess* asminelProc =
                                  new G4AntiSigmaMinusInelasticProcess();
  G4LEAntiSigmaMinusInelastic* LEPasmModel =
                                  new G4LEAntiSigmaMinusInelastic();
  asminelProc->RegisterMe(LEPasmModel);
  G4HEAntiSigmaMinusInelastic* HEPasmModel =
                                  new G4HEAntiSigmaMinusInelastic();
  asminelProc->RegisterMe(HEPasmModel);
  pManager->AddDiscreteProcess(asminelProc);

  ///////////////////
  //               //
  //    Sigma+     //
  //               //
  ///////////////////
  //
  pManager = G4SigmaPlus::SigmaPlus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4SigmaPlusInelasticProcess* spinelProc = new G4SigmaPlusInelasticProcess();
  G4LESigmaPlusInelastic* LEPspModel = new G4LESigmaPlusInelastic();
  spinelProc->RegisterMe(LEPspModel);
  G4HESigmaPlusInelastic* HEPspModel = new G4HESigmaPlusInelastic();
  spinelProc->RegisterMe(HEPspModel);
  pManager->AddDiscreteProcess(spinelProc);

  ///////////////////
  //               //
  //  Anti-Sigma+  //
  //               //
  ///////////////////
  //
  pManager = G4AntiSigmaPlus::AntiSigmaPlus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4AntiSigmaPlusInelasticProcess* aspinelProc =
                                  new G4AntiSigmaPlusInelasticProcess();
  G4LEAntiSigmaPlusInelastic* LEPaspModel =
                                  new G4LEAntiSigmaPlusInelastic();
  aspinelProc->RegisterMe(LEPaspModel);
  G4HEAntiSigmaPlusInelastic* HEPaspModel =
                                  new G4HEAntiSigmaPlusInelastic();
  aspinelProc->RegisterMe(HEPaspModel);
  pManager->AddDiscreteProcess(aspinelProc);

  ///////////////////
  //               //
  //      Xi-      //
  //               //
  ///////////////////
  //
  pManager = G4XiMinus::XiMinus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4XiMinusInelasticProcess* xminelProc = new G4XiMinusInelasticProcess();
  G4LEXiMinusInelastic* LEPxmModel = new G4LEXiMinusInelastic();
  xminelProc->RegisterMe(LEPxmModel);
  G4HEXiMinusInelastic* HEPxmModel = new G4HEXiMinusInelastic();
  xminelProc->RegisterMe(HEPxmModel);
  pManager->AddDiscreteProcess(xminelProc);

  ///////////////////
  //               //
  //   Anti-Xi-    //
  //               //
  ///////////////////
  //
  pManager = G4AntiXiMinus::AntiXiMinus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4AntiXiMinusInelasticProcess* axminelProc =
                                  new G4AntiXiMinusInelasticProcess();
  G4LEAntiXiMinusInelastic* LEPaxmModel = new G4LEAntiXiMinusInelastic();
  axminelProc->RegisterMe(LEPaxmModel);
  G4HEAntiXiMinusInelastic* HEPaxmModel = new G4HEAntiXiMinusInelastic();
  axminelProc->RegisterMe(HEPaxmModel);
  pManager->AddDiscreteProcess(axminelProc);

  ///////////////////
  //               //
  //      Xi0      //
  //               //
  ///////////////////
  //
  pManager = G4XiZero::XiZero()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4XiZeroInelasticProcess* x0inelProc = new G4XiZeroInelasticProcess();
  G4LEXiZeroInelastic* LEPx0Model = new G4LEXiZeroInelastic();
  x0inelProc->RegisterMe(LEPx0Model);
  G4HEXiZeroInelastic* HEPx0Model = new G4HEXiZeroInelastic();
  x0inelProc->RegisterMe(HEPx0Model);
  pManager->AddDiscreteProcess(x0inelProc);

  ///////////////////
  //               //
  //   Anti-Xi0    //
  //               //
  ///////////////////
  //
  pManager = G4AntiXiZero::AntiXiZero()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4AntiXiZeroInelasticProcess* ax0inelProc =
                                new G4AntiXiZeroInelasticProcess();
  G4LEAntiXiZeroInelastic* LEPax0Model = new G4LEAntiXiZeroInelastic();
  ax0inelProc->RegisterMe(LEPax0Model);
  G4HEAntiXiZeroInelastic* HEPax0Model = new G4HEAntiXiZeroInelastic();
  ax0inelProc->RegisterMe(HEPax0Model);
  pManager->AddDiscreteProcess(ax0inelProc);

  ///////////////////
  //               //
  //    Omega-     //
  //               //
  ///////////////////
  //
  pManager = G4OmegaMinus::OmegaMinus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4OmegaMinusInelasticProcess* ominelProc =
                                      new G4OmegaMinusInelasticProcess();
  G4LEOmegaMinusInelastic* LEPomModel = new G4LEOmegaMinusInelastic();
  ominelProc->RegisterMe(LEPomModel);
  G4HEOmegaMinusInelastic* HEPomModel = new G4HEOmegaMinusInelastic();
  ominelProc->RegisterMe(HEPomModel);
  pManager->AddDiscreteProcess(ominelProc);

  ///////////////////
  //               //
  //  Anti-Omega-  //
  //               //
  ///////////////////
  //
  pManager = G4AntiOmegaMinus::AntiOmegaMinus()->GetProcessManager();

  // EM processes
  #if G4VERSION_NUMBER < 940
  pManager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
  #else
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  #endif
  pManager->AddProcess(new G4hIonisation(),         -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(theElasticProcess);

  // hadron inelastic
  G4AntiOmegaMinusInelasticProcess* aominelProc =
                                      new G4AntiOmegaMinusInelasticProcess();
  G4LEAntiOmegaMinusInelastic* LEPaomModel =
                                      new G4LEAntiOmegaMinusInelastic();
  aominelProc->RegisterMe(LEPaomModel);
  G4HEAntiOmegaMinusInelastic* HEPaomModel =
                                      new G4HEAntiOmegaMinusInelastic();
  aominelProc->RegisterMe(HEPaomModel);
  pManager->AddDiscreteProcess(aominelProc);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructNeutronProcess()
{

  G4ProcessManager*   pManager = 0;

  G4bool HPN;

  if (getenv("NeutronHPCrossSections")) {
    G4cout << "physics list: Constructing high precision neutron models" << G4endl;
    G4cout << "              using cross sections in "
           << getenv("NeutronHPCrossSections") << G4endl;
    HPN = true;
  } else {
    G4cout << "physics list: Constructing non-high-precision neutron models" << G4endl;
    HPN = false;
  }

  pManager = G4Neutron::Neutron()->GetProcessManager();

  G4double HPNLimit = 19.9*MeV;


  //====================================================
  // Neutron elastic process, models and cross sections
  //====================================================
  //
  G4HadronElasticProcess* theElasticProcess = new G4HadronElasticProcess();
  G4LElastic*             theLElasticModel  = new G4LElastic();

  if (HPN) {

      theLElasticModel->SetMinEnergy(HPNLimit);

      G4NeutronHPElastic*     theHPElasticModel = new G4NeutronHPElastic();
      G4NeutronHPElasticData* theHPElasticData  = new G4NeutronHPElasticData();

      theElasticProcess->RegisterMe(theHPElasticModel);
      theElasticProcess->AddDataSet(theHPElasticData);
  }

  theElasticProcess->RegisterMe(theLElasticModel);

  pManager->AddDiscreteProcess(theElasticProcess);


  //========================================================
  // Neutron inelastic process, models and cross sections
  // Use Quark-Gluon String Model between 15 GeV and 100 TeV
  //========================================================
  //
  G4NeutronInelasticProcess* ninelProc = new G4NeutronInelasticProcess("inelastic");

//   G4TheoFSGenerator*               QGSPModel   = new G4TheoFSGenerator();
//   G4GeneratorPrecompoundInterface* theCascade  = new G4GeneratorPrecompoundInterface();
//   G4ExcitationHandler*             exHandler   = new G4ExcitationHandler();
//   G4PreCompoundModel*              preCompound = new G4PreCompoundModel(exHandler);
//
//   theCascade->SetDeExcitation(preCompound);
//   QGSPModel->SetTransport(theCascade);
//
//   G4QGSMFragmentation*            frag        = new G4QGSMFragmentation();
//   G4ExcitedStringDecay*           stringDecay = new G4ExcitedStringDecay(frag);
//   G4QGSModel<G4QGSParticipants>*  stringModel = new G4QGSModel<G4QGSParticipants>();
//
//   stringModel->SetFragmentationModel(stringDecay);
//   QGSPModel->SetHighEnergyGenerator(stringModel);
//   QGSPModel->SetMinEnergy( 15*GeV);
//   QGSPModel->SetMaxEnergy(100*TeV);
//
//   // Use LEP model between 9.5 and 25 GeV
//   G4LENeutronInelastic* LEPnModel = new G4LENeutronInelastic();
//   LEPnModel->SetMinEnergy(  9.5*GeV);
//   LEPnModel->SetMaxEnergy( 25.0*GeV);
//
  // Use Bertini cascade model between 0 and 9.9 GeV
  G4CascadeInterface* theBertiniModel = new G4CascadeInterface();
  theBertiniModel->SetMaxEnergy(9.9*GeV);

  if (HPN) {
    // Use high precision neutron model below 20 MeV
    theBertiniModel->SetMinEnergy(HPNLimit);

    G4NeutronHPInelastic*     theHPInelasticModel = new G4NeutronHPInelastic();
    G4NeutronHPInelasticData* theHPInelasticData  = new G4NeutronHPInelasticData();

    ninelProc->RegisterMe(theHPInelasticModel);
    ninelProc->AddDataSet(theHPInelasticData);

  } else {

      G4NeutronInelasticCrossSection* neutron_XC = new G4NeutronInelasticCrossSection();
      ninelProc->AddDataSet(neutron_XC);
  }

  //ninelProc->RegisterMe(QGSPModel);
  //ninelProc->RegisterMe(LEPnModel);
  ninelProc->RegisterMe(theBertiniModel);

  pManager->AddDiscreteProcess(ninelProc);



  //===========================================================
  // Neutron-induced fission process, models and cross sections
  //===========================================================
  //
  G4HadronFissionProcess* neutronFission   = new G4HadronFissionProcess();
  G4LFission*             theLFissionModel = new G4LFission();
                          theLFissionModel->SetMaxEnergy(20.*TeV);

  if (HPN) {

      theLFissionModel->SetMinEnergy(HPNLimit);

      G4NeutronHPFission*     theHPFissionModel = new G4NeutronHPFission();
      G4NeutronHPFissionData* theHPFissionData  = new G4NeutronHPFissionData();

      neutronFission->RegisterMe(theHPFissionModel);
      neutronFission->AddDataSet(theHPFissionData);
  }

  neutronFission->RegisterMe(theLFissionModel);

  pManager->AddDiscreteProcess(neutronFission);


  //====================================================
  // Neutron capture process, models and cross sections
  //====================================================
  //
  G4HadronCaptureProcess* neutronCapture   = new G4HadronCaptureProcess();
  G4LCapture*             theLCaptureModel = new G4LCapture();

  theLCaptureModel->SetMaxEnergy(20.*TeV);

  if (HPN) {

      theLCaptureModel->SetMinEnergy(HPNLimit);

      G4NeutronHPCapture*     theHPCaptureModel = new G4NeutronHPCapture();
      G4NeutronHPCaptureData* theHPCaptureData  = new G4NeutronHPCaptureData();

      neutronCapture->RegisterMe(theHPCaptureModel);
      neutronCapture->AddDataSet(theHPCaptureData);
  }

  neutronCapture->RegisterMe(theLCaptureModel);

  pManager->AddDiscreteProcess(neutronCapture);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructPhotonNuclearProcess()
{

  //======================================
  // First define the gamma-nuclear models
  //======================================

  // low energy part
  G4GammaNuclearReaction* lowEGammaModel = new G4GammaNuclearReaction();
                          lowEGammaModel->SetMaxEnergy(3.5*GeV);

//   // high energy part
//   G4TheoFSGenerator*               highEGammaModel = new G4TheoFSGenerator();
//   G4GeneratorPrecompoundInterface* preComModel     = new G4GeneratorPrecompoundInterface();
//                                    highEGammaModel->SetTransport(preComModel);
//
//   G4QGSModel<G4GammaParticipants>* theStringModel = new G4QGSModel<G4GammaParticipants>;
//   G4QGSMFragmentation*             fragModel      = new G4QGSMFragmentation();
//   G4ExcitedStringDecay*            stringDecay    = new G4ExcitedStringDecay(fragModel);
//
//                                    theStringModel->SetFragmentationModel(stringDecay);
//
//                                    highEGammaModel->SetHighEnergyGenerator(theStringModel);
//                                    highEGammaModel->SetMinEnergy(3.*GeV);
//                                    highEGammaModel->SetMaxEnergy(100.*TeV);

  // Now add the processes to the gamma, including e+e- pair creation,
  // Compton scattering and photo-electric effect

  G4ProcessManager* pManager = G4Gamma::Gamma()->GetProcessManager();
  pManager->AddDiscreteProcess(new G4GammaConversion());
  pManager->AddDiscreteProcess(new G4ComptonScattering());
  pManager->AddDiscreteProcess(new G4PhotoElectricEffect());

  G4PhotoNuclearProcess* thePhotoNuclearProcess = new G4PhotoNuclearProcess();
                         thePhotoNuclearProcess->RegisterMe(lowEGammaModel);
                         //thePhotoNuclearProcess->RegisterMe(highEGammaModel);

  pManager->AddDiscreteProcess(thePhotoNuclearProcess);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructElectronNuclearProcess()
{
    G4ProcessManager* pManager = 0;

    pManager = G4Electron::Electron()->GetProcessManager();

    // Model for e+/e- nuclear reactions
    G4ElectroNuclearReaction* theElectronReaction       = new G4ElectroNuclearReaction();
    G4ElectronNuclearProcess* theElectronNuclearProcess = new G4ElectronNuclearProcess();

    theElectronNuclearProcess->RegisterMe(theElectronReaction);

    pManager->AddDiscreteProcess(theElectronNuclearProcess);

    //Positron physics
    pManager = G4Positron::Positron()->GetProcessManager();

    G4PositronNuclearProcess* thePositronNuclearProcess = new G4PositronNuclearProcess();
    thePositronNuclearProcess->RegisterMe(theElectronReaction);

    pManager->AddDiscreteProcess(thePositronNuclearProcess);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::ConstructDecayProcess()
{
    // Add Decay Process
    theParticleIterator->reset();

    while( (*theParticleIterator)() ){
	G4ParticleDefinition* particle = theParticleIterator->value();
	G4ProcessManager* pManager = particle->GetProcessManager();

	if (fDecayProcess.IsApplicable(*particle)) {

	    pManager ->AddProcess(&fDecayProcess);

	    // set ordering for PostStepDoIt and AtRestDoIt
	    pManager ->SetProcessOrdering(&fDecayProcess, idxPostStep);
	    pManager ->SetProcessOrdering(&fDecayProcess, idxAtRest);
	}
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::SetVerbose(G4int verbose)
{
  theCerenkovProcess->SetVerboseLevel(verbose);
  // theScintillationProcess->SetVerboseLevel(verbose);
  theAbsorptionProcess->SetVerboseLevel(verbose);
  //theRayleighScatteringProcess->SetVerboseLevel(verbose);
  theBoundaryProcess->SetVerboseLevel(verbose);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::SetNbOfPhotonsCerenkov(G4int MaxNumber)
{
  theCerenkovProcess->SetMaxNumPhotonsPerStep(MaxNumber);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPhysicsList::SetCuts()
{
  //G4VUserPhysicsList::SetCutsWithDefault method sets
  //the default cut value for all particle types
  //
//   SetCutValue(cutForGamma, "gamma");
//   SetCutValue(cutForElectron, "e-");
//   SetCutValue(cutForPositron, "e+");

  SetCutsWithDefault();

  if (verboseLevel>0) DumpCutValuesTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

