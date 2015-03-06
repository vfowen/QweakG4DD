// Author Ciprian
#include <string.h>
#include "stdio.h"
#include "iostream"
#include <iomanip>
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "QweakSimUserMainEvent.hh"
#include "math.h"
#include "stdlib.h"

using namespace std;
void addNm(TString a,std::vector<TString> &pn, std::vector<int> &np);
void printProcess(std::vector<TString> pn,std::vector<int> np);
void fullPrint(QweakSimUserMainEvent* event, int nr);

int main(int argc, char** argv)
{
    if(argc != 2) {
        cout<<" Please specify infile with paths to output QweakSimG4 trees "<<endl;
        return 1;
    }
    string fin(argv[1]);

    TChain* QweakSimG4_Tree = new TChain("QweakSimG4_Tree");
    ifstream ifile(fin.c_str());
    char _data[500];
    int scale=0;
    while(ifile>>_data){
      scale+=10000;
      QweakSimG4_Tree->Add(_data);
      cout<<_data<<endl;
    }

    //set addresses of leafs
    QweakSimUserMainEvent* event = 0;
    QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);

    TFile *fout=new TFile("o_ana.root","RECREATE");
    TH1D *hx = new TH1D("hx","hx",200,-20.0,20.0);
    TH1D *hy = new TH1D("hy","hy",200,325.0,345.0);
    TH2D *h2dhit=new TH2D("h2dHit","Cerenkov Detector Hit Postion", 200, -20, 20,200,325,345);
    TH1D *hE = new TH1D("hE","Total Energy of Track",200,0,1000);
    TH1D *hEe = new TH1D("hEe","Total Energy of e",200,0,1000);
    TH1D *hEeC = new TH1D("hEeC","Total Energy of e with Cerenkov Threshold cut",200,0,1000);
    TH1D *hEg = new TH1D("hEg","Total Energy of gamma",200,0,1000);
    TH1D *hxg = new TH1D("hxg","hx gamma",200,-20.0,20.0);
    TH1D *hyg = new TH1D("hyg","hy gamma",200,325.0,345.0);
    TH2D *hAngles=new TH2D("hAngles","{#phi} vs {#theta}",100,-300,100,100,0,180);

    TH1D *hxe = new TH1D("hxe","e x coord",200,-20.0,20.0);
    TH1D *hye = new TH1D("hye","e y coord",200,326.0,343.0);
    TH1D *hze = new TH1D("hze","e z coord",100,570.0,580.0);
    
    TH1D *Lphie= new TH1D("Lphie","local {#phi} angle e^{#pm}",100,-300,100);
    TH1D *Lthe= new TH1D("Lthe","local {#theta} angle e^{#pm}",100,0,180);
    TH1D *Gphie= new TH1D("Gphie","global {#phi} angle e^{#pm}",100,-300,100);
    TH1D *Gthe= new TH1D("Gthe","global {#theta} angle e^{#pm}",100,0,180);
    
    TH2D *xLphi=new TH2D("xLphi","e x vs local phi",200,-20,20,100,-360,360);    
    TH2D *xGphi=new TH2D("xGphi","e x vs global phi",200,-20,20,100,-280,100);
    TH2D *xE   =new TH2D("xE",   "e x vs E",200,-20,20,100,0,1000);
    
    TH1D *LnPEs=new TH1D("LnPEs","Number of PEs Left / hit" ,240,0,240);
    TH1D *RnPEs=new TH1D("RnPEs","Number of PEs Right/ hit" ,240,0,240);
    
    TH1D *LTnPEs=new TH1D("LTnPEs","Number of PEs / event Left" ,200,0,200);
    TH1D *RTnPEs=new TH1D("RTnPEs","Number of PEs / event Right",200,0,200);
    
    TH1D *LRasym=new TH1D("LRasym","PMT LR asymmetry (L-R)/(L+R)",100,-1,1);
    
    std::vector<TString> ProcessName;
    std::vector<int> nProc;
    double cutoff=1./1.458;
    double emass=0.510998910;//MeV
    double _xL=0;
    double _xR=0;
    double _peMin=100;
    double _peMax=0;
    cout<<" total nr ev: "<<QweakSimG4_Tree->GetEntries()<<endl;
    
    for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {
        QweakSimG4_Tree->GetEntry(i);

        if(i%10000==1) cout<<" at event: "<<i<<endl;
        //loop over hits
        for (int hit = 0; hit < event->Cerenkov.Detector.GetDetectorNbOfHits(); hit++) {
	  if(event->Cerenkov.Detector.GetDetectorID()[hit]!=3) continue;
	  
	  double _p=sqrt(pow(event->Cerenkov.Detector.GetGlobalMomentumX()[hit],2)+
                                 pow(event->Cerenkov.Detector.GetGlobalMomentumY()[hit],2)+
                                 pow(event->Cerenkov.Detector.GetGlobalMomentumZ()[hit],2));
	  double v=sqrt(pow(_p,2)/(pow(emass,2)+pow(_p,2)));

	  TString pn=event->Cerenkov.Detector.GetCreatorProcessName()[hit];
            //cout<<i<<" "<<hit<<" "<<pn.Data()<<endl;
          if(event->Cerenkov.Detector.GetDetectorGlobalPositionZ()[hit] > 580 ||
             event->Cerenkov.Detector.GetDetectorGlobalPositionZ()[hit] < 570) continue;

            //addNm(pn,ProcessName,nProc);
            double E=event->Cerenkov.Detector.GetTotalEnergy()[hit];
            //if(strcmp(pn.Data(),"eIoni")!=0) continue;
            hE->Fill(E);
            hx->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit]);
            hy->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionY()[hit]);
            h2dhit->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit],
                         event->Cerenkov.Detector.GetDetectorGlobalPositionY()[hit]);
            if(event->Cerenkov.Detector.GetParticleType()[hit]==22) {
                hxg->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit]);
                hyg->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionY()[hit]);
                hEg->Fill(E);
            }
            if(abs(event->Cerenkov.Detector.GetParticleType()[hit])==11) {
                hxe->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit]);
                hye->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionY()[hit]);
		hze->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionZ()[hit]);
		Gphie->Fill(event->Cerenkov.Detector.GetGlobalPhiAngle()[hit]);
                Gthe->Fill(event->Cerenkov.Detector.GetGlobalThetaAngle()[hit]);
		hAngles->Fill(event->Cerenkov.Detector.GetGlobalPhiAngle()[hit],
			      event->Cerenkov.Detector.GetGlobalThetaAngle()[hit]);
                hEe->Fill(E);
		
		Lphie->Fill(event->Cerenkov.Detector.GetLocalPhiAngle()[hit]);
		Lthe->Fill(event->Cerenkov.Detector.GetLocalThetaAngle()[hit]);
		xLphi->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit],event->Cerenkov.Detector.GetLocalPhiAngle()[hit]);
		xGphi->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit],event->Cerenkov.Detector.GetGlobalPhiAngle()[hit]);
		xE->Fill(event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit],E);
		if(event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit]>0) _xR+=E;
		else _xL+=E;
		if(v>cutoff) hEeC->Fill(E);
            }

        }
    
	float _ltnPE=0;
	float _rtnPE=0;
	for (int hit = 0; hit < event->Cerenkov.PMT.GetDetectorNbOfHits(); hit++){
	  if(abs(event->Cerenkov.PMT.GetPMTOctantOfHits()[hit])!=3) continue;
	  float _lpe=event->Cerenkov.PMT.GetPMTLeftNbOfPEs()[hit];
	  float _rpe=event->Cerenkov.PMT.GetPMTRightNbOfPEs()[hit];
	  if(_lpe>0) LnPEs->Fill(_lpe);
	  if(_rpe>0) RnPEs->Fill(_rpe);
	  _rtnPE+=_rpe;
	  _ltnPE+=_lpe;
	}
	LTnPEs->Fill(_ltnPE);
	RTnPEs->Fill(_rtnPE);
	if(_ltnPE>_peMax) _peMax=_ltnPE;
	if(_ltnPE<_peMin) _peMin=_ltnPE;
	if(_ltnPE>5 && _rtnPE>5)
	  LRasym->Fill((_ltnPE-_rtnPE)/(_ltnPE+_rtnPE));
    }
  
    cout<<_xL<<" L Energy of electrons R "<<_xR<<endl;
    cout<<" X position mean rms "<<hxe->GetMean()<<" "<<hxe->GetRMS()<<endl;
    cout<<" L Min Max NPE event "<<_peMin<<" "<<_peMax<<endl;
    LRasym ->Scale(1.0/scale);
    LnPEs  ->Scale(1.0/scale);
    RnPEs  ->Scale(1.0/scale);
    LTnPEs ->Scale(1.0/scale);
    RTnPEs ->Scale(1.0/scale);
    
    h2dhit->Write();
    hE->Write();
    hEe->Write();
    hEeC->Write();
    hEg->Write();
    hx->Write();
    hy->Write();
    hxg->Write();
    hyg->Write();
    hxe->Write();
    hye->Write();
    hze->Write();
    Gphie->Write();
    Gthe->Write();
    Lphie->Write();
    Lthe->Write();
    xLphi->Write();
    xGphi->Write();
    xE->Write();
    hAngles->Write();
    LTnPEs->Write();
    RTnPEs->Write();
    LnPEs->Write();
    RnPEs->Write();
    LRasym->Write();
    fout->Close();

    return 0;
}

