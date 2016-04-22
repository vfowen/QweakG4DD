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
 * g++ --std=c++11 `root-config --glibs --cflags` -ggdb -O0 -Wall -Wextra -o \
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
    std::vector < TH1D* > pe_pos_sum(5);
    std::vector < TH1D* > pe_ang_sum(5);

    // Read out the histograms for models 0-4 into vectors
    for(int i = 0; i < 5; i++) {
        peL_pos[i] = (TH1D*)rootfile->Get(Form("peL_pos_%d",i));
        peR_pos[i] = (TH1D*)rootfile->Get(Form("peR_pos_%d",i));
        peL_ang[i] = (TH1D*)rootfile->Get(Form("peL_ang_%d",i));
        peR_ang[i] = (TH1D*)rootfile->Get(Form("peR_ang_%d",i));
    }

    // Scale histograms for models 1-4 by integral
    for(int i = 1; i < 5; i++) {
        peL_pos[i]->Scale(2/peL_pos[0]->Integral());
        peR_pos[i]->Scale(2/peR_pos[0]->Integral());
        peL_ang[i]->Scale(2/peL_ang[0]->Integral());
        peR_ang[i]->Scale(2/peR_ang[0]->Integral());

        // Clone the left histograms and subtract the right histograms
        pe_pos_diff[i] = (TH1D*)peL_pos[i]->Clone();
        pe_ang_diff[i] = (TH1D*)peL_ang[i]->Clone();
        pe_pos_sum[i] = (TH1D*)peL_pos[i]->Clone();
        pe_ang_sum[i] = (TH1D*)peL_ang[i]->Clone();

        // Calculate sums and differences
        pe_pos_diff[i]->Add(peR_pos[i], -1);
        pe_ang_diff[i]->Add(peR_ang[i], -1);
        pe_pos_sum[i]->Add(peR_pos[i], 1);
        pe_ang_sum[i]->Add(peR_ang[i], 1);

        // Scale sums by 0.5 to get averages
        pe_pos_sum[i]->Scale(0.5);
        pe_ang_sum[i]->Scale(0.5);
    }

    // Create all the canvases and such
    std::vector< TCanvas* > tc(4);
    std::vector< TPad* > pad1(4);
    std::vector< TPad* > pad2(4);
    std::vector< TPaveText* > text1(4);
    std::vector<TString> title = {
        "Normalized Asym*PE L-R vs position mirrored, md8Config16, across23",
        "Normalized Asym*PE L-R vs angle mirrored, md8Config16, across23",
        "Normalized Asym*PE L+R vs position mirrored, md8Config16, across23",
        "Normalized Asym*PE L+R vs angle mirrored, md8Config16, across23"};

    for(int i = 0; i < 4; i++) {
        tc[i] = new TCanvas(Form("tc%d",i),Form("tc%d",i),1200,800);
        tc[i]->Draw();
        pad1[i] = new TPad(Form("pad1%d",i),Form("pad1%d",i),0.005,0.900,0.990,0.990);
        pad2[i] = new TPad(Form("pad2%d",i),Form("pad2%d",i),0.005,0.005,0.990,0.900);
        pad1[i]->SetFillColor(0);
        pad1[i]->Draw();
        pad2[i]->Draw();
        pad2[i]->SetFillColor(0);
        pad1[i]->cd();
        text1[i] = new TPaveText(.05,.1,.95,.8);
        text1[i]->AddText(title[i]);
        text1[i]->Draw();
        pad2[i]->Divide(2,2);
    }

    for(int i = 0; i < 4; i++) {
        pad2[0]->cd(i+1);
        pe_pos_diff[i+1]->Draw();
        pad2[1]->cd(i+1);
        pe_ang_diff[i+1]->Draw();
        pad2[2]->cd(i+1);
        pe_pos_sum[i+1]->Draw();
        pad2[3]->cd(i+1);
        pe_ang_sum[i+1]->Draw();
    }

    /* Close rootfile. */
    /* TApplication crap. */
    app->Run();
    return 0;
}
