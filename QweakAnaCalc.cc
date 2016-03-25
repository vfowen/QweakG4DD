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

TH1D *asym[4];
TH1D *asymNorm[4];
TH1D *angleNorm[4];
TH2D *lPEvsAsym,*rPEvsAsym;
TH1D *distAsL,*distAsR;//1000 ev Asymmetry distributions 
TH1D *distAngL,*distAngR;//angle distributions normalized by PE*Asymmetry
double lpeP(0),lpeM(0),rpeP(0),rpeM(0);
double asymCut(0);
const int asCuts=4;
double asCut[asCuts]={0.005,0.01,0.05,0.5};
TGraph *convL[asCuts],*convR[asCuts],*convN[asCuts],*convA[asCuts];
TH1D *angNormL[asCuts],*angNormR[asCuts],*angNormN[asCuts],*angNormA[asCuts];
int ngL[asCuts]={0,0,0,0},ngR[asCuts]={0,0,0,0},ngN[asCuts]={0,0,0,0};
TGraph *as;
int nga(0);
double tstasAv(0);
int tstnAv(0);


int main(int argc, char** argv)
{

  if( argc < 2 ) {
    cout<<" usage: build/QweakAna [path to infile with list of output QweakSimG4 trees]"<<endl;
    return 1;
  }

  readPEs();
  
  string files(argv[1]);

  TFile *fout=new TFile("o_calcAsym.root","RECREATE");  

  TH1I *hNev=new TH1I("hNev","total number of events processed",1,0,1);
  as=new TGraph();
  for(int i=0;i<asCuts;i++){
    convL[i]=new TGraph();
    convR[i]=new TGraph();
    convN[i]=new TGraph();
    convA[i]=new TGraph();
    angNormL[i]=new TH1D(Form("angNormL_%d",i),Form("angX<-0.01 asym Normalized for abs(asym)<%f; angle[deg]",asCut[i]),360,-90,90);
    angNormR[i]=new TH1D(Form("angNormR_%d",i),Form("angX> 0.01 asym Normalized for abs(asym)<%f; angle[deg]",asCut[i]),360,-90,90);
    angNormN[i]=new TH1D(Form("angNormN_%d",i),Form("Null asym Normalized for abs(asym)<%f; angle[deg]",asCut[i]),360,-90,90);
    angNormA[i]=new TH1D(Form("angNormA_%d",i),Form("Angle sign weigthed asym Normalized for abs(asym)<%f; angle[deg]",asCut[i]),360,-90,90);
  }
  
  lPEvsAsym=new TH2D("lPEvsAsym","; left # PEs;asymetry",500,0,500,500,-1,1);
  rPEvsAsym=new TH2D("rPEvsAsym",";right # PEs;asymetry",500,0,500,500,-1,1);
  distAsL=new TH1D("distAsL","Left distAs" ,1000,-1e-3,1e-3);
  distAsR=new TH1D("distAsR","Right distAs",1000,-1e-3,1e-3);
  distAngL=new TH1D("distAngL","Left  distAng",360,-90,90);
  distAngR=new TH1D("distAngR","Right distAng",360,-90,90);
  
  string hTitle[4]={"(P+ - P-)/(P+ + P-)","(P+ - P-)","(P+ + P-) - 2","P+ - 1"};

  for(int i=0;i<4;i++){
    asym[i]=new TH1D(Form("asym%d",i),Form("dist %s",hTitle[i].c_str()),
		     500,-1,1);

    asymNorm[i]=new TH1D(Form("asymNorm%d",i),Form("Norm dist %s",hTitle[i].c_str()),
			 500,-1,1);

    angleNorm[i]=new TH1D(Form("angleNorm%d",i),Form("Norm angle %s",hTitle[i].c_str()),
			  360,-90,90);

  }

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
  //13.46 is the ratio for light between all the shower and primaries

  cout<<"Primary plus minus asymmetry"<<endl;
  cout<<"L "<<lpeP<<" "<<lpeM<<" "<<(lpeP-lpeM)/(lpeP+lpeM)<<endl;
  cout<<"R "<<rpeP<<" "<<rpeM<<" "<<(rpeP-rpeM)/(rpeP+rpeM)<<endl;
  cout<<" DD "<<(lpeP-lpeM)/(lpeP+lpeM) - (rpeP-rpeM)/(rpeP+rpeM)<<endl;
  double lave=(lpeP+lpeM)/2.;
  double rave=(rpeP+rpeM)/2.;
  lpeP += lave*13.46;
  lpeM += lave*13.46;
  rpeP += rave*13.46;
  rpeM += rave*13.46;
  cout<<"Everything plus minus asymmetry"<<endl;
  cout<<"L "<<lpeP<<" "<<lpeM<<" "<<(lpeP-lpeM)/(lpeP+lpeM)<<endl;
  cout<<"R "<<rpeP<<" "<<rpeM<<" "<<(rpeP-rpeM)/(rpeP+rpeM)<<endl;
  cout<<" DD "<<(lpeP-lpeM)/(lpeP+lpeM) - (rpeP-rpeM)/(rpeP+rpeM)<<endl;
  

  fout->cd();

  for(int i=0;i<asCuts;i++){    
    convL[i]->SetName(Form("convL_%d",i));
    convL[i]->SetTitle(Form("convergence of x<-0.01 asymmetry for abs(asym)<%f;ev number",asCut[i]));
    convL[i]->Write();
    convR[i]->SetName(Form("convR_%d",i));
    convR[i]->SetTitle(Form("convergence of x> 0.01 asymmetry for abs(asym)<%f;ev number",asCut[i]));
    convR[i]->Write();
    convN[i]->SetName(Form("convN_%d",i));
    convN[i]->SetTitle(Form("Null convergence asymmetry for abs(asym)<%f;ev number",asCut[i]));
    convN[i]->Write();
    convA[i]->SetName(Form("convA_%d",i));
    convA[i]->SetTitle(Form("convergence for angle sign weighted asymmetry for abs(asym)<%f;ev number",asCut[i]));
    convA[i]->Write();
    angNormL[i]->Write();
    angNormR[i]->Write();
    angNormN[i]->Write();
    angNormA[i]->Write();
  }
  
  hNev->SetBinContent(1,totEv);
  hNev->Write();
  
  for(int i=0;i<4;i++){
    asym[i]->Write();
    asymNorm[i]->Scale(1./asymNorm[i]->GetEntries());
    angleNorm[i]->Scale(1./angleNorm[i]->GetEntries());
    asymNorm[i]->Write();
    angleNorm[i]->Write();    
  }
  lPEvsAsym->Write();
  rPEvsAsym->Write();
  distAsL->Write();
  distAsR->Write();
  distAngL->Write();
  distAngR->Write();
  as->SetName("as");
  as->SetTitle("asymmetry;ev number");
  as->Write();
  fout->Close();
  return 0;
}

