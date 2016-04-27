void drawLRhistAsym(){
  TFile *fin=TFile::Open("../output/mottUpdateCH/o_dist_Center_V_1e2xMott_001Step_34635000.root","READ");
  string hnm[2]={"distPe","distAe"};
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(2210);
  for(int i=0;i<2;i++){
    TH3 *h=(TH3*)fin->Get(hnm[i].c_str());

    TH1 *h1=h->Project3D("x");
    doOne(h1,Form("%s position",hnm[i].c_str()));

    TH1 *h2=h->Project3D("y");
    doOne(h2,Form("%s angle",hnm[i].c_str()));

    //TH1 *h3=h1->Clone(Form();
  }
  fin->Close();
}

void doOne(TH1 *h,string gnm){
  TCanvas *c1=new TCanvas(gnm.c_str(),gnm.c_str(),1200,600);
  c1->Divide(2);
  c1->cd(1);
  h->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  
  int nb=h->GetNbinsX();
  int mid;
  int extra=0;
  if(nb%2==0){
    mid=nb/2;
    extra=1;
  } else mid=(nb+1)/2;

  TGraphErrors *g=new TGraphErrors();
  int ng=0;
  for(int i=1;i<mid;i++){
    double x=h->GetBinCenter(mid+i);
    //cout<<h->GetBinCenter(mid-i+extra)<<" "<<h->GetBinCenter(mid+i)<<endl;
    double lbin=h->GetBinContent(mid-i+extra);
    double rbin=h->GetBinContent(mid+i);
    double y=(lbin-rbin)/(lbin+rbin);
    double dy=2./pow(lbin+rbin,2)*sqrt(lbin*lbin*rbin+rbin*rbin*lbin);
    g->SetPoint(ng,x,y);
    g->SetPointError(ng,0,dy);
    if(lbin>0 && rbin>0)    
      {
	//cout<<ng<<" "<<x<<" "<<y<<" "<<dy<<" "<<lbin<<" "<<rbin<<endl;
	ng++;
      }
    
  }
  g->SetTitle(gnm.c_str());
  g->SetMarkerStyle(20);
  c1->cd(2);
  g->Draw("AP");
  g->Fit("pol0");
  gPad->SetGridx(1);
  gPad->SetGridy(1);

}
