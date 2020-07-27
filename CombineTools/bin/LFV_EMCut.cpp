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
#include "CombineHarvester/CombineTools/interface/UtilityFunctions.h"

using namespace std;

int main(int argc, char* argv[]){

  printf ("Creating LFV ETau_mu datacards \n ");

  string folder="shapes_em_CutBased";
  string lumi="";
  string inputFile="shapesEMuQCD";
  string outputFile="HETau_etaumu_2017_m125.input";
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

  TFile* TheFile = new TFile((aux_shapes + dirInput+"/"+inputFile+".root").c_str());

  ch::CombineHarvester cb;
  // cb.SetVerbosity(3);

  ch::Categories cats = {
    {1, "0jet"},
    {2, "1jet"},
    {3, "2jet_gg"},
    {4, "2jet_vbf"}
  };

  vector<string> masses = ch::MassesFromRange("125");

  cb.AddObservations({"*"}, {"HETau"}, {"2017"}, {"etaumu"}, cats);

  vector<string> bkg_procs = {"ggH_htt", "qqH_htt", "ggH_hww", "qqH_hww", "Zothers", "EWK", "W", "TT", "T", "Diboson", "QCD", "ZTauTau"};
  cb.AddProcesses({"*"}, {"HETau"}, {"2017"}, {"etaumu"}, bkg_procs, cats, false);

  vector<string> sig_procs = {"LFVGG", "LFVVBF"};
  cb.AddProcesses(masses, {"HETau"}, {"2017"}, {"etaumu"}, sig_procs, cats, true);

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

  cb.cp().AddSyst(cb, "pdf_Higgs_qqbar", "lnN", SystMap<process,bin_id>::init
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {1}, 1.021)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {2}, 1.021)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {3}, 1.021)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {4}, 1.021)
		  );

  // Acceptance
  cb.cp().AddSyst(cb,"pdf_Higgs_gg_ACCEPT", "lnN", SystMap<process,bin_id>::init
                  ({"LFVGG"}, {1}, 0.999)
                  ({"LFVGG"}, {2}, 1.001)
                  ({"LFVGG"}, {3}, 1.003)
                  ({"LFVGG"}, {4}, 1.005)
                  ({"ggH_htt"}, {1}, 0.999)
                  ({"ggH_htt"}, {2}, 1.001)
                  ({"ggH_htt"}, {3}, 1.003)
                  ({"ggH_htt"}, {4}, 1.005)
                  ({"ggH_hww"}, {1}, 0.999)
                  ({"ggH_hww"}, {2}, 1.001)
                  ({"ggH_hww"}, {3}, 1.003)
                  ({"ggH_hww"}, {4}, 1.005)
                  );

  cb.cp().AddSyst(cb,"pdf_Higgs_qqbar_ACCEPT", "lnN", SystMap<process,bin_id>::init
                  ({"LFVVBF"}, {1}, 1.003)
                  ({"LFVVBF"}, {2}, 1.000)
                  ({"LFVVBF"}, {3}, 0.999)
                  ({"LFVVBF"}, {4}, 0.999)
                  ({"qqH_htt"}, {1}, 1.003)
                  ({"qqH_htt"}, {2}, 1.000)
                  ({"qqH_htt"}, {3}, 1.000)
                  ({"qqH_htt"}, {4}, 0.999)
                  ({"qqH_hww"}, {1}, 1.004)
                  ({"qqH_hww"}, {2}, 1.001)
                  ({"qqH_hww"}, {3}, 1.003)
                  ({"qqH_hww"}, {4}, 0.998)
                  );

  cb.cp().AddSyst(cb,"QCDscale_ggH_ACCEPT", "lnN", SystMap<process,bin_id>::init
                  ({"LFVGG"}, {1}, 1.019)
                  ({"LFVGG"}, {2}, 0.977)
                  ({"LFVGG"}, {3}, 0.946)
                  ({"LFVGG"}, {4}, 0.919)
                  ({"ggH_htt"}, {1}, 1.023)
                  ({"ggH_htt"}, {2}, 0.977)
                  ({"ggH_htt"}, {3}, 0.938)
                  ({"ggH_htt"}, {4}, 0.902)
                  ({"ggH_hww"}, {1}, 1.019)
                  ({"ggH_hww"}, {2}, 0.979)
                  ({"ggH_hww"}, {3}, 0.948)
                  ({"ggH_hww"}, {4}, 0.913)
                  );

  cb.cp().AddSyst(cb,"QCDscale_qqH_ACCEPT", "lnN", SystMap<process,bin_id>::init
                  ({"LFVVBF"}, {1}, 0.999)
                  ({"LFVVBF"}, {2}, 0.999)
                  ({"LFVVBF"}, {3}, 1.016)
                  ({"LFVVBF"}, {4}, 0.991)
                  ({"qqH_htt"}, {1}, 0.998)
                  ({"qqH_htt"}, {2}, 0.999)
                  ({"qqH_htt"}, {3}, 1.016)
                  ({"qqH_htt"}, {4}, 0.991)
                  ({"qqH_hww"}, {1}, 0.999)
                  ({"qqH_hww"}, {2}, 0.999)
                  ({"qqH_hww"}, {3}, 1.017)
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
  cb.cp().process({"Zothers"}).AddSyst(cb, "norm_Zothers_etaumu_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"W"}).AddSyst(cb, "norm_W", "lnN", SystMap<>::init(1.10));

  cb.cp().process({"Diboson"}).AddSyst(cb, "norm_Diboson", "lnN", SystMap<>::init(1.05));
  cb.cp().process({"Diboson"}).AddSyst(cb, "norm_Diboson_etaumu_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"TT"}).AddSyst(cb, "norm_TT ", "lnN", SystMap<>::init(1.06));
  cb.cp().process({"TT"}).AddSyst(cb, "norm_TT_etaumu_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"T"}).AddSyst(cb, "norm_T", "lnN", SystMap<>::init(1.05));
  cb.cp().process({"T"}).AddSyst(cb, "norm_T_etaumu_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"EWK"}).AddSyst(cb, "norm_EWK", "lnN", SystMap<>::init(1.10));
  cb.cp().process({"EWK"}).AddSyst(cb, "norm_EWK_etaumu_$BIN", "lnN", SystMap<>::init(1.05));

  // Luminosity
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_2017", "lnN", SystMap<>::init(1.020));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_XY", "lnN", SystMap<>::init(1.008));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_LS", "lnN", SystMap<>::init(1.003));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_BBD", "lnN", SystMap<>::init(1.004));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_DB", "lnN", SystMap<>::init(1.005));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_BCC", "lnN", SystMap<>::init(1.003));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_GS", "lnN", SystMap<>::init(1.001));

  // Pileup, Prefiring
  AddShapes({"CMS_pileup", "CMS_prefiring"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Trigger
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_eff_trigger_etaumu_2017", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_trigger_emb_etaumu_2017", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_doublemutrg_2017", "lnN", SystMap<>::init(1.04));

  // Electron Efficiency
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_eff_e", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_e", "lnN", SystMap<>::init(1.01));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_e_emb", "lnN", SystMap<>::init(1.01732));

  // Muon Efficiency
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_eff_m", "lnN", SystMap<>::init(1.02));
  cb.cp().process({{"ZTauTau"}})
    .AddSyst(cb, "CMS_eff_m", "lnN", SystMap<>::init(1.01));
  cb.cp().process({{"ZTauTau"}})
    .AddSyst(cb, "CMS_eff_m_emb", "lnN", SystMap<>::init(1.01732));

  // Electron Energy Scale
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_e", "shape", SystMap<>::init(1.0));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_e_emb", "shape", SystMap<>::init(1.0));
  // AddShapes({"CMS_scale_e"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Muon Energy Scale
  AddShapes({"CMS_scale_m_etaLt1p2", "CMS_scale_m_eta1p2to2p1", "CMS_scale_m_eta2p1to2p4"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Recoil Uncertainty
  AddShapes({"CMS_scale_met_0Jet_2017", "CMS_res_met_0Jet_2017", "CMS_scale_met_1Jet_2017", "CMS_res_met_1Jet_2017", "CMS_scale_met_2Jet_2017", "CMS_res_met_2Jet_2017"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, rec_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Reweighting and b-tagging uncertainty
  cb.cp().process({"Zothers"})
    .AddSyst(cb, "CMS_dyShape_2017", "shape", SystMap<>::init(1.0));

  AddShapes({"CMS_eff_b_2017"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // QCD estimation uncertainty
  AddShapes({"CMS_qcd_0jet_rate_2017", "CMS_qcd_1jet_rate_2017", "CMS_qcd_2jet_rate_2017", "CMS_qcd_0jet_shape_2017", "CMS_qcd_1jet_shape_2017", "CMS_qcd_2jet_shape_2017", "CMS_qcd_extrapolation"}, {"QCD"}, &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Jet Energy Scale and Resolution
  AddShapes({"CMS_scale_j_Absolute", "CMS_scale_j_Absolute_2017", "CMS_scale_j_BBEC1", "CMS_scale_j_BBEC1_2017", "CMS_scale_j_FlavorQCD", "CMS_scale_j_EC2", "CMS_scale_j_EC2_2017", "CMS_scale_j_HF", "CMS_scale_j_HF_2017", "CMS_scale_j_RelativeBal", "CMS_scale_j_RelativeSample_2017", "CMS_res_j_2017"}, {"TT", "T", "Diboson"}, &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Unclustered Energy Scale
  AddShapes({"CMS_scale_met_charged", "CMS_scale_met_ecal", "CMS_scale_met_hcal", "CMS_scale_met_hf"}, {"TT", "T", "Diboson"}, &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  cb.cp().backgrounds().ExtractShapes(aux_shapes + dirInput+"/"+inputFile+".root", "$BIN/$PROCESS", "$BIN/$PROCESS_$SYSTEMATIC");
  cb.cp().signals().ExtractShapes(aux_shapes + dirInput+"/"+inputFile+".root", "$BIN/$PROCESS$MASS", "$BIN/$PROCESS$MASS_$SYSTEMATIC");

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
