void nTupleAna()
{
  //gStyle->SetOptStat(0);
  double pi=3.14159265;

  TH1F *bphi=new TH1F("bphi","phi pre step" ,200,0,2*pi);
  TH1F *aphi=new TH1F("aphi","phi post step",200,0,2*pi);
  TH1F *dphi=new TH1F("dphi","#Delta #phi" ,200,0,2*pi);
  TH2F *phi=new TH2F("phi","before vs after phi",200,0,2*pi,200,0,2*pi);

  TH2F *thph=new TH2F("thph","All interactions PostStep; #theta ; #phi"      ,100,0,pi/4,200,0,2*pi);
  TH2F *thphmsc=new TH2F("thphmsc","MSc interactions PostStep; #theta ; #phi",100,0,pi/4,200,0,2*pi);
  
  TH1F *inter=new TH1F("inter","number of interactions per event",200,0,200);
  TH1F *interMsc=new TH1F("interMsc","number of MSc interactions per event",150,0,150);

  TH1F *xPosStartAll=new TH1F("xPosStartAll","Position in Prestep for first int"  ,101,-5,5); 
  TH1F *xPosStopAll=new TH1F("xPosStopAll","Position in Poststep for last int"    ,101,-20,20); 
  TH1F *xPosDiffAll=new TH1F("xPosDiffAll","Position diff (last - first) all int ",101,-10,10); 

  TH1F *xPosStart=new TH1F("xPosStart","Position in Prestep for first Msc int"  ,101,-20,20); 
  TH1F *xPosStop=new TH1F("xPosStop","Position in Poststep for last Msc int"    ,101,-20,20); 
  TH1F *xPosDiff=new TH1F("xPosDiff","Position diff (last - first) for Msc int" ,101,-20,20); 

  TH2F *eMscInt  = new TH2F("eMscInt","; MSC interaction [#]; log 10 of Prestep energy [MeV]",150,0,150,200,0,3.5);
  TH2F *deMscInt = new TH2F("deMscInt","; MSC interaction [#];energy diff [MeV]"  ,150,0,150,300,0,4);

  TH2F *eZ     = new TH2F("eZ"    ,"All int; Prestep z coordinate [mm]; log10 of Prestep energy"   ,100,5705,5735,200,0,3.5);
  TH2F *deZ    = new TH2F("deZ"   ,"All int; Prestep z coordinate [mm]; log10 of energy diff [MeV]",100,5705,5735,200,0,3.5);
  TH2F *eZmsc  = new TH2F("eZmsc" ,"MSc int; Prestep z coordinate [mm]; log10 of Prestep energy"   ,100,5705,5735,200,0,3.5);
  TH2F *deZmsc = new TH2F("deZmsc","MSc int; Prestep z coordinate [mm]; log10 of energy diff [MeV]",100,5705,5735,200,0,2);

  TH2F *eAngZmsc  = new TH2F("eAngZmsc" ,"MSc int Z coordinate as color; Scattering angle [rad]; log10 of Prestep energy"   ,400,0,pi,200,0,3.5);

  TH2F *aeZ     = new TH2F("aeZ"    ,"All int; PreStep z coordinate [mm]; log10 of Poststep energy"   ,100,5705,5735,200,0,3.5);
  TH2F *aeZmsc  = new TH2F("aeZmsc" ,"MSc int; PreStep z coordinate [mm]; log10 of Poststep energy"   ,100,5705,5735,200,0,3.5);

  TH2F *eStepL    = new TH2F("eStepL"    ,"All int; Step Length [mm]; log10 of Prestep energy"   ,100,0,1.6,200,0,3.5);
  TH2F *eStepLmsc = new TH2F("eStepLmsc" ,"MSc int; Step Length [mm]; log10 of Prestep energy"   ,100,0,1.6,200,0,3.5);

  TH2F *zStepL    = new TH2F("zStepL"    ,"All int;PreStep z coord [mm]; Step Length [mm]"   ,100,5705,5735,100,0,1.6);
  TH2F *zStepLmsc = new TH2F("zStepLmsc" ,"MSc int;PreStep z coord [mm]; Step Length [mm]"   ,100,5705,5735,100,0,1.6);

  TH1F *scatAng    =new TH1F("scatAng"   ,"Scattering angle All inter [rad]",800,0,pi);
  TH1F *scatAngMsc =new TH1F("scatAngmsc","Scattering angle MSc inter [rad]",800,0,pi);

  //TH2F *anaPow2 = new TH2F("anaPow2","MSc interactions;log preStep energy [MeV]; analyzing power",200,0,3.5,100,0,1);  
  
  TH2F *escatAng    =new TH2F("escatAng"   ,"All int;Scattering angle[rad];log 10 Prestep E [MeV]",400,0,pi,200,0,3.5);
  TH2F *escatAngMsc =new TH2F("escatAngmsc","MSc int;Scattering angle[rad];log 10 Prestep E [MeV]",400,0,pi,200,0,3.5);

  TH2F *eAnMsc = new TH2F("eAnMsc","MSc interactions; log 10 Prestep E [MeV]; analyzing power",200,0,3.5,100,0,1);
  TH2F *eAnMsc2 = new TH2F("eAnMsc2","MSc interactions; log 10 Prestep E [MeV]; log analyzing power",200,0,3.5,100,-7,0);
  
  float startPosx;
  float stopPosx;
  float startPosxA;
  float stopPosxA;
  
  int currentEv=-1;
  int Ninter=0;
  int NmscInter=0;
  
  TFile *fin=TFile::Open("../output/farm/mL_1160_000.00_335.00_560.00_015/o_tuple.root");
  //TFile *fin=TFile::Open("../output/farm/mV_1160_000.00_335.00_560.00_008/o_tuple.root");

  TNtuple *t=(TNtuple*)fin->Get("t");
  float be,bdpx,bdpy,bdpz;
  float ae,adpx,adpy,adpz;
  float ax,ay,az;
  float bx,by,bz;
  float proc;
  float stepL;
  float evN;
  
  t->SetBranchAddress("be",  &be);
  t->SetBranchAddress("bdpx",&bdpx);
  t->SetBranchAddress("bdpy",&bdpy);
  t->SetBranchAddress("bdpz",&bdpz);
  t->SetBranchAddress("bx",&bx);
  t->SetBranchAddress("by",&by);
  t->SetBranchAddress("bz",&bz);
  t->SetBranchAddress("ae",  &ae);
  t->SetBranchAddress("adpx",&adpx);
  t->SetBranchAddress("adpy",&adpy);
  t->SetBranchAddress("adpz",&adpz);
  t->SetBranchAddress("ax",&ax);
  t->SetBranchAddress("ay",&ay);
  t->SetBranchAddress("az",&az);
  t->SetBranchAddress("process",&proc);//1:msc; 2:CoulombSc; 3:eBrem;..
  t->SetBranchAddress("evN",&evN);
  t->SetBranchAddress("stepL",&stepL);
  
  int nentries=t->GetEntries();
  for(int i=0;i<nentries;i++){
    t->GetEntry(i);
    if(i%100000==1)cout<<"event "<<i<<endl;

    eZ->Fill(bz,log10(be));
    deZ->Fill(bz,log10(be-ae));
    aeZ->Fill(bz,log10(ae));
    eStepL->Fill(stepL,log10(be));
    zStepL->Fill(bz,stepL);
    if(proc==1){
      eZmsc->Fill(bz,log10(be));
      aeZmsc->Fill(bz,log10(ae));
      deZmsc->Fill(bz,log10(be-ae));
      eStepLmsc->Fill(stepL,log10(be));
      zStepLmsc->Fill(bz,stepL);
    }
    
    TVector3 bdp(bdpx,bdpy,bdpz);
    TVector3 adp(adpx,adpy,adpz);
    float _bphi,_aphi;
    if(bdp.Phi()<0) _bphi=bdp.Phi()+2*pi;
    else _bphi=bdp.Phi();
    if(adp.Phi()<0) _aphi=adp.Phi()+2*pi;
    else _aphi=adp.Phi();
    float _bth,_ath;
    if(bdp.Theta()<0) _bth=bdp.Theta()+2*pi;
    else _bth=bdp.Theta();
    if(adp.Theta()<0) _ath=adp.Theta()+2*pi;
    else _ath=adp.Theta();

    thph->Fill(_ath,_aphi);
    scatAng->Fill(bdp.Angle(adp));
    escatAng->Fill(bdp.Angle(adp),log10(be));

    if(proc==1) {
      thphmsc->Fill(_ath,_aphi);
      scatAngMsc->Fill(bdp.Angle(adp));
      escatAngMsc->Fill(bdp.Angle(adp),log10(be));
      eAngZmsc->Fill(bdp.Angle(adp),log10(be),bz);
      double an=1./be*sin(bdp.Angle(adp));
      eAnMsc->Fill(log10(be),an);
      if(an>0.0000001)
	eAnMsc2->Fill(log10(be),log10(an));
    }
    
    
    if(currentEv!=(int)evN){      
      if(currentEv!=-1){
	inter->Fill(Ninter);
	interMsc->Fill(NmscInter);
	xPosStop->Fill(stopPosx);
	xPosDiff->Fill(stopPosx-startPosx);
	xPosStopAll->Fill(stopPosxA);
	xPosDiffAll->Fill(stopPosxA-startPosxA);	
      }
      currentEv=(int)evN;
      Ninter=1;
      startPosxA=bx;
      xPosStartAll->Fill(startPosxA);
      if(proc==1) {
	NmscInter=1;
	eMscInt->Fill(NmscInter,log10(be));
	deMscInt->Fill(NmscInter,be-ae);
	startPosx=bx;
	stopPosx=ax;
	xPosStart->Fill(startPosx);
      }
      else NmscInter=0;
    }
    else{
      Ninter++;
      stopPosxA=ax;
      if(proc==1) {
	NmscInter++;
	eMscInt->Fill(NmscInter,log10(be));
	deMscInt->Fill(NmscInter,be-ae);
	stopPosx=ax;
      }
    }

    if(NmscInter==1){
      startPosx=bx;
      xPosStart->Fill(startPosx);	  

      bphi->Fill(_bphi);
      aphi->Fill(_aphi);
      phi->Fill(_bphi,_aphi);
      dphi->Fill(_aphi-_bphi);
    }

  }

  //gStyle->SetOptStat(1);

  c1=new TCanvas();
  bphi->DrawCopy();
  c2=new TCanvas();
  aphi->DrawCopy();
  c3=new TCanvas();
  phi->DrawCopy("colz");
  c4=new TCanvas();
  dphi->DrawCopy();

  c5=new TCanvas();
  inter->DrawCopy();
  c6=new TCanvas();
  interMsc->DrawCopy();

  c7=new TCanvas();
  eMscInt->DrawCopy("colz");
  c8=new TCanvas();
  deMscInt->DrawCopy("colz");
  
  c9=new TCanvas();  
  gPad->SetLogy(1);
  gPad->SetGridx(1);
  xPosStart->DrawCopy();
  c10=new TCanvas();
  gPad->SetLogy(1);
  gPad->SetGridx(1);
  xPosStop->DrawCopy();
  c11=new TCanvas();
  gPad->SetLogy(1);
  gPad->SetGridx(1);
  xPosDiff->DrawCopy();

  c12=new TCanvas();
  gPad->SetLogy(1);
  gPad->SetGridx(1);
  xPosStartAll->DrawCopy();
  c13=new TCanvas();
  gPad->SetLogy(1);
  gPad->SetGridx(1);
  xPosStopAll->DrawCopy();
  c14=new TCanvas();
  gPad->SetLogy(1);
  gPad->SetGridx(1);
  xPosDiffAll->DrawCopy();

  c15=new TCanvas();
  thph->DrawCopy("colz");
  c16=new TCanvas();
  thphmsc->DrawCopy("colz");

  c17=new TCanvas();
  eZ->DrawCopy("colz");
  c18=new TCanvas();
  deZ->DrawCopy("colz");

  c19=new TCanvas();
  eZmsc->DrawCopy("colz");
  c20=new TCanvas();
  deZmsc->DrawCopy("colz");

  c21=new TCanvas();
  aeZmsc->DrawCopy("colz");
  c22=new TCanvas();
  aeZ->DrawCopy("colz");

  c23=new TCanvas();
  eStepLmsc->DrawCopy("colz");
  c24=new TCanvas();
  eStepL->DrawCopy("colz");

  c25=new TCanvas();
  zStepLmsc->DrawCopy("colz");
  c26=new TCanvas();
  zStepL->DrawCopy("colz");

  c27=new TCanvas();
  scatAng->DrawCopy("");
  c28=new TCanvas();
  scatAngMsc->DrawCopy("");

  c29=new TCanvas();
  escatAng->DrawCopy("colz");
  c30=new TCanvas();
  escatAngMsc->DrawCopy("colz");

  c31=new TCanvas();
  eAngZmsc->DrawCopy("colz");
  
  c32=new TCanvas();
  eAnMsc->DrawCopy("colz");
  c33=new TCanvas();
  eAnMsc2->DrawCopy("colz");
  TProfile *eAnMsc2prof=eAnMsc2->ProfileX();
  eAnMsc2prof->SetMarkerStyle(20);
  eAnMsc2prof->SetMarkerColor(4);  
  eAnMsc2prof->SetLineColor(4);  
  //eAnMsc2prof->DrawCopy("same");
  c44=new TCanvas();
  eAnMsc2prof->DrawCopy();
  
  fin->Close();
}
