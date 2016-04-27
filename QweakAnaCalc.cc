#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>

#include "QweakSimUserMainEvent.hh"
#include "QweakSimSystemOfUnits.hh"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TGraph.h"

using namespace std;

void findInt(std::vector<int> &inter,std::vector<int> &val, int trackID,int parent, int &hasPar, int &nInt);
void processOne(TTree *QweakSimG4_Tree);


const int dimension=5;//3 DoF + 2 PE values
vector<double> scanPoints[dimension];
const int debugPrint=0;
vector<double> totPE(4,0);
void readPEs();
void getCorners(int lowerIndex, int upperIndex, int depth, std::vector<double> point,
		std::vector<double> points[dimension]);
void getPEs(std::vector<double> in[dimension], std::vector<double> pt,
	    double &outL, double &outR);

void analyzePEs(TH1D *h1,TH1D *h2,TFile *fout,string hNm);
TH1D *wrapHist(TH1D *h,double op);

TH1D *dasym,*dasymPos,*dasymAng;
TH1D *dpe[2],*dpePos[2],*dpeAng[2];//[2]=l/r
double lpeP(0),lpeM(0),rpeP(0),rpeM(0);
TH2D *lPEvsAsym,*rPEvsAsym;

int main(int argc, char** argv)
{

  if( argc < 2 ) {
    cout<<" usage: build/QweakAna [path to infile with list of output QweakSimG4 trees]"<<endl;
    return 1;
  }

  readPEs();
  
  string files(argv[1]);

  TFile *fout=new TFile("o_calcAsym.root","RECREATE");  
  string lr[2]={"L","R"};

  dasym=new TH1D("dasym","Asymmetry distribution",1000,-1,1);
  dasymPos=new TH1D("dasymPos","Asymmetry distribution;position[cm]",200,-100,100);
  dasymAng=new TH1D("dasymAng","Asymmetry distribution;angle in shower[deg]",360,-90,90);

  for(int i=0;i<2;i++){
    dpe[i]=new TH1D(Form("dpe_%s",lr[i].c_str()),Form("%s PE*asym",lr[i].c_str()),1000,-1,1);
    dpePos[i]=new TH1D(Form("dpePos_%s",lr[i].c_str()),Form("%s PE*asym;position[cm]",lr[i].c_str()),200,-100,100);
    dpeAng[i]=new TH1D(Form("dpeAng_%s",lr[i].c_str()),Form("%s PE*asym;angle in shower [deg]",lr[i].c_str()),360,-90,90);
  }
  
  lPEvsAsym=new TH2D("lPEvsAsym","; left # PEs;asymetry",500,0,500,500,-1e-1,1e-1);
  rPEvsAsym=new TH2D("rPEvsAsym",";right # PEs;asymetry",500,0,500,500,-1e-1,1e-1);

  int totEv=0;
  if ( files.find(".root") < files.size() ){
    cout<<"single file " <<files<<endl;
    TFile *fin=new TFile(files.c_str(),"READ");
    if(!fin->IsOpen()){
      cout<<"Problem: can't find file: "<<files<<endl;
      fout->Close();
      return -3;
    }
    
    TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
    cout<<"processing only one file: "<<files.c_str()<<" for detector 3"<<endl;    
    
    int evts=QweakSimG4_Tree->GetEntries();
    totEv+=evts;
    cout<<" total nr ev: "<<evts<<" "<<totEv<<endl;    
    processOne(QweakSimG4_Tree);    
    cout<<"Done looping!"<<endl;
    fin->Close();
    delete fin;
  }else{
    cout<<"multiple files from: "<<files<<endl;
    ifstream ifile(files.c_str());
    string data;
    while(ifile>>data){      
      TFile *fin=new TFile(data.c_str(),"READ");
      if(!fin->IsOpen()){
	cout<<"Problem: can't find file: "<<data<<endl;
	continue;
      }
      TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
      cout<<"processing : "<<data.c_str()<<" for detector 3"<<endl;          
      int evts=QweakSimG4_Tree->GetEntries();
      totEv+=evts;
      cout<<" total nr ev: "<<evts<<" "<<totEv<<endl;      
      processOne(QweakSimG4_Tree);      
      cout<<"Done looping!"<<endl;
      fin->Close();
      delete fin;
    }
    ifile.close();
  }
  
  cout<<"Processed "<<totEv<<" events"<<endl;

  cout<<"Primary: plus minus asymmetry"<<endl;
  cout<<"L "<<lpeP<<" "<<lpeM<<" "<<(lpeP-lpeM)/(lpeP+lpeM)<<endl;
  cout<<"R "<<rpeP<<" "<<rpeM<<" "<<(rpeP-rpeM)/(rpeP+rpeM)<<endl;
  cout<<" DD "<<(lpeP-lpeM)/(lpeP+lpeM) - (rpeP-rpeM)/(rpeP+rpeM)<<endl;
  cout<<" bias "<<((lpeP-lpeM)/(lpeP+lpeM) + (rpeP-rpeM)/(rpeP+rpeM))/2.<<endl;
  double lave=(lpeP+lpeM)/2.;
  double rave=(rpeP+rpeM)/2.;
  //13.46 is the ratio for light between all the shower and primaries
  lpeP += lave*13.46;
  lpeM += lave*13.46;
  rpeP += rave*13.46;
  rpeM += rave*13.46;
  cout<<"Everything: plus minus asymmetry"<<endl;
  cout<<"L "<<lpeP<<" "<<lpeM<<" "<<(lpeP-lpeM)/(lpeP+lpeM)<<endl;
  cout<<"R "<<rpeP<<" "<<rpeM<<" "<<(rpeP-rpeM)/(rpeP+rpeM)<<endl;
  cout<<" DD "<<(lpeP-lpeM)/(lpeP+lpeM) - (rpeP-rpeM)/(rpeP+rpeM)<<endl;
  cout<<" bias "<<((lpeP-lpeM)/(lpeP+lpeM) + (rpeP-rpeM)/(rpeP+rpeM))/2.<<endl;
  
  fout->cd();

  dasym->Write();
  dasymAng->Write();
  dasymPos->Write();
  for(int i=0;i<2;i++){
    dpe[i]->Write();
    dpePos[i]->Write();
    dpeAng[i]->Write();
  }
  lPEvsAsym->Write();
  rPEvsAsym->Write();

  analyzePEs(dpe[0],dpe[1],fout,"h");
  analyzePEs(dpePos[0],dpePos[1],fout,"hPos");
  analyzePEs(dpeAng[0],dpeAng[1],fout,"hAng");

  fout->Close();
  return 0;
}

