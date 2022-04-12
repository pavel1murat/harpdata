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

  printf("JinrDataset::GetMomentumSlice: PMin, PMax: %10.3f %10.3f %3i\n",PMin, PMax, ind);
  
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

  printf("JinrDataset::GetThetaSlice: ThMin, ThMax: %10.3f %10.3f %3i\n",ThMin, ThMax, ind);

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

  if (xs < 0) return;
  int slice = GetThetaSlice(tmin,tmax);
  
  if (slice < 0) {
    printf(">>> JinrDataset::FillMomentumHistograms ERROR: tmin, tmax,theta_slice = %10.3f %10.3f %i\n",
	   tmin,tmax,slice);
  }
  else {
    float p = (pmin+pmax)/2;
    for (int ibeam=0; ibeam<kNBeamMomenta; ibeam++) {
      int bin = GetBinNumber(fHist.fD2xDpDtVsMomentum[0],p);
      if (bin > 0) {
	fHist.fD2xDpDtVsMomentum[slice]->SetBinContent(bin,xs );
	fHist.fD2xDpDtVsMomentum[slice]->SetBinError  (bin,exs);
      }
    }
  }
}

//-----------------------------------------------------------------------------
void JinrDataset::FillD3xDp3EkinHistograms() {
  // 1. get theta slice - index of the dsigma/dp histograms
  printf("JinrDataset::FillD3xDp3EkinHistograms ekin, d3xdp3,ed3xdp3: %10.3f %10.3f %10.3f\n",
	 ekin, d3xdp3,ed3xdp3);
  
  if (xs < 0) return;
  int slice = GetThetaSlice(tmin,tmax);
  
  if (slice < 0) {
    printf(">>> ERROR in JinrDataset::FillD3xDp3EkinHistograms: tmin, tmax,theta_slice = %10.3f %10.3f %i\n",
	   tmin,tmax,slice);
  }
  else {
    for (int ibeam=0; ibeam<kNBeamMomenta; ibeam++) {
      int bin = GetBinNumber(fHist.fD3xDp3VsEkin[0],ekin);
      printf("JinrDataset::FillD3xDp3EkinHistograms bin: %3i\n", bin);
      if (bin > 0) {
	fHist.fD3xDp3VsEkin[slice]->SetBinContent(bin,d3xdp3 );
	fHist.fD3xDp3VsEkin[slice]->SetBinError  (bin,ed3xdp3);
      }
    }
  }
}

//-----------------------------------------------------------------------------
// xsection vs theta
//-----------------------------------------------------------------------------
void JinrDataset::FillThetaHistograms() {
  
  if (xs < 0) return;

  int slice = GetMomentumSlice(pmin,pmax);

  if (slice < 0) {
    printf(">>> ERROR in JinrDataset::FillThetaHistograms: pmin, pmax, mom_slice = %10.3f %10.3f %i\n",
	   pmin,pmax,slice);
  }
  else {
    float theta = (tmin+tmax)/2;
    for (int ibeam=0; ibeam<kNBeamMomenta; ibeam++) {
      int bin = GetBinNumber(fHist.fD2xDpDtVsTheta[0],theta);
      if (bin > 0) {
	fHist.fD2xDpDtVsTheta[slice]->SetBinContent(bin,xs );
	fHist.fD2xDpDtVsTheta[slice]->SetBinError  (bin,exs);
      }
    }
  }
}

