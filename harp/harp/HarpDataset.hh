///////////////////////////////////////////////////////////////////////////////
// HarpDataset: data for a given beam, target, and output particle type (pi-, pi+)
// 4 incident beam bins: 0: 3 GeV, 1: 5 GeV, 2: 8 GeV, 3: 12 GeV
//
// angular histograms : 0.15 - 2.15 radians, 10 bins, 0.2 rad bin
// momentum histograms - variable binning:
//
// for the proton beam and pi+/pi- output HARP has 11 momentum slices:
//
// 0.10-0.15
// 0.15-0.20
// 0.20-0.25
// 0.25-0.30
// 0.30-0.35
// 0.35-0.40
// 0.40-0.45
// 0.45-0.50
// 0.50-0.60
// 0.60-0.70
// 0.70-0.80
//
// 9 angular slices:
//
// 0.35-0.55
// 0.55-0.75
// 0.75-0.95
// 0.95-1.15
// 1.15-1.35
// 1.35-1.55
// 1.55-1.75
// 1.75-1.95
// 1.95-2.15
//
//-----------------------------------------------------------------------------
#ifndef __harp_dataset_hh__
#define __harp_dataset_hh__

#include "TH1.h"
#include "TString.h"
#include "TNtuple.h"

#include "Dataset.hh"

class HarpDataset : public Dataset {
public:
  enum { kNBeamBins       =  4 };
  enum { kNMomentumSlices = 11 };
  enum { kNThetaSlices    =  9 };

  struct Hist_t {
    TH1F*    fD2xDpDtVsTheta    [kNBeamBins][kNMomentumSlices]; // momentum slices
    TH1F*    fD2xDpDtVsMomentum [kNBeamBins][kNThetaSlices]; // theta    slices
  };

public:
  Hist_t   fHist;
					   // data
  float    tmin;
  float    tmax;
  float    pmin;
  float    pmax;
  float    xs [4];			   // cross sections (3,5,8,12 GeV)
  float    exs[4];			   // cross section errors

  float    fTheta   [kNThetaSlices+1];
  float    fMomentum[kNMomentumSlices+1];

  HarpDataset();
  HarpDataset(int ID, const char* Beam, const char* Target, const char* Particle, const char* Fn);
  
  void  BookHistograms();
  void  FillMomentumHistograms();
  void  FillThetaHistograms   ();

  int   GetMomentumSlice(float PMin,  float PMax );
  int   GetThetaSlice   (float ThMin, float ThMax);
  int   GetBinNumber    (TH1* Hist, float X);

  void  InitLimits();

  TH1F* GetMomentumHist(int BeamBin, int ThetaSlice   ) {
    return fHist.fD2xDpDtVsMomentum [BeamBin][ThetaSlice];
  }
  
  TH1F* GetThetaHist   (int BeamBin, int MomentumSlice) {
    return fHist.fD2xDpDtVsTheta [BeamBin][MomentumSlice];
  }
  
};

#endif
