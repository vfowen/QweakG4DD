void transverseModel(){
  cout<<cdf(2.0,90.0)<<endl;

  c2=new TCanvas();
  TF2 *f2=new TF2("f2","1/x*sin(y)",1,1000,0,3.14159265/2);
  // f2->SetNpx(10000);
  // f2->SetNpy(1000);
  //f2->Draw("colz");
}

double cdf(double e=1, double th=90)
{
  double pi=3.14159265;
  TH1F *rf=new TH1F("rf","randf",300,0,2*pi);
  TH1F *rf1=new TH1F("rf1","randf",300,0,2*pi);
  TF1 *fit=new TF1("fit","[0]+[1]*sin(x+[2])",0,2*pi);

  TRandom3 a(0);
  TRandom3 c(2);
  double pre=1.0/e*sin(th/180.0*pi);
  cout<<pre<<endl;
  for(int i=0;i<100000;i++){
    double y=a.Uniform()*2*pi;
    double pr=c.Uniform();

    if(pr < sin(y-pi)*pre )
      y-=pi;

    rf->Fill(y);
    //  if(pr < sin(y-pr) ) rf->Fill(y-pi);
    // else rf->Fill(y);
  }

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);
  c4=new TCanvas();
  rf->DrawCopy();
  rf1->SetLineColor(2);
  fit->SetParameters(332,332,0);
  rf->Fit("fit");

  double base=fit->GetParameter(0);
  double amp=fit->GetParameter(1);
  return amp/base;
}

