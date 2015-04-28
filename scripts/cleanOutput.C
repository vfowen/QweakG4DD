void cleanOutput(){
  string patern="";
  
}

void removeSegmentation(string pat){
  gSystem->Exec(Form("tail %s/log/log.out | grep -B 10 Segmentation | grep '==>' > z_Seg.lst",pat.c_str()));

  ifstream fin("z_Seg.lst");
  string data;
  while(fin>>data){
    TString file(data.c_str());
    file.Remove(0,file.First('_')-2);
    file.Remove(file.First('/'),file.Length());
    gSystem->Exec(Form("rm -rf %s",file.Data()));
  }
  
  gSystem->Exec("rm -rf z_Seg.lst");
}


void removeNoLog(string pat){
  gSystem->Exec(Form("ls %s/log/log.out > z_log.lst",pat.c_str()));

  ifstream fin("z_log.lst");
  string data;
  while(fin>>data){
    ifstream tst(data);
    if(!tst){    
      TString file(data.c_str());
      file.Remove(0,file.First('_')-2);
      file.Remove(file.First('/'),file.Length());
      gSystem->Exec(Form("rm -rf %s",file.Data()));
    }
  }  
  gSystem->Exec("rm -rf z_log.lst");
}
