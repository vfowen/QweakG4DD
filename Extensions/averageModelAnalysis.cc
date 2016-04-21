#include <TROOT.h>
#include <Riostream.h>
#include <TSQLServer.h>
#include <TFile.h>
#include <TTree.h>
#include <TApplication.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TLine.h>
#include <TLegend.h>
#include <TF1.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TColor.h>
#include <TPaveText.h>
#include <string>

/*
 * averageModelAnalysis.cc
 * Author: Wade Duvall <wsduvall@jlab.org>
 *
 * Compile with:
 *
 * g++ `root-config --glibs --cflags` -ggdb -O0 -Wall -Wextra -o \
 * averageModelAnalysis averageModelAnalysis.cc 
 *
 */

int main(Int_t argc, Char_t* argv[]) {

    TString rootfile_name = ""; 
    for(Int_t i = 1; i < argc; i++) {                          
        if(0 == strcmp("--rootfile", argv[i])) rootfile_name = argv[i+1];
    }                                                          

    // Print paramaters
    cout << "rootfile:  " << rootfile_name << endl;

    // Open the rootfile
    TFile* rootfile;
    rootfile = TFile::Open(rootfile_name);

    // ROOT display stuff
    TApplication *app = new TApplication("slopes", &argc, argv);

    // Histograms to fill from rootfile
    std::vector < TH1D* > peL_pos(5);
    std::vector < TH1D* > peR_pos(5);
    std::vector < TH1D* > peL_ang(5);
    std::vector < TH1D* > peR_ang(5);
    // Histogram results
    std::vector < TH1D* > pe_pos_diff(5);
    std::vector < TH1D* > pe_ang_diff(5);

    // Read out the histograms into vectors
    for(int i = 0; i < 5; i++) {
        peL_pos[i] = (TH1D*)rootfile->Get(Form("peL_pos_%d",i));
        peR_pos[i] = (TH1D*)rootfile->Get(Form("peR_pos_%d",i));
        peL_ang[i] = (TH1D*)rootfile->Get(Form("peL_ang_%d",i));
        peR_ang[i] = (TH1D*)rootfile->Get(Form("peR_ang_%d",i));

        // Scale histograms by integral
        peL_pos[i]->Scale(peL_pos[0]->Integral());
        peR_pos[i]->Scale(peR_pos[0]->Integral());
        peL_ang[i]->Scale(peL_ang[0]->Integral());
        peR_ang[i]->Scale(peR_ang[0]->Integral());

        // Clone the left histograms and subtract the right histograms
        pe_pos_diff[i] = (TH1D*)peL_pos[i]->Clone();
        pe_ang_diff[i] = (TH1D*)peL_ang[i]->Clone();
        pe_pos_diff[i]->Add(peR_pos[i], -1);
        pe_ang_diff[i]->Add(peR_ang[i], -1);
    }

    // Draw position
    TCanvas* tc1;
    tc1 = new TCanvas("tc1","tc1",1200,800);
    tc1->Draw();
    TPad*pad1 = new TPad("pad1","pad1",0.005,0.900,0.990,0.990);
    TPad*pad2 = new TPad("pad2","pad2",0.005,0.005,0.990,0.900);
    pad1->SetFillColor(0);
    pad1->Draw();
    pad2->Draw();
    pad2->SetFillColor(0);
    pad1->cd();
    TPaveText *text1 = new TPaveText(.05,.1,.95,.8);
    text1->AddText("Normalized Asym*PE L-R vs position mirrored, md8Config16, across23");
    text1->Draw();
    pad2->Divide(2,2);
    pad2->cd();

    for(int i = 0; i < 4; i++) {
        pad2->cd(i+1);
        pe_pos_diff[i]->Draw();
    }

    // Draw position
    TCanvas* tc2;
    tc2 = new TCanvas("tc2","tc2",1200,800);
    tc2->Draw();
    TPad*pad3 = new TPad("pad3","pad3",0.005,0.900,0.990,0.990);
    TPad*pad4 = new TPad("pad4","pad4",0.005,0.005,0.990,0.900);
    pad3->SetFillColor(0);
    pad3->Draw();
    pad4->Draw();
    pad4->SetFillColor(0);
    pad3->cd();
    TPaveText *text2 = new TPaveText(.05,.1,.95,.8);
    text2->AddText("Normalized Asym*PE L-R vs angle mirrored, md8Config16, across23");
    text2->Draw();
    pad4->Divide(2,2);
    pad4->cd();

    for(int i = 0; i < 4; i++) {
        pad4->cd(i+1);
        pe_ang_diff[i+1]->Draw();
    }

    /* Close rootfile. */
    /* TApplication crap. */
    app->Run();
    return 0;
}
