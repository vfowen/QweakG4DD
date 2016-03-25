#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>

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
vector<double> totPE(4,0);

void readPEs();
void getCorners(int lowerIndex, int upperIndex, int depth, std::vector<double> point,
		std::vector<double> points[dimension]);
void getPEs(std::vector<double> in[dimension], std::vector<double> pt,
	    double &outL, double &outR);
double processOneFile(string fname,int verbose);

int main(int argc, char** argv){

  if( argc !=2 ) {
    cout<<" usage:  "<<endl;
    cout<<"     a) build/QweakCalcPMTDD [path to root file with distributions from QweakSimG4 trees]"<<endl;
    cout<<"     b) build/QweakCalcPMTDD [path to list of files with distributions from QweakSimG4 trees]"<<endl;
    return 1;
  }

  readPEs();
  


  string file(argv[1]);
  if ( file.find(".root") < file.size() ){
    for(int i=0;i<4;i++) totPE[i]=0.;
    processOneFile(file,1);
  }else{
    TFile *fout=new TFile("o_totPE.root","RECREATE");
    TGraph *simNr=new TGraph();
    simNr->SetName("simNr");
    simNr->SetTitle("simulation number");
    TGraph *nrEv=new TGraph();
    nrEv->SetName("nrEv");
    nrEv->SetTitle("number events for sim file");
    TGraphErrors *g[4];
    string gNm[4]={"lPe","rPe","lAe","rAe"};
    string gTit[4]={"Primary L PE","Primary R PE","All L PE","All R PE"};
    for(int i=0;i<4;i++){
      g[i]=new TGraphErrors();
      g[i]->SetName(gNm[i].c_str());
      g[i]->SetTitle(Form("%s;sim file #",gTit[i].c_str()));    
    }

    ifstream ifile(file.c_str());
    string data;
    int ng=0;
    while(ifile>>data){
      cout<<data<<endl;
      string nrSim=data.substr(0,data.find_last_of("/"));
      nrSim=nrSim.substr(nrSim.find_last_of("_")+1);
      simNr->SetPoint(ng,ng+1,atoi(nrSim.c_str()));
      for(int i=0;i<4;i++) totPE[i]=0.;
      nrEv->SetPoint(ng,ng+1,processOneFile(data,0));
      for(int i=0;i<4;i++) g[i]->SetPoint(ng,ng+1,totPE[i]);      
      ng++;      
    }
    ifile.close();

    fout->cd();
    for(int i=0;i<4;i++){
      g[i]->SetMarkerStyle(20);
      g[i]->Write();
    }    
    simNr->SetMarkerStyle(20);
    nrEv->SetMarkerStyle(20);
    simNr->Write();
    nrEv->Write();
    fout->Close();
  }

}

double processOneFile(string fname,int verbose){
  TFile *fin=new TFile(fname.c_str(),"READ");
  //  TFile *fin=TFile::Open(fname.c_str(),"READ");
  if(!fin->IsOpen()) {
    cout<<endl<<endl<<"Skipping file :"<<fname<<endl<<endl;
    delete fin;
    return -1;
  }else if(!fin->GetListOfKeys()->Contains("distPe") || 
	   !fin->GetListOfKeys()->Contains("distAe") || 
	   !fin->GetListOfKeys()->Contains("hNev")){
    cout<<endl<<endl<<"Skipping file :"<<fname<<endl<<endl;
    delete fin;
    return -1;
  }

  TH1D *hNev=(TH1D*)fin->Get("hNev");
  double totEv=hNev->GetBinContent(1);
  if(totEv<=0){
    cout<<endl<<"Skipping "<<fname<<" has hNev entry "<<totEv<<endl;
    delete fin;
    return -1;
  }
  string part[2]={"Pe","Ae"};
  string partTit[2]={"Primary e-","All e"};

  for(int i=0;i<2;i++){
    string histNm="dist"+part[i];
    TH3D *dist=(TH3D*)fin->Get(histNm.c_str());
    if(verbose)cout<<"looking at "<<dist->GetTitle()<<endl;
    
    double lTotPE(0),rTotPE(0);
    int counter=0;
    int printStep=500000;
    
    for(int xx=1;xx<=dist->GetXaxis()->GetNbins();xx++)//position
      for(int yy=1;yy<=dist->GetYaxis()->GetNbins();yy++)//angle
	for(int zz=1;zz<=dist->GetZaxis()->GetNbins();zz++){//energy
	  double entries=dist->GetBinContent(xx,yy,zz);
	  if(entries<=0) continue;
	  
	  std::vector<double> pt1(dimension-2,0);//correct point
	  std::vector<double> pt2(dimension-2,0);//mirror point
	  std::vector<double> pts1[dimension];
	  std::vector<double> pts2[dimension];

	  pt1[0]=dist->GetXaxis()->GetBinCenter(xx);
	  pt1[2]=dist->GetYaxis()->GetBinCenter(yy);
	  pt1[1]=dist->GetZaxis()->GetBinCenter(zz);
	  if(pt1[1]>100) pt1[1]=100.;

	  pt2[0]=-pt1[0];
	  pt2[2]=-pt1[2];
	  pt2[1]=pt1[1];

	  if(fabs(pt1[0])>90) continue;
	  if(fabs(pt1[2])>80) continue;
	  if(pt1[1]>100 || pt1[1]<3) continue;

	  if((debugPrint || counter%printStep==1) && verbose)
	    cout<<endl<<counter<<" !! Calc for pos, ang, E: "<<pt1[0]<<" "<<pt1[2]<<" "<<pt1[1]<<endl;

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
	  
	  if((debugPrint || counter%printStep==1) && verbose){
	    cout<<"    ~~~~ lpe rpe TL TR "<<lpe<<" "<<rpe<<" "<<lTotPE<<" "<<rTotPE<<endl;
	    if(debugPrint) cin.ignore();
	  }

	  lTotPE+=lpe*entries;
	  rTotPE+=rpe*entries;
	  counter++;
	  if(std::isnan(lpe) || std::isnan(rpe)) exit(2);
	}
    double das=2.*lTotPE*rTotPE/(pow(lTotPE+rTotPE,2))*sqrt((1./lTotPE)+(1./rTotPE));
    if(verbose)cout<<partTit[i]<<" : L R (L-R)/(L+R) "
		   <<setprecision(12)<<lTotPE<<" "<<rTotPE<<" "
		   <<(lTotPE-rTotPE)/(lTotPE+rTotPE)<<" pm "<<das<<endl;
    
    totPE[i*2]   = lTotPE;
    totPE[i*2+1] = rTotPE;
  }  
  fin->Close();
  delete fin;
  return totEv;
}

void readPEs(){
  ifstream fin("input/idealBar_alongDir_acrossAng0_lightPara.txt");
  //ifstream fin("input/md8Config16_alongDir_acrossAng0_lightPara.txt");
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
