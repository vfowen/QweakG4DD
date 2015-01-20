{
  gSystem.Load("libGeom");
  TGeoManager::Import("qweak.gdml");
  gGeoManager->GetTopVolume()->Draw("ogl");
}
