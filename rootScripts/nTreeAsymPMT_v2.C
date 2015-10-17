TCanvas *c1=new TCanvas("c1","c1",800,600);
string onm;

void nTreeAsymPMT_v2(){
  string flist="f_Name_L.lst";
  onm="../output/y_PMTasym_v2_L.pdf";
  // string flist="f_Name_mott.lst";
  // onm="../output/y_PMTasym_v2_1e2mott.pdf";
 
  ifstream fin(flist.c_str());
  string data;
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n=0;
  TH1D *hf=new TH1D("hf","(L-R)/(L+R)",201,-1,1);

  while(fin>>data){
    nTupleAna(data,n,hf);
    n++;
  }

  gStyle->SetOptFit(1);
  hf->Fit("gaus");
  hf->DrawCopy();
  c1->Print(onm.c_str(),"pdf");

  c1->Print(Form("%s]",onm.c_str()),"pdf");
}


void nTupleAna(string fn, int n,TH1 *hf)
{    

  TFile *fin=TFile::Open(fn.c_str());
  TTree *t=(TTree*)fin->Get("QweakSimG4_Tree");
  if(t->GetEntries()<10000)
    cout<<fn.c_str()<<" "<<t->GetEntries()<<endl;

  TH1D *h=new TH1D(Form("h%d",n),Form("PMT asym for sim file %d",n),201,-1,1);
  t->Project(Form("h%d",n),Form("(Cerenkov.PMT.PMTLeftNbOfPEs[3] - Cerenkov.PMT.PMTRightNbOfPEs[3])/(Cerenkov.PMT.PMTLeftNbOfPEs[3] + Cerenkov.PMT.PMTRightNbOfPEs[3])"),"Cerenkov.PMT.PMTLeftNbOfPEs[3]!=0 && Cerenkov.PMT.PMTRightNbOfPEs[3]!=0");

  hf->Add(h);

  fin->Close();
}
