TCanvas *c1=new TCanvas("c1","c1",1200,600);
string onm,fnm;

void calcPEasymFromDistr(){
  onm="y_posPEasym_LV_1Ecut_TreeTst.pdf";
  fnm="o_distributions_1Ecut_treeTst.root";
  c1->Print(Form("%s[",onm.c_str()),"pdf");

  TFile *fd=TFile::Open(fnm.c_str(),"READ");
  TFile *fas=TFile::Open("o_PEasyms.root","READ");
  TGraphErrors *hasPos=(TGraphErrors*)fas->Get("asym_9");
  TGraph *hasAng=(TGraph*)fas->Get("angle");

  TGraphErrors *gr[15];
  double mn[15],dmn[15];
  
  TH1F *hL1=(TH1F*)fd->Get("hX_L_0");
  TH1F *mL1=(TH1F*)fd->Get("mX_L_10");
  gr[0]=calcAsym(hL1,mL1,hasPos,0);
  TH1F *hV1=(TH1F*)fd->Get("hX_V_0");
  TH1F *mV1=(TH1F*)fd->Get("mX_V_10");
  gr[1]=calcAsym(hV1,mV1,hasPos,0);
  gr[10]=getDiff(gr[1],gr[0],"gXprim","A_{V} - A_{L} primary e-;x pos");  
  calcMean(gr[1],hV1,mn[1],dmn[1]);
  calcMean(gr[0],hL1,mn[0],dmn[0]);
  calcMean(gr[10],hV1,mn[10],dmn[10]);

  
  TH1F *hL2=(TH1F*)fd->Get("hX_L_3");
  TH1F *mL2=(TH1F*)fd->Get("mX_L_13");
  gr[2]=calcAsym(hL2,mL2,hasPos,0);
  TH1F *hV2=(TH1F*)fd->Get("hX_V_3");
  TH1F *mV2=(TH1F*)fd->Get("mX_V_13");
  gr[3]=calcAsym(hV2,mV2,hasPos,0);
  gr[11]=getDiff(gr[3],gr[2],"gXall","A_{V} - A_{L} all e#pm;x pos");
  calcMean(gr[3],hV2,mn[3],dmn[3]);
  calcMean(gr[2],hL2,mn[2],dmn[2]);
  calcMean(gr[11],hV2,mn[11],dmn[11]);

  TH1F *hL3=(TH1F*)fd->Get("hangX_L_0");
  TH1F *mL3=(TH1F*)fd->Get("mangX_L_10");
  hL3->Rebin();
  gr[4]=calcAsym(hL3,mL3,hasAng,1);
  TH1F *hV3=(TH1F*)fd->Get("hangX_V_0");
  TH1F *mV3=(TH1F*)fd->Get("mangX_V_10");
  hV3->Rebin();
  gr[5]=calcAsym(hV3,mV3,hasAng,1);
  gr[12]=getDiff(gr[5],gr[4],"gAXprim","A_{V} - A_{L} primary e-;angle along bar");
  calcMean(gr[5],hV3,mn[5],dmn[5]);
  calcMean(gr[4],hL3,mn[4],dmn[4]);
  calcMean(gr[12],hV3,mn[12],dmn[12]);

  TH1F *hL4=(TH1F*)fd->Get("hangX_L_3");
  TH1F *mL4=(TH1F*)fd->Get("mangX_L_13");
  hL4->Rebin();
  gr[6]=calcAsym(hL4,mL4,hasAng,1);
  TH1F *hV4=(TH1F*)fd->Get("hangX_V_3");
  TH1F *mV4=(TH1F*)fd->Get("mangX_V_13");
  hV4->Rebin();
  gr[7]=calcAsym(hV4,mV4,hasAng,1);
  gr[13]=getDiff(gr[7],gr[6],"gAXall","A_{V} - A_{L} all e#pm;angle along bar");
  calcMean(gr[7],hV4,mn[7],dmn[7]);
  calcMean(gr[6],hL4,mn[6],dmn[6]);
  calcMean(gr[13],hV4,mn[13],dmn[13]);

  c1->Clear();
  c1->Divide(3);
  TLegend *legv=new TLegend(0.15,0.8,0.75,0.95);
  legv->SetFillStyle(0);
  legv->SetTextSize(0.045);
  TLegend *legl=new TLegend(0.15,0.8,0.75,0.95);
  legl->SetFillStyle(0);      
  legl->SetTextSize(0.045);
  TLegend *legb=new TLegend(0.15,0.8,0.75,0.95);
  legb->SetFillStyle(0);
  legb->SetTextSize(0.045);

  double yL[4]={0.005,0.0005,0.05,0.01};
  double yV[4]={0.02,0.002,0.1,0.02};
  double al[4]={0.04,0.01,0.1,0.02};
  for(int i=0;i<4;i++){
    c1->cd(1);
    gr[2*i+1]->SetTitle("A_{V}");
    gr[2*i+1]->GetYaxis()->SetRangeUser(-yV[i],yV[i]);
    gr[2*i+1]->Draw("AP");
    legv->Clear();
    cout<<i<<" "<<mn[2*i+1]<<" "<<mn[2*i+1]*1000000<<endl;
    legv->AddEntry(gr[2*i+1],Form("mean: %4.0f #pm %4.0f ppm",mn[2*i+1]*1000000,dmn[2*i+1]*1000000),"lep");
    legv->Draw();
    gPad->SetGridy(1);

    c1->cd(2);
    gr[2*i]->SetTitle("A_{L}");
    gr[2*i]->GetYaxis()->SetRangeUser(-yL[i],yL[i]);
    gr[2*i]->Draw("AP");
    legl->Clear();
    legl->AddEntry(gr[2*i],Form("mean: %4.0f #pm %4.0f ppm",mn[2*i]*1000000,dmn[2*i]*1000000),"lep");
    legl->Draw();
    gPad->SetGridy(1);

    c1->cd(3);
    gr[10+i]->GetYaxis()->SetRangeUser(-al[i],al[i]);
    gr[10+i]->Draw("AP");
    legb->Clear();
    legb->AddEntry(gr[10+i],Form("mean: %4.0f #pm %4.0f ppm",mn[i+10]*1000000,dmn[i+10]*1000000),"lep");
    legb->Draw();
    gPad->SetGridy(1);

    c1->Print(onm.c_str(),"pdf");
  }
  
  c1->Print(Form("%s]",onm.c_str()),"pdf");
  fd->Close();
  fas->Close();
}

