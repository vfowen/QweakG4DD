void drawEffModelFctions(string fnm="../o_avgModelFction.root"){
  TFile *fin=TFile::Open(fnm.c_str(),"READ");
  TGraphErrors *g5=(TGraphErrors*)fin->Get("model_5");  
  g5->Draw("AL");
  TGraphErrors *gr[8];
  for(int i=2;i<8;i++){
    gr[i]=(TGraphErrors*)fin->Get(Form("model_%d",i));
    gr[i]->SetLineWidth(2);
    if(i==7)
      gr[i]->SetLineColor(2);
    gr[i]->Draw("L");
  }
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  fin->Close();
}