void processOne(TTree *QweakSimG4_Tree){

  std::vector<int> interaction;
  std::vector<int> trackID;

  //set addresses of leafs
  QweakSimUserMainEvent* event = 0;
  QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);    

  for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {
    QweakSimG4_Tree->GetEntry(i);
    if(i%10000==1)  cout<<"   at event: "<<i<<endl;

    interaction.clear();
    trackID.clear();

    double asVal[4];
    asVal[0]=event->Primary.GetAsymPrim();
    asVal[1]=event->Primary.GetAsymNomi();
    asVal[2]=event->Primary.GetAsymDeno() - 2;
    asVal[3]=event->Primary.GetAsymPlus() - 1;
    
    for (int hit = 0; hit < event->Cerenkov.Detector.GetDetectorNbOfHits(); hit++) {	
      if(event->Cerenkov.Detector.GetDetectorID()[hit]!=3) continue;
      if(event->Cerenkov.Detector.GetParticleType()[hit]!=11) continue;
      int parentID=event->Cerenkov.Detector.GetParentID()[hit];
      int tID     =event->Cerenkov.Detector.GetParticleID()[hit];
      if(parentID!=0) continue;
      if(tID!=1) continue;
      int hasParent(-1),nInt(-1);
      findInt(interaction,trackID,tID,parentID,hasParent,nInt);
      if(nInt!=1 || hasParent==1) continue;

      double x=event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit];            
      if(fabs(x)>90) continue;
      
      double Gphi   = event->Cerenkov.Detector.GetGlobalPhiAngle()[hit];
      double Gtheta = event->Cerenkov.Detector.GetGlobalThetaAngle()[hit];	
      double _Gtheta=Gtheta/180.*pi;
      double _Gphi=(Gphi+90)/180.*pi; //+90 to account for the offset in the output
      double angX = atan2(sin(_Gtheta)*cos(_Gphi),cos(_Gtheta)) * 180.0 / pi;
      if(fabs(angX)>80) continue;

      double E=event->Cerenkov.Detector.GetTotalEnergy()[hit];            
      if(E<3) continue;
      if(E>100) E=100;

      std::vector<double> pt1(dimension-2,0);//correct point
      std::vector<double> pts1[dimension];

      pt1[0]=x;
      pt1[2]=angX;
      pt1[1]=E;
            
      double rpe(-1),lpe(-1);
      getCorners(0,scanPoints[0].size(),0,pt1,pts1);
      getPEs(pts1,pt1,lpe,rpe);
      
      if(lpe==-1 || rpe==-1 ||
	 isnan(lpe) || isnan(rpe) ||
	 isinf(lpe) || isinf(rpe)){

	cout<<"Problem with interpolator!"<<lpe<<" "<<rpe<<" "<<pt1[0]<<" "<<pt1[1]<<" "<<pt1[2]<<endl;
	exit(1);
      }      

      dasym->Fill(asVal[0]);
      dasymPos->Fill(x,asVal[0]);
      dasymAng->Fill(angX,asVal[0]);

      dpe[0]->Fill(lpe*asVal[0]);
      dpe[1]->Fill(rpe*asVal[0]);

      dpePos[0]->Fill(x,lpe*asVal[0]);
      dpePos[1]->Fill(x,rpe*asVal[0]);

      dpeAng[0]->Fill(angX,lpe*asVal[0]);
      dpeAng[1]->Fill(angX,rpe*asVal[0]);

      lPEvsAsym->Fill(lpe,asVal[0]);
      rPEvsAsym->Fill(rpe,asVal[0]);
            
      lpeP += lpe*(1. + asVal[0]);
      lpeM += lpe*(1. - asVal[0]);
      rpeP += rpe*(1. + asVal[0]);
      rpeM += rpe*(1. - asVal[0]);
    }//nhit
  }//tree entries
}

