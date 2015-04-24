TCanvas *c1=new TCanvas("c1","c1",1200,500);
double val[300];

//string onm="y_Xdev_mV.pdf";
//string onm="y_Xdev_mL.pdf";
string onm="y_Xdev_V.pdf";
//string onm="y_Xdev_L.pdf";

void nTupleXdeviation(){
  //string flist="../output/farm/fTuple_mV_0.in";
  //string flist="../output/farm/fTuple_mL_0.in";
  string flist="../output/farm/fTuple_V_0.in";
  //string flist="../output/farm/fTuple_L_0.in";
  ifstream fin(flist.c_str());
  string data;
  double x[300];
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n=0;
  double min=100;
  double max=-100;
  c1->cd(0);
  c1->Divide(3);
  while(fin>>data){
    cout<<data.c_str()<<endl;
    val[n]=nTupleAna(data,n);
    cout<<n<<" "<<val[n]<<endl;
    if(bad(n)) continue;
    if(val[n]==-9999) continue;
    if(val[n]<min) min=val[n];
    if(val[n]>max) max=val[n];
    x[n]=n;
    n++;
  }
  TGraph *xMean=new TGraph(n,x,val);
  xMean->GetXaxis()->SetTitle("simulation file number");
  xMean->GetYaxis()->SetTitle("x mean difference between first and last interaction [mm]");
  xMean->Fit("pol0");
  xMean->SetMarkerStyle(20);
  xMean->SetMarkerColor(4);
  c1->cd(0);
  gStyle->SetOptFit(1);
  xMean->GetYaxis()->SetRangeUser(min-0.01,max+0.01);
  xMean->Draw("AP");
  c1->Print(onm.c_str(),"pdf");

  c1->Print(Form("%s]",onm.c_str()),"pdf");
}


double nTupleAna(string fn, int n)
{  
  float startPosx;
  float stopPosx;
  float startPosxA;
  float stopPosxA;
  
  int currentEv=-1;
  int Ninter=0;
  int NmscInter=0;
  
  TFile *fin=TFile::Open(fn.c_str());

  TH1F *xPos1=new TH1F(Form("xPos1_%d",n),Form("Position in Prestep for first int %d",n)    ,101,-20,20); 
  TH1F *xPos2=new TH1F(Form("xPos2_%d",n),Form("Position in Poststep for last int %d",n)    ,101,-20,20); 
  TH1F *xPosD=new TH1F(Form("xPost_%d",n),Form("Position diff (last - first) for int %d",n) ,101,-20,20); 


  TNtuple *t=(TNtuple*)fin->Get("t");
  float ax,bx,evN;
  float proc;
  
  t->SetBranchAddress("bx",&bx);
  t->SetBranchAddress("ax",&ax);
  t->SetBranchAddress("process",&proc);//1:msc; 2:CoulombSc; 3:eBrem;..
  if(!t->GetBranch("evN")){
    cout<<fn.c_str()<<" does not have evN branch .. quitting!"<<endl;
    fin->Close();
    return -9999;
  }
  else t->SetBranchAddress("evN",&evN);
  
  int nentries=t->GetEntries();
  for(int i=0;i<nentries;i++){
    t->GetEntry(i);
    //if(i%100000==1)cout<<"event "<<i<<endl;
       
    if(currentEv!=(int)evN){      
      if(currentEv!=-1){
	xPosD->Fill(stopPosxA-startPosxA);
	xPos2->Fill(stopPosxA);
      }
      currentEv=(int)evN;
      Ninter=1;
      startPosxA=bx;
      stopPosxA=ax;
      xPos1->Fill(startPosxA);
      if(proc==1) {
	NmscInter=1;
	startPosx=bx;
	stopPosx=ax;
      }
      else NmscInter=0;
    }else{
      Ninter++;
      stopPosxA=ax;
      if(proc==1) {
	stopPosx=ax;
      }
    }
  }

  c1->cd(1);
  xPos1->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(2);
  xPos2->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(3);
  xPosD->DrawCopy();
  gPad->SetLogy(1);
  double a=xPosD->GetMean();
  c1->Print(onm.c_str(),"pdf");
  fin->Close();
  return a;
}

int bad(int n){
  for(int i=0;i<n;i++){
    cout<<i<<" "<<val[i]<<" "<<val[n]<<" "<<fabs(val[n]-val[i])<<endl;
    if(fabs((val[n]-val[i])) < 0.0001)
      return 1;
  }
  return 0;
}
