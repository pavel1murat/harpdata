///////////////////////////////////////////////////////////////////////////////
// example
// HARP datasets: ID=1
// JINR datasets: ID=2
//
// angular bins :
// bin     0            1          2          3         4         5          6          7           8         9
// JINR 0.00-0.17  0.17-0.35  0.35-0.52  0.52-0.70
// HARP 0.35-0.55  0.55-0.75  0.75-0.95  0.95-1.05  1.05-1.15  1.15-1.35  1.35-1.55  1.55-1.75  1.75-1.95  1.95-2.15
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void test01() {
  Harp* h = new Harp();

  HarpDataset* dh1 = (HarpDataset*) h->GetDataset(1,"proton","Ta","pi-");
  dh1->fHist.fXsVsTheta[2][0]->Draw();

  dj1->fHist.fXsVsTheta[0]->Draw();

  HarpDataset* dh2 = (HarpDataset*) h->GetDataset(1,"proton","Ta","pi-");
  JinrDataset* dj2 = (JinrDataset*) h->GetDataset(2,"proton","Ta","pi-");

  // compare momentum distributions JINR:[0.52-0.70] vs HARP:[0.55-0.75]
  dj2->fHist.fD2xDpDtVsMomentum[3]->Draw();
  dh2->fHist.fXsVsMomentum[2][1]->Draw("same");

  // cross-check: d3x/dp3 Ekin distribution - JINR in the first angular bin
  dj2->fHist.fD3xDp3VsEkin[0]->Draw();
  
}
