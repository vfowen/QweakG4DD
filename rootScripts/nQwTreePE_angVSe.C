TCanvas *c1=new TCanvas("c1","c1",1600,1200);
string onm;
string fnm;

void nQwTreePE_angVSe(){
  const int ne=5;
  const int energy[5]={5,10,30,50,100};

  onm="y_MD3_nPE_angVSe.pdf";
  gStyle->SetOptFit(1);
  c1->cd(0);
  c1->Divide(2);
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  
  fnm="o_angVSe.root";
  TFile *fout=new TFile(fnm.c_str(),"RECREATE");
  fout->Close();
  
  for(int i=0;i<ne;i++){    
    gSystem->Exec(Form("ls /lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput/angVSe/jobs/L_%04d_*/QwSim_0.root > z_list.in",energy[i]));
    asymPMT("z_list.in",energy[i]);
    gSystem->Exec("rm -rf z_list.in");
  }

  c1->Print(Form("%s]",onm.c_str()),"pdf");

}

void asymPMT(string flist, int energ){

  TFile *fout=TFile::Open(fnm.c_str(),"UPDATE");
  
  ifstream fin(flist.c_str());
  string data;
    
  TGraphErrors *al=new TGraphErrors();
  TGraphErrors *ar=new TGraphErrors();
  al->SetName(Form("peL_%d",energ));
  ar->SetName(Form("peR_%d",energ));  
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

  int n=0;

  while(fin>>data){ 
    //format /lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput/xVSangVSe/jobs/L_0005_000.10_335.00_576.00_000.04_001/QwSim_0.root
    TString _ang(data.c_str());
    _ang.Remove(_ang.Last('/'),_ang.Length());
    _ang.Remove(_ang.Last('_'),_ang.Length());
    _ang.Remove(0,_ang.Last('_')+1);
    double ang=_ang.Atof();
    
    cout<<data<<" > "<<_ang<<" is "<<ang<<endl;
    double _l, _dl, _r, _dr; 
    doAna(data.c_str(),_l,_dl,_r,_dr,n);

    al->SetPoint(n,ang,_l);
    ar->SetPoint(n,ang,_r);
    al->SetPointError(n,0,_dl);
    ar->SetPointError(n,0,_dr);
    n++;
  }

  c1->Clear();
  c1->cd(0);
  c1->Divide(2);
  al->SetTitle("Left nPEs for angle deviations ");
  c1->cd(1);
  al->Draw("AP");
  gPad->SetLogy(0);
  c1->cd(2);
  ar->Draw("AP");
  gPad->SetLogy(0);
  c1->Print(onm.c_str(),"pdf");      

  fout->cd();
  al->Write();
  ar->Write();
  fout->Close()

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

  c1->Clear();
  c1->cd(0);
  c1->Divide(2);  
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

  if(n%30==1)
    c1->Print(onm.c_str(),"pdf");//probably not worth drawing all the crap here

  fin->Close();
}

