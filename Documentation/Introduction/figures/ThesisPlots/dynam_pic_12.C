void dynam_pic_12()
{
  Int_t xmove = 0;
  Int_t ymove = 0;

  TCanvas *c1 = new TCanvas("c1", "A canvas", 10,10, 600, 450);
  c1->Range(0, 0, 160, 120);
  Int_t linsav = gStyle->GetLineWidth();
  gStyle->SetLineWidth(3);
  TLatex t;
  t.SetTextAlign(22);
  t.SetTextSize(0.05);
  TLine * l;
  TArrow *a;
  TEllipse *el;
  
  el = new TEllipse(40+xmove,40+ymove,6,14);el->Draw();
  el = new TEllipse(120+xmove,40+ymove,6,14);el->Draw();
  el = new TEllipse(120+xmove,90+ymove,6,8);el->Draw();
  el = new TEllipse(107.65+xmove,76.78+ymove,4,17/4);el->SetFillColor(33);el->SetFillStyle(1001);el->Draw();

  l = new TLine(40+xmove,54+ymove,120+xmove,54+ymove); l->Draw();
  l = new TLine(46+xmove,40+ymove,114+xmove,40+ymove); l->Draw();
  l = new TLine(40+xmove,26+ymove,120+xmove,26+ymove); l->Draw();

  l = new TLine(111.41+xmove,78.48+ymove,120.81+xmove,82.18+ymove); l->Draw();
  l = new TLine(94.23+xmove,71.66+ymove,104.16+xmove,75.36+ymove); l->Draw();
  l = new TLine(116.24+xmove,96.4+ymove,94.23+xmove,71.94+ymove); l->Draw();

  TCurlyLine *zb1 = new TCurlyLine(94.5+xmove, 71.66+ymove, 74.9+xmove, 54.31+ymove);
  zb1->SetWavy();
  zb1->Draw();
  
  c1->Update();
  gStyle->SetLineWidth(linsav);
}
