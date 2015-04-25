TCanvas *c1=new TCanvas("c1","c1",1600,1200);
string onm;

void nTreeAsymPMT_xPosMD5(){
  onm="y_MD1_asymPMT_xVar_H.pdf";
  gSystem->Exec("ls /Users/ciprian/qweak/QweakG4DD/output/farm/MD1/H_1160_*/o_anaTree.root > z_list.in");
  asymPMT("z_list.in");
  gSystem->Exec("rm -rf z_list.in");
}
void asymPMT(string flist){
  c1->Clear();
  ifstream fin(flist.c_str());
  string data;
  double val[500][16];
  
  TGraphErrors *gl=new TGraphErrors();
  TGraphErrors *gr=new TGraphErrors();
  TGraphErrors *ga=new TGraphErrors();
  gl->SetName("gl");
  gr->SetName("gr");
  ga->SetName("ga");
  gl->GetYaxis()->SetTitle("L Number of PMT Hits");
  gr->GetYaxis()->SetTitle("R Number of PMT Hits");
  ga->GetYaxis()->SetTitle("Asym for PMT Hits");
  gl->GetXaxis()->SetTitle("initial beam y position [cm] ");
  gr->GetXaxis()->SetTitle("initial beam y position [cm] ");
  ga->GetXaxis()->SetTitle("initial beam y position [cm] ");
  gl->SetMarkerStyle(20);
  gr->SetMarkerStyle(20);
  ga->SetMarkerStyle(20);
  gl->SetMarkerColor(4);
  gr->SetMarkerColor(4);
  ga->SetMarkerColor(4);
  
  gStyle->SetOptFit(1);
  c1->cd(0);
  c1->Divide(3);
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n=0;
  while(fin>>data){
    TString _yp(data.c_str());
    _yp.Remove(0,_yp.First('1')+17);
    _yp.Remove(_yp.First('_'),_yp.Length());
    float ypos=_yp.Atof();
    cout<<data<<" > "<<_yp<<" is "<<ypos<<endl;

    doAna(data.c_str(),val[n][0],val[n][8],val[n][1],val[n][9],val[n][2],val[n][10],n);
    if(bad(val,n,0) && bad(val,n,1) && bad(val,n,2) && bad(val,n,8) && bad(val,n,9) && bad(val,n,10)) continue;

    ga->SetPoint(n,ypos,val[n][0]);
    gl->SetPoint(n,ypos,val[n][1]);
    gr->SetPoint(n,ypos,val[n][2]);
    ga->SetPointError(n,0,val[n][8]);
    gl->SetPointError(n,0,val[n][9]);
    gr->SetPointError(n,0,val[n][10]);
    n++;
  }

  TF1 *fp=new TF1("fp","pol1");

  c1->cd(1);
  gl->Fit("fp");
  gl->Draw("AP");
  c1->cd(2);
  gr->Fit("fp");
  gr->Draw("AP");
  c1->cd(3);
  ga->Fit("fp");
  ga->Draw("AP");

  //   gPad->Update();
  // TPaveStats *ps = (TPaveStats *)asym->GetListOfFunctions()->FindObject("stats");
  // ps->SetX1NDC(0.35);
  // ps->SetX2NDC(0.75);
  // gPad->SetGridy(1);
  // gPad->SetGridx(1);
  // gPad->Modified();
  // gPad->Update();
  
  c1->Print(onm.c_str(),"pdf");

  
  c1->Print(Form("%s]",onm.c_str()),"pdf");
}


double doAna(char *fn, double &a, double &da, double &l, double &dl, double &r, double &dr, int n)
{
  TString nb(fn);
  nb.Remove(nb.Last('/'),nb.Length());
  nb.Remove(0,nb.Last('/')+1);
  
  TFile *fin=TFile::Open(fn,"READ");
  TTree *t=(TTree*)fin->Get("te");

  TH1F *ha=new TH1F(Form("ha%d",n),Form("PMT asym %d",n) ,101,-1.01,1.01);
  TH1F *hl=new TH1F(Form("hl%d",n),Form("%s",nb.Data())  ,300,-0.5,299.5);
  TH1F *hr=new TH1F(Form("hr%d",n),Form("R PMT hit %d",n),300,-0.5,299.5);
  
  
  t->Project(Form("ha%d",n),"(LnPMThit-RnPMThit)/(LnPMThit+RnPMThit)","LnPMThit>0 && RnPMThit>0");
  t->Project(Form("hl%d",n),"LnPMThit","LnPMThit>0 && RnPMThit>0");
  t->Project(Form("hr%d",n),"RnPMThit","LnPMThit>0 && RnPMThit>0");

  TF1 *gs=new TF1("gs","gaus(0)");
  c1->cd(1);
  gs->SetParameters(hl->GetMaximum(),hl->GetMean(),hl->GetRMS());
  hl->Fit("gs","Q","",hl->GetMean()-2*hl->GetRMS(),hl->GetMean()+2*hl->GetRMS());  
  hl->DrawCopy();
  l =gs->GetParameter(1);
  dl=gs->GetParError(1);
  gPad->SetLogy(1);
  c1->cd(2);
  gs->SetParameters(hr->GetMaximum(),hr->GetMean(),hr->GetRMS());
  hr->Fit("gs","Q","",hr->GetMean()-2*hr->GetRMS(),hr->GetMean()+2*hr->GetRMS());  
  hr->DrawCopy();
  r =gs->GetParameter(1);
  dr=gs->GetParError(1);
  gPad->SetLogy(1);
  c1->cd(3);
  gs->SetParameters(ha->GetMaximum(),ha->GetMean(),ha->GetRMS());
  ha->Fit("gs","Q");
  ha->DrawCopy();
  c1->Print(onm.c_str(),"pdf");

  a =gs->GetParameter(1);
  da=gs->GetParError(1);
  fin->Close();
}


int bad(double a[500][16],int n,int m){
  for(int i=0;i<n;i++)
    if(fabs(a[n][m]-a[i][m])<0.0001) return 1;
  return 0;
}
