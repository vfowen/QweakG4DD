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

using namespace std;

const int dimension=5;//3 DoF + 2 PE values
vector<double> scanPoints[dimension];
int debugPrint=0;
vector<double> totPE(4,0);
void readPEs();
void getCorners(int lowerIndex, int upperIndex, int depth, std::vector<double> point,
		std::vector<double> points[dimension]);
void getPEs(std::vector<double> in[dimension], std::vector<double> pt,
	    double &outL, double &outR);

const int nModels = 5;
//0=                                     
//1= cnst*sgn(angX) for abs(angX)=[20,40]
//2= cnst*angX                           
//3= cnst*sgn(angX)*angX^2               
//4= cnst*angX^3                         

//model,L/R,Upper/Lower
const int rangeTst=0;
// //DA moustache/centered - md8Config16 - acrossAng0
// double asymLimits[nModels][2][2]={
//   {{-0.200,-0.175},{0.200,0.225}},
//   {{-0.200,-0.170},{0.190,0.225}},
//   {{-0.237,-0.210},{0.257,0.283}},
//   {{-0.210,-0.175},{0.200,0.235}},
//   {{-0.250,-0.155},{0.150,0.255}}
// };
// //DA moustache/centered - md8Config16 - acrossAng23
// double asymLimits[nModels][2][2]={
//   {{-0.200,-0.175},{0.200,0.225}},
//   {{-0.175,-0.140},{0.175,0.205}},
//   {{-0.175,-0.145},{0.205,0.240}},
//   {{-0.225,-0.160},{0.190,0.240}},
//   {{-0.250,-0.165},{0.180,0.285}}
// };
//DA moustache mirrored x,x' - md8Config16 - acrossAng23 
double asymLimits[nModels][2][2]={
  {{-0.200,-0.175},{0.200,0.225}},
  {{-0.195,-0.165},{0.155,0.185}},
  {{-0.230,-0.200},{0.150,0.190}},
  {{-0.225,-0.180},{0.160,0.210}},
  {{-0.265,-0.185},{0.170,0.250}}
};

float model(float val,int type);


int main(int argc, char** argv)
{

  if( argc < 2 ) {
    cout<<" usage: build/avgModel [root file with hits]"<<endl;
    return 1;
  }

  readPEs();

  string files(argv[1]);

  TFile *fin=TFile::Open(files.c_str(),"READ");
  TTree *t=(TTree*)fin->Get("t");
  int evNr;
  int primary;//0 secondary, 1 primary
  float x,y,z,E;
  float angX,angY;
  float polT;
  t->SetBranchAddress("evNr",&evNr);
  t->SetBranchAddress("primary",&primary);
  t->SetBranchAddress("x",&x);
  t->SetBranchAddress("y",&y);
  t->SetBranchAddress("z",&z);
  t->SetBranchAddress("E",&E);
  t->SetBranchAddress("angX",&angX);
  t->SetBranchAddress("angY",&angY);
  t->SetBranchAddress("polT",&polT);
  
  TFile *fout=new TFile("o_avgModel.root","RECREATE");  

  string lr[2]={"R","L"};

  TH1D *hpe[2][nModels],*posPE[2][nModels],*angPE[2][nModels];
  TH1D *as[2][nModels];

  for(int i=0;i<nModels;i++)
    for(int j=0;j<2;j++){
      as[j][i]=new TH1D(Form("as%s_%d",lr[j].c_str(),i),Form("model %d %s PMT;asymmetry [ppm]",i,lr[j].c_str()),
			200,asymLimits[i][j][0],asymLimits[i][j][1]);      
      hpe[j][i] = new TH1D(Form("pe%s_%d",lr[j].c_str(),i),Form("model %d %s #PEs",i,lr[j].c_str()),
			   500,0,500);
      posPE[j][i] = new TH1D(Form("pe%s_pos_%d",lr[j].c_str(),i),
			     Form("model %d %s #PEs;position [cm]",i,lr[j].c_str()),
			     200,-100,100);
      angPE[j][i] = new TH1D(Form("pe%s_ang_%d",lr[j].c_str(),i),
			     Form("model %d %s #PEs;angle [deg]",i,lr[j].c_str()),
			     180,-90,90);
    }
  
  
  std::vector<double> avgStepL(nModels,0);
  std::vector<double> avgStepR(nModels,0);
  
  double stepSize=0.2;
  double currentStep=stepSize;

  int nev=t->GetEntries();

  for(int i=0;i<nev;i++){
    t->GetEntry(i);
    if(i%1000000==1) cout<<" at event: "<<i<<" "<<float(i+1)/nev*100<<"%"<<endl;

    if(float(i+1)/nev*100>currentStep){
      for(int imod=1;imod<nModels;imod++){
	as[0][imod]->Fill( avgStepR[imod]/avgStepR[0]*1e6 );
	as[1][imod]->Fill( avgStepL[imod]/avgStepL[0]*1e6 );
	if(rangeTst){
	  cout<<i<<" "<<imod<<" L "<<avgStepR[imod]<<" "<<avgStepR[0]<<" "<<avgStepR[imod]/avgStepR[0]*1e6<<endl;
	  cout<<i<<" "<<imod<<" R "<<avgStepL[imod]<<" "<<avgStepL[0]<<" "<<avgStepL[imod]/avgStepL[0]*1e6<<endl;
	}
	avgStepL[imod]=0;
	avgStepR[imod]=0;
      }
      avgStepL[0]=0;
      avgStepR[0]=0;
	
      currentStep+=stepSize;
    }
    
    if(i>1000000 && rangeTst) break;

    //x-=3.335;
    x=-x;
    angX=-angX;
    
    if(abs(x)>90) continue;
    if(abs(angX)>80) continue;
    if(E<3) continue;
    if(E>100) E=100;
        
    std::vector<double> pt(dimension-2,0);//correct point
    std::vector<double> pts[dimension];

    pt[0]=x;
    pt[1]=E;
    pt[2]=angX;
    
    double lpe(-1),rpe(-1);
    getCorners(0,scanPoints[0].size(),0,pt,pts);
    getPEs(pts,pt,lpe,rpe);

    if(lpe==-1 || rpe==-1 ||
       isnan(lpe) || isnan(rpe) ||
       isinf(lpe) || isinf(rpe)){
      cout<<"Problem with interpolator! "<<endl;
      cout<<" "<<lpe<<" "<<rpe<<endl;
      exit(1);
    }

    for(int imod=0;imod<nModels;imod++){
      double asym=model(angX,imod);
      avgStepL[imod]+=asym*lpe;
      avgStepR[imod]+=asym*rpe;

      hpe[0][imod]->Fill((1.+asym)*rpe);
      posPE[0][imod]->Fill(x,(1.+asym)*rpe);
      angPE[0][imod]->Fill(angX,(1.+asym)*rpe);
      hpe[1][imod]->Fill((1.+asym)*lpe);
      posPE[1][imod]->Fill(x,(1.+asym)*lpe);
      angPE[1][imod]->Fill(angX,(1.+asym)*lpe);
    }
    
    
  }


  fout->cd();
  for(int i=0;i<2;i++)
    for(int j=0;j<nModels;j++){      
      hpe[i][j]->Write();
      posPE[i][j]->Write();
      angPE[i][j]->Write();
      as[i][j]->Write();
    }
  
  fout->Close();
  return 0;
}

