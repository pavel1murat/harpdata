///////////////////////////////////////////////////////////////////////////////
// example
// HARP datasets: ID=1
// JINR datasets: ID=2
//
// angular bins :
// bin     0          1          2        3        4         5          6        7         8         9         10       11
// JINR 0.00-0.17 0.17-0.35 0.35-0.52 0.52-0.70 0.70-0.87 0.87-1.05 1.05-1.22 1.22-1.40 1.40-1.57 1.57-1.92 1.92-2.27 2.27-3.14
//   deg  0.-10     10-20     20-30    30-40       40-50     50-60     60-70   70-80      80-90    90-110    110-130   130-180
//
// HARP
// 0: 0.35-0.55
// 1: 0.55-0.75
// 2: 0.75-0.95
// 3: 0.95-1.05
// 4: 1.05-1.15
// 5: 1.15-1.35 <---
// 6: 1.35-1.55
// 7: 1.55-1.75
// 8: 1.75-1.95
// 9: 1.95-2.15
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

//-----------------------------------------------------------------------------
void test02() {
  HarpDataset* dh2 = (HarpDataset*) h->GetDataset(1,"proton","Ta","pi-");
  JinrDataset* dj2 = (JinrDataset*) h->GetDataset(2,"proton","Ta","pi-");
  dj2->fHist.fD2xDpDtVsTheta[0]->Draw("");
  dj2->fHist.fD2xDpDtVsTheta[1]->Draw("");
  dh2->fHist.fXsVsTheta[2][1]->Draw("");
  dh2->fHist.fXsVsTheta[2][2]->Draw("");
  dj2->fHist.fD2xDpDtVsTheta[1]->Draw("");
  dh2->fHist.fXsVsTheta[2][2]->Draw("same");

  dj2->fHist.fD2xDpDtVsTheta[0]->Draw("");
  dh2->fHist.fXsVsTheta[2][1]->Draw("");
  dj2->fHist.fD2xDpDtVsTheta[0]->Draw("");
  dh2->fHist.fXsVsTheta[2][1]->Draw("same");
  dh2->fHist.fXsVsTheta[2][0]->Draw("same");
}
