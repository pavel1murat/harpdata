//
#include "harp/HarpDataset.hh"

//-----------------------------------------------------------------------------
HarpDataset::HarpDataset() {
}

//-----------------------------------------------------------------------------  
int HarpDataset::GetMomentumSlice(float PMin, float PMax) {
  int ind(-1);

  for (int i=0; i<kNMomentumSlices; i++) {
    if (fabs(PMin-fMomentum[i]) < 0.01) {
      ind = i;
      break;
    }
  }

  return ind;
}
  
//-----------------------------------------------------------------------------  
int HarpDataset::GetThetaSlice(float ThMin, float ThMax) {
  int ind(-1);
  
  for (int i=0; i<kNThetaSlices; i++) {
    if (fabs(ThMin-fTheta[i]) < 0.01) {
      ind = i;
      break;
    }
  }

  return ind;
}

//-----------------------------------------------------------------------------
int HarpDataset::GetBinNumber(TH1* Hist, float X) {
  int bin(-1);
  float xmin, xmax;
  int nbins = Hist->GetNbinsX();
  for (int i=1; i<=nbins; i++) {
    xmin = Hist->GetBinLowEdge(i);
    xmax = xmin+Hist->GetBinWidth(i);
    if ((X>=xmin) && (X<xmax)) {
      bin = i;
      break;
    }
  }
  return bin;
}

//-----------------------------------------------------------------------------
void HarpDataset::FillMomentumHistograms() {
  // 1. get theta slice - index of the dsigma/dp histograms

  int slice = GetThetaSlice(tmin,tmax);
  
  if (slice < 0) {
    printf(">>> ERROR: theta_slice = %i\n",slice);
  }
  else {
    float p = (pmin+pmax)/2;
    for (int ibeam=0; ibeam<4; ibeam++) {
      int bin = GetBinNumber(fHist.fXsVsMomentum[ibeam][0],p);
      if (bin > 0) {
	fHist.fXsVsMomentum[ibeam][slice]->SetBinContent(bin,xs [ibeam]);
	fHist.fXsVsMomentum[ibeam][slice]->SetBinError  (bin,exs[ibeam]);
      }
    }
  }
}

//-----------------------------------------------------------------------------
// xsection vs theta
//-----------------------------------------------------------------------------
void HarpDataset::FillThetaHistograms() {
  
  int slice = GetMomentumSlice(pmin,pmax);

  if (slice < 0) {
    printf(">>> ERROR: mom_slice = %i\n",slice);
  }
  else {
    float theta = (tmin+tmax)/2;
    for (int ibeam=0; ibeam<4; ibeam++) {
      int bin = GetBinNumber(fHist.fXsVsTheta[ibeam][0],theta);
      if (bin > 0) {
	fHist.fXsVsTheta[ibeam][slice]->SetBinContent(bin,xs [ibeam]);
	fHist.fXsVsTheta[ibeam][slice]->SetBinError  (bin,exs[ibeam]);
      }
    }
  }
}

//-----------------------------------------------------------------------------
void HarpDataset::InitLimits() {
  float theta_limit[kNThetaSlices+1] = {
    0.35, 0.55, 0.75, 0.95, 1.15, 1.35, 1.55, 1.75, 1.95, 2.15
  };

  float momentum_limit[kNMomentumSlices+1] = {
    0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.60, 0.70, 0.80
  };


  for (int i=0; i<kNThetaSlices+1; i++) {
    fTheta[i] = theta_limit[i];
  }
  
  for (int i=0; i<kNMomentumSlices+1; i++) {
    fMomentum[i] = momentum_limit[i];
  }
  
}

//-----------------------------------------------------------------------------
void HarpDataset::BookHistograms() {
  char name[200], title[200];
  
  float mom_lower[] = {
    0.00, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.60, 0.70, 0.80
  };
  
  TH1::AddDirectory(0);

  for (int ibeam=0; ibeam<4; ibeam++) {
    for (int i=0; i<kNThetaSlices; i++) {
      sprintf(name ,"d2sigma_dp_dth_vs_mom_%i_%02i",ibeam,i);
      sprintf(title,"d2#sigma/dpd#theta vs P, %5.2f < #theta < %5.2f",fTheta[i],fTheta[i+1]);
      fHist.fXsVsMomentum[ibeam][i] = new TH1F(name,title,13,mom_lower);
      fHist.fXsVsMomentum[ibeam][i]->SetMarkerStyle(20);
      fHist.fXsVsMomentum[ibeam][i]->GetXaxis()->SetTitle("P, GeV/c");
      fHist.fXsVsMomentum[ibeam][i]->SetStats(0);
    }
  }

  for (int ibeam=0; ibeam<4; ibeam++) {
    for (int i=0; i<kNMomentumSlices; i++) {
      sprintf(name,"d2sigma_dp_dth_vs_th_%i_%02i",ibeam,i);
      sprintf(title,"d^{2}#sigma/dpd#theta vs #theta, %4.2f < P < %4.2f",fMomentum[i],fMomentum[i+1]);
      fHist.fXsVsTheta[ibeam][i] = new TH1F(name,title,16,-0.05,3.15);
      fHist.fXsVsTheta[ibeam][i]->SetMarkerStyle(20);
      fHist.fXsVsTheta[ibeam][i]->GetXaxis()->SetTitle("#theta, rad");
      fHist.fXsVsTheta[ibeam][i]->SetStats(0);
    }
  }
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
HarpDataset::HarpDataset(int ID, const char* Beam, const char* Target, const char* Particle, const char* Fn) {
  fID       = ID;
  fBeam     = Beam;
  fTarget   = Target;
  fParticle = Particle;
  fFn       = Fn;

  if (ID == 1) {
    fNtuple   = new TNtuple("harp","harp","tmin:tmax:pmin:pmax:x3:ex3:x5:ex5:x8:ex8:x12:ex12");
    fNtuple->ReadFile(Fn);

    InitLimits();
    BookHistograms();
  
    float* var;

    int n = fNtuple->GetEntries();
    for (int i=0; i<n; i++) {
      fNtuple->GetEntry(i);
      var    = fNtuple->GetArgs();
      //    printf("%10.3f %10.3f %10.3f\n",var[0],var[1],var[2]);
      tmin   = var[0];
      tmax   = var[1];
      pmin   = var[2];
      pmax   = var[3];
      // 4 cross sections - at 3,5,8, and 12 GeV/c
      xs [0] = var[ 4];
      exs[0] = var[ 5];
      xs [1] = var[ 6];
      exs[1] = var[ 7];
      xs [2] = var[ 8];
      exs[2] = var[ 9];
      xs [3] = var[10];
      exs[3] = var[11];
      
      FillMomentumHistograms();
      FillThetaHistograms   ();
    }
  }
    
}
