///////////////////////////////////////////////////////////////////////////////
// references:
// 1: PhysRevC.77.055207 : HARP Official Collaboration (HARP-OC)
// 2: JINR P1-91-191     : 
///////////////////////////////////////////////////////////////////////////////

#ifndef __harp_harp_hh__
#define __harp_harp_hh__

#include "harp/HarpDataset.hh"

class Harp {
protected:

  TObjArray*  fListOfDatasets;
public:  
  Harp ();
  ~Harp();
  
  int InitDatasets();

  Dataset* GetDataset(int ID, const char* Beam, const char* Target, const char* Particle);
  
};

#endif
