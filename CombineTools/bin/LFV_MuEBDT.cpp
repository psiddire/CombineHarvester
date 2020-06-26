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

using namespace std;

int main(int argc, char* argv[]){

  printf ("Creating LFV MuTau_e datacards \n ");

  string folder="shapes_me_BDT";
  string lumi="";
  string inputFile="shapesMuEBDTQCD";
  string outputFile="HMuTau_mutaue_2018_m125.input";
  string dirInput="";
  bool binbybin=false;
  string name="def";

  if (argc > 1)
    {
      int count=0;
      for (count = 1; count < argc; count++)
	{
	  if(strcmp(argv[count] ,"--i")==0) inputFile=argv[count+1];
	  if(strcmp(argv[count] ,"--o")==0) outputFile=argv[count+1];
	  if(strcmp(argv[count] ,"--l")==0) lumi=argv[count+1];
	  if(strcmp(argv[count] ,"--d")==0) dirInput=argv[count+1];
	  if(strcmp(argv[count] ,"--f")==0) folder=argv[count+1];
	  if(strcmp(argv[count] ,"--b")==0) binbybin=true;
	  if(strcmp(argv[count] ,"--name")==0) name=argv[count+1];
	}
    }

  string aux_shapes = string(getenv("CMSSW_BASE")) + "/src/auxiliaries/shapesForLimit";

  ch::CombineHarvester cb;
  // cb.SetVerbosity(3);

  ch::Categories cats = {
    {1, "0jet"},
    {2, "1jet"},
    {3, "2jet_gg"},
    {4, "2jet_vbf"}
  };

  vector<string> masses = ch::MassesFromRange("125");

  cb.AddObservations({"*"}, {"HMuTau"}, {"2018"}, {"mutaue"}, cats);

  vector<string> bkg_procs = {"ggH_htt", "qqH_htt", "ggH_hww", "qqH_hww", "Zothers", "EWK", "W", "TT", "T", "Diboson", "QCD", "ZTauTau"};
  cb.AddProcesses({"*"}, {"HMuTau"}, {"2018"}, {"mutaue"}, bkg_procs, cats, false);

  vector<string> sig_procs = {"LFVGG", "LFVVBF"};
  cb.AddProcesses(masses, {"HMuTau"}, {"2018"}, {"mutaue"}, sig_procs, cats, true);

  vector<string> mc_procs = {"ggH_htt", "qqH_htt", "ggH_hww", "qqH_hww", "Zothers", "EWK", "W", "TT", "T", "Diboson"};
  vector<string> rec_procs = {"ggH_htt", "qqH_htt", "ggH_hww", "qqH_hww", "Zothers", "EWK", "W"};

  using ch::syst::SystMap;
  using ch::syst::era;
  using ch::syst::bin_id;
  using ch::syst::process;

  // QCD Scale and PDF uncertainty
  cb.cp().AddSyst(cb, "QCDscale_ggH", "lnN", SystMap<process,bin_id>::init
		  ({"LFVGG", "ggH_htt", "ggH_hww"}, {1}, 1.039)
		  ({"LFVGG", "ggH_htt", "ggH_hww"}, {2}, 1.039)
		  ({"LFVGG", "ggH_htt", "ggH_hww"}, {3}, 1.039)
		  ({"LFVGG", "ggH_htt", "ggH_hww"}, {4}, 1.039)
		  );

  cb.cp().AddSyst(cb, "QCDscale_qqH", "lnN", SystMap<process,bin_id>::init
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {1}, 1.005)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {2}, 1.005)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {3}, 1.005)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {4}, 1.005)
		  );

  cb.cp().AddSyst(cb, "pdf_Higgs_gg", "lnN", SystMap<process,bin_id>::init
		  ({"LFVGG", "ggH_htt", "ggH_hww"}, {1}, 1.032)
		  ({"LFVGG", "ggH_htt", "ggH_hww"}, {2}, 1.032)
		  ({"LFVGG", "ggH_htt", "ggH_hww"}, {3}, 1.032)
		  ({"LFVGG", "ggH_htt", "ggH_hww"}, {4}, 1.032)
		  );

  cb.cp().AddSyst(cb, "pdf_Higgs_qq", "lnN", SystMap<process,bin_id>::init
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {1}, 1.021)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {2}, 1.021)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {3}, 1.021)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {4}, 1.021)
		  );

  // Acceptance
  cb.cp().AddSyst(cb,"acceptance_pdf_gg", "lnN", SystMap<process,bin_id>::init
                  ({"LFVGG", "ggH_htt", "ggH_hww"}, {1}, 0.999)
                  ({"LFVGG", "ggH_htt", "ggH_hww"}, {2}, 1.001)
                  ({"LFVGG", "ggH_htt", "ggH_hww"}, {3}, 1.003)
                  ({"LFVGG", "ggH_htt", "ggH_hww"}, {4}, 1.005)
                  );

  cb.cp().AddSyst(cb,"acceptance_pdf_vbf", "lnN", SystMap<process,bin_id>::init
                  ({"LFVVBF"}, {1}, 1.003)
                  ({"LFVVBF"}, {2}, 1.001)
                  ({"LFVVBF"}, {3}, 1.000)
                  ({"LFVVBF"}, {4}, 0.999)
                  ({"qqH_htt"}, {1}, 1.006)
                  ({"qqH_htt"}, {2}, 0.999)
                  ({"qqH_htt"}, {3}, 1.001)
                  ({"qqH_htt"}, {4}, 1.001)
                  ({"qqH_hww"}, {1}, 1.003)
                  ({"qqH_hww"}, {2}, 1.000)
                  ({"qqH_hww"}, {3}, 1.000)
                  ({"qqH_hww"}, {4}, 0.999)
                  );

  cb.cp().AddSyst(cb,"acceptance_scale_gg", "lnN", SystMap<process,bin_id>::init
                  ({"LFVGG"}, {1}, 1.020)
                  ({"LFVGG"}, {2}, 0.979)
                  ({"LFVGG"}, {3}, 0.944)
                  ({"LFVGG"}, {4}, 0.916)
                  ({"ggH_htt"}, {1}, 1.025)
                  ({"ggH_htt"}, {2}, 0.978)
                  ({"ggH_htt"}, {3}, 0.938)
                  ({"ggH_htt"}, {4}, 0.903)
                  ({"ggH_hww"}, {1}, 1.025)
                  ({"ggH_hww"}, {2}, 0.981)
                  ({"ggH_hww"}, {3}, 0.943)
                  ({"ggH_hww"}, {4}, 0.920)
                  );

  cb.cp().AddSyst(cb,"acceptance_scale_vbf", "lnN", SystMap<process,bin_id>::init
                  ({"LFVVBF"}, {1}, 0.996)
                  ({"LFVVBF"}, {2}, 0.999)
                  ({"LFVVBF"}, {3}, 1.015)
                  ({"LFVVBF"}, {4}, 0.992)
                  ({"qqH_htt"}, {1}, 1.005)
                  ({"qqH_htt"}, {2}, 1.002)
                  ({"qqH_htt"}, {3}, 1.015)
                  ({"qqH_htt"}, {4}, 0.987)
                  ({"qqH_hww"}, {1}, 0.999)
                  ({"qqH_hww"}, {2}, 0.998)
                  ({"qqH_hww"}, {3}, 1.016)
                  ({"qqH_hww"}, {4}, 0.991)
                  );

  // Uncertainty on BR for HTT @ 125 GeV
  cb.cp().process({"ggH_htt", "qqH_htt"}).AddSyst(cb, "BR_htt_THU", "lnN", SystMap<>::init(1.017));
  cb.cp().process({"ggH_htt", "qqH_htt"}).AddSyst(cb, "BR_htt_PU_mq", "lnN", SystMap<>::init(1.0099));
  cb.cp().process({"ggH_htt", "qqH_htt"}).AddSyst(cb, "BR_htt_PU_alphas", "lnN", SystMap<>::init(1.0062));

  // Uncertainty on BR of HWW @ 125 GeV
  cb.cp().process({"ggH_hww", "qqH_hww"}).AddSyst(cb, "BR_hww_THU", "lnN", SystMap<>::init(1.0099));
  cb.cp().process({"ggH_hww", "qqH_hww"}).AddSyst(cb, "BR_hww_PU_mq", "lnN", SystMap<>::init(1.0099));
  cb.cp().process({"ggH_hww", "qqH_hww"}).AddSyst(cb, "BR_hww_PU_alphas", "lnN", SystMap<>::init(1.0066));

  // Normalization
  cb.cp().process({"Zothers"}).AddSyst(cb, "norm_Zothers", "lnN", SystMap<>::init(1.04));
  cb.cp().process({"Zothers"}).AddSyst(cb, "norm_Zothers_mutaue_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"W"}).AddSyst(cb, "norm_w", "lnN", SystMap<>::init(1.10));

  cb.cp().process({"Diboson"}).AddSyst(cb, "norm_Diboson", "lnN", SystMap<>::init(1.05));
  cb.cp().process({"Diboson"}).AddSyst(cb, "norm_Diboson_mutaue_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"TT"}).AddSyst(cb, "norm_TT ", "lnN", SystMap<>::init(1.06));
  cb.cp().process({"TT"}).AddSyst(cb, "norm_TT_mutaue_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"T"}).AddSyst(cb, "norm_T", "lnN", SystMap<>::init(1.05));
  cb.cp().process({"T"}).AddSyst(cb, "norm_T_mutaue_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"EWK"}).AddSyst(cb, "norm_EWK", "lnN", SystMap<>::init(1.10));
  cb.cp().process({"EWK"}).AddSyst(cb, "norm_EWK_mutaue_$BIN", "lnN", SystMap<>::init(1.05));

  // Luminosity
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_2018_13TeV", "lnN", SystMap<>::init(1.022));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_xy-factorization_13TeV", "lnN", SystMap<>::init(1.009));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_beam-beam-deflection_13TeV", "lnN", SystMap<>::init(1.004));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_dynamic-beta_13TeV", "lnN", SystMap<>::init(1.005));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_ghosts-satellites_13TeV", "lnN", SystMap<>::init(1.004));

  // Pileup
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_Pileup_13TeV", "shape", SystMap<>::init(1.0));

  // PS Uncertainties
  cb.cp().process({"LFVGG", "LFVVBF"})
    .AddSyst(cb, "CMS_PartonShower_ISR_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"LFVGG", "LFVVBF"})
    .AddSyst(cb, "CMS_PartonShower_FSR_2018_13TeV", "shape", SystMap<>::init(1.0));

  // Trigger
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_Trigger_mutaue_2018_13TeV", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_Trigger_emb_mutaue_2018_13TeV", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_selection_dimuon_emb_2018_13TeV", "lnN", SystMap<>::init(1.04));

  // Muon Efficiency
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_eff_m", "lnN", SystMap<>::init(1.02));
  cb.cp().process({{"ZTauTau"}})
    .AddSyst(cb, "CMS_eff_m", "lnN", SystMap<>::init(1.01));
  cb.cp().process({{"ZTauTau"}})
    .AddSyst(cb, "CMS_eff_emb_m", "lnN", SystMap<>::init(1.01732));

  // Electron Efficiency
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_eff_e", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_e", "lnN", SystMap<>::init(1.01));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_emb_e", "lnN", SystMap<>::init(1.01732));

  // Muon Energy Scale
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_m_etaLt1p2_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_m_eta1p2to2p1_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_m_eta2p1to2p4_13TeV", "shape", SystMap<>::init(1.0));

  // Electron Energy Scale
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_e_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_e_emb_13TeV", "shape", SystMap<>::init(1.0));

  // Recoil Uncertainty
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_scale_met_0Jet_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_reso_met_0Jet_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_scale_met_1Jet_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_reso_met_1Jet_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_scale_met_2Jet_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_reso_met_2Jet_2018_13TeV", "shape", SystMap<>::init(1.0));

  // Reweighting and b-tagging uncertainty
  cb.cp().process({"Zothers"})
    .AddSyst(cb, "CMS_DYpTreweight_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"TT", "T"})//.bin_id({2})
    .AddSyst(cb, "CMS_eff_btag_2018_13TeV", "shape", SystMap<>::init(1.0));

  // QCD estimation uncertainty
  cb.cp().process({"QCD"})
    .AddSyst(cb, "CMS_QCD_0JetRate_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"QCD"})
    .AddSyst(cb, "CMS_QCD_1JetRate_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"QCD"})
    .AddSyst(cb, "CMS_QCD_2JetRate_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"QCD"})
    .AddSyst(cb, "CMS_QCD_0JetShape_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"QCD"})
    .AddSyst(cb, "CMS_QCD_1JetShape_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"QCD"})
    .AddSyst(cb, "CMS_QCD_2JetShape_2018_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"QCD"})
    .AddSyst(cb, "CMS_QCD_Extrapolation_13TeV", "shape", SystMap<>::init(1.0));

  // Jet Energy Scale and Resolution
  TString JESNAMES[12] = {"CMS_Jes_JetAbsolute_13TeV", "CMS_Jes_JetAbsolute_2018_13TeV", "CMS_Jes_JetBBEC1_13TeV", "CMS_Jes_JetBBEC1_2018_13TeV", "CMS_Jes_JetFlavorQCD_13TeV", "CMS_Jes_JetEC2_13TeV", "CMS_Jes_JetEC2_2018_13TeV", "CMS_Jes_JetHF_13TeV", "CMS_Jes_JetHF_2018_13TeV", "CMS_Jes_JetRelativeBal_13TeV", "CMS_Jes_JetRelativeSample_13TeV", "CMS_Jer_2018_13TeV"};
  for (int i = 0; i < 12; i++){
    cb.cp().process({"TT", "T", "Diboson"})
      .AddSyst(cb, JESNAMES[i].Data(), "shape", SystMap<>::init(1.0));
  }

  // Unclustered Energy Scale
  cb.cp().process({"TT", "T", "Diboson"})
    .AddSyst(cb, "CMS_MET_chargedUes_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"TT", "T", "Diboson"})
    .AddSyst(cb, "CMS_MET_ecalUes_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"TT", "T", "Diboson"})
    .AddSyst(cb, "CMS_MET_hcalUes_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"TT", "T", "Diboson"})
    .AddSyst(cb, "CMS_MET_hfUes_13TeV", "shape", SystMap<>::init(1.0));

  cb.cp().backgrounds().ExtractShapes(aux_shapes + dirInput+"/"+inputFile+".root", "$BIN/$PROCESS", "$BIN/$PROCESS_$SYSTEMATIC");
  cb.cp().signals().ExtractShapes(aux_shapes + dirInput+"/"+inputFile+".root", "$BIN/$PROCESS$MASS", "$BIN/$PROCESS$MASS_$SYSTEMATIC");

  // Bin By Bin Uncertainty
  // if(binbybin){
  //   auto bbb = ch::BinByBinFactory()
  //     .SetAddThreshold(0.1)
  //     .SetMergeThreshold(0.5)
  //     .SetFixNorm(false);
  //   //bbb.MergeBinErrors(cb.cp().backgrounds());
  //   bbb.MergeBinErrors(cb.cp().process({"ggH_htt", "qqH_htt", "ggH_hww", "qqH_hww", "Zothers", "EWK", "W", "TT", "T", "Diboson", "QCD", "ZTauTau"}));
  //   bbb.AddBinByBin(cb.cp().backgrounds(), cb);
  // }

  // This function modifies every entry to have a standardised bin name of the form: {analysis}_{channel}_{bin_id}_{era} which is commonly used in the htt analyses
  ch::SetStandardBinNames(cb);

  boost::filesystem::create_directories(folder);

  set<string> bins = cb.bin_set();

  string textbinbybin="";
  if(binbybin) textbinbybin="_bbb";

  TFile output((folder + "/" + outputFile + ".root").c_str(), "RECREATE");

  for (auto b : bins) {
    for (auto m : masses) {
      cout << ">> Writing datacard for bin: " << b << " and mass: " << m
           << "\n";
      cb.cp().bin({b}).mass({m, "*"}).WriteDatacard(folder + "/" + b + "_m" + m + ".txt", output);
    }
  }
}