//-----------------------------------------------------------------------------
// xsection vs theta
//-----------------------------------------------------------------------------
void JinrDataset::FillD3xDp3ThetaHistograms() {
  printf(">>> JinrDataset::FillD3xDp3ThetaHistograms : pmin, pmax, thmin, thmax = %10.3f %10.3f %10.3f %10.3f\n",
	 pmin,pmax,tmin,tmax);
  
  if (xs < 0) return;

  int slice = GetMomentumSlice(pmin,pmax);

  if (slice < 0) {
    printf(">>> JinrDataset::FillD3xDp3ThetaHistograms ERROR: pmin, pmax, mom_slice = %10.3f %10.3f %i\n",
	   pmin,pmax,slice);
  }
  else {
    float theta = (tmin+tmax)/2;
    for (int ibeam=0; ibeam<kNBeamMomenta; ibeam++) {
      int bin = GetBinNumber(fHist.fD2xDpDtVsTheta[0],theta);
      printf(">>> JinrDataset::FillD3xDp3ThetaHistograms : theta, bin = %10.3f %3i\n",theta, bin);
      if (bin > 0) {
	fHist.fD3xDp3VsTheta[slice]->SetBinContent(bin,d3xdp3 );
	fHist.fD3xDp3VsTheta[slice]->SetBinError  (bin,ed3xdp3);
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
    0.00, 0.20, 0.40, 0.60, 0.80, 1.00, 1.20, 1.40, 1.60, 1.80,
    2.00, 2.20, 2.40, 2.60, 2.80, 3.00, 3.20
  };

  for (int i=0; i<kNThetaSlices+1; i++) {
    fTheta[i] = theta_limit[i];
  }
  
  for (int i=0; i<kNMomentumSlices+1; i++) {
    fMomentum[i] = momentum_limit[i];
  }

  for (int i=0; i<kNMomentumSlices+1; i++) {
    printf(" %7.2f",fMomentum[i]);
  }
  printf("\n");

  for (int i=0; i<kNThetaSlices+1; i++) {
    printf("%7.2f",fTheta[i]);
  }
  printf("\n");

  
}

//-----------------------------------------------------------------------------
void JinrDataset::BookHistograms() {
  char name[200], title[200];
  
  float mom_lower[kNMomentumSlices+1] = {
    0.00, 0.20, 0.40, 0.60, 0.80, 1.00, 1.20, 1.40, 1.60, 1.80, 2.00, 2.20, 2.40,
    2.60, 2.80, 3.00, 3.20
  };
  
  float ekin_lower[kNMomentumSlices+1] = {
    0.00, 0.10, 0.30, 0.50, 0.70, 0.90, 1.10, 1.30, 1.50, 1.70, 1.90, 2.10, 2.30,
    2.50, 2.70, 2.90, 3.10
  };
  
  TH1::AddDirectory(0);

  for (int i=0; i<kNThetaSlices; i++) {
    sprintf(name ,"d2sigma_dp_dth_vs_mom_%02i",i);
    sprintf(title,"JINR d2#sigma/dpd#theta vs P, %5.2f < #theta < %5.2f",fTheta[i],fTheta[i+1]);
    fHist.fD2xDpDtVsMomentum[i] = new TH1F(name,title,kNMomentumSlices,mom_lower);
    fHist.fD2xDpDtVsMomentum[i]->SetMarkerStyle(20);
    fHist.fD2xDpDtVsMomentum[i]->GetXaxis()->SetTitle("P, GeV/c");
    fHist.fD2xDpDtVsMomentum[i]->SetStats(0);

    sprintf(name ,"d3xdp3_vs_ekin_%02i",i);
    sprintf(title,"JINR (E/A) #times d3#sigma/dp3 vs E(kin), %5.2f < #theta < %5.2f",fTheta[i],fTheta[i+1]);
    fHist.fD3xDp3VsEkin[i] = new TH1F(name,title,kNMomentumSlices,ekin_lower);
    fHist.fD3xDp3VsEkin[i]->SetMarkerStyle(20);
    fHist.fD3xDp3VsEkin[i]->GetXaxis()->SetTitle("Ekin, GeV");
    fHist.fD3xDp3VsEkin[i]->SetStats(0);
  }

  for (int i=0; i<kNMomentumSlices; i++) {
    sprintf(name,"d2sigma_dp_dth_vs_th_%02i",i);
    sprintf(title,"JINR d^{2}#sigma/dpd#theta vs #theta, %4.2f < P < %4.2f",fMomentum[i],fMomentum[i+1]);
    fHist.fD2xDpDtVsTheta[i] = new TH1F(name,title,16,-0.05,3.15);
    fHist.fD2xDpDtVsTheta[i]->SetMarkerStyle(20);
    fHist.fD2xDpDtVsTheta[i]->GetXaxis()->SetTitle("#theta, rad");
    fHist.fD2xDpDtVsTheta[i]->SetStats(0);

    sprintf(name,"d3sigma_dp3_vs_th_%02i",i);
    sprintf(title,"JINR d^{3}#sigma/dp^{3} vs #theta, %4.2f < P < %4.2f",fMomentum[i],fMomentum[i+1]);
    fHist.fD3xDp3VsTheta[i] = new TH1F(name,title,16,-0.05,3.15);
    fHist.fD3xDp3VsTheta[i]->SetMarkerStyle(20);
    fHist.fD3xDp3VsTheta[i]->GetXaxis()->SetTitle("#theta, rad");
    fHist.fD3xDp3VsTheta[i]->SetStats(0);
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

  fNtuple   = new TNtuple("jinr","jinr","thmin:thmax:ekin:p:x:ex:pmin:pmax:ekmin:ekmax");
  fNtuple->ReadFile(Fn);

  InitLimits();
  BookHistograms();

  float a(.0);
  if      (fTarget == "C")  a = 12 ;
  else if (fTarget == "Ta") a = 181;

  float pion_mass(0.13957);  // charged pion mass
    
  float* var;
  float  p, e;

  int n = fNtuple->GetEntries();
    
  for (int i=0; i<n; i++) {
    fNtuple->GetEntry(i);
    var     = fNtuple->GetArgs();
    //    printf("%10.3f %10.3f %10.3f\n",var[0],var[1],var[2]);
    tmin    = var[0];
    tmax    = var[1];
    ekin    = var[2];
    p       = var[3];
    e       = ekin+pion_mass;
    d3xdp3  = var[4];			// d^3sigma/dp3 vs Ekin (original data)
    ed3xdp3 = var[5];			// error on that
    xs      = var[4]*(a/e)*(2*M_PI)*p*p/1.e3*sin((tmin+tmax)/2);  // convert millbarns to barns..
    exs     = var[5]*(a/e)*(2*M_PI)*p*p/1.e3*sin((tmin+tmax)/2);
    pmin    = var[6];
    pmax    = var[7];
    ekmin   = var[8];
    ekmax   = var[9];
    
    FillD3xDp3EkinHistograms ();
    FillD3xDp3ThetaHistograms();
    FillMomentumHistograms   ();
    FillThetaHistograms      ();
  }
}

TH1F* JinrDataset::GetMomentumHist(int BeamBin, int ThetaSlice   ) { 
  return fHist.fD2xDpDtVsMomentum [ThetaSlice];
}
  
TH1F* JinrDataset::GetThetaHist   (int BeamBin, int MomentumSlice) {
  return fHist.fD2xDpDtVsTheta [MomentumSlice];
}
  

