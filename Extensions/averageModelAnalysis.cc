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
#include <TPad.h>
#include <TVirtualPad.h>
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
    std::cout << "rootfile:  " << rootfile_name << std::endl;

    // Open the rootfile
    TFile* rootfile;
    rootfile = TFile::Open(rootfile_name);

    // ROOT display stuff
    TApplication *app = new TApplication("slopes", &argc, argv);

    // Histograms to fill from rootfile
    std::vector < TH1D* > peL_pos(7);
    std::vector < TH1D* > peR_pos(7);
    std::vector < TH1D* > peL_ang(7);
    std::vector < TH1D* > peR_ang(7);
    // Histogram results
    std::vector < TH1D* > pe_pos_diff(6);
    std::vector < TH1D* > pe_ang_diff(6);
    std::vector < TH1D* > pe_pos_sum(6);
    std::vector < TH1D* > pe_ang_sum(6);

    TString bar;
    TString angle;
    TString dist;
    bar = rootfile->Get("bar")->GetTitle();
    angle = rootfile->Get("angle")->GetTitle();
    dist = rootfile->Get("distribution")->GetTitle();

    // Read out the histograms for models 0-6 into vectors
    for(int i = 0; i < 7; i++) {
        peL_pos[i] = (TH1D*)rootfile->Get(Form("peL_pos_%d",i));
        peR_pos[i] = (TH1D*)rootfile->Get(Form("peR_pos_%d",i));
        peL_ang[i] = (TH1D*)rootfile->Get(Form("peL_ang_%d",i));
        peR_ang[i] = (TH1D*)rootfile->Get(Form("peR_ang_%d",i));
    }

    // Scale histograms for models 1-4 by integral
    for(int i = 0; i < 6; i++) {
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
    std::vector<int> pe_pos_sum_nbin(6);
    std::vector<int> pe_ang_sum_nbin(6);
    std::vector<int> pe_pos_sum_midbin(6);
    std::vector<int> pe_ang_sum_midbin(6);
    std::vector<int> pe_pos_diff_nbin(6);
    std::vector<int> pe_ang_diff_nbin(6);
    std::vector<int> pe_pos_diff_midbin(6);
    std::vector<int> pe_ang_diff_midbin(6);
    // Offset in case there are an even number of bins
    std::vector<int> pe_pos_sum_offset(6,0);
    std::vector<int> pe_ang_sum_offset(6,0);
    std::vector<int> pe_pos_diff_offset(6,0);
    std::vector<int> pe_ang_diff_offset(6,0);
    // Output summed histograms
    std::vector < TH1D* > pe_pos_sum_wrap(6);
    std::vector < TH1D* > pe_ang_sum_wrap(6);
    std::vector < TH1D* > pe_pos_diff_wrap(6);
    std::vector < TH1D* > pe_ang_diff_wrap(6);

    for(int i = 0; i < 6; i++) {
        // Store the number of bins in a vector
        pe_pos_sum_nbin[i] = pe_pos_sum[1]->GetNbinsX();
        pe_ang_sum_nbin[i] = pe_ang_sum[1]->GetNbinsX();
        pe_pos_diff_nbin[i] = pe_pos_diff[1]->GetNbinsX();
        pe_ang_diff_nbin[i] = pe_ang_diff[1]->GetNbinsX();

        // Compute the mid position of the positive bins and offset
        if(pe_pos_sum_midbin[i] % 2 == 0) {
            pe_pos_sum_midbin[i] = pe_pos_sum_nbin[i]/2;
            pe_ang_sum_midbin[i] = pe_ang_sum_nbin[i]/2;
            pe_pos_sum_offset[i] = 1;
            pe_ang_sum_offset[i] = 1;
            pe_pos_diff_midbin[i] = pe_pos_diff_nbin[i]/2;
            pe_ang_diff_midbin[i] = pe_ang_diff_nbin[i]/2;
            pe_pos_diff_offset[i] = 1;
            pe_ang_diff_offset[i] = 1;
        } else {
            pe_pos_sum_midbin[i] = (pe_pos_sum_midbin[i]+1)/2;
            pe_ang_sum_midbin[i] = (pe_pos_sum_midbin[i]+1)/2;
            pe_pos_diff_midbin[i] = (pe_pos_diff_midbin[i]+1)/2;
            pe_ang_diff_midbin[i] = (pe_pos_diff_midbin[i]+1)/2;
        }
        
        //cout << pe_pos_sum_midbin[i] << endl;
        //cout << pe_ang_sum_midbin[i] << endl;
        // Initilize histogram
        pe_pos_sum_wrap[i] = new TH1D(Form("pe_pos_sum_wrap_%d",i+1),
                                      Form("pe_pos_sum_wrap_%d",i+1),
                                      pe_pos_sum_midbin[i], 0,
                                      pe_pos_sum[1]->GetBinLowEdge(pe_pos_sum_nbin[i])
                                      + pe_pos_sum[1]->GetBinWidth(pe_pos_sum_nbin[i]));
        pe_ang_sum_wrap[i] = new TH1D(Form("pe_ang_sum_wrap_%d",i+1),
                                      Form("pe_ang_sum_wrap_%d",i+1),
                                      pe_ang_sum_midbin[i], 0,
                                      pe_ang_sum[1]->GetBinLowEdge(pe_ang_sum_nbin[i])
                                      + pe_ang_sum[1]->GetBinWidth(pe_ang_sum_nbin[i]));
        pe_pos_diff_wrap[i] = new TH1D(Form("pe_pos_diff_wrap_%d",i+1),
                                      Form("pe_pos_diff_wrap_%d",i+1),
                                      pe_pos_diff_midbin[i], 0,
                                      pe_pos_diff[1]->GetBinLowEdge(pe_pos_diff_nbin[i])
                                      + pe_pos_diff[1]->GetBinWidth(pe_pos_diff_nbin[i]));
        pe_ang_diff_wrap[i] = new TH1D(Form("pe_ang_diff_wrap_%d",i+1),
                                      Form("pe_ang_diff_wrap_%d",i+1),
                                      pe_ang_diff_midbin[i], 0,
                                      pe_ang_diff[1]->GetBinLowEdge(pe_ang_diff_nbin[i])
                                      + pe_ang_diff[1]->GetBinWidth(pe_ang_diff_nbin[i]));

        for (int j = 1; j <= pe_pos_sum_midbin[i]; j++) {
            double temp_lbin = pe_pos_sum[i]->GetBinContent(
                    pe_pos_sum_midbin[i]-j+pe_pos_sum_offset[i]);
            double temp_rbin = pe_pos_sum[i]->GetBinContent(
                    pe_pos_sum_midbin[i]+j);
            pe_pos_sum_wrap[i]->SetBinContent(j, temp_lbin+temp_rbin);
        }
        for (int j = 1; j <= pe_ang_sum_midbin[i]; j++) {
            double temp_lbin = pe_ang_sum[i]->GetBinContent(
                    pe_ang_sum_midbin[i]-j+pe_ang_sum_offset[i]);
            double temp_rbin = pe_ang_sum[i]->GetBinContent(
                    pe_ang_sum_midbin[i]+j);
            pe_ang_sum_wrap[i]->SetBinContent(j, temp_lbin+temp_rbin);
        }
        for (int j = 1; j <= pe_pos_diff_midbin[i]; j++) {
            double temp_lbin = pe_pos_diff[i]->GetBinContent(
                    pe_pos_diff_midbin[i]-j+pe_pos_diff_offset[i]);
            double temp_rbin = pe_pos_diff[i]->GetBinContent(
                    pe_pos_diff_midbin[i]+j);
            pe_pos_diff_wrap[i]->SetBinContent(j, temp_lbin+temp_rbin);
        }
        for (int j = 1; j <= pe_ang_diff_midbin[i]; j++) {
            double temp_lbin = pe_ang_diff[i]->GetBinContent(
                    pe_ang_diff_midbin[i]-j+pe_ang_diff_offset[i]);
            double temp_rbin = pe_ang_diff[i]->GetBinContent(
                    pe_ang_diff_midbin[i]+j);
            pe_ang_diff_wrap[i]->SetBinContent(j, temp_lbin+temp_rbin);
        }
    }

    // Output divided histograms
    std::vector < TH1D* > pe_pos_wrap_div(4);
    std::vector < TH1D* > pe_ang_wrap_div(4);

    // Clone wrapped sum histograms and divide by diff histograms
    for(int i = 0; i < 6; i++) {
        pe_pos_wrap_div[i] = (TH1D*)pe_pos_sum_wrap[i]->Clone();
        pe_ang_wrap_div[i] = (TH1D*)pe_ang_sum_wrap[i]->Clone();

        pe_pos_wrap_div[i]->Divide(pe_pos_diff_wrap[i]);
        pe_ang_wrap_div[i]->Divide(pe_ang_diff_wrap[i]);
    }
    //cout << pe_ang_sum_wrap[1]->GetBinContent(20) << "  " <<
    //        pe_ang_diff_wrap[1]->GetBinContent(20) << "  " <<
    //        pe_ang_wrap_div[1]->GetBinContent(20) << endl;
    //cout << pe_ang_sum_wrap[1]->GetBinLowEdge(20) << "  " <<
    //        pe_ang_diff_wrap[1]->GetBinLowEdge(20) << "  " <<
    //        pe_ang_wrap_div[1]->GetBinLowEdge(20) << endl;
    //cout << pe_ang_sum_wrap[1]->GetBinWidth(20) << "  " <<
    //        pe_ang_diff_wrap[1]->GetBinWidth(20) << "  " <<
    //        pe_ang_wrap_div[1]->GetBinWidth(20) << endl;

    // Output summed CDF histograms
    std::vector < TH1D* > pe_pos_sum_wrap_cdf(6);
    std::vector < TH1D* > pe_ang_sum_wrap_cdf(6);
    std::vector < TH1D* > pe_pos_diff_wrap_cdf(6);
    std::vector < TH1D* > pe_ang_diff_wrap_cdf(6);

    for(int i = 0; i < 6; i++) {
        pe_pos_sum_wrap_cdf[i] = (TH1D*)pe_pos_sum_wrap[i]->Clone();
        pe_ang_sum_wrap_cdf[i] = (TH1D*)pe_ang_sum_wrap[i]->Clone();
        pe_pos_diff_wrap_cdf[i] = (TH1D*)pe_pos_diff_wrap[i]->Clone();
        pe_ang_diff_wrap_cdf[i] = (TH1D*)pe_ang_diff_wrap[i]->Clone();

        for(int j = 2; j <= pe_pos_sum_wrap_cdf[i]->GetNbinsX(); j++) {
            int bin = pe_pos_sum_wrap_cdf[i]->GetBin(j);
            pe_pos_sum_wrap_cdf[i]->SetBinContent(bin, pe_pos_sum_wrap_cdf[i]->GetBinContent(bin)
                + pe_pos_sum_wrap_cdf[i]->GetBinContent(bin-1));
        }
        //pe_pos_sum_wrap_cdf[i]->Scale(1/pe_pos_sum_wrap_cdf[i]->Integral(),"nosw2");
        for(int j = 2; j <= pe_ang_sum_wrap_cdf[i]->GetNbinsX(); j++) {
            int bin = pe_ang_sum_wrap_cdf[i]->GetBin(j);
            pe_ang_sum_wrap_cdf[i]->SetBinContent(bin, pe_ang_sum_wrap_cdf[i]->GetBinContent(bin)
                + pe_ang_sum_wrap_cdf[i]->GetBinContent(bin-1));
        }
        //pe_ang_sum_wrap_cdf[i]->Scale(1/pe_ang_sum_wrap_cdf[i]->Integral(),"nosw2");
        for(int j = 2; j <= pe_pos_diff_wrap_cdf[i]->GetNbinsX(); j++) {
            int bin = pe_pos_diff_wrap_cdf[i]->GetBin(j);
            pe_pos_diff_wrap_cdf[i]->SetBinContent(bin, pe_pos_diff_wrap_cdf[i]->GetBinContent(bin)
                + pe_pos_diff_wrap_cdf[i]->GetBinContent(bin-1));
        }
        //pe_pos_diff_wrap_cdf[i]->Scale(1/pe_pos_diff_wrap_cdf[i]->Integral(),"nosw2");
        for(int j = 2; j <= pe_ang_diff_wrap_cdf[i]->GetNbinsX(); j++) {
            int bin = pe_ang_diff_wrap_cdf[i]->GetBin(j);
            pe_ang_diff_wrap_cdf[i]->SetBinContent(j, pe_ang_diff_wrap_cdf[i]->GetBinContent(bin)
                + pe_ang_diff_wrap_cdf[i]->GetBinContent(bin-1));
        }
        //pe_ang_diff_wrap_cdf[i]->Scale(1/pe_ang_diff_wrap[i]->Integral(),"nosw2");
    }

    gStyle->SetOptStat(0);
    //gStyle->SetOptStat("eiRM");
	gStyle->SetStatW(0.3);
	gStyle->SetStatH(0.1);

    // Create all the canvases and such
    int num_plots = 14;
    std::vector< TCanvas* > tc(num_plots);
    std::vector< TCanvas* > tc_individual(num_plots*6);
    std::vector< TPad* > pad1(num_plots);
    std::vector< TPad* > pad2(num_plots);
    std::vector< TPaveText* > text1(num_plots);
    std::vector<TString> title = {
        Form("Normalized Asym*PE L-R vs position: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Normalized Asym*PE L-R vs angle: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Normalized Asym*PE L+R vs position: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Normalized Asym*PE L+R vs angle: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Wrapped Asym*PE L+R vs position: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Wrapped Asym*PE L+R vs angle: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Wrapped Asym*PE L-R vs position: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Wrapped Asym*PE L-R vs angle: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Wrapped Asym*PE L+R/L-R vs position: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Wrapped Asym*PE L+R/L-R vs angle: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Wrapped Asym*PE L+R vs position CDF: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Wrapped Asym*PE L+R vs angle CDF: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Wrapped Asym*PE L-R vs position CDF: %s, %s, %s",dist.Data(),bar.Data(),angle.Data()),
        Form("Wrapped Asym*PE L-R vs angle CDF: %s, %s, %s",dist.Data(),bar.Data(),angle.Data())
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
        pad2[i]->Divide(3,2);
    }

    for(int i = 0; i < 6; i++) {
        pad2[0]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_pos_diff[i]->Draw();
        pad2[1]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_ang_diff[i]->Draw();
        pad2[2]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_pos_sum[i]->Draw();
        pad2[3]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_ang_sum[i]->Draw();
        pad2[4]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_pos_sum_wrap[i]->Draw();
        pad2[5]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_ang_sum_wrap[i]->Draw();
        pad2[6]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_pos_diff_wrap[i]->Draw();
        pad2[7]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_ang_diff_wrap[i]->Draw();
        pad2[8]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_pos_wrap_div[i]->Draw();
        pad2[9]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_ang_wrap_div[i]->Draw();
        pad2[10]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_pos_sum_wrap_cdf[i]->Draw();
        pad2[11]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_ang_sum_wrap_cdf[i]->Draw();
        pad2[12]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_pos_diff_wrap_cdf[i]->Draw();
        pad2[13]->cd(i+1);
        gPad->SetGridx(1);
        gPad->SetGridy(1);
        pe_ang_diff_wrap_cdf[i]->Draw();
    }

    for(int i = 0; i < 6; i++) {
        tc_individual[i*14] = new TCanvas(Form("tc_individual%d",i*14),Form("tc_individual%d",i*14),1200,800);
        pe_pos_diff[i]->Draw();
        tc_individual[i*14]->Print(Form("pe_pos_diff_%d.pdf",i+1));
        tc_individual[i*14+1] = new TCanvas(Form("tc_individual%d",i*14+1),Form("tc_individual%d",i*14+1),1200,800);
        pe_ang_diff[i]->Draw();
        tc_individual[i*14+1]->Print(Form("pe_ang_diff_%d.pdf",i+1));
        tc_individual[i*14+2] = new TCanvas(Form("tc_individual%d",i*14+2),Form("tc_individual%d",i*14+2),1200,800);
        pe_pos_sum[i]->Draw();
        tc_individual[i*14+2]->Print(Form("pe_pos_sum_%d.pdf",i+1));
        tc_individual[i*14+3] = new TCanvas(Form("tc_individual%d",i*14+3),Form("tc_individual%d",i*14+3),1200,800);
        pe_ang_sum[i]->Draw();
        tc_individual[i*14+3]->Print(Form("pe_ang_sum_%d.pdf",i+1));
        tc_individual[i*14+4] = new TCanvas(Form("tc_individual%d",i*14+4),Form("tc_individual%d",i*14+4),1200,800);
        pe_pos_sum_wrap[i]->Draw();
        tc_individual[i*14+4]->Print(Form("pe_pos_sum_wrap_%d.pdf",i+1));
        tc_individual[i*14+5] = new TCanvas(Form("tc_individual%d",i*14+5),Form("tc_individual%d",i*14+5),1200,800);
        pe_ang_sum_wrap[i]->Draw();
        tc_individual[i*14+5]->Print(Form("pe_ang_sum_wrap_%d.pdf",i+1));
        tc_individual[i*14+6] = new TCanvas(Form("tc_individual%d",i*14+6),Form("tc_individual%d",i*14+6),1200,800);
        pe_pos_diff_wrap[i]->Draw();
        tc_individual[i*14+6]->Print(Form("pe_pos_diff_wrap_%d.pdf",i+1));
        tc_individual[i*14+7] = new TCanvas(Form("tc_individual%d",i*14+7),Form("tc_individual%d",i*14+7),1200,800);
        pe_ang_diff_wrap[i]->Draw();
        tc_individual[i*14+7]->Print(Form("pe_ang_diff_wrap_%d.pdf",i+1));
        tc_individual[i*14+8] = new TCanvas(Form("tc_individual%d",i*14+8),Form("tc_individual%d",i*14+8),1200,800);
        pe_pos_wrap_div[i]->Draw();
        tc_individual[i*14+8]->Print(Form("pe_pos_wrap_div_%d.pdf",i+1));
        tc_individual[i*14+9] = new TCanvas(Form("tc_individual%d",i*14+9),Form("tc_individual%d",i*14+9),1200,800);
        pe_ang_wrap_div[i]->Draw();
        tc_individual[i*14+9]->Print(Form("pe_ang_wrap_div_%d.pdf",i+1));
        tc_individual[i*14+10] = new TCanvas(Form("tc_individual%d",i*14+10),Form("tc_individual%d",i*14+10),1200,800);
        pe_pos_sum_wrap_cdf[i]->Draw();
        tc_individual[i*14+10]->Print(Form("pe_pos_sum_wrap_cdf_%d.pdf",i+1));
        tc_individual[i*14+11] = new TCanvas(Form("tc_individual%d",i*14+11),Form("tc_individual%d",i*14+11),1200,800);
        pe_ang_sum_wrap_cdf[i]->Draw();
        tc_individual[i*14+11]->Print(Form("pe_ang_sum_wrap_cdf_%d.pdf",i+1));
        tc_individual[i*14+12] = new TCanvas(Form("tc_individual%d",i*14+12),Form("tc_individual%d",i*14+12),1200,800);
        pe_pos_diff_wrap_cdf[i]->Draw();
        tc_individual[i*14+12]->Print(Form("pe_pos_diff_wrap_cdf_%d.pdf",i+1));
        tc_individual[i*14+13] = new TCanvas(Form("tc_individual%d",i*14+13),Form("tc_individual%d",i*14+13),1200,800);
        pe_ang_diff_wrap_cdf[i]->Draw();
        tc_individual[i*14+13]->Print(Form("pe_ang_diff_wrap_cdf_%d.pdf",i+1));
    }

    std::vector<TString> files = {
        "pe_pos_diff.pdf",
        "pe_ang_diff.pdf",
        "pe_pos_sum.pdf",
        "pe_ang_sum.pdf",
        "pe_pos_sum_wrapped.pdf",
        "pe_ang_sum_wrapped.pdf",
        "pe_pos_diff_wrapped.pdf",
        "pe_ang_diff_wrapped.pdf",
        "pe_pos_wrapped_div.pdf",
        "pe_ang_wrapped_div.pdf",
        "pe_pos_sum_wrap_cdf.pdf",
        "pe_ang_sum_wrap_cdf.pdf",
        "pe_pos_diff_wrap_cdf.pdf",
        "pe_ang_diff_wrap_cdf.pdf"
    };

    for(int i = 0; i < num_plots; i++) {
        tc[i]->Update();
        tc[i]->Modified();
        tc[i]->Print(files[i]);
    }

    /* Close rootfile. */
    /* TApplication crap. */
    app->Run();
    return 0;
}
