//
#include "harp/JinrDataset.hh"

//-----------------------------------------------------------------------------
JinrDataset::JinrDataset() {
}

//-----------------------------------------------------------------------------  
int JinrDataset::GetMomentumSlice(float PMin, float PMax) {
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
int JinrDataset::GetThetaSlice(float ThMin, float ThMax) {
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
int JinrDataset::GetBinNumber(TH1* Hist, float X) {
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
void JinrDataset::FillMomentumHistograms() {
  // 1. get theta slice - index of the dsigma/dp histograms

  int slice = GetThetaSlice(tmin,tmax);
  
  if (slice < 0) {
    printf(">>> ERROR: theta_slice = %i\n",slice);
  }
  else {
    float p = (pmin+pmax)/2;
    for (int ibeam=0; ibeam<4; ibeam++) {
      int bin = GetBinNumber(fHist.fXsVsMomentum[0],p);
      if (bin > 0) {
	fHist.fXsVsMomentum[slice]->SetBinContent(bin,xs );
	fHist.fXsVsMomentum[slice]->SetBinError  (bin,exs);
      }
    }
  }
}

//-----------------------------------------------------------------------------
// xsection vs theta
//-----------------------------------------------------------------------------
void JinrDataset::FillThetaHistograms() {
  
  int slice = GetMomentumSlice(pmin,pmax);

  if (slice < 0) {
    printf(">>> ERROR: mom_slice = %i\n",slice);
  }
  else {
    float theta = (tmin+tmax)/2;
    for (int ibeam=0; ibeam<4; ibeam++) {
      int bin = GetBinNumber(fHist.fXsVsTheta[0],theta);
      if (bin > 0) {
	fHist.fXsVsTheta[slice]->SetBinContent(bin,xs );
	fHist.fXsVsTheta[slice]->SetBinError  (bin,exs);
      }
    }
  }
}

//-----------------------------------------------------------------------------
void JinrDataset::InitLimits() {
  float theta_limit[kNThetaSlices+1] = {
    0.00, 0.17, 0.35, 0.52, 0.70
  };

  float momentum_limit[kNMomentumSlices+1] = {
    0.20, 0.40, 0.60, 0.80, 1.00, 1.20, 1.40, 1.60, 1.80,
    2.00, 2.20, 2.40, 2.60, 2.80, 3.00, 3.20
  };

  for (int i=0; i<kNThetaSlices+1; i++) {
    fTheta[i] = theta_limit[i];
  }
  
  for (int i=0; i<kNMomentumSlices+1; i++) {
    fMomentum[i] = momentum_limit[i];
  }
  
}

//-----------------------------------------------------------------------------
void JinrDataset::BookHistograms() {
  char name[200], title[200];
  
  float mom_lower[] = {
    0.00, 0.20, 0.40, 0.60, 0.80, 1.00, 1.20, 1.40, 1.60, 1.80, 2.00, 2.20, 2.40,
    2.60, 2.80, 3.00, 3.20
  };
  
  TH1::AddDirectory(0);

  for (int i=0; i<kNThetaSlices; i++) {
    sprintf(name ,"d2sigma_dp_dth_vs_mom_%02i",i);
    sprintf(title,"d2#sigma/dpd#theta vs P, %5.2f < #theta < %5.2f",fTheta[i],fTheta[i+1]);
    fHist.fXsVsMomentum[i] = new TH1F(name,title,13,mom_lower);
    fHist.fXsVsMomentum[i]->SetMarkerStyle(20);
    fHist.fXsVsMomentum[i]->GetXaxis()->SetTitle("P, GeV/c");
    fHist.fXsVsMomentum[i]->SetStats(0);
  }

  for (int ibeam=0; ibeam<4; ibeam++) {
    for (int i=0; i<kNMomentumSlices; i++) {
      sprintf(name,"d2sigma_dp_dth_vs_th_%02i",i);
      sprintf(title,"d^{2}#sigma/dpd#theta vs #theta, %4.2f < P < %4.2f",fMomentum[i],fMomentum[i+1]);
      fHist.fXsVsTheta[i] = new TH1F(name,title,16,-0.05,3.15);
      fHist.fXsVsTheta[i]->SetMarkerStyle(20);
      fHist.fXsVsTheta[i]->GetXaxis()->SetTitle("#theta, rad");
      fHist.fXsVsTheta[i]->SetStats(0);
    }
  }
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
JinrDataset::JinrDataset(int ID, const char* Beam, const char* Target, const char* Particle, const char* Fn) {
  fID       = ID;
  fBeam     = Beam;
  fTarget   = Target;
  fParticle = Particle;
  fFn       = Fn;

  fNtuple   = new TNtuple("jinr","jinr","thmin:thmax:ekin:p:x:ex:pmin:pmax");
  fNtuple->ReadFile(Fn);

  InitLimits();
  BookHistograms();

  float a(.0);
  if      (fTarget == "C")  a = 12 ;
  else if (fTarget == "Ta") a = 181;

  float pion_mass(0.13957);  // charged pion mass
    
  float* var;
  float  ekin, p, e;

  int n = fNtuple->GetEntries();
    
  for (int i=0; i<n; i++) {
    fNtuple->GetEntry(i);
    var    = fNtuple->GetArgs();
    //    printf("%10.3f %10.3f %10.3f\n",var[0],var[1],var[2]);
    tmin   = var[0];
    tmax   = var[1];
    ekin   = var[2];
    p      = var[3];
    e      = ekin+pion_mass;
    xs     = var[ 4]*(a/e)*(2*M_PI)*p*p/1.e3;  // convert millbarns to barns..
    exs    = var[ 5]*(a/e)*(2*M_PI)*p*p/1.e3;
    pmin   = var[6];
    pmax   = var[7];
    
    FillMomentumHistograms();
    FillThetaHistograms   ();
  }
}

TH1F* JinrDataset::GetMomentumHist(int BeamBin, int ThetaSlice   ) { 
  return fHist.fXsVsMomentum [ThetaSlice];
}
  
TH1F* JinrDataset::GetThetaHist   (int BeamBin, int MomentumSlice) {
  return fHist.fXsVsTheta [MomentumSlice];
}
  

