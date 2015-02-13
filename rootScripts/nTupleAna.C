void nTupleAna()
{
  gStyle->SetOptStat(0);
  double pi=3.14159265;
  TFile *fin=TFile::Open("../o_tuple_AroundPolNoOldDir_V.root");
  //TFile *fin=TFile::Open("../o_tuple_10k_L.root");
  TNtuple *t=(TNtuple*)fin->Get("t");
  float be,bdpx,bdpy,bdpz;
  float ae,adpx,adpy,adpz;
  float proc;
  t->SetBranchAddress("be",  &be);
  t->SetBranchAddress("bdpx",&bdpx);
  t->SetBranchAddress("bdpy",&bdpy);
  t->SetBranchAddress("bdpz",&bdpz);
  t->SetBranchAddress("ae",  &ae);
  t->SetBranchAddress("adpx",&adpx);
  t->SetBranchAddress("adpy",&adpy);
  t->SetBranchAddress("adpz",&adpz);
  t->SetBranchAddress("process",&proc);//1:msc; 2:CoulombSc; 3:eBrem;..
  
  TH1F *bphi=new TH1F("bphi","phi pre step" ,200,0,2*pi);
  TH1F *aphi=new TH1F("aphi","phi post step",200,0,2*pi);
  TH1F *dphi=new TH1F("dphi","#Delta #phi" ,200,0,2*pi);
  TH2F *phi=new TH2F("phi","before vs after phi",200,0,2*pi,200,0,2*pi);
  
  int nentries=t->GetEntries();
  for(int i=0;i<nentries;i++){
    t->GetEntry(i);
    TVector3 bdp(bdpx,bdpy,bdpz);
    TVector3 adp(adpx,adpy,adpz);
    float _bphi,_aphi;
    if(bdp.Phi()<0) _bphi=bdp.Phi()+2*pi;
    else _bphi=bdp.Phi();
    if(adp.Phi()<0) _aphi=adp.Phi()+2*pi;
    else _aphi=adp.Phi();

    if(proc==1 && fabs(be-ae)>0.1){
      bphi->Fill(_bphi);
      aphi->Fill(_aphi);
      phi->Fill(_bphi,_aphi);
      dphi->Fill(_aphi-_bphi);
    }
  }

  c1=new TCanvas();
  bphi->DrawCopy();
  c2=new TCanvas();
  aphi->DrawCopy();
  c3=new TCanvas();
  phi->DrawCopy("colz");
  c4=new TCanvas();
  dphi->DrawCopy();
  
  fin->Close();
}
