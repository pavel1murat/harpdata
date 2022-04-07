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
#ifndef __dataset_hh__
#define __dataset_hh__

#include "TH1.h"
#include "TString.h"
#include "TNtuple.h"

class Dataset : public TObject {
public:

public:
  int      fID;                            // dataset ID
  TString  fBeam;
  TString  fTarget;			   // 
  TString  fParticle;			   // 
  TString  fFn;				   // filename
  TNtuple* fNtuple;			   // ntuple with the data

					   // data
  Dataset();
  Dataset(int ID, const char* Beam, const char* Target, const char* Particle, const char* Fn);
  
  virtual void  BookHistograms        ();
  virtual void  FillMomentumHistograms();
  virtual void  FillThetaHistograms   ();

  virtual int   GetMomentumSlice(float PMin,  float PMax ) = 0;
  virtual int   GetThetaSlice   (float ThMin, float ThMax) = 0;
  virtual int   GetBinNumber    (TH1* Hist, float X);

  virtual void  InitLimits();

  int      ID      () { return fID;       }
  TString& Beam    () { return fBeam;     }
  TString& Target  () { return fTarget;   }
  TString& Particle() { return fParticle; }
  
  virtual TH1F* GetMomentumHist(int BeamBin, int ThetaSlice) = 0;
  
  virtual TH1F* GetThetaHist   (int BeamBin, int MomentumSlice) = 0;
};

#endif
