#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>

#include "QweakSimUserMainEvent.hh"
#include "QweakSimSystemOfUnits.hh"
#include "TH3D.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TH1D.h"

using namespace std;

const int dimension=5;//3 DoF + 2 PE values
vector<double> scanPoints[dimension];
const int debugPrint=0;
TGraph *peL,*peR,*aeL,*aeR,*npL,*npR;
int nGraph(0);

void readPEs();
void getCorners(int lowerIndex, int upperIndex, int depth, std::vector<double> point,
		std::vector<double> points[dimension]);
void getPEs(std::vector<double> in[dimension], std::vector<double> pt,
	    double &outL, double &outR);
void findInt(std::vector<int> &inter,std::vector<int> &val, int trackID,int parent, int &hasPar, int &nInt);
void processOneFile(string fname);

int main(int argc, char** argv){

  if( argc !=2 ) {
    cout<<" usage:  "<<endl;
    cout<<"     a) build/QweakAnaPEs [path to root file with distributions from QweakSimG4 trees]"<<endl;
    cout<<"     b) build/QweakAnaPEs [path to list of files with distributions from QweakSimG4 trees]"<<endl;
    return 1;
  }

  readPEs();  
  TFile *fout=new TFile("o_anaPE.root","RECREATE");
  peL=new TGraph();
  peR=new TGraph();
  npL=new TGraph();
  npR=new TGraph();
  aeL=new TGraph();
  aeR=new TGraph();

  string file(argv[1]);
  if ( file.find(".root") < file.size() ){
    processOneFile(file);
  }else{

    ifstream ifile(file.c_str());
    string data;
    while(ifile>>data){
      cout<<data<<endl;
      processOneFile(data);
    }
    ifile.close();
  }

  fout->cd();
  peL->SetMarkerStyle(20);
  peR->SetMarkerStyle(20);
  aeL->SetMarkerStyle(20);
  aeR->SetMarkerStyle(20);
  npL->SetMarkerStyle(20);
  npR->SetMarkerStyle(20);
  peL->SetName("lpe");
  peR->SetName("rpe");
  aeL->SetName("lae");
  aeR->SetName("rae");
  npL->SetName("lnp");
  npR->SetName("rnp");
  peL->Write();
  peR->Write();
  aeL->Write();
  aeR->Write();
  npL->Write();
  npR->Write();
  fout->Close();

}

void processOneFile(string fname){

  TFile *fin=new TFile(fname.c_str(),"READ");
  if(!fin->IsOpen()) {
    cout<<endl<<endl<<"Skipping file :"<<fname<<endl<<endl;
    delete fin;
    return;
  }else if(!fin->GetListOfKeys()->Contains("QweakSimG4_Tree")){
    cout<<endl<<endl<<"Skipping file tree :"<<fname<<endl<<endl;
    delete fin;
    return;
  }

  TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
  cout<<"   evts: "<<QweakSimG4_Tree->GetEntries()<<endl;

  std::vector<int> interaction;
  std::vector<int> trackID;

  //set addresses of leafs
  QweakSimUserMainEvent* event = 0;
  QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);    

  for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {
    QweakSimG4_Tree->GetEntry(i);

    double lprimaryPE=0.;
    double rprimaryPE=0.;
    double lnonPrimPE=0.;
    double rnonPrimPE=0.;

    interaction.clear();
    trackID.clear();
    
    for (int hit = 0; hit < event->Cerenkov.Detector.GetDetectorNbOfHits(); hit++) {	
      if(event->Cerenkov.Detector.GetDetectorID()[hit]!=3) continue;
      int pTypeHit=event->Cerenkov.Detector.GetParticleType()[hit];
      if(abs(pTypeHit)!=11) continue;
      double E=event->Cerenkov.Detector.GetTotalEnergy()[hit];
      
      int parentID=event->Cerenkov.Detector.GetParentID()[hit];
      int tID     =event->Cerenkov.Detector.GetParticleID()[hit];
      
      int hasParent(-1),nInt(-1);
      findInt(interaction,trackID,tID,parentID,hasParent,nInt);
      if(nInt!=1 || hasParent==1) continue;
      
      std::vector<double> pt1(dimension-2,0);//correct point
      pt1[0]=event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit];
      if(fabs(pt1[0])>90) continue;
      
      double Gphi   = event->Cerenkov.Detector.GetGlobalPhiAngle()[hit];
      double Gtheta = event->Cerenkov.Detector.GetGlobalThetaAngle()[hit];	
      double _Gtheta=Gtheta/180.*pi;
      double _Gphi=(Gphi+90)/180.*pi; //+90 to account for the offset in the output
      pt1[2] = atan2(sin(_Gtheta)*cos(_Gphi),cos(_Gtheta)) * 180.0 / pi;      
      if(fabs(pt1[2])>80) continue;
      
      pt1[1] = ( E>100 ) ? 100 : E;
      if (pt1[1]<3) continue;
      
      //calculate PEs
      std::vector<double> pt2(dimension-2,0);//mirror point
      std::vector<double> pts1[dimension];
      std::vector<double> pts2[dimension];
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
	//cout<<lp1<<" "<<rp1<<" "<<lp2<<" "<<rp2<<" "<<lpe<<" "<<rpe<<endl;
      }else{
	cout<<"Problem with interpolator!"<<lpe<<" "<<rpe<<" "<<pt1[0]<<" "<<pt1[1]<<" "<<pt1[2]<<endl;
	exit(1);
      }

      
      if(tID==1 && parentID==0){ //primary		
	//add to event PEs
	lprimaryPE+=lpe;
	rprimaryPE+=rpe;
      }else{ //nonprimary
	//add to event PEs
	lnonPrimPE+=lpe;
	rnonPrimPE+=rpe;
      }      
    }//nhit

    peL->SetPoint(nGraph,nGraph,lprimaryPE);
    peR->SetPoint(nGraph,nGraph,rprimaryPE);
    npL->SetPoint(nGraph,nGraph,lnonPrimPE);
    npR->SetPoint(nGraph,nGraph,rnonPrimPE);
    aeL->SetPoint(nGraph,nGraph,lprimaryPE+lnonPrimPE);
    aeR->SetPoint(nGraph,nGraph,rprimaryPE+rnonPrimPE);
    nGraph++;
  }//tree entries
  fin->Close();
  delete fin;
}

void readPEs(){
  ifstream fin("input/idealBar_alongDir_acrossAng0_lightPara.txt");
  //ifstream fin("input/md8Config16_alongDir_acrossAng0_lightPara.txt");
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
