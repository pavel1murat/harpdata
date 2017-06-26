//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

#include "harp/Harp.hh"

//-----------------------------------------------------------------------------
Harp::Harp() {
  InitDatasets();
}

//-----------------------------------------------------------------------------
Harp::~Harp() {
}

//-----------------------------------------------------------------------------
int Harp::InitDatasets() {
  const char* HarpDataDir = "./harpdata/data";
  fProtTaPim = new HarpDataset("proton","Ta","pi-",Form("%s/harp_prot_Ta_pim_data.txt",HarpDataDir));
  fProtTaPip = new HarpDataset("proton","Ta","pi+",Form("%s/harp_prot_Ta_pip_data.txt",HarpDataDir));
  fProtPbPim = new HarpDataset("proton","Pb","pi-",Form("%s/harp_prot_Pb_pim_data.txt",HarpDataDir));
  fProtPbPip = new HarpDataset("proton","Pb","pi+",Form("%s/harp_prot_Pb_pip_data.txt",HarpDataDir));

  return 0;
}

//-----------------------------------------------------------------------------
HarpDataset* Harp::GetDataset(const char* Beam, const char* Target, const char* Secondary) {
  HarpDataset* ds(NULL);

  TString beam, target, part;
  
  if (strcmp(Beam,"proton") == 0) {
    if      (strcmp(Target,"Pb") == 0) {
      if      (strcmp(Secondary,"pi+") == 0) ds = fProtPbPip;
      else if (strcmp(Secondary,"pi-") == 0) ds = fProtPbPim;
    }
    else if (strcmp(Target,"Ta") == 0) {
      if      (strcmp(Secondary,"pi+") == 0) ds = fProtTaPip;
      else if (strcmp(Secondary,"pi-") == 0) ds = fProtTaPim;
    }
  }
  else {
    printf ("ERROR: data for beam=%s target=%s secondary=%s are not yet available. BAIL OUT\n",
	    Beam,Target,Secondary);
  }

  return ds;
}

