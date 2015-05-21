TCanvas *c1=new TCanvas("c1","c1",1600,1200);
string onm;

void nTreePE_xVSangVSe(){
  onm="y_MD1_asymPMT_xVar_H_off.pdf";
  int ne=10;
  for(int i=0;i<ne;i++){    
    gSystem->Exec(Form("ls /L_%04d_*/QwSim_0.root > z_list.in",(i+1)*5));
    asymPMT("z_list.in",(i+1)*5);
    gSystem->Exec("rm -rf z_list.in");
  }
}

void asymPMT(string flist, int energ){

  c1->Clear();
  ifstream fin(flist.c_str());
  string data;
  
  TGraph2DErrors *gl=new TGraph2DErrors();
  TGraph2DErrors *gr=new TGraph2DErrors();
  gl->SetName("gl");
  gr->SetName("gr");
  gl->GetZaxis()->SetTitle(Form("L Number of PMT Hits for E=%d",energ));
  gr->GetZaxis()->SetTitle(Form("R Number of PMT Hits for E=%d",energ));
  gl->GetXaxis()->SetTitle("initial beam x position [cm] ");
  gr->GetXaxis()->SetTitle("initial beam x position [cm] ");
  gl->GetYaxis()->SetTitle("initial beam angle along bar [deg] ");
  gr->GetYaxis()->SetTitle("initial beam angle along bar [deg] ");
  gl->SetMarkerStyle(20);
  gr->SetMarkerStyle(20);
  gl->SetMarkerColor(2);
  gr->SetMarkerColor(2);
  gl->SetLineColor(4);
  gr->SetLineColor(4);
  
  gStyle->SetOptFit(1);
  c1->cd(0);
  c1->Divide(2);
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n=0;

  while(fin>>data){ //format L_0035_-00.02_335.00_576.00_000.20_004
    TString _xp(data.c_str());
    _xp.Remove(0,_xp.First('_')+6);
    _xp.Remove(_xp.First('_'),_xp.Length());
    double xpos=_xp.Atof();
    TString _ang(data.c_str());
    _ang.Remove(_ang.Last('/'),_ang.Length());
    _ang.Remove(_ang.Last('_'),_ang.Length());
    _ang.Remove(0,_ang.Last('_'));
    double ang=_ang.Atof();
    
    cout<<data<<" > "<<_xp<<" is "<<xpos<<" and "<<_ang<<" is "<<ang<<endl;
    double _l, _dl, _r, _dr; 
    doAna(data.c_str(),_l,_dl,_r,_dr,n);

    gl->SetPoint(n,xpos,ang,_l);
    gr->SetPoint(n,xpos,ang,_r);

    gl->SetPointError(n,0,0,_dl);
    gr->SetPointError(n,0,0,_dr);
    n++;
  }

  c1->cd(1);
  //gl->Draw("CONT");
  gl->Draw("PCOL");
  gPad->SetLogy(0);
  c1->cd(2);
  gr->Draw("PCOL");
  gPad->SetLogy(0);
  
  c1->Print(onm.c_str(),"pdf");

  
  c1->Print(Form("%s]",onm.c_str()),"pdf");
}


double doAna(char *fn, double &l, double &dl, double &r, double &dr, int n)
{
  TString nb(fn);
  nb.Remove(nb.Last('/'),nb.Length());
  nb.Remove(0,nb.Last('/')+1);
  
  TFile *fin=TFile::Open(fn,"READ");
  TTree *t=(TTree*)fin->Get("QweakSimG4_Tree");

  TH1F *hl=new TH1F(Form("hl%d",n),Form("%s",nb.Data())  ,300,-0.5,299.5);
  TH1F *hr=new TH1F(Form("hr%d",n),Form("R PMT hit %d",n),300,-0.5,299.5);
  
  t->Project(Form("hl%d",n),"Cerenkov.PMT.PMTLeftNbOfPEs[3]",
	     "Cerenkov.PMT.PMTLeftNbOfPEs[3]>0 && Cerenkov.PMT.PMTRightNbOfPEs[3]>0");
  t->Project(Form("hr%d",n),"Cerenkov.PMT.PMTRightNbOfPEs[3]",
	     "Cerenkov.PMT.PMTLeftNbOfPEs[3]>0 && Cerenkov.PMT.PMTRightNbOfPEs[3]>0");

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

  fin->Close();
}