void addNm(TString a,std::vector<TString> &pn, std::vector<int> &np)
{
    int found=-1;
    for(int i=0; i<(int)pn.size() && found==-1; i++) {
        if(strcmp(a.Data(),pn[i].Data())==0) found=i;
    }
    if(found==-1) {
        pn.push_back(a);
        np.push_back(1);
    }
    else
        np[found]++;
}

void printProcess(std::vector<TString> pn,std::vector<int> np)
{
    double allp=0;
    for(int i=0; i<(int)np.size(); i++) allp+=np[i];
    for(int i=0; i<(int)pn.size(); i++)
        std::cout<<i<<" "<<pn[i].Data()<<" "<<np[i]<<" "<<np[i]/allp<<endl;

}

void fullPrint(QweakSimUserMainEvent* event, int nr)
{
    cout<<"event "<<nr <<" with Nhits: "<<event->Cerenkov.Detector.GetDetectorNbOfHits()<<endl;
    for (int i = 0; i < event->Cerenkov.Detector.GetDetectorNbOfHits(); i++) {
//     if(event->Cerenkov.Detector.GetParticleType()[i]!=11) continue;
        cout<<"Hit # "<<i<<" name type id Parent-id creator "<<event->Cerenkov.Detector.GetParticleName()[i]<<" "
            <<event->Cerenkov.Detector.GetParticleType()[i]<<" "
            <<event->Cerenkov.Detector.GetParticleID()[i]<<" "
            <<event->Cerenkov.Detector.GetParentID()[i]<<" "
            <<event->Cerenkov.Detector.GetCreatorProcessName()[i]<<endl;
        if(event->Cerenkov.Detector.GetPolarizationZ()[i]!=0 && event->Cerenkov.Detector.GetPolarizationZ()[i]!=1)
            cout<<"~~~~~~~~~~~~~~~~";
        cout<<" tE kE Polarziation xyz "<<event->Cerenkov.Detector.GetTotalEnergy()[i]<<" "
            <<event->Cerenkov.Detector.GetKineticEnergy()[i]<<" "
            <<event->Cerenkov.Detector.GetPolarizationX()[i]<<" "
            <<event->Cerenkov.Detector.GetPolarizationY()[i]<<" "
            <<event->Cerenkov.Detector.GetPolarizationZ()[i]<<endl;
//     //cout<<"~~~~~~~~~~~~~Secondary particles: "<< event->Cerenkov.Detector.
//     cout<<" Cerenkov photon energy: "<<event->Cerenkov.Detector.GetCerenkovPhotonEnergy()[i]<<endl;
//     cout<<" Hit locations: "<<endl;
//     cout<<" Local x y z : "<<event->Cerenkov.Detector.GetDetectorLocalPositionX()[i]<<" "
//     <<event->Cerenkov.Detector.GetDetectorLocalPositionY()[i]<<" "
//     <<event->Cerenkov.Detector.GetDetectorLocalPositionZ()[i]<<endl;
//     cout<<" Local Exit x y z : "<<event->Cerenkov.Detector.GetDetectorLocalExitPositionX()[i]<<" "
//     <<event->Cerenkov.Detector.GetDetectorLocalExitPositionY()[i]<<" "
//     <<event->Cerenkov.Detector.GetDetectorLocalExitPositionZ()[i]<<endl;
//     cout<<" Global x y z : "<<event->Cerenkov.Detector.GetDetectorGlobalPositionX()[i] <<" "
//     <<event->Cerenkov.Detector.GetDetectorGlobalPositionY()[i]<<" "
//     <<event->Cerenkov.Detector.GetDetectorGlobalPositionZ()[i]<<endl;
//     cout<<" Origin Vertex x y z : "<<event->Cerenkov.Detector.GetOriginVertexPositionX()[i] <<" "
//     <<event->Cerenkov.Detector.GetOriginVertexPositionY()[i]<<" "
//     <<event->Cerenkov.Detector.GetOriginVertexPositionZ()[i]<<endl;
//


    }
}
