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
    std::vector < TH1D* > pe_pos_diff(4);
    std::vector < TH1D* > pe_ang_diff(4);
    std::vector < TH1D* > pe_pos_sum(4);
    std::vector < TH1D* > pe_ang_sum(4);

    // Read out the histograms for models 0-4 into vectors
    for(int i = 0; i < 5; i++) {
        peL_pos[i] = (TH1D*)rootfile->Get(Form("peL_pos_%d",i));
        peR_pos[i] = (TH1D*)rootfile->Get(Form("peR_pos_%d",i));
        peL_ang[i] = (TH1D*)rootfile->Get(Form("peL_ang_%d",i));
        peR_ang[i] = (TH1D*)rootfile->Get(Form("peR_ang_%d",i));
    }

    // Scale histograms for models 1-4 by integral
    for(int i = 0; i < 4; i++) {
        peL_pos[i+1]->Scale(2/peL_pos[0]->Integral());
        peR_pos[i+1]->Scale(2/peR_pos[0]->Integral());
        peL_ang[i+1]->Scale(2/peL_ang[0]->Integral());
        peR_ang[i+1]->Scale(2/peR_ang[0]->Integral());

        // Clone the left histograms and subtract the right histograms
        pe_pos_diff[i] = (TH1D*)peL_pos[i+1]->Clone();
        pe_ang_diff[i] = (TH1D*)peL_ang[i+1]->Clone();
        pe_pos_sum[i] = (TH1D*)peL_pos[i+1]->Clone();
        pe_ang_sum[i] = (TH1D*)peL_ang[i+1]->Clone();

        // Calculate sums and differences
        pe_pos_diff[i]->Add(peR_pos[i+1], -1);
        pe_ang_diff[i]->Add(peR_ang[i+1], -1);
        pe_pos_sum[i]->Add(peR_pos[i+1], 1);
        pe_ang_sum[i]->Add(peR_ang[i+1], 1);

        // Scale sums by 0.5 to get averages
        pe_pos_sum[i]->Scale(0.5);
        pe_ang_sum[i]->Scale(0.5);
    }

    // Take the sum of + and - bids and plot vs + bin number
    std::vector<int> pe_pos_nbin(4);
    std::vector<int> pe_ang_nbin(4);
    std::vector<int> pe_pos_midbin(4);
    std::vector<int> pe_ang_midbin(4);
    // Offset in case there are an even number of bins
    std::vector<int> pe_pos_offset(4,0);
    std::vector<int> pe_ang_offset(4,0);
    // Output summed histograms
    std::vector < TH1D* > pe_pos_sum_wrap(4);
    std::vector < TH1D* > pe_ang_sum_wrap(4);
    for(int i = 0; i < 4; i++) {
        // Store the number of bins in a vector
        pe_pos_nbin[i] = pe_pos_sum[1]->GetNbinsX();
        pe_ang_nbin[i] = pe_ang_sum[1]->GetNbinsX();

        // Compute the mid position of the positive bins and offset
        if(pe_pos_midbin[i] % 2 == 0) {
            pe_pos_midbin[i] = pe_pos_nbin[i]/2;
            pe_ang_midbin[i] = pe_ang_nbin[i]/2;
            pe_pos_offset[i] = 1;
            pe_ang_offset[i] = 1;
        } else {
            pe_pos_midbin[i] = (pe_pos_midbin[i]+1)/2;
            pe_ang_midbin[i] = (pe_pos_midbin[i]+1)/2;
        }
        
        // Initilize histogram
        pe_pos_sum_wrap[i] = new TH1D(Form("pe_pos_sum_wrap_%d",i+1),
                                      Form("pe_pos_sum_wrap_%d",i+1),
                                      pe_pos_midbin[i], 0, pe_pos_midbin[i]);
        pe_ang_sum_wrap[i] = new TH1D(Form("pe_ang_sum_wrap_%d",i+1),
                                      Form("pe_ang_sum_wrap_%d",i+1),
                                      pe_ang_midbin[i], 0, pe_ang_midbin[i]);

        for (int j = 1; j <= pe_pos_midbin[i]; j++) {
            double temp_lbin = pe_pos_sum[i]->GetBinContent(
                    pe_pos_midbin[i]-j+pe_pos_offset[i]);
            double temp_rbin = pe_pos_sum[i]->GetBinContent(
                    pe_pos_midbin[i]+j);
            pe_pos_sum_wrap[i]->SetBinContent(j, temp_lbin+temp_rbin);
            //cout << "L bin Center:  "
            //    << pe_pos_sum[i]->GetBinCenter(
            //            pe_pos_midbin[i]-j+pe_pos_offset[i])
            //    << "  R bin Center:  "
            //    << pe_pos_sum[i]->GetBinCenter(pe_pos_midbin[i]+j)
            //    << "  value  "
            //    << temp_lbin
            //    << "  bin value  "
            //    << j 
            //    << endl;
        }
        for (int j = 1; j <= pe_ang_midbin[i]; j++) {
            double temp_lbin = pe_ang_sum[i]->GetBinContent(
                    pe_ang_midbin[i]-j+pe_ang_offset[i]);
            double temp_rbin = pe_ang_sum[i]->GetBinContent(
                    pe_ang_midbin[i]+j);
            pe_ang_sum_wrap[i]->SetBinContent(j, temp_lbin+temp_rbin);
        }
    }

    // Create all the canvases and such
    int num_plots = 6;
    std::vector< TCanvas* > tc(num_plots);
    std::vector< TPad* > pad1(num_plots);
    std::vector< TPad* > pad2(num_plots);
    std::vector< TPaveText* > text1(num_plots);
    std::vector<TString> title = {
        "Normalized Asym*PE L-R vs position mirrored, md8Config16, across23",
        "Normalized Asym*PE L-R vs angle mirrored, md8Config16, across23",
        "Normalized Asym*PE L+R vs position mirrored, md8Config16, across23",
        "Normalized Asym*PE L+R vs angle mirrored, md8Config16, across23",
        "Wrapped Asym*PE L+R vs position mirrored, md8Config16, across23",
        "Wrapped Asym*PE L+R vs angle mirrored, md8Config16, across23",
    };

    for(int i = 0; i < num_plots; i++) {
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
        pe_pos_diff[i]->Draw();
        pad2[1]->cd(i+1);
        pe_ang_diff[i]->Draw();
        pad2[2]->cd(i+1);
        pe_pos_sum[i]->Draw();
        pad2[3]->cd(i+1);
        pe_ang_sum[i]->Draw();
        pad2[4]->cd(i+1);
        pe_pos_sum_wrap[i]->Draw();
        //pad2[5]->cd(i+1);
        //pe_ang_sum_wrap[i]->Draw();
    }

    /* Close rootfile. */
    /* TApplication crap. */
    app->Run();
    return 0;
}
