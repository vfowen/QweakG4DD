// Make polarization profile plots across the Cerenkov detector bars.
// Pass the tree that should be used and a tag to append to standard output file names (e.g. "_horizontal")
// Example:
// build/QweakSimRoot QwSim_0.root
//   .L polarization
//   polarization(QweakSimG4_Tree,"_horizontal")
//
void polarization (TTree* QweakSimG4_Tree, const char* tag)
{
  // Cuts:
  //  Cerenkov.Detector.ParticleType==11 -> electrons only
  //  Cerenkov.Detector.HitLocalPositionZ>0 -> avoid double counting entry and exit point of track
  //  Cerenkov.Detector.DetectorID == 1 -> require correct octant (varies from octant to octant, of course)
  //  sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01 -> require non-zero polarization to get rid of many unpolarized shower(?) electrons

  // Longitudinal polarization (this is dot product of polarization vector and normalized momentum)
  TCanvas c1("c1","Longitudinal polarization at Cerenkov detector plane",1280,1024);
  c1.Divide(3,3);
  c1.cd(4);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.LongitudinalPolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 1 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c1.cd(1);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.LongitudinalPolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 2 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c1.cd(2);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.LongitudinalPolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 3 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c1.cd(3);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.LongitudinalPolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 4 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c1.cd(6);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.LongitudinalPolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 5 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c1.cd(9);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.LongitudinalPolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 6 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c1.cd(8);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.LongitudinalPolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 7 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c1.cd(7);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.LongitudinalPolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 8 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c1.SaveAs(Form("images/longitudinal_polarization%s.png",tag));

  // Transverse polarization (this is the magnitude of the difference of the total polarization vector and the longitudinal polarization vector)
  TCanvas c2("c2","Transverse polarization at Cerenkov detector plane",1280,1024);
  c2.Divide(3,3);
  c2.cd(4);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.TransversePolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 1 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c2.cd(1);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.TransversePolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 2 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c2.cd(2);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.TransversePolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 3 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c2.cd(3);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.TransversePolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 4 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c2.cd(6);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.TransversePolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 5 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c2.cd(9);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.TransversePolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 6 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c2.cd(8);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.TransversePolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 7 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c2.cd(7);
  QweakSimG4_Tree->Draw("Cerenkov.Detector.TransversePolarization:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 8 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c2.SaveAs(Form("images/transverse_polarization%s.png",tag));

  // Transverse polarization vector when projected on Cerenkov detectors (angle spanned by the transverse X and Y components)
  TCanvas c3("c3","Transverse polarization direction at Cerenkov detector plane",1280,1024);
  c3.Divide(3,3);
  c3.cd(4);
  QweakSimG4_Tree->Draw("0.0+Cerenkov.Detector.TransversePolarizationPhiAngle:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 1 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3.cd(1);
  QweakSimG4_Tree->Draw("-45.0+Cerenkov.Detector.TransversePolarizationPhiAngle:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 2 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3.cd(2);
  QweakSimG4_Tree->Draw("-90.0+Cerenkov.Detector.TransversePolarizationPhiAngle:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 3 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3.cd(3);
  QweakSimG4_Tree->Draw("-135.0+Cerenkov.Detector.TransversePolarizationPhiAngle:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 4 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3.cd(6);
  QweakSimG4_Tree->Draw("+180.0+Cerenkov.Detector.TransversePolarizationPhiAngle:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 5 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3.cd(9);
  QweakSimG4_Tree->Draw("+135.0+Cerenkov.Detector.TransversePolarizationPhiAngle:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 6 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3.cd(8);
  QweakSimG4_Tree->Draw("+90.0+Cerenkov.Detector.TransversePolarizationPhiAngle:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 7 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3.cd(7);
  QweakSimG4_Tree->Draw("+45.0+Cerenkov.Detector.TransversePolarizationPhiAngle:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 8 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3.SaveAs(Form("images/transverse_polarization_direction%s.png",tag));

  // Transverse polarization component along the Cerenkov detectors
  TCanvas c3x("c3x","Transverse polarization perpendicular to the bar at Cerenkov detector plane",1280,1024);
  c3x.Divide(3,3);
  c3x.cd(4);
  QweakSimG4_Tree->Draw("cos(0.0)*Cerenkov.Detector.TransversePolarizationX+sin(0.0)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 1 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3x.cd(1);
  QweakSimG4_Tree->Draw("cos(+3.14159/4)*Cerenkov.Detector.TransversePolarizationX+sin(+3.14159/4)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 2 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3x.cd(2);
  QweakSimG4_Tree->Draw("cos(+3.14159/2)*Cerenkov.Detector.TransversePolarizationX+sin(+3.14159/2)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 3 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3x.cd(3);
  QweakSimG4_Tree->Draw("cos(+3.0*3.14159/4)*Cerenkov.Detector.TransversePolarizationX+sin(+3.0*3.14159/4)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 4 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3x.cd(6);
  QweakSimG4_Tree->Draw("cos(+3.14159)*Cerenkov.Detector.TransversePolarizationX+sin(+3.14159)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 5 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3x.cd(9);
  QweakSimG4_Tree->Draw("cos(-3.0*3.14159/4)*Cerenkov.Detector.TransversePolarizationX+sin(-3.0*3.14159/4)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 6 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3x.cd(8);
  QweakSimG4_Tree->Draw("cos(-3.14159/2)*Cerenkov.Detector.TransversePolarizationX+sin(-3.14159/2)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 7 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3x.cd(7);
  QweakSimG4_Tree->Draw("cos(-3.14159/4)*Cerenkov.Detector.TransversePolarizationX+sin(-3.14159/4)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 8 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3x.SaveAs(Form("images/transverse_polarization_perpendicular_to_bar%s.png",tag));

  // Transverse polarization component along the Cerenkov detectors
  TCanvas c3y("c3y","Transverse polarization along the bar at Cerenkov detector plane",1280,1024);
  c3y.Divide(3,3);
  c3y.cd(4);
  QweakSimG4_Tree->Draw("-sin(0.0)*Cerenkov.Detector.TransversePolarizationX+cos(0.0)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 1 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3y.cd(1);
  QweakSimG4_Tree->Draw("-sin(+3.14159/4)*Cerenkov.Detector.TransversePolarizationX+cos(+3.14159/4)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 2 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3y.cd(2);
  QweakSimG4_Tree->Draw("-sin(+3.14159/2)*Cerenkov.Detector.TransversePolarizationX+cos(+3.14159/2)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 3 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3y.cd(3);
  QweakSimG4_Tree->Draw("-sin(+3.0*3.14159/4)*Cerenkov.Detector.TransversePolarizationX+cos(+3.0*3.14159/4)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 4 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3y.cd(6);
  QweakSimG4_Tree->Draw("-sin(+3.14159)*Cerenkov.Detector.TransversePolarizationX+cos(+3.14159)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 5 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3y.cd(9);
  QweakSimG4_Tree->Draw("-sin(-3.0*3.14159/4)*Cerenkov.Detector.TransversePolarizationX+cos(-3.0*3.14159/4)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 6 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3y.cd(8);
  QweakSimG4_Tree->Draw("-sin(-3.14159/2)*Cerenkov.Detector.TransversePolarizationX+cos(-3.14159/2)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 7 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3y.cd(7);
  QweakSimG4_Tree->Draw("-sin(-3.14159/4)*Cerenkov.Detector.TransversePolarizationX+cos(-3.14159/4)*Cerenkov.Detector.TransversePolarizationY:Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 8 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c3y.SaveAs(Form("images/transverse_polarization_along_bar%s.png",tag));

  // Spin precession angle (at least when assuming that events started from longitudinal polarization)
  TCanvas c4("c4","Polarization precession at Cerenkov detector plane",1280,1024);
  // TransversePolarization is always positive as a magnitude, LongitudinalPolarization can be positive or negative.
  // Since the precession angle will be between 0 and 90 degrees, take the absolute value of LongitudinalPolarization.
  // FIXME: This will have to be changed for 3.3 GeV beam since precession may be larger than 90 degrees there!
  c4.Divide(3,3);
  c4.cd(4);
  QweakSimG4_Tree->Draw("180.0/3.14159265*atan2(Cerenkov.Detector.TransversePolarization,abs(Cerenkov.Detector.LongitudinalPolarization)):Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 1 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c4.cd(1);
  QweakSimG4_Tree->Draw("180.0/3.14159265*atan2(Cerenkov.Detector.TransversePolarization,abs(Cerenkov.Detector.LongitudinalPolarization)):Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 2 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c4.cd(2);
  QweakSimG4_Tree->Draw("180.0/3.14159265*atan2(Cerenkov.Detector.TransversePolarization,abs(Cerenkov.Detector.LongitudinalPolarization)):Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 3 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c4.cd(3);
  QweakSimG4_Tree->Draw("180.0/3.14159265*atan2(Cerenkov.Detector.TransversePolarization,abs(Cerenkov.Detector.LongitudinalPolarization)):Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 4 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c4.cd(6);
  QweakSimG4_Tree->Draw("180.0/3.14159265*atan2(Cerenkov.Detector.TransversePolarization,abs(Cerenkov.Detector.LongitudinalPolarization)):Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 5 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c4.cd(9);
  QweakSimG4_Tree->Draw("180.0/3.14159265*atan2(Cerenkov.Detector.TransversePolarization,abs(Cerenkov.Detector.LongitudinalPolarization)):Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 6 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c4.cd(8);
  QweakSimG4_Tree->Draw("180.0/3.14159265*atan2(Cerenkov.Detector.TransversePolarization,abs(Cerenkov.Detector.LongitudinalPolarization)):Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 7 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c4.cd(7);
  QweakSimG4_Tree->Draw("180.0/3.14159265*atan2(Cerenkov.Detector.TransversePolarization,abs(Cerenkov.Detector.LongitudinalPolarization)):Cerenkov.Detector.HitLocalPositionX","Cerenkov.Detector.ParticleType==11 && Cerenkov.Detector.HitLocalPositionZ>0 && Cerenkov.Detector.DetectorID == 8 && sqrt(Cerenkov.Detector.PolarizationX**2+Cerenkov.Detector.PolarizationY**2+Cerenkov.Detector.PolarizationZ**2)>0.01","prof");
  c4.SaveAs(Form("images/polarization_precession%s.png",tag));
}
