TH3D *hIn;

void samplePrimaryDist(UInt seed, int nevents){
  if(gRandom) detele gRandom;
  gRandom = new TRandom3(seed);
  
  hIn=new TH3D("hIn","input h",15,320,350,20,-100,100,14,0.34,0.48);
  readDist();
  sampleDist(nevents);
  
}

void readDist(){
  ifstream fin("../macros/md_dist.txt");
  double x,y,xs,val;
  while(fin>>x>>y>>xs>>val){
    cout<<x<<" "<<y<<" "<<xs<<" "<<val<<endl;
    if(val==0)continue;
    h->SetBinContent(x+1,y+1,xs+1,val);
  }
}

void sampleDist(int nevents){

  ofstream fout("dist.in",std::ofstream:out);
  ofstream fpol("pol.in",std::ofstream::out);
  for(int i=0;i<nevents;i++){
    double x(-1);//x position (across bar) 
    double y(-1);//y position (along bar)  
    dobule z(-1);//x angle (across bar)    
    hIn->GetRandom3(x,y,z);
    
    double pbXang=getAngY(y);
    double pbXpos=getPbPos(y,pbXang);
    double pbYang=z;
    double pbYpos=getPbPos(x,z);
    fout<<pbXpos<<" "<<pbXang<<" "<<pbYpos<<" "<<pbYang<<endl;
    double pX,pY;
    getPol(y,pX,pY);
    fpol<<pX<<" "<<pY<<endl;
  }
  fout.close();
  fpol.close();
}


void getPol(double pos,double &polX, double &polY){
  //[pos]=cm=position along bar
  double f=1./0.53;
  polX=0.0002*pos*f;
  polY=sqrt(0.53*0.53-polX*polX)*f;
}

double getPbPos(double pos,double ang){
  return 5.375*tan(ang)+pos;//[cm]
}

double getAngY(double posY){//[posY]=cm
  return (1.375e-3 * posY + 0.01); //[rad]
}

void tstRndm(TH3D *ht){
  TH3D *aft=new TH3D("aft","sampled",
		     ht->GetXaxis()->GetNbins(),ht->GetXaxis()->GetXmin(),ht->GetXaxis()->GetXmax(),
		     ht->GetYaxis()->GetNbins(),ht->GetYaxis()->GetXmin(),ht->GetYaxis()->GetXmax(),
		     ht->GetZaxis()->GetNbins(),ht->GetZaxis()->GetXmin(),ht->GetZaxis()->GetXmax());

  for(int i=0;i<80000;i++){
    double x,y,z;
    ht->GetRandom3(x,y,z);
    aft->Fill(x,y,z);
  }

  c3=new TCanvas();
  h1xy=ht->Project3D("xy");
  h1xy->Draw("colz");

  c4=new TCanvas();
  h2xy=aft->Project3D("xy");
  h2xy->Draw("colz");

}
