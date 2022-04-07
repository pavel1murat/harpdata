///////////////////////////////////////////////////////////////////////////////
// JinrDataset: data for a given beam, target, and output particle type (pi-, pi+)
// 1 incident beam bin:  10 GeV/c
//
//
// for the proton beam and pi- outpu
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
// 4 angular slices:
//
/* 
| th_min (deg) | th_max (deg | th_min(rad) | th_max(rad |
|--------------+-------------+-------------+------------|
|            0 |          10 |        0.00 |       0.17 |
|           10 |          20 |        0.17 |       0.35 |
|           20 |          30 |        0.35 |       0.52 |
|           30 |          40 |        0.52 |       0.70 |
|           40 |          50 |        0.70 |       0.87 |
|           50 |          60 |        0.87 |       1.05 |
|           60 |          70 |        1.05 |       1.22 |
|           70 |          80 |        1.22 |       1.40 |
|           80 |          90 |        1.40 |       1.57 |
|           90 |         110 |        1.57 |       1.92 |
|          110 |         130 |        1.92 |       2.27 |
|          130 |         180 |        2.27 |       3.14 |
|--------------+-------------+-------------+------------|
*/
//-----------------------------------------------------------------------------
#ifndef __jinr_dataset_hh__
#define __jinr_dataset_hh__

#include "TH1.h"
#include "TString.h"
#include "TNtuple.h"

#include "Dataset.hh"

class JinrDataset : public Dataset {
public:
  enum { kNMomentumSlices = 15 };
  enum { kNThetaSlices    =  4 };

  struct Hist_t {
    TH1F*    fXsVsTheta    [kNMomentumSlices]; // momentum slices
    TH1F*    fXsVsMomentum [kNThetaSlices   ]; // theta    slices
  };

public:
  Hist_t   fHist;
					   // data
  float    tmin;
  float    tmax;
  float    pmin;
  float    pmax;
  float    xs ;			   // cross sections (3,5,8,12 GeV)
  float    exs;			   // cross section errors

  float    fTheta   [kNThetaSlices+1   ];
  float    fMomentum[kNMomentumSlices+1];

  JinrDataset();
  JinrDataset(int ID, const char* Beam, const char* Target, const char* Particle, const char* Fn);
  
  virtual void  BookHistograms();
  virtual void  FillMomentumHistograms();
  virtual void  FillThetaHistograms   ();

  virtual int   GetMomentumSlice(float PMin , float PMax );
  virtual int   GetThetaSlice   (float ThMin, float ThMax);
  virtual int   GetBinNumber    (TH1*  Hist , float X    );

  virtual void  InitLimits();

  virtual TH1F* GetMomentumHist(int BeamBin, int ThetaSlice);
  
  virtual TH1F* GetThetaHist   (int BeamBin, int MomentumSlice);
};

#endif
