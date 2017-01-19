void transverseModel(){
  cout<<cdf(1.0,90.0)<<endl;

  cout<<wght(1.0,90)<<endl;
  // c2=new TCanvas();
  // TF2 *f2=new TF2("f2","1/x*sin(y)",1,1000,0,3.14159265/2);
  // f2->SetNpx(10000);
  // f2->SetNpy(1000);
  //f2->Draw("colz");
}

double cdf(double e=1, double th=90)
{
  double pi=acos(-1);
  TH1F *rf=new TH1F("rf","randf",300,0,2*pi);
  //TH1F *rf=new TH1F("rf","randf",300,-2*pi,4*pi);
  TH1F *rf1=new TH1F("rf1","randf",300,0,2*pi);
  TF1 *fit=new TF1("fit","[0]+[1]*sin(x+[2])",0,2*pi);

  TH1F *chi=new TH1F("chi","chi2",100,0,10);
  TF1 *chiPDF=new TF1("chiPDF","pow(x,[0]/2-1)*exp(-x/2)/(pow(2,[0]/2)*TMath::Gamma([0]/2))",0,10);

  TRandom3 a(0);
  TRandom3 c(2);
  double pre=1.0/e*sin(th/180.0*pi);
  cout<<pre<<endl;
  for(int i=0;i<1000000;i++){
    double pr=c.Uniform();
    double y=a.Uniform()*2*pi;        
    if(pr < -sin(y) )
      y-=pi;
    if(y<0) y+=2*pi;
    else if(y>2*pi) y=fmod(y,2*pi);
    rf->Fill(y);

  }

  TH1F *res=(TH1F*)rf->Clone("res");
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);
  c4=new TCanvas();
  rf->DrawCopy();
  rf1->SetLineColor(2);
  fit->SetParameters(3332,3332,0);
  rf->Fit("fit");

  for(int i=1;i<=res->GetXaxis()->GetNbins();i++){
    double val = rf->GetBinContent(i);
    //fit->SetParameters(fit->GetParameter(0),fit->GetParameter(1),fit->GetParameter(2));
    double vfit = fit->Eval(res->GetXaxis()->GetBinCenter(i));
    if(val>0){
      res->SetBinContent(i,(val-vfit)/sqrt(val) );
      chi->Fill(pow((val-vfit)/sqrt(val),2));
    }
  }

  c8=new TCanvas();
  res->DrawCopy();
  c9=new TCanvas();
  chi->DrawCopy();
  chiPDF->SetParameter(0,fit->GetNDF());
  chiPDF->SetLineColor(2);
  //chiPDF->Draw("same");
  
  double base=fit->GetParameter(0);
  double amp=fit->GetParameter(1);
  return amp/base;
}


double wght(double e=1, double th=90)
{
  double pi=acos(-1);
  TH1F *rf2=new TH1F("rf2","randf",300,0,2*pi);
  TH1F *rfv=new TH1F("rfv","randf",300,0,2*pi);
  TF1 *fit2=new TF1("fit2","[0]+[1]*sin(x+[2])",0,2*pi);

  TH1F *chi2=new TH1F("chi2","chi2",100,0,10);
  TF1 *chiPDF2=new TF1("chiPDF2","pow(x,[0]/2-1)*exp(-x/2)/(pow(2,[0]/2)*TMath::Gamma([0]/2))",0,10);

  TRandom3 a(0);
  TRandom3 c(2);
  double pre=1.0/e*sin(th/180.0*pi);
  cout<<pre<<endl;

  for(int i=0;i<1000000;i++){
    double pr=c.Uniform();
    double y=a.Uniform()*2*pi;    
    rf2->Fill(y,1+sin(y));
    rfv->Fill(y);
  }

  TH1F *res2=(TH1F*)rf2->Clone("res2");
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);
  c5=new TCanvas();
  rf2->DrawCopy();
  fit2->SetParameters(3332,3332,0);
  rf2->Fit("fit");

  for(int i=1;i<=res2->GetXaxis()->GetNbins();i++){
    double val = rf2->GetBinContent(i);
    //fit2->SetParameters(fit2->GetParameter(0),fit2->GetParameter(1),fit2->GetParameter(2));
    double vfit = fit2->Eval(res2->GetXaxis()->GetBinCenter(i));
    // cout<<i<<" "<<val<<" "<<vfit<<" "<<endl;
    // std::cin.ignore();
    double dval=sqrt(rfv->GetBinContent(i))*(1+sin(rfv->GetXaxis()->GetBinCenter(i)));
    if(val>0){
      res2->SetBinContent(i,(val-vfit)/dval );
      chi2->Fill(pow((val-vfit)/dval,2));
    }
  }

  c6=new TCanvas();
  res2->DrawCopy();
  c7=new TCanvas();
  chi2->Draw();
  chi->SetLineColor(2);
  chi->Draw("same");
  //chiPDF2->SetParameter(0,fit2->GetChiquare()/fit2->GetNDF());
  chiPDF2->SetLineColor(2);
  //chiPDF2->Draw();
  
  double base=fit->GetParameter(0);
  double amp=fit->GetParameter(1);
  return amp/base;
}