//models go here
float model(float val,int type){

  if(type==0)
    return 1;  
  else if(type==1 && (abs(val)>=20 && abs(val)<40) )
    return 4e-6*val/abs(val);
  else if(type==2)
    return 4e-8*val;
  else if(type==3)
    return 1.5e-9*val/abs(val)*pow(val,2);
  else if(type==4)
    return 4e-11*pow(val,3);

  return 0;
}


void readPEs(){
  //ifstream fin("input/idealBar_alongDir_acrossAng0_lightPara.txt");
  //ifstream fin("input/md8Config16_alongDir_acrossAng0_lightPara.txt");
  //ifstream fin("input/idealBar_alongDir_acrossAng23_lightPara.txt");
  ifstream fin("input/md8Config16_alongDir_acrossAng23_lightPara.txt");
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
    exit(1);
  }
  if(lowerIndex==upperIndex) return;
  
  int lI(-1),hI(-1);
  double valSmaller(999),valLarger(999);
  int nextDepth=depth+1;
  
  std::vector<double>::iterator begin=scanPoints[depth].begin();
  std::vector<double>::iterator start=begin+lowerIndex;
  std::vector<double>::iterator stop =begin+upperIndex;
  
  if(debugPrint)
    cout<<endl<<__LINE__<<" "<<__PRETTY_FUNCTION__<<endl
	<<"start upper : "<<point[depth]<<" "<<*start<<" "<<*(stop-1)<<" "
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
    cout<<endl<<__LINE__<<" "<<__PRETTY_FUNCTION__<<endl<<depth<<" "<<lowerIndex<<" "<<upperIndex<<" "<<lI<<" "<<hI<<endl;
    cout<<" "<<valSmaller<<"<"<<point[depth]<<"<"<<valLarger<<endl
	<<" range: "<<scanPoints[depth][lI]<<" "<<scanPoints[depth][hI-1]<<endl
	<<"  depth lI hI "<<depth<<" "<<lI<<" "<<hI<<endl;
  }

  if(depth==dimension-3){

    for(int i=0;i<dimension;i++) {
      points[i].push_back(scanPoints[i][lI]);
      points[i].push_back(scanPoints[i][hI]);
    }
    
    if(debugPrint){
      cout<<endl<<__LINE__<<" "<<__PRETTY_FUNCTION__<<endl
	  <<"End lower: "<<endl;
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
    cout<<endl<<__LINE__<<" "<<__PRETTY_FUNCTION__<<endl<<"start upper : "<<depth<<" "<<point[depth]<<" "<<*start<<" "<<*(stop-1)<<" "
	<<int(start-begin)<<" "<<int(stop-begin)<<endl;
  
  lI = int( upper_bound(start,stop,point[depth]) - begin );
  if( point[depth] == *(stop-1) )
    hI = upperIndex;
  else{
    valLarger=*(lower_bound(start,stop,point[depth]));
    hI = int( upper_bound(start,stop,valLarger) - begin );
  }
  if(debugPrint){
    cout<<endl<<__LINE__<<" "<<__PRETTY_FUNCTION__<<endl
	<<depth<<" "<<lowerIndex<<" "<<upperIndex<<" "<<lI<<" "<<hI<<endl;
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
    cout<<endl<<__LINE__<<" "<<__PRETTY_FUNCTION__<<endl
	<<"start "<<in[0].size()<<endl;
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
    cout<<endl<<__LINE__<<" "<<__PRETTY_FUNCTION__<<endl
	<<depth<<endl;
    for(unsigned long i=0;i<in[0].size();i++){
      for(int j=0;j<dimension;j++)
	cout<<in[j][i]<<" ";
      cout<<endl;
    }
  }
  getPEs(in,pt,outL,outR);
}
