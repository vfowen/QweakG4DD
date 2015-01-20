void feynman01()
{
   //
   // To see the output of this macro, click begin_html <a href="gif/feynman.gif">here</a>. end_html
   //
   TCanvas *c1 = new TCanvas("c1", "A canvas", 10,10, 600, 350);
   c1->Range(0, 0, 140, 70);
   Int_t linsav = gStyle->GetLineWidth();
   gStyle->SetLineWidth(3);
   TLatex t;
   t.SetTextAlign(22);
   t.SetTextSize(0.05);
   TLine * l;
   TArrow *a;
   TEllipse *el;
   a = new TArrow(10,30,22,42,0.05,"|>");a->SetFillColor(1);a->Draw();
   l = new TLine(10,30,30,50); l->Draw();
   el = new TEllipse(35,50,5,5);el->SetFillColor(1);el->SetFillStyle(3004);el->Draw();
   a = new TArrow(60,30,50,20,0.05,"|>");a->SetFillColor(1);a->Draw();
   l = new TLine(40, 10, 60, 30); l->Draw();
   a = new TArrow(40,50,52,38,0.05,"|>");a->SetFillColor(1);a->Draw();
   l = new TLine(40, 50, 60, 30); l->Draw();
   t.DrawLatex(10,25,"#bar{q} ,k_{4}");
   t.DrawLatex(40,5,"q ,k_{3}");
   t.DrawLatex(52,43,"P");
   t.DrawLatex(35,58,"#Gamma^{#rho} #tilde{f} (-#vec{p},-#vec{k}_{4}) ");

   TCurlyLine *zb1 = new TCurlyLine(60, 30, 72, 30);
   zb1->SetWavy();
   zb1->Draw();
   a = new TArrow(73,30,74,30,0.05,"|>");a->SetFillColor(1);a->Draw();
   TCurlyLine *zb2 = new TCurlyLine(73, 30, 85, 30);
   zb2->SetWavy();
   zb2->Draw();
   t.DrawLatex(72.5,35,"k_{1}-k_{2}");
   
   a = new TArrow(105,50,93,38,0.05,"|>");a->SetFillColor(1);a->Draw();
   l = new TLine(85, 30, 105, 50); l->Draw();
   a = new TArrow(85,30,95,20,0.05,"|>");a->SetFillColor(1);a->Draw();
   l = new TLine(85, 30, 105, 10); l->Draw();
   t.DrawLatex(105,52,"q' ,k_{2}");
   t.DrawLatex(105,5,"q' ,k_{1}");


   c1->Update();
   gStyle->SetLineWidth(linsav);
}
