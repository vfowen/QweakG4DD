void getPEdata(){

  int beamE[2]={10,50};
  double xP[2]={0,60};
  double xA[5]={-40,-20,-10,-5,0};
  double yP[5]={326,332,335,338,344};
  double yA[9]={-80,-40,-20,-10,0,5,15,30,60};

  TFile *fout=new TFile("o_scanData.root","RECREATE");
  double bE,xp,xa,yp,ya,lpe,dlpe,rpe,drpe;
  TTree *t=new TTree("t","pe values for different scans");
  t->Branch("beamE",&bE,"beamE/F");
  t->Branch("xP",&xp,"xP/F");
  t->Branch("xA",&xa,"xA/F");
  t->Branch("yP",&yp,"yP/F");
  t->Branch("yA",&ya,"yA/F");
  t->Branch("lpe",&lpe,"lpe/F");
  t->Branch("dlpe",&dlpe,"dlpe/F");
  t->Branch("rpe",&rpe,"rpe/F");
  t->Branch("drpe",&drpe,"drpe/F");

  for(int ie=0;ie<2;ie++)
    for(int ixp=0;ixp<2;ixp++)
      for(int ixa=0;ixa<5;ixa++)
	for(int iyp=0;iyp<5;iyp++)
	  for(int iya=0;iya<9;iya++){
	    bE=beamE[ie];
	    xp=xP[ixp];
	    yp=yP[iyp];
	    xa=xA[ixa];
	    ya=yA[iya];
	    string fnm=Form("L_%04d_%06.2f_%06.2f_575.00_%06.2f_%06.2f_000",bE,xp,yp,xa,ya);
	    lpe=-999;
	    dlep=-999;
	    rpe=-999;
	    drpe=-999;
	    doOneFile(fnm,lpe,rpe,dlpe,drpe);
	    t->Fill();
	  }

  fout->cd();
  t->Write();
  fout->Close();
}

void doOneFile(string fname,double &lpe,double &rpe,
	       double &dlpe,double &drpe){
  //TFile *fin=TFile::Open(fname.c_str(),"READ");
  fname="/lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput/acrossYposCheck/"
    +fname+"/o_QweakSimTree_PEs.root";
  TFile *fin=new TFile(fname.c_str(),"READ");
  if(!fin->IsOpen()){
    cout<<" no file "<<fname<<endl;
    delete fin;
    return;
  }
  
  if(!fin->GetListOfKeys()->Contains("lpe") || !fin->GetListOfKeys()->Contains("rpe")){
    cout<<" can't find histos in "<<fname<<endl;
    delete fin;
    return;
  }
  TH1D *hl=(TH1D*)fin->Get("lpe");
  TH1D *hr=(TH1D*)fin->Get("rpe");
  lpe=hl->GetMean();
  dlpe=hl->GetMeanError();
  rpe=hr->GetMean();
  drpe=hr->GetMeanError();
  
  fin->Close();
  delete fin;
}
