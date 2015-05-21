string onm;
void nXcheckTupleTree(){
  onm="y_XcheckTupleTree_Primary.pdf";
  nXcheckTupleTreeOne(11);
  // onm="y_XcheckTupleTree_emNotPrimary.pdf";
  // nXcheckTupleTreeOne(11);
  // onm="y_XcheckTupleTree_epNotPrimary.pdf";
  // nXcheckTupleTreeOne(-11);
  // onm="y_XcheckTupleTree_gamma.pdf";
  // nXcheckTupleTreeOne(22);

}


void nXcheckTupleTreeOne(int partType){
  TFile *ft=TFile::Open("../output/o_anaTree_10k_V_allPb.root","READ");
  TTree *th=(TTree*)ft->Get("th");

  int evN,pType,nInt,tID,parID;
  float x,y,z;
  float Gth,Gph,aX,aY;
  float momx,momy,momz,E;
  float poly;
  th->SetBranchAddress("x",&x);
  th->SetBranchAddress("y",&y);
  th->SetBranchAddress("z",&z);
  th->SetBranchAddress("angX",&aX);
  th->SetBranchAddress("angY",&aY);
  th->SetBranchAddress("nInt",&nInt);
  th->SetBranchAddress("tID",&tID);
  th->SetBranchAddress("pType",&pType);
  th->SetBranchAddress("evNr",&evN);
  th->SetBranchAddress("Gth",&Gth);
  th->SetBranchAddress("Gph",&Gph);
  th->SetBranchAddress("poly",&poly);
  th->SetBranchAddress("px",&momx);
  th->SetBranchAddress("py",&momy);
  th->SetBranchAddress("pz",&momz);
  th->SetBranchAddress("E",&E);
  th->SetBranchAddress("parentID",&parID);

  double ux,uy,uth,uph,uax,uay;
  float umom,ue;

  TH1F *hmom=new TH1F("hmom","log10(momentum) MD"   ,100,-3,3.5);
  TH1F *pmom=new TH1F("pmom","log10(momentum) Pb"   ,100,-3,3.5);
  TH1F *dmom=new TH1F("dmom","log10(momentum Pb-MD)",100,-3,3.5);

  TH1F *hE=new TH1F("hE","log10(E) MD"   ,100,-3,3.5);
  TH1F *pE=new TH1F("pE","log10(E) Pb"   ,100,-3,3.5);
  TH1F *dE=new TH1F("dE","log10(E) Pb-MD",100,-3,3.5);
  
  TH1F *hx=new TH1F("hx","x distribution MD",201,-40,40);
  TH1F *px=new TH1F("px","x MD projection",201,-40,40);
  TH1F *dx=new TH1F("dx","x MD - proj",201,-40,40);

  TH1F *hy=new TH1F("hy","y distribution MD",100,315,355);
  TH1F *py=new TH1F("py","y MD projection",100,315,355);
  TH1F *dy=new TH1F("dy","y MD-proj",201,-40,40);
  
  TH1F *rth=new TH1F("rth","theta MD distribution",360,0,180);
  TH1F *lth=new TH1F("lth","theta Pb distribution",721,-180,180);
  TH1F *dth=new TH1F("dth","theta MD-Pb"          ,721,-180,180);

  TH1F *rph=new TH1F("rph","phi   MD distribution",721,-200,200);
  TH1F *lph=new TH1F("lph","phi   Pb distribution",721,-200,200);
  TH1F *dph=new TH1F("dph","phi   MD-Pb"          ,721,-180,180);

  TH1F *rax=new TH1F("rax","MD angX",361,-180,180);
  TH1F *lax=new TH1F("lax","MD angX",361,-180,180);
  TH1F *dax=new TH1F("dax","MD-Pb angX",361,-180,180);

  TH1F *ray=new TH1F("ray","MD angY",361,-180,180);
  TH1F *lay=new TH1F("lay","MD angY",361,-180,180);
  TH1F *day=new TH1F("day","MD-Pb angY",361,-180,180);

  int start=0;
  int nev=th->GetEntries();
  for(int i=0;i<nev;i++){
    th->GetEntry(i);
    //if(evN>100) break;
    if(nInt!=1) continue;
    if(pType!=partType) continue;//11 here is -11 in the nTuple
    if(poly<0.1) continue;//primary
    //if(poly>0.1) continue;//non primary

    if(partType==22)
      start=doTuple(start,evN,tID,22,z,patID,ux,uy,uph,uth,uax,uay,umom,ue);
    else
      start=doTuple(start,evN,tID,-partType,z,parID,ux,uy,uph,uth,uax,uay,umom,ue);
    if(start<0){
      start=-1*start-1;
      //cout<<tID<<" "<<partType<<" "<<nInt<<" not found at Pb "<<start<<endl;
      continue;
    }
    //cout<<" found one "<<tID<<" "<<start<<endl;
    start--;

    double _mom=sqrt(pow(momx,2)+pow(momy,2)+pow(momz,2));
    cout<<momx<<" "<<momy<<" "<<momz<<endl;
    hmom->Fill(log10(_mom));
    pmom->Fill(log10(umom));
    cout<<umom<<" "<<_mom<<" ! "<<ue<<" "<<E<<endl;
    dmom->Fill(log10(umom-_mom));

    hE->Fill(log10(E));
    pE->Fill(log10(ue));
    dE->Fill(log10(ue-E));

    hx->Fill(x);
    hy->Fill(y);
    px->Fill(ux);
    py->Fill(uy);
    dx->Fill(x-ux);
    dy->Fill(y-uy);
    
    rth->Fill(Gth);
    rph->Fill(Gph+90);
    lth->Fill(uth);
    lph->Fill(uph);
    dth->Fill(Gth-uth);
    dph->Fill(Gph-uph+90);

    rax->Fill(aX);
    ray->Fill(aY);    
    lax->Fill(uax);
    lay->Fill(uay);
    dax->Fill(aX-uax);
    day->Fill(aY-uay);
  }

  TCanvas *c1=new TCanvas("c1","c1",1200,800);
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  c1->Divide(2);

  c1->cd(1);
  hx->DrawCopy();
  px->SetLineColor(2);
  px->DrawCopy("same");
  gPad->SetLogy(1);
  c1->cd(2);
  dx->DrawCopy();
  gPad->SetLogy(1);
  c1->Print(onm.c_str(),"pdf");

  c1->cd(1);
  hy->DrawCopy();
  py->SetLineColor(2);
  py->DrawCopy("same");
  gPad->SetLogy(1);
  c1->cd(2);
  dy->DrawCopy();
  gPad->SetLogy(1);
  c1->Print(onm.c_str(),"pdf");

  c1->cd(1);
  rth->DrawCopy();
  lth->SetLineColor(2);
  lth->DrawCopy("same");
  gPad->SetLogy(1);
  c1->cd(2);
  dth->DrawCopy();
  gPad->SetLogy(1);
  c1->Print(onm.c_str(),"pdf");

  c1->cd(1);
  rph->DrawCopy();
  lph->SetLineColor(2);
  lph->DrawCopy("same");
  gPad->SetLogy(1);
  c1->cd(2);
  dph->DrawCopy();
  gPad->SetLogy(1);
  c1->Print(onm.c_str(),"pdf");

  c1->cd(1);
  rax->DrawCopy();
  lax->SetLineColor(2);
  lax->DrawCopy("same");
  gPad->SetLogy(1);
  c1->cd(2);
  dax->DrawCopy();
  gPad->SetLogy(1);
  c1->Print(onm.c_str(),"pdf");

  c1->cd(1);
  ray->DrawCopy();
  lay->SetLineColor(2);
  lay->DrawCopy("same");
  gPad->SetLogy(1);
  c1->cd(2);
  day->DrawCopy();
  gPad->SetLogy(1);
  c1->Print(onm.c_str(),"pdf");

  c1->cd(1);
  hmom->DrawCopy();
  pmom->SetLineColor(2);
  pmom->DrawCopy("same");
  gPad->SetLogy(1);
  c1->cd(2);
  dmom->DrawCopy();
  gPad->SetLogy(1);
  c1->Print(onm.c_str(),"pdf");

  c1->cd(1);
  hE->DrawCopy();
  pE->SetLineColor(2);
  pE->DrawCopy("same");
  gPad->SetLogy(1);
  c1->cd(2);
  dE->DrawCopy();
  gPad->SetLogy(1);
  c1->Print(onm.c_str(),"pdf");

  c1->Print(Form("%s]",onm.c_str()),"pdf");

  ft->Close();
}

