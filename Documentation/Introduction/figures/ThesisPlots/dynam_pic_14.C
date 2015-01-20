void dynam_pic_14()
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
  el = new TEllipse(107.92+xmove,68.82+ymove,4,17/4);el->SetFillColor(33);el->SetFillStyle(1001);el->Draw();
  l = new TLine(38.34+xmove,53.74+ymove,118.12+xmove,97.54+ymove); l->Draw();
  l = new TLine(40+xmove,26+ymove,120+xmove,26+ymove); l->Draw();
  l = new TLine(46+xmove,40+ymove,114+xmove,40+ymove); l->Draw();
  l = new TLine(40+xmove,26+ymove,120+xmove,26+ymove); l->Draw();
  l = new TLine(123.76+xmove,83.89+ymove,110.6+xmove,71.66+ymove); l->Draw();
  l = new TLine(104.97+xmove,66.54+ymove,91+xmove,54.31+ymove); l->Draw();
  l = new TLine(120+xmove,54+ymove,90.74+xmove,54+ymove); l->Draw();
  TCurlyLine *zb1 = new TCurlyLine(90.74+xmove, 54+ymove, 76.24+xmove, 40+ymove);
  zb1->SetWavy();
  zb1->Draw();
  
  /*  
  t.DrawLatex(40+xmove,48+ymove,"l");
  t.DrawLatex(40+xmove,40+ymove,"n");
  t.DrawLatex(40+xmove,30+ymove,"m");

  t.DrawLatex(120+xmove,48+ymove,"i");
  t.DrawLatex(120+xmove,40+ymove,"j");
  t.DrawLatex(120+xmove,30+ymove,"k");

  t.DrawLatex(120+xmove,94+ymove,"#pi");
  t.DrawLatex(120+xmove,86+ymove,"#bar{#pi}");  


  t.DrawLatex(27+xmove,51+ymove,"d(u)");
  t.DrawLatex(27+xmove,40+ymove,"u(d)");
  t.DrawLatex(27+xmove,28+ymove,"d(u)");

  t.DrawLatex(133+xmove,51+ymove,"u(d)");
  t.DrawLatex(133+xmove,40+ymove,"u(d)");
  t.DrawLatex(133+xmove,28+ymove,"d(u)");

  t.DrawLatex(133+xmove,97+ymove,"d(u)");
  t.DrawLatex(134+xmove,87+ymove,"#bar{u}(#bar{d})");  
  */
  c1->Update();
  gStyle->SetLineWidth(linsav);
}