void analyzePEs(TH1D *h1,TH1D *h2,TFile *fout,string hNm){

  fout->cd();
  TH1D *hdd=(TH1D*)h1->Clone(Form("%sdd",hNm.c_str()));
  hdd->Scale(1./hdd->Integral());
  hdd->Add(h2,-1./h2->Integral());
  hdd->Write();
  TH1D *hddwp=wrapHist(hdd,1);
  hddwp->Write();
  TH1D *hddwm=wrapHist(hdd,-1);
  hddwm->Write();

  TH1D *hbias=(TH1D*)h1->Clone(Form("%sbias",hNm.c_str()));
  hbias->Scale(1./hbias->Integral());
  hbias->Add(h2,1./h2->Integral());
  hbias->Scale(1./2);
  hbias->Write();
  TH1D *hbiaswp=wrapHist(hbias,1);
  hbiaswp->Write();
  TH1D *hbiaswm=wrapHist(hbias,-1);
  hbiaswm->Write();
  
}

TH1D *wrapHist(TH1D *h,double op){
  int nbin=h->GetXaxis()->GetNbins();
  double bh=h->GetBinLowEdge(nbin)+h->GetBinWidth(nbin);

  string hnm;
  if(op==1)
    hnm="sum";
  else
    hnm="dif";
  TH1D *wrap=new TH1D(Form("wrap_%s_%s",h->GetName(),hnm.c_str()),
		      Form("wrap: %s Mbin+(%d)*Pbin",h->GetTitle(),(int)op),
		      nbin/2,0,bh);

  for(int i=nbin/2+1;i<=nbin;i++){
    double pbin=h->GetBinContent(i);
    double mbin=h->GetBinContent(nbin-i+1);
    wrap->SetBinContent(i-nbin/2,pbin+op*mbin);
  }
  return wrap;
}


