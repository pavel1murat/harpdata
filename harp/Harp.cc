//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

#include "harp/Harp.hh"
#include "harp/JinrDataset.hh"

//-----------------------------------------------------------------------------
Harp::Harp() {
  fListOfDatasets = new TObjArray();
  InitDatasets();
}

//-----------------------------------------------------------------------------
Harp::~Harp() {
}

//-----------------------------------------------------------------------------
int Harp::InitDatasets() {
  Dataset* ds;
  const char* HarpDataDir = "./harpdata/data";

//-----------------------------------------------------------------------------
// official HARP datasets for Pb and Ta
//-----------------------------------------------------------------------------
  ds = new HarpDataset(1,"proton","Ta","pi-",
		       Form("%s/PhysRevC.77.055207/harp_prot_Ta_pim_data.txt",HarpDataDir));
  fListOfDatasets->Add(ds);

  ds = new HarpDataset(1,"proton","Ta","pi+",
		       Form("%s/PhysRevC.77.055207/harp_prot_Ta_pip_data.txt",HarpDataDir));
  fListOfDatasets->Add(ds);

  ds = new HarpDataset(1,"proton","Pb","pi-",
		       Form("%s/PhysRevC.77.055207/harp_prot_Pb_pim_data.txt",HarpDataDir));
  fListOfDatasets->Add(ds);

  ds = new HarpDataset(1,"proton","Pb","pi+",
		       Form("%s/PhysRevC.77.055207/harp_prot_Pb_pip_data.txt",HarpDataDir));
  fListOfDatasets->Add(ds);
//-----------------------------------------------------------------------------
// JINR 1991 datasets : measured are (E/A) d^3sigma/dp^3
//-----------------------------------------------------------------------------
  ds = new JinrDataset(2,"proton","C","pi-",
		       Form("%s/jinr-p1-91-191/jinr-p1-91-191-C.dat",HarpDataDir));
  fListOfDatasets->Add(ds);

  ds = new JinrDataset(2,"proton","Ta","pi-",
		       Form("%s/jinr-p1-91-191/jinr-p1-91-191-Ta.dat",HarpDataDir));
  fListOfDatasets->Add(ds);

  return 0;
}

//-----------------------------------------------------------------------------
Dataset* Harp::GetDataset(int ID, const char* Beam, const char* Target, const char* Particle) {
  Dataset* dset(nullptr);

  TString beam, target, part;

  int nds = fListOfDatasets->GetEntriesFast();
  for (int i=0; i<nds; i++) {
    Dataset* ds = (Dataset*) fListOfDatasets->UncheckedAt(i);
    if ((ds->ID() == ID) and (ds->Beam() == Beam) and
	(ds->Target() == Target) and (ds->Particle() == Particle)) {
      dset = ds;
      break;
    }
  }

  if (dset == nullptr) {
    printf ("ERROR: data for beam=%s target=%s secondary=%s are not yet available. BAIL OUT\n",
	    Beam,Target,Particle);
  }

  return dset;
}

