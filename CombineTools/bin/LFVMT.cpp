#include <string>
#include <map>
#include <set>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include "CombineHarvester/CombineTools/interface/CombineHarvester.h"
#include "CombineHarvester/CombineTools/interface/Observation.h"
#include "CombineHarvester/CombineTools/interface/Process.h"
#include "CombineHarvester/CombineTools/interface/Utilities.h"
#include "CombineHarvester/CombineTools/interface/Systematics.h"
#include "CombineHarvester/CombineTools/interface/BinByBin.h"

#include "TTree.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TLine.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLatex.h"
#include <TROOT.h>
#include <TStyle.h>
#include "TMath.h"

using namespace std;

double ComputeSumYLimit(double BranchingRatio);

int main(int argc, char* argv[]){

 string basepath = "$CMSSW_BASE/src/CombineHarvester/CombineTools/";
 string folder = "shapes_mt_BDT";
 string label = "Limit Plot";
 string lumi = "35.9";

 if (argc > 1)
   {
     int count=0;
     for (count = 1; count < argc; count++)
       {
	 if(strcmp(argv[count] ,"--l")==0) label = argv[count+1];
	 if(strcmp(argv[count] ,"--f")==0) folder = argv[count+1];
	 if(strcmp(argv[count] ,"--L")==0) lumi = argv[count+1];
       }
   }

 double intLumi = atof(lumi.c_str());
 printf("Luminosity: %.2f",intLumi);

 double MEDIAN[5];
 double ERR2DOWN[5];
 double ERRDOWN[5];
 double ERR2UP[5];
 double ERRUP[5];

 string appendix[5] = {"0Jet", "1Jet", "2JetGG", "2JetVBF", "Comb"};
 printf("Extended Table with uncertainties \n");
 printf("================================= \n");
 printf("Channel -2s -1s Median +1s +2s \n");
 printf("================================= \n");

 for (int i = 0; i < 5; i++)
   {
     string inputFile = "higgsCombineTest.AsymptoticLimits." + appendix[i] + ".mH125.root";
     TFile input((basepath + folder + "/" + inputFile).c_str(), "READONLY");

     TTree* limitTree = (TTree*)input.Get("limit"); limitTree->SetName("limitTree");
     Float_t quantileExpected;
     Double_t limit;
     limitTree->SetBranchAddress("limit", &limit);
     limitTree->SetBranchAddress("quantileExpected", &quantileExpected);
     Long64_t nentries = limitTree->GetEntries();
     for (Long64_t k = 0; k < nentries; k++)
       {
	 limitTree->GetEntry(k);
	 if(k==2) MEDIAN[i] = limit;
	 if(k==0) ERR2DOWN[i] = limit;
	 if(k==1) ERRDOWN[i] = limit;
	 if(k==3) ERRUP[i] = limit;
	 if(k==4) ERR2UP[i] = limit;
       }
   }

 printf(" \n\n\n SUMMARY TABLE\n");
 printf("=====================\n");

 printf("Expected 95%% CL limits on BR \n");
 printf("------------------------------\n");

 for (int i = 0; i < 5; i++) printf("\t %s", appendix[i].c_str());
 printf(" \n");
 for (int i = 0; i < 5; i++) printf("\t & $<$ %2.2f", MEDIAN[i]);

 printf(" \n\n\n YUKAWA LIMIT\n");
 printf("====================\n");

 double yukawa = sqrt(ComputeSumYLimit(MEDIAN[4]/100));
 printf("\t EXPECTED: Branching Ratio: <%2.2f :  Yukawa limit: < %2.6f \n", MEDIAN[4], yukawa);

 // Run I STYLE PLOT MAKING

 gStyle->SetOptFit(1);
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);

 TCanvas *PLOTLIMIT = new TCanvas("PLOTLIMIT", "BEST FIT", 400, 400);
 // 600, 22, 664, 763
 PLOTLIMIT->Range(-1.298202, -1.436207, 2.706292, 7.434483);
 PLOTLIMIT->SetFillColor(0);
 PLOTLIMIT->SetBorderMode(0);
 PLOTLIMIT->SetBorderSize(2);
 PLOTLIMIT->SetTickx(1);
 PLOTLIMIT->SetTicky(1);
 PLOTLIMIT->SetLeftMargin(0.2);
 PLOTLIMIT->SetRightMargin(0.05);
 PLOTLIMIT->SetTopMargin(0.12);
 PLOTLIMIT->SetBottomMargin(0.12);
 PLOTLIMIT->SetFrameFillStyle(0);
 PLOTLIMIT->SetFrameLineWidth(2);
 PLOTLIMIT->SetFrameBorderMode(0);
 PLOTLIMIT->SetFrameFillStyle(0);
 PLOTLIMIT->SetFrameLineWidth(2);
 PLOTLIMIT->SetFrameBorderMode(0);

 const Int_t ny = 5;
 string channels[ny] = {"#mu#tau_{h}", "#mu#tau_{h}, VBF","#mu#tau_{h}, 2 Jets","#mu#tau_{h}, 1 Jet", "#mu#tau_{h}, 0 Jets"};

 double y[5] = {0.5, 1.5, 2.5, 3.5, 4.5};
 double erry[5] = {0, 0, 0, 0, 0};

 // Reordering to keep most of the old macro
 double MEDIANplot[5] = {MEDIAN[4], MEDIAN[3], MEDIAN[2], MEDIAN[1], MEDIAN[0]};
 double ERR2DOWNplot[5] = {ERR2DOWN[4], ERR2DOWN[3], ERR2DOWN[2], ERR2DOWN[1], ERR2DOWN[0]};
 double ERRDOWNplot[5] = {ERRDOWN[4], ERRDOWN[3], ERRDOWN[2], ERRDOWN[1], ERRDOWN[0]};
 double ERR2UPplot[5] = {ERR2UP[4], ERR2UP[3], ERR2UP[2], ERR2UP[1], ERR2UP[0]};
 double ERRUPplot[5] = {ERRUP[4], ERRUP[3], ERRUP[2], ERRUP[1], ERRUP[0]};

 double R2DOWNplot[5] = {ERR2DOWN[4], ERR2DOWN[3], ERR2DOWN[2], ERR2DOWN[1], ERR2DOWN[0]};
 double RDOWNplot[5] = {ERRDOWN[4], ERRDOWN[3], ERRDOWN[2], ERRDOWN[1], ERRDOWN[0]};
 double R2UPplot[5] = {ERR2UP[4], ERR2UP[3], ERR2UP[2], ERR2UP[1], ERR2UP[0]};
 double RUPplot[5] = {ERRUP[4], ERRUP[3], ERRUP[2], ERRUP[1], ERRUP[0]};

 for (int i = 0; i < 5; i++)
   {
     ERR2DOWNplot[i] = -ERR2DOWNplot[i] + MEDIANplot[i];
     ERRDOWNplot[i] = -ERRDOWNplot[i] + MEDIANplot[i];
     ERRUPplot[i] = ERRUPplot[i] - MEDIANplot[i];
     ERR2UPplot[i] = ERR2UPplot[i] - MEDIANplot[i];
   }

 TString channels2[5];
 for(int i = 0; i < 5; i++)
   {
     channels2[i] = Form("#splitline{%s}{ #scale[0.8]{(%1.2f%%)}} ", channels[i].c_str(), MEDIANplot[i]);
   }

 PLOTLIMIT->cd();

 TH2F *h = new TH2F("h", "test", 1, -1.5, 14.5, 5, 0, 5);
 for (int j = 0; j < ny; j++) h->Fill(1, channels2[j], 0);
 h->SetXTitle("95% CL limit on #bf{#it{#Beta}}(H#rightarrow #mu#tau) %");
 h->GetXaxis()->SetLabelSize(0.04);
 h->GetXaxis()->SetTitleSize(0.05);
 h->GetYaxis()->SetLabelSize(0.05);
 h->Draw();
 h->GetYaxis()->CenterLabels();

 for (int i = 0; i < 5; i++)
   {
     TPave *pave = new TPave(R2DOWNplot[i], i + 0.75, R2UPplot[i], i + 0.25, 4, "br");
     pave->Draw();
     pave->SetBorderSize(0);
     pave->SetFillColor(kOrange);
     TPave *pave2 = new TPave(RDOWNplot[i], i + 0.75, RUPplot[i], i + 0.25, 4, "br");
     pave2->Draw();
     pave2->SetBorderSize(0);
     pave2->SetFillColor(kGreen+1);
   }

 TGraphAsymmErrors *GRAPHMEDIAN = new TGraphAsymmErrors(5, MEDIANplot, y, 0, 0, erry, erry);
 GRAPHMEDIAN->SetLineColor(kBlue); GRAPHMEDIAN->SetMarkerStyle(5); GRAPHMEDIAN->SetMarkerColor(kBlue+2); GRAPHMEDIAN->SetMarkerSize(1.5); GRAPHMEDIAN->SetLineWidth(1);
 GRAPHMEDIAN->Draw("P,sames");

 TLine *lineV = new TLine(0, 0, 0, 9);
 lineV->SetLineStyle(kDotted);
 lineV->SetLineColor(kGray);
 lineV->Draw();

 TLine *lineH = new TLine(-1.5, 1, 14.5, 1);
 lineH->SetLineWidth(2);
 lineH->Draw();

 TLegend *leg = new TLegend(0.645, 0.60, 0.98, 0.80, NULL, "brNDC");
 leg->SetTextFont(62);
 leg->SetTextSize(0.02721088);
 leg->SetFillColor(0);
 leg->SetFillStyle(0);
 leg->SetBorderSize(0);
 TLegendEntry *entry;
 leg->SetHeader(label.c_str());
 entry=leg->AddEntry(GRAPHMEDIAN, "Median expected", "p");
 entry=leg->AddEntry("NULL", "68% expected", "f");
 entry->SetFillColor(kGreen+1);
 entry->SetFillStyle(1001);
 entry->SetLineStyle(1);
 entry=leg->AddEntry("NULL", "95% expected", "f");
 entry->SetFillColor(kOrange);
 entry->SetFillStyle(1001);
 entry->SetLineStyle(1);
 leg->Draw();

 TLatex latex;
 latex.SetNDC();
 latex.SetTextSize(0.04);
 latex.SetTextSize(0.04 * 0.80);
 latex.SetTextFont(42);
 latex.SetTextAlign(31); // align right
 latex.DrawLatex(0.95, 0.9, Form("%.1f fb^{-1} (13 TeV)", intLumi));
 latex.SetTextSize(0.04);
 latex.SetTextFont(61);
 latex.SetTextAlign(11); // align left
 latex.DrawLatex(0.27, 0.9, "CMS Preliminary");

 string inputFile = folder + "/Limits.pdf";
 PLOTLIMIT->SaveAs(inputFile.c_str());

}

double ComputeSumYLimit(double BranchingRatio = 0.1){
  // cout << "Computing Ratio for " << BranchingRatio << endl;
  if (BranchingRatio == 1)
    {
      cout << "Branching Ratio cannot be 1" << endl;
      return 0;
    }
  // Higgs Mass
  double mh = 125;
  // Higgs Width at 125 GeV is 4.1 MeV
  double gammah = 4.1/1000;
  // Magic Formulas, #26 and #27 from
  // BR(h->mutau) = Width(h->mutau) / ( Width(h->mutau) + SM_Higgs_Width)
  // Width(h->mutau) = mh / 8Pi * (|Y(mutau)|**2 + |Y(taumu)|**2)
  // (|Y(mutau)|**2 + |Y(taumu)|**2) = (BR * SM_Higgs_Width) / ()*(1- BR)
  double LimitOnSumY = 8 * TMath::Pi() / mh * BranchingRatio * gammah / (1 - BranchingRatio);
  // cout << sqrt(LimitOnSumY) << endl;
  return LimitOnSumY;
}