int doTuple(int st,float _evN,float _tID, float _pType,float z,int parID,
	    double &x,double &y,double &ph,double &th,double &aX,double &aY, float &mom,float &E)
{
  double pi=3.14159265;
  TFile *fin=TFile::Open("../output/o_tuple_10k_V_allPb.root","READ");
  TNtuple *t=(TNtuple*)fin->Get("t");
  float be,bdpx,bdpy,bdpz;
  float ae,adpx,adpy,adpz;
  float apx,apy,apz;
  float bpx,bpy,bpz;
  float ax,ay,az;
  float bx,by,bz;
  float proc,evN;
  float pType,tID,parentID;
  
  t->SetBranchAddress("be",  &be);
  t->SetBranchAddress("bx",&bx);
  t->SetBranchAddress("by",&by);
  t->SetBranchAddress("bz",&bz);
  t->SetBranchAddress("ae",  &ae);
  t->SetBranchAddress("apx",&apx);
  t->SetBranchAddress("apy",&apy);
  t->SetBranchAddress("apz",&apz);
  t->SetBranchAddress("bpx",&bpx);
  t->SetBranchAddress("bpy",&bpy);
  t->SetBranchAddress("bpz",&bpz);
  t->SetBranchAddress("bdpx",&bdpx);
  t->SetBranchAddress("bdpy",&bdpy);
  t->SetBranchAddress("bdpz",&bdpz);
  t->SetBranchAddress("adpx",&adpx);
  t->SetBranchAddress("adpy",&adpy);
  t->SetBranchAddress("adpz",&adpz);
  t->SetBranchAddress("ax",&ax);
  t->SetBranchAddress("ay",&ay);
  t->SetBranchAddress("az",&az);
  if(!t->GetBranch("evN")){
    cout<<fnm.c_str()<<" does not have evN branch .. quitting!"<<endl;
    return;
  }
  t->SetBranchAddress("evN",&evN);
  t->SetBranchAddress("trackID",&tID);
  t->SetBranchAddress("pType",&pType);
  t->SetBranchAddress("parentID",&parentID);

  double angY,angX;
  float _bphi,_aphi;
  float _bth,_ath;
  int end;
  double _ax,_ay,_az,aph,ath=-999;
  double _apx,_apy,_apz;
  int nentries=t->GetEntries();
  if((int)_evN%100==1)
    cout<<"Event "<<_evN<<endl;
  for(int i=st;i<nentries;i++){
    t->GetEntry(i);
    end=i;
    if(i%100000==1)
      cout<<i<<endl;
    if(evN>_evN) break;
    if(evN!=_evN) continue;
    if(pType!=_pType) continue;
    if(tID!=_tID) continue;
    if(parentID!=parID) continue;

    //cout<<" asdfasd"<<endl;
    TVector3 bdp(bdpx,bdpy,bdpz);
    TVector3 adp(adpx,adpy,adpz);
    _bphi=bdp.Phi();
    _aphi=adp.Phi();
    _bth=bdp.Theta();
    _ath=adp.Theta();

    angY=atan2(sin(_ath)*sin(_aphi),cos(_ath))*180./pi;
    angX=atan2(sin(_ath)*cos(_aphi),cos(_ath))*180./pi;
    _ax=ax;
    _ay=ay;
    _az=az;
    _apx=apx;
    _apy=apy;
    _apz=apz;
    aph=_aphi;
    ath=_ath;
    aX=angX;
    aY=angY;
    E=ae;
  }

  if(ath==-999) {
    fin->Close();
    return -1*end;
  }
  mom=sqrt(pow(_apx,2)+pow(_apy,2)+pow(_apz,2));
  cout<<mom<<" "<<_apx<<" "<<_apy<<" "<<_apz<<endl;
  project(z*10,_ax,_ay,_az,ath,aph,x,y);
  ph=aph*180./pi;
  th=ath*180./pi;
  x=x/10;
  y=y/10;
  fin->Close();
  return end;
}

void project(double z,double ax,double ay,double az,double th, double ph,double &x,double &y){
  double r=(z-az)/cos(th);
  x=r*sin(th)*cos(ph)+ax;
  y=r*sin(th)*sin(ph)+ay;
}
