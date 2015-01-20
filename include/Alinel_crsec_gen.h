#ifndef __ALINEL_CRSEC_GEN_HH
#define __ALINEL_CRSEC_GEN_HH



// data gives: FF^2 vs q
// need to write a generator that returns crsec
// 
// input: E_in, theta
//  -- evaluate q for these input parameters
//  -- evaluate FF^2 for this particular q
//  -- get the crsec & rate using this FF^2
//
// -- start with longitudinal FFs -- 10^2 greater than transverse FFs

G4double getAlinel_FF2(G4double q);

G4double Alinel_crsec_gen(G4double E_in=1160, G4double th=8.0){

  ///
  G4double M_p = 938.2796;  // proton mass in MeV
  G4double Z_Al = 13.0;
  G4double A_Al = 27.0;
  G4double M_Al = M_p*A_Al;

  th = th*3.14159/180.;  // convert to radians
  G4double CTH = cos(th/2.0);
  G4double STH = sin(th/2.0);

  // now get qsq
  G4double ETA = 1.0+2.0*E_in*STH*STH/M_Al;
  G4double E_out = E_in/ETA;
  
  G4double Q2 = 4*E_in*E_out*STH*STH;     //unit: MeV^2
  G4double hbarc = 197.3269631; // MeV fm
  G4double q2 = Q2/(hbarc*hbarc);  //convert MeV^2 into fm^(-2)
  G4double qq = sqrt(q2);

  G4double FF2 = getAlinel_FF2(qq);
  
  // get crsec mott, ub/sr
  G4double sigma_mott = pow(Z_Al*0.719982/E_in*CTH/(STH*STH),2)/(1+2*E_in/M_Al*STH*STH)*10000;

  G4double sigma = sigma_mott * FF2;

  // G4cout <<"Q2(GeV^2):: "<< Q2*1e-6 << G4endl;
  /* G4cout <<"q(1/fm):: " << qq << G4endl; */
  /* G4cout <<"FF2_tot:: " << FF2 << G4endl; */
  /* G4cout <<"crsec(ub/sr):: " << sigma << G4endl; */

  return sigma;
}

G4double getAlinel_FF2(G4double q){
  
  TF1 *ff2[8];
  ff2[0] = new TF1("844","0.000427*exp(-0.5*((x-0.958792)/0.341168)**2)",0.5,1.8);
  ff2[1] = new TF1("1016","0.000706*exp(-0.5*((x-0.868077)/0.350506)**2)",0.5,1.8);
  ff2[2] = new TF1("2211","0.002337*exp(-0.5*((x-0.857955)/0.290595)**2)",0.5,1.8);
  ff2[3] = new TF1("2735","0.000306*exp(-0.5*((x-0.955732)/0.379688)**2)",0.5,1.8);
  ff2[4] = new TF1("2735","0.001598*exp(-0.5*((x-0.948107)/0.330035)**2)",0.5,1.8);
  ff2[5] = new TF1("3680","0.000042*exp(-0.5*((x-0.992771)/0.395955)**2)",0.5,1.8);
  ff2[6] = new TF1("4510","0.000135*exp(-0.5*((x-1.340052)/0.302506)**2)",0.5,1.8);
  ff2[7] = new TF1("4580","0.000162*exp(-0.5*((x-1.297271)/0.352787)**2)",0.5,1.8);

  G4double ffT=0;
  for(G4int i=0;i<8;i++){
    if((q>=0.5) && (q<=1.8))
      ffT += ff2[i]->Eval(q);
    else 
      ffT += 0;
    delete ff2[i];
  }

  //  G4String printff2[] = {"844","1016","2211","2735"};
  //  for(G4int i=0;i<4;i++) G4cout << printff2[i] << ":: " << ff2[i]->Eval(q) << G4endl;

  return(ffT);
}

#endif
