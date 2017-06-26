//

#ifndef __harp_harp_hh__
#define __harp_harp_hh__

#include "harp/HarpDataset.hh"

class Harp {
protected:
					// proton beam data, Ta target
  HarpDataset *fProtTaPim;
  HarpDataset *fProtTaPip;
					// proton beam data, Pb target
  HarpDataset *fProtPbPim;
  HarpDataset *fProtPbPip;
					// so far, nothing else
public:  
  Harp ();
  ~Harp();
  
  int InitDatasets();

  HarpDataset* GetDataset(const char* Beam, const char* Target, const char* Secondary);
  
};

#endif