TGraphErrors *getDiff(TGraphErrors *g1, TGraphErrors *g2,string nm,string title){
  TGraphErrors *gd=new TGraphErrors();
  gd->SetName(nm.c_str());
  gd->SetTitle(title.c_str());
  for(int i=0;i<g1->GetN();i++){
    double x1,x2,as1,as2;
    double das1,das2;
    g1->GetPoint(i,x1,as1);
    g2->GetPoint(i,x2,as2);
    if(fabs(x1-x2)>0.01) cout<<" ~~~~~!!!!!!~~~~~~"<<x1<<" "<<x2<<endl;
    das1=g1->GetErrorY(i);
    das2=g2->GetErrorY(i);
    double val=as1-as2;
    double dval=sqrt(pow(das1,2)+pow(das2,2));
    gd->SetPoint(i,x1,val);
    gd->SetPointError(i,0,dval);
  }
  gd->SetMarkerStyle(24);
  return gd;
}

TGraphErrors *calcAsym(TH1F *a, TH1F *mean, TGraph *b, int n){
 
  int nb=a->GetXaxis()->GetNbins()/2;
  float b2=a->GetBinCenter(nb*2)+a->GetBinWidth(nb*2)/2;    
  int mb=mean->GetXaxis()->GetNbins()/2;
  int nav=mb/nb;
  
  TGraphErrors *asym=new TGraphErrors();
  asym->SetName(Form("gPEasym_%d",n));
  double tot=0;
  double dtot=0;
  for(int i=1;i<=nb;i++){
    if(a->GetBinCenter(nb+i)<20 || n==1){ 
      float n1=a->GetBinContent(nb+i);
      float n2=a->GetBinContent(nb-i+1);
      tot+=n1+n2;
      float a1,a2;
      if(a->GetBinCenter(nb+i)>45){
	a1=0.90;
	a2=-0.90;
      }else{
	double m1=mean->GetBinContent(1+(i-1)*nav+mb);
	double m2=mean->GetBinContent(mb-(i-1)*nav);
	for(int j=1;j<nav;j++){
	  m1=(m1+j*mean->GetBinContent(1+(i-1)*nav+mb+j))/(j+1);
	  m2=(m2+j*mean->GetBinContent(1+(i-1)*nav+mb-j))/(j+1);
	}
	a1=b->Eval(m1,0,"S");
	a2=b->Eval(m2,0,"S");
	double am=(a1-a2)/2;
	a1=am;
	a2=-am;
      }
      float val=(n1*a1+n2*a2)/(n1+n2);
      //float dval=2*sqrt(pow(n2,2)*n1+pow(n1,2)*n2)/pow(n1+n2,2);//this is so ducking fumb
      float dval=sqrt(pow(n2*(a1-a2),2)*n1+pow(n1*(a2-a1),2)*n2)/pow(n1+n2,2);
      dtot+=dval;
      asym->SetPoint(i-1,a->GetBinCenter(nb+i),val);
      asym->SetPointError(i-1,0,dval);
     }
  }
  
  asym->SetMarkerStyle(20);
  asym->SetMarkerColor(4);

  c1->cd(0);
  c1->Clear();
  c1->Divide(3);

  c1->cd(1);
  a->DrawCopy();
  if(n==0)
    gPad->SetLogy(1);

  c1->cd(2);
  b->Draw("APL");

  c1->cd(3);
  gStyle->SetOptFit(1);
  asym->Draw("AP");
  
  c1->Print(onm.c_str(),"pdf");

  return asym;
}

void calcMean(TGraphErrors *a, TH1F *dist, double &m,double &dm){

  int n=a->GetN();
  double x[500],y[500];
  double sumV=0;
  double sumW=0;
  double sumD=0;
  double sumN=0;
  
  a->GetPoint(n-1,x[n-1],y[n-1]);
  int b1=dist->GetXaxis()->FindBin(-x[n-1]);
  int b2=dist->GetXaxis()->FindBin(x[n-1]);
  double ntot=dist->Integral(b1,b2);
  
  for(int i=0;i<n;i++){
    a->GetPoint(i,x[i],y[i]);
    double dy=a->GetErrorY(i);
    double w=(dist->GetBinContent(dist->GetXaxis()->FindBin(-x[i]))+dist->GetBinContent(dist->GetXaxis()->FindBin(x[i])));
    sumN+=w;
    w/=ntot;
    sumW+=w;
    sumV+=y[i]*w;
    sumD+=pow(w*dy,2);
  }

  m=sumV;
  dm=sqrt(sumD);
  //cout<<ntot<<" "<<sumN<<" "<<sumW<<" "<<sumV<<" "<<sqrt(sumD)<<endl;
}
