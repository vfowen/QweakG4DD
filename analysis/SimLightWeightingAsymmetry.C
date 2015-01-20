void SimLightWeightingAsymmetry ()
{
  // Create and load the chain
  TChain *QweakSimG4_Tree = new TChain("QweakSimG4_Tree");
  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan/myLightWeightScan_*.root");

  // Split the data into n chunks to calculate uncertainties
  Int_t n = 10;
  Int_t nentries = QweakSimG4_Tree->GetEntries();

  // Mean values, RMS values, both weighted and unweighted
  Double_t mean_asym = 0.0;
  Double_t mean_asym_w = 0.0;
  Double_t sigma_asym = 0.0;
  Double_t sigma_asym_w = 0.0;
  Double_t mean_q2 = 0.0;
  Double_t mean_q2_w = 0.0;
  Double_t sigma_q2 = 0.0;
  Double_t sigma_q2_w = 0.0;

  // Loop over chunks
  for (Int_t i = 0; i < n; i++) {
    // Determine starting and ending entry for this chunk
    Int_t n1 = nentries / n * i;
    Int_t n2 = nentries / n * (i+1);

    // Draw a histogram of the asymmetry (in ppm) weighted by cross section
    QweakSimG4_Tree->Draw("1000*Primary.Asymmetry >> h_asym",Form("Primary.CrossSection * (%d < Entry$) * (Entry$ < %d)",n1,n2));
    // Draw a histogram of the asymmetry (in ppm) weighted by cross section and total number of PEs (all octants)
    QweakSimG4_Tree->Draw("1000*Primary.Asymmetry >> h_asym_w",Form("Primary.CrossSection * Cerenkov.PMT.PMTTotalNbOfPEs * (%d < Entry$) * (Entry$ < %d)",n1,n2));

    // Add mean for this chunk to sum of means
    mean_asym += h_asym->GetMean();
    mean_asym_w += h_asym_w->GetMean();
    // Add mean squared for this chunck to sum of mean squares
    sigma_asym += h_asym->GetMean() * h_asym->GetMean();
    sigma_asym_w += h_asym_w->GetMean() * h_asym_w->GetMean();

    // Draw a histogram of the Q2 (in ppm) weighted by cross section
    QweakSimG4_Tree->Draw("1000*Primary.PrimaryQ2 >> h_q2",Form("Primary.CrossSection * (%d < Entry$) * (Entry$ < %d)",n1,n2));
    // Draw a histogram of the Q2 (in ppm) weighted by cross section and total number of PEs (all octants)
    QweakSimG4_Tree->Draw("1000*Primary.PrimaryQ2 >> h_q2_w",Form("Primary.CrossSection * Cerenkov.PMT.PMTTotalNbOfPEs * (%d < Entry$) * (Entry$ < %d)",n1,n2));

    // Add mean for this chunk to sum of means
    mean_q2 += h_q2->GetMean();
    mean_q2_w += h_q2_w->GetMean();
    // Add mean squared for this chunck to sum of mean squares
    sigma_q2 += h_q2->GetMean() * h_q2->GetMean();
    sigma_q2_w += h_q2_w->GetMean() * h_q2_w->GetMean();

    // Chunk number: from event -- to event, asymmetry and weighted asymmetry, Q2 and weighted Q2
    cout << i << ": " << n1 << "--" << n2 << ", " 
		<< "A_PV = " << h_asym->GetMean() << ", " << h_asym_w->GetMean() << " ppb, " 
		<< "Q^2 = " << h_q2->GetMean() << ", " << h_q2_w->GetMean() << " m(GeV^2)" << endl;
  }

  // Turn sum of means into mean of all chunks
  mean_asym /= n;
  mean_asym_w /= n;
  // Turn sum of mean squared into uncertainty on mean of all chunks
  sigma_asym = sqrt(sigma_asym / n - mean_asym * mean_asym);
  sigma_asym_w = sqrt(sigma_asym_w / n - mean_asym_w * mean_asym_w);
  // Percent difference between mean asymmetries
  Double_t correction_asym = mean_asym_w/mean_asym - 1;
  // Uncertainty on percent difference between mean asymmetries
  Double_t d_correction_asym = (mean_asym_w/mean_asym)*sqrt(pow(sigma_asym/mean_asym,2)+pow(sigma_asym_w/mean_asym_w,2));
  cout << "asymmetry(unweighted) = " << mean_asym << " +/- " << sigma_asym << " ppb" << endl;
  cout << "asymmetry(weighted) = " << mean_asym_w << " +/- " << sigma_asym_w << " ppb" << endl;
  cout << "asymmetry(weighted)/asymmetry(unweighted) - 1 = " << 100*correction_asym << "% +/- " << 100*d_correction_asym << "%" << endl;

  // Turn sum of means into mean of all chunks
  mean_q2 /= n;
  mean_q2_w /= n;
  // Turn sum of mean squared into uncertainty on mean of all chunks
  sigma_q2 = sqrt(sigma_q2 / n - mean_q2 * mean_q2);
  sigma_q2_w = sqrt(sigma_q2_w / n - mean_q2_w * mean_q2_w);
  // Percent difference between mean Q2
  Double_t correction_q2 = mean_q2_w/mean_q2 - 1;
  // Uncertainty on percent difference between mean Q2
  Double_t d_correction_q2 = (mean_q2_w/mean_q2)*sqrt(pow(sigma_q2/mean_q2,2)+pow(sigma_q2_w/mean_q2_w,2));
  cout << "Q^2(unweighted) = " << mean_q2 << " +/- " << sigma_q2 << " m(GeV)^2" << endl;
  cout << "Q^2(weighted) = " << mean_q2_w << " +/- " << sigma_q2_w  << " m(GeV)^2" << endl;
  cout << "Q^2(weighted)/Q^2(unweighted) - 1 = " << 100*correction_q2 << "% +/- " << 100*d_correction_q2 << "%" << endl;

  cout << "correction(asymmetry)/correction(Q^2) = " << correction_asym/correction_q2 << " +/- "
		<< sqrt(pow(d_correction_asym/correction_asym,2)+pow(d_correction_q2/correction_q2,2)) << endl;
}
