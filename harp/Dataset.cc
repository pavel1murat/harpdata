//
#include "harp/Dataset.hh"

//-----------------------------------------------------------------------------
Dataset::Dataset() {
}

//-----------------------------------------------------------------------------
int Dataset::GetBinNumber(TH1* Hist, float X) {
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
void Dataset::FillMomentumHistograms() {
  printf("Dataset::FillMomentumHistograms undefined\n");
}

//-----------------------------------------------------------------------------
// xsection vs theta
//-----------------------------------------------------------------------------
void Dataset::FillThetaHistograms() {
  
  printf("Dataset::FillThetaHistograms undefined\n");
}

//-----------------------------------------------------------------------------
void Dataset::InitLimits() {
  printf("Dataset::InitLimits undefined\n");
}

//-----------------------------------------------------------------------------
void Dataset::BookHistograms() {
  printf("Dataset::BookHistograms undefined\n");
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
Dataset::Dataset(int ID, const char* Beam, const char* Target, const char* Particle, const char* Fn) : TObject() {
  fID       = ID;
  fBeam     = Beam;
  fTarget   = Target;
  fParticle = Particle;
  fFn       = Fn;
}