void processOne(TTree *QweakSimG4_Tree){

  std::vector<int> interaction;
  std::vector<int> trackID;

  //set addresses of leafs
  QweakSimUserMainEvent* event = 0;
  QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);    

  double klpeP(0),krpeP(0);
  double klpeM(0),krpeM(0);
  for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {
    QweakSimG4_Tree->GetEntry(i);
    if(i%10000==1)  cout<<"   at event: "<<i<<endl;

    if(i>100 && i%1000==0){
      distAsL->Fill( (klpeP-klpeM)/(klpeP+klpeM) );
      distAsR->Fill( (krpeP-krpeM)/(krpeP+krpeM) );
      klpeP = 0;
      klpeM = 0;
      krpeP = 0;
      krpeM = 0;
    }
    interaction.clear();
    trackID.clear();

    double asVal[4];
    asVal[0]=event->Primary.GetAsymPrim();
    asVal[1]=event->Primary.GetAsymNomi();
    asVal[2]=event->Primary.GetAsymDeno() - 2;
    asVal[3]=event->Primary.GetAsymPlus() - 1;

    double asAv=0;
    int nAv=0;
    
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
      std::vector<double> pt2(dimension-2,0);//mirror point
      std::vector<double> pts1[dimension];
      std::vector<double> pts2[dimension];

      pt1[0]=x;
      pt1[2]=angX;
      pt1[1]=E;

      pt2[0]=-pt1[0];
      pt2[2]=-pt1[2];
      pt2[1]=pt1[1];
            
      double rpe(-1),lpe(-1);
      double rp1(-1),rp2(-1);
      double lp1(-1),lp2(-1);
      getCorners(0,scanPoints[0].size(),0,pt1,pts1);
      getPEs(pts1,pt1,lp1,rp1);
      
      getCorners(0,scanPoints[0].size(),0,pt2,pts2);
      getPEs(pts2,pt2,lp2,rp2);
      
      if(lp1!=-1 && rp1!=-1 && lp2!=-1 && rp2!=-1){
	lpe=(lp1+rp2)/2;
	rpe=(rp1+lp2)/2;	    
      }else{
	cout<<"Problem with interpolator!"<<lpe<<" "<<rpe<<" "<<pt1[0]<<" "<<pt1[1]<<" "<<pt1[2]<<endl;
	exit(1);
      }      
      
      for(int j=0;j<4;j++){
	asym[j]->Fill(asVal[j]);
	asymNorm[j]->Fill(asVal[j],asVal[j]);
	angleNorm[j]->Fill(angX,asVal[j]);
      }

      for(int ii=0;ii<asCuts;ii++)
	if(abs(asVal[0])<asCut[ii]){
	  angNormN[ii]->Fill(angX,asVal[0]);
	  angNormA[ii]->Fill(angX,asVal[0]*angX/abs(angX));

	  angNormN[ii]->Scale(1./angNormN[ii]->GetEntries());
	  angNormA[ii]->Scale(1./angNormA[ii]->GetEntries());
	  convN[ii]->SetPoint(ngN[ii],ngN[ii],angNormN[ii]->Integral());
	  convA[ii]->SetPoint(ngN[ii],ngN[ii],angNormA[ii]->Integral());
	  angNormN[ii]->Scale(angNormN[ii]->GetEntries());
	  angNormA[ii]->Scale(angNormA[ii]->GetEntries());
	  ngN[ii]++;
	  
	  if(angX<0){
	    angNormL[ii]->Fill(angX,asVal[0]);
	    angNormL[ii]->Scale(1./angNormL[ii]->GetEntries());
	    convL[ii]->SetPoint(ngL[ii],ngL[ii],angNormL[ii]->Integral());	
	    angNormL[ii]->Scale(angNormL[ii]->GetEntries());
	    ngL[ii]++;
	  }else if(angX>0){
	    angNormR[ii]->Fill(angX,asVal[0]);
	    angNormR[ii]->Scale(1./angNormR[ii]->GetEntries());
	    convR[ii]->SetPoint(ngR[ii],ngR[ii],angNormR[ii]->Integral());	
	    angNormR[ii]->Scale(angNormR[ii]->GetEntries());
	    ngR[ii]++;
	  }
	}

      if(nAv%1000==0 && nAv>0){
	tstasAv+=asAv/1000.;
	tstnAv++;
	as->SetPoint(tstnAv,tstnAv,tstasAv/tstnAv);
	asAv=0;
      }

      asAv+=asVal[0];
      nAv++;
      
      distAngL->Fill(angX,asVal[0]*lpe);
      distAngR->Fill(angX,asVal[0]*rpe);
      
      lPEvsAsym->Fill(lpe,asVal[0]);
      rPEvsAsym->Fill(rpe,asVal[0]);
      
      lpeP += lpe*(1. + asVal[0]);
      lpeM += lpe*(1. - asVal[0]);
      rpeP += rpe*(1. + asVal[0]);
      rpeM += rpe*(1. - asVal[0]);

      klpeP += lpe*(1. + asVal[0]);
      klpeM += lpe*(1. - asVal[0]);
      krpeP += rpe*(1. + asVal[0]);
      krpeM += rpe*(1. - asVal[0]);      
    }//nhit
  }//tree entries
}


void readPEs(){

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