void readPEs(){
  //ifstream fin("input/idealBar_alongDir_acrossAng0_lightPara.txt");
  ifstream fin("input/md8Config16_alongDir_acrossAng0_lightPara.txt");
  if(!fin.is_open()) {
    cout<<" cannot read file for PE parametrization :macros/yl_md3_angle_scan.txt" <<endl;
    exit(2);
  }
  double x1,x2,x3,x4,x5,x6,x7,x8,x9;  
  string data;
  getline(fin,data);

  for(int i=0;i<dimension;i++)
    scanPoints[i].clear();
  
  while(fin>>x1>>x2>>x3>>x4>>x5>>x6>>x7>>x8>>x9){
    scanPoints[0].push_back(x1);//position
    scanPoints[1].push_back(x2);//energy
    scanPoints[2].push_back(x3);//angle
    scanPoints[3].push_back(x6);//LPEs
    scanPoints[4].push_back(x8);//RPEs
    if(debugPrint)
      cout<<x1<<" "<<x2<<" "<<x3<<" "<<x6<<" "<<x8<<endl;
  }
  
  fin.close();
}

void getCorners(int lowerIndex, int upperIndex, int depth, std::vector<double> point,
		std::vector<double> points[dimension]){

  if(lowerIndex==-1 || upperIndex==-1 || lowerIndex>upperIndex){
    cout<<"Problem with index: "<<lowerIndex<<" "<<upperIndex<<endl;
    exit(0);
  }
  if(lowerIndex==upperIndex) return;
  
  int lI(-1),hI(-1);
  double valSmaller(999),valLarger(999);
  int nextDepth=depth+1;
  
  std::vector<double>::iterator begin=scanPoints[depth].begin();
  std::vector<double>::iterator start=begin+lowerIndex;
  std::vector<double>::iterator stop =begin+upperIndex;

  if(debugPrint)
    cout<<"start upper : "<<point[depth]<<" "<<*start<<" "<<*(stop-1)<<" "
	<<int(start-begin)<<" "<<int(stop-begin)<<endl;

  if( point[depth]== *start)
    lI=lowerIndex;
  else if( point[depth] == *(stop-1) ){
    lI = int( lower_bound(start,stop,point[depth]) - begin );
  }else{    
    valSmaller = *( lower_bound(start,stop,point[depth]) - 1 );
    lI = int( lower_bound(start,stop,valSmaller) - begin );
  }
  
  hI = int( upper_bound(start,stop,point[depth]) - begin );

  if(debugPrint){
    cout<<depth<<" "<<lowerIndex<<" "<<upperIndex<<" "<<lI<<" "<<hI<<endl;
    cout<<" "<<valSmaller<<" "<<point[depth]<<" "<<valLarger<<" "
	<<scanPoints[depth][lI]<<" "<<scanPoints[depth][hI-1]<<endl;
  }

  if(depth==dimension-3){

    for(int i=0;i<dimension;i++) {
      points[i].push_back(scanPoints[i][lI]);
      points[i].push_back(scanPoints[i][hI]);
    }
    
    if(debugPrint){
      cout<<endl<<endl<<"End lower: "<<endl;
      for(int i=0;i<dimension;i++) cout<<scanPoints[i][lI]<<" ";
      cout<<endl;
      for(int i=0;i<dimension;i++) cout<<scanPoints[i][hI]<<" ";
      cout<<endl<<endl;
    }
    return;
  }else{
    getCorners(lI,hI,nextDepth,point,points);
  }

  if( point[depth] == *(stop-1) ) return;

  if(debugPrint)
    cout<<"start upper : "<<depth<<" "<<point[depth]<<" "<<*start<<" "<<*(stop-1)<<" "
	<<int(start-begin)<<" "<<int(stop-begin)<<endl;
  
  lI = int( upper_bound(start,stop,point[depth]) - begin );
  if( point[depth] == *(stop-1) )
    hI = upperIndex;
  else{
    valLarger=*(lower_bound(start,stop,point[depth]));
    hI = int( upper_bound(start,stop,valLarger) - begin );
  }
  if(debugPrint){
    cout<<depth<<" "<<lowerIndex<<" "<<upperIndex<<" "<<lI<<" "<<hI<<endl;
    cout<<" "<<valSmaller<<" "<<point[depth]<<" "<<valLarger<<" "
	<<scanPoints[depth][lI]<<" "<<scanPoints[depth][hI-1]<<endl;
  }
  
  if( point[depth]!= *start )
    getCorners(lI,hI,nextDepth,point,points);
}

