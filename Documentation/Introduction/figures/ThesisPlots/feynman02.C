void feynman02()
{
   //
   // To see the output of this macro, click begin_html <a href="gif/feynman.gif">here</a>. end_html
   //
  Int_t xmove = 0;
  Int_t ymove = -5;

   TCanvas *c1 = new TCanvas("c1", "A canvas", 10,10, 600, 450);
   c1->Range(0, 0, 140, 70);
   Int_t linsav = gStyle->GetLineWidth();
   gStyle->SetLineWidth(3);
   TLatex t;
   t.SetTextAlign(22);
   t.SetTextSize(0.05);
   TLine * l;
   TArrow *a;
   TEllipse *el;

   el = new TEllipse(30+xmove,58+ymove,5.64,4.31);el->SetFillColor(33);el->SetFillStyle(1001);el->Draw();
   
   a = new TArrow(66.68+xmove,68.51+ymove,48.12+xmove,64.53+ymove,0.04,"|>");a->SetFillColor(1);a->SetAngle(30);a->Draw();
   l = new TLine(33.79+xmove,61.37+ymove,48.12+xmove,64.53+ymove); l->Draw();
   a = new TArrow(34.2+xmove,55.34+ymove,47+xmove,52.65+ymove,0.04,"|>");a->SetFillColor(1);a->SetAngle(30);a->Draw();
   l = new TLine(46+xmove,52.85+ymove,60+xmove,50+ymove); l->Draw();
   a = new TArrow(60+xmove,50+ymove,77.5+xmove,52.5+ymove,0.04,"|>");a->SetFillColor(1);a->SetAngle(30);a->Draw();
   l = new TLine(76.5+xmove,52.35+ymove,95+xmove,55+ymove); l->Draw();
   TCurlyLine *zb1 = new TCurlyLine(60+xmove, 50+ymove, 80+xmove, 20+ymove);
   zb1->SetWavy();
   zb1->Draw();
   a = new TArrow(50+xmove,15+ymove,65+xmove,17.5+ymove,0.04,"|>");a->SetFillColor(1);a->SetAngle(30);a->Draw();
   l = new TLine(64+xmove,17.333+ymove,80+xmove,20+ymove); l->Draw();
   a = new TArrow(80+xmove,20+ymove,95+xmove,17.5+ymove,0.04,"|>");a->SetFillColor(1);a->SetAngle(30);a->Draw();
   l = new TLine(94+xmove,17.6+ymove,110+xmove,15+ymove); l->Draw();

   t.DrawLatex(70+xmove,71+ymove,"#bar{q},k_{4}");
   t.DrawLatex(98+xmove,58+ymove,"q ,k_{3}");
   t.DrawLatex(48+xmove,56+ymove,"S^{+}(-k_{4})");   
   t.DrawLatex(20+xmove,66+ymove,"#Gamma^{#rho} #tilde{f} (2|#vec{k}_{4}|) ");
   t.DrawLatex(85+xmove,35+ymove,"D^{#mu#nu}_{Z}(k_{1}-k_{2})");   
   t.DrawLatex(113+xmove,18+ymove,"q' ,k_{1}");
   t.DrawLatex(47+xmove,18+ymove,"q' ,k_{2}");


   c1->Update();
   gStyle->SetLineWidth(linsav);
}
