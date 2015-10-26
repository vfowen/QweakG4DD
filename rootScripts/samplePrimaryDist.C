#include <iostream>
#include <fstream>

TH3D *hIn;

void samplePrimaryDist(int seed, int nevents,int vPol){
  if(gRandom) delete gRandom;
  gRandom = new TRandom3(seed);  
  hIn=new TH3D("hIn","input h",15,320,350,20,-100,100,14,0.34,0.48);
  readDist();
  sampleDist(nevents,vPol);  
}

void readDist(){
  ifstream fin("../macros/md_dist.txt");
  double x,y,xs,val;
  while(fin>>x>>y>>xs>>val){
    //cout<<x<<" "<<y<<" "<<xs<<" "<<val<<endl;
    if(val==0)continue;
    hIn->SetBinContent(x+1,y+1,xs+1,val);
  }
}

void sampleDist(int nevents,int vPol){
  ofstream fout("positionMomentum.in",std::ofstream::out);
  ofstream fpol("polarization.in",std::ofstream::out);
  for(int i=0;i<nevents;i++){
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
  }
  fout.close();
  fpol.close();
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
  return (1.375e-3 * posY + 0.01); //[rad]
}