void getPEs(std::vector<double> in[dimension], std::vector<double> pt,
	    double &outL, double &outR){

  std::vector<double> dm[dimension];

  if(debugPrint){
    cout<<"start "<<in[0].size()<<endl;
    for(unsigned long i=0;i<in[0].size();i++){
      for(int j=0;j<dimension;j++)
	cout<<in[j][i]<<" ";
      cout<<endl;
    }
  }
  
  if(in[0].size()==1){
    outL=in[dimension-2].front();
    outR=in[dimension-1].front();
    return;
  }

  int depth(-1);
  for(int j=0;j<dimension-2;j++)
    if(in[j][0]!=in[j][1])
      depth=j;
  
  for(int i=0;i<dimension;i++){
    dm[i].resize(in[i].size());
    for(unsigned long j=0;j<in[i].size();j++)
      dm[i][j]=in[i][j];
  }

  for(int i=0;i<dimension;i++)
    in[i].resize(dm[i].size()/2);

  for(unsigned long i=0;i<dm[0].size();i+=2){

    double l1=dm[dimension-2][i];
    double r1=dm[dimension-1][i];
    double l2=dm[dimension-2][i+1];
    double r2=dm[dimension-1][i+1];
    double fl=l1+(l2-l1)*(pt[depth]-dm[depth][i])/(dm[depth][i+1]-dm[depth][i]);
    double fr=r1+(r2-r1)*(pt[depth]-dm[depth][i])/(dm[depth][i+1]-dm[depth][i]);
      
    for(int j=0;j<dimension-2;j++)
      if(j!=depth)
	in[j][i/2]=dm[j][i];
      else
	in[j][i/2]=pt[depth];
    in[dimension-2][i/2]=fl;
    in[dimension-1][i/2]=fr;      
  }

  if(debugPrint){
    cout<<endl<<depth<<endl;
    for(unsigned long i=0;i<in[0].size();i++){
      for(int j=0;j<dimension;j++)
	cout<<in[j][i]<<" ";
      cout<<endl;
    }
  }
  getPEs(in,pt,outL,outR);
}


void findInt(std::vector<int> &inter,std::vector<int> &val, int trackID,int parent, int &hasPar, int &nInt){
  int found=0;
  nInt=-2;
  int findParent=0;
  for(unsigned int i=0;i<val.size();i++){
    if(trackID==val[i]){
      inter[i]++;
      nInt=inter[i];
      found++;
    }
    if(parent==val[i])
      findParent++;
  }
  
  if(findParent) hasPar=1;
  else hasPar=0;
  
  if(!found){
    val.push_back(trackID);
    inter.push_back(1);
    nInt=1;
  }
  if(found>1){
    cout<<"multiple entries for track "<<trackID<<endl;
  }
}
