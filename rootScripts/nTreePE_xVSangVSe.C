TCanvas *c1=new TCanvas("c1","c1",1600,1200);
string onm;

void nTreePE_xVSangVSe(){
  int ne=10;
  for(int i=0;i<ne;i++){    
    onm=Form("y_MD3_nPE_xVSang_e%d.pdf",(i+1)*5);
    //gSystem->Exec(Form("ls /lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput/xVSangVSe/jobs/L_%04d_*/QwSim_0.root > z_list_%d.in",(i+1)*5,i));
    asymPMT(Form("z_list_%d.in",i),(i+1)*5);
    //gSystem->Exec("rm -rf z_list.in");
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
  
  TGraphErrors *al=new TGraphErrors();
  TGraphErrors *ar=new TGraphErrors();
  al->SetName("al");
  ar->SetName("ar");  
  al->SetPoint(0,0,0);
  ar->SetPoint(0,0,0);
  al->SetMarkerStyle(20);
  al->SetMarkerColor(2);
  al->SetLineColor(4);
  al->GetXaxis()->SetTitle("angle devition along bar [deg]");
  al->GetYaxis()->SetTitle("number PEs left");
  ar->SetMarkerStyle(20);
  ar->SetMarkerColor(2);
  ar->SetLineColor(4);
  ar->GetXaxis()->SetTitle("angle devition along bar [deg]");
  ar->GetYaxis()->SetTitle("number PEs right");

  gStyle->SetOptFit(1);
  c1->cd(0);
  c1->Divide(2);
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n=0;
  int nx=0;
  double ck_x=-1;
  while(fin>>data){ 
    //format /lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput/xVSangVSe/jobs/L_0005_000.10_335.00_576.00_000.04_001/QwSim_0.root
    TString _xp(data.c_str());
    _xp.Remove(0,_xp.First('_')+6);
    _xp.Remove(_xp.First('_'),_xp.Length());
    double xpos=_xp.Atof();
    TString _ang(data.c_str());
    _ang.Remove(_ang.Last('/'),_ang.Length());
    _ang.Remove(_ang.Last('_'),_ang.Length());
    _ang.Remove(0,_ang.Last('_')+1);
    double ang=_ang.Atof();
    
    if(ck_x==-1)
      ck_x=xpos;
    else if(ck_x!=xpos){
      al->SetTitle(Form("n PEs for angle deviations at xpos = %f",ck_x));
      c1->cd(1);
      al->Fit("pol1");
      al->Draw("AP");
      gPad->SetLogy(0);
      c1->cd(2);
      ar->Fit("pol1");
      ar->Draw("AP");
      gPad->SetLogy(0);
      c1->Print(onm.c_str(),"pdf");      
      ck_x=xpos;
      nx=0;
    }

    cout<<data<<" > "<<_xp<<" is "<<xpos<<" and "<<_ang<<" is "<<ang<<endl;
    double _l, _dl, _r, _dr; 
    doAna(data.c_str(),_l,_dl,_r,_dr,n);

    gl->SetPoint(n,xpos,ang,_l);
    gr->SetPoint(n,xpos,ang,_r);
    gl->SetPointError(n,0,0,_dl);
    gr->SetPointError(n,0,0,_dr);

    al->SetPoint(nx,ang,_l);
    ar->SetPoint(nx,ang,_r);
    al->SetPointError(nx,0,_dl);
    ar->SetPointError(nx,0,_dr);
    n++;
    nx++;
  }

  al->SetTitle(Form("n PEs for angle deviations at xpos = %f",ck_x));
  c1->cd(1);
  al->Fit("pol1");
  al->Draw("AP");
  gPad->SetLogy(0);
  c1->cd(2);
  ar->Fit("pol1");
  ar->Draw("AP");
  gPad->SetLogy(0);
  c1->Print(onm.c_str(),"pdf");      

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
  
  t->Project(Form("hl%d",n),"Cerenkov.PMT.PMTLeftNbOfPEs[3]", "Cerenkov.PMT.PMTLeftNbOfPEs[3]>0 && Cerenkov.PMT.PMTRightNbOfPEs[3]>0");
  t->Project(Form("hr%d",n),"Cerenkov.PMT.PMTRightNbOfPEs[3]","Cerenkov.PMT.PMTLeftNbOfPEs[3]>0 && Cerenkov.PMT.PMTRightNbOfPEs[3]>0");

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

  //c1->Print(onm.c_str(),"pdf");//probably not worth drawing all the crap here

  fin->Close();
}

