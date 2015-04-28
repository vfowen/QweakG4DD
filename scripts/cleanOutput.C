void cleanOutput(){
  
  string patern="V_1160_010.00*";
  cout<<"removeSegmentation"<<endl;
  removeSegmentation(patern);
  cout<<"Log files don't exit"<<endl;
  removeNoLog(patern);
}

void removeSegmentation(string pat){
  gSystem->Exec(Form("tail %s/log/log.out | grep -B 10 Segmentation | grep '==>' > z_Seg.lst",pat.c_str()));

  ifstream fin("z_Seg.lst");
  string data;
  while(fin>>data){//==>
    fin>>data;//get folder
    TString file(data.c_str());
    file.Remove(file.First('/'),file.Length());
    gSystem->Exec(Form("rm -rf %s",file.Data()));
    cout<<data<<" removing folder "<<file.Data()<<endl;
    fin>>data;// <==
  }
  fin.close();
  gSystem->Exec("rm -rf z_Seg.lst");
}


void removeNoLog(string pat){
  gSystem->Exec(Form("ls -d %s > z_log.lst",pat.c_str()));

  ifstream fin("z_log.lst");
  string data;
  while(fin>>data){
    data+="/log/log.out";
    ifstream tst(data.c_str(),ios::in);
    if(!tst.good()){    
      TString file(data.c_str());
      file.Remove(file.First('/'),file.Length());
      gSystem->Exec(Form("rm -rf %s",file.Data()));
      cout<<data<<" removing folder "<<file.Data()<<endl;
    }
    else tst.close();
  }
  fin.close();
  gSystem->Exec("rm -rf z_log.lst");
}
