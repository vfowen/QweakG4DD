#include <iostream>
#include <fstream>

TH3D *hIn;

void samplePrimaryDist(int seed, int nevents,int vPol){
  if(gRandom) delete gRandom;
  gRandom = new TRandom3(0);  
  //gRandom = new TRandom3(seed);
  //use for files with Hit_Map_Tracks ... DA tracking files
  //hIn=new TH3D("hIn","input h",15,320,350,20,-100,100,14,0.34,0.48);
  //use for MC files (JP)
  hIn=new TH3D("hIn","input h",22,324,346,200,-100,100,14,0.34,0.48);
  readDist();
  sampleDist(nevents,vPol);
  //drawDist();
}

void readDist(){
  //ifstream fin("../macros/md_dist.txt");
  //ifstream fin("../input/Hit_Map_Tracks_13671_MD2_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_13671_MD6_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_13674_MD4_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_13674_MD8_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_13676_MD3_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_13676_MD7_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_13679_MD3_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_13679_MD7_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_13681_MD1_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_13681_MD5_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_15121_MD1_.txt");
  //ifstream fin("../input/Hit_Map_Tracks_15121_MD5_.txt");
  //ifstream fin("../input/MC_HitMap_Oct1.txt");
  ifstream fin("../input/MC_HitMap_Oct3.txt");

  double x,y,xs,val;
  while(fin>>x>>y>>xs>>val){
    //cout<<x<<" "<<y<<" "<<xs<<" "<<val<<endl;
    if(val==0)continue;    
    //hIn->SetBinContent(x+1,y+1,xs+1,val);//if using tracking data
    hIn->SetBinContent(x,y,xs,val);//if using sim data
  }
}

void sampleDist(int nevents,int vPol){
  ofstream fout("positionMomentum.in",std::ofstream::out);
  ofstream fpol("polarization.in",std::ofstream::out);
  int nv=0;
  do{
    double x(-1);//x position (across bar) 
    double y(-1);//y position (along bar)  
    double z(-1);//x angle (across bar)    
    hIn->GetRandom3(x,y,z);

    double pbZpos=571.9;//cm
    double deg=180./3.14159265359;
    double pbXang=getAngY(y);
    double pbXpos=getPbPos(y,pbXang);
    double pbYang=z;
    double pbYpos=getPbPos(x,z);

    if( (pow(sin(pbYang),2)+pow(sin(pbXang),2)) > 1 ) continue;
    if( pbYpos<326 || pbYpos>344 ) continue;
    if( fabs(pbXpos)>=100 ) continue;

    fout<<pbXpos<<" "<<pbYpos<<" "<<pbZpos<<" "<<pbXang*deg<<" "<<pbYang*deg<<endl;

    double pX,pY;
    getPol(y,pX,pY);
    if(pY>1) pY=1;
    fpol<<vPol*pX<<" "<<vPol*pY<<endl;

    nv++;
  }while(nv<=nevents);

  fout.close();
  fpol.close();
}

void drawDist(){
  TCanvas *c1=new TCanvas("c1","c1",1600,1400);
  c1->Divide(2);
  c1->cd(1);
  TH2D *h1=hIn->Project3D("xy");
  h1->DrawCopy("colz");
  c1->cd(2);
  TH1D *h2=hIn->Project3D("y");
  h2->DrawCopy("colz");
  gPad->SetGridx(1);
  gPad->SetGridy(1);
}

void getPol(double pos,double &polX, double &polY){
  //[pos]=cm=position along bar
  polX=0.0038*pos;
  polY=sqrt(0.999999-pow(polX,2));
  double polZ=sqrt(1.-polX*polX-polY*polY);
  //cout<<pos<<" "<<polX<<" "<<polY<<" "<<polZ<<endl;
}

double getPbPos(double pos,double ang){
  return 5.375*tan(ang)+pos;//[cm]
}

double getAngY(double posY){//[posY]=cm
  //return (1.375e-3 * posY + 0.01); //from DA - data [rad]
  //return (1.39e-3 * posY - 1.8e-4); //from JP - sim Oct1 [rad]
  return (1.41e-3 * posY - 5.0e-5); //from JP - sim Oct3 [rad]
}

