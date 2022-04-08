///////////////////////////////////////////////////////////////////////////////
// example
///////////////////////////////////////////////////////////////////////////////

void test01() {
  Harp* h = new Harp();

  HarpDataset* d1 = (HarpDataset*) h->GetDataset(1,"proton","Ta","pi-");
  d1->fHist.fXsVsTheta[2][0]->Draw();

  JinrDataset* d2 = (JinrDataset*) h->GetDataset(1,"proton","Ta","pi-");
  d2->fHist.fXsVsTheta[0]->Draw()
}
