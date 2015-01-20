void outAna()
{
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  TFile *fin=new TFile("o_ana.root","READ");
  TH2D *h2=(TH2D*)fin->Get("h2dHit");
  TH1D *hx=(TH1D*)fin->Get("hx");
  TH1D *hy=(TH1D*)fin->Get("hy");
  TH1D *hxg=(TH1D*)fin->Get("hxg");
  TH1D *hyg=(TH1D*)fin->Get("hyg");
  TH1D *hxe=(TH1D*)fin->Get("hxe");
  TH1D *hye=(TH1D*)fin->Get("hye");
  TH1D *hE=(TH1D*)fin->Get("hE");
  TH1D *hEe=(TH1D*)fin->Get("hEe");
  TH1D *hEg=(TH1D*)fin->Get("hEg");
  TH1D *hEeC=(TH1D*)fin->Get("hEeC");
  TH1D *hthe=(TH1D*)fin->Get("hthe");
  TH1D *hphi=(TH1D*)fin->Get("hphie");

  TF1 *f1=new TF1("fit1",lorentzianPeak,-10,10,3);
  f1->SetParameters(1,1,5);
  c1=new TCanvas("c1","c1",1500,500);
  c1->Divide(3,1);
  c1->cd(1);
  h2->DrawCopy("colz");
  c1->cd(2);
  hxg->Fit(f1);
  hx->SetLineColor(3);
  hxg->SetLineColor(4);
  hxe->SetLineColor(2);
  hx->DrawCopy();
  hxg->DrawCopy("same");
  hxe->DrawCopy("same");
  TPaveText *pt1 = new TPaveText(.55,.5,.9,.9,"NDC");
  pt1->AddText("Lorentzian Fit:");
  pt1->AddText(Form("norm: %4.2e #pm %4.2e", f1->GetParameter(0),f1->GetParError(0)));
  pt1->AddText(Form("mean: %4.2e #pm %4.2e", f1->GetParameter(2),f1->GetParError(2)));
  pt1->AddText(Form("width:%4.2e #pm %4.2e",f1->GetParameter(1),f1->GetParError(1)));
  pt1->SetFillStyle(0);
  pt1->SetBorderSize(0);
  pt1->Draw("");
  c1->cd(3);
  f1->SetParameters(2000,326,0.3);
  hyg->Fit(f1);
  hy->SetLineColor(3);
  hyg->SetLineColor(4);
  hye->SetLineColor(2);
  hy->DrawCopy();
  hyg->DrawCopy("same");
  hye->DrawCopy("same");
  TPaveText *pt2 = new TPaveText(.55,.5,.9,.9,"NDC");
  pt2->AddText("Lorentzian Fit:");
  pt2->AddText(Form("norm: %4.2e #pm %4.2e", f1->GetParameter(0),f1->GetParError(0)));
  pt2->AddText(Form("mean: %4.2e #pm %4.2e", f1->GetParameter(2),f1->GetParError(2)));
  pt2->AddText(Form("width:%4.2e #pm %4.2e",f1->GetParameter(1),f1->GetParError(1)));
  pt2->SetFillStyle(0);
  pt2->SetBorderSize(0);
  pt2->Draw("");
  c1->Print("scripts/y_outAna.pdf[","pdf");
  c1->Print("scripts/y_outAna.pdf","pdf");
  c1->cd(1);
  gPad->SetLogz(1);
  c1->cd(2);
  gPad->SetLogy(1);
  c1->cd(3);
  gPad->SetLogy(1);
  c1->Print("scripts/y_outAna.pdf","pdf");

  c2=new TCanvas("c2","c2",1600,800);
  c2->Divide(2);
  c2->cd(1);
  hE->SetLineColor(2);
  hEe->SetLineColor(4);
  hEg->SetLineColor(1);
  hE->DrawCopy();
  hEe->DrawCopy("same");
  hEg->DrawCopy("same");
  gPad->SetLogy(1);
  leg = new TLegend(0.4,0.5,0.89,0.9);
  leg->AddEntry(hE,"E distribution all","l");
  leg->AddEntry(hEe,"E distribution #gamma","l");
  leg->AddEntry(hEg,"E distribution e^{#pm}","l");
  leg->AddEntry(hEeC,"E distribution e^{#pm} with Cerenkov Threshold","l");
  leg->Draw();
  c2->cd(2);
  hEe->GetXaxis()->SetRangeUser(0,70);
  hEe->DrawCopy("");
  hEeC->SetLineColor(3);
  hEeC->DrawCopy("same");
  gPad->SetLogy(1);
  c2->Print("scripts/y_outAna.pdf","pdf"); 

  c2->cd(1);
  hphi->DrawCopy();
  gPad->SetLogy(0);
  c2->cd(2);
  hthe->DrawCopy();
  gPad->SetLogy(0);
  c2->Print("scripts/y_outAna.pdf","pdf"); 
  c2->cd(1);
  hphi->DrawCopy();
  gPad->SetLogy(1);
  c2->cd(2);
  hthe->DrawCopy();
  gPad->SetLogy(1);
  c2->Print("scripts/y_outAna.pdf","pdf"); 


  fin->Close();
  c1->Print("scripts/y_outAna.pdf]","pdf");
}

// Lorenzian Peak function
Double_t lorentzianPeak(Double_t *x, Double_t *par) {
  return (0.5*par[0]*par[1]/TMath::Pi()) / 
    TMath::Max( 1.e-10,(x[0]-par[2])*(x[0]-par[2]) 
   + .25*par[1]*par[1]);
}
