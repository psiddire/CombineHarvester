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

  printf ("Creating LFV MuTau_had datacards \n ");

  string folder="shapes_mt_BDT";
  string lumi="";
  string inputFile="shapesMTBDT";
  string outputFile="HMuTau_mutauhad_2016_m125.input";
  string dirInput="";
  bool binbybin=false;
  string name="def";

  string aux_shapes = string(getenv("CMSSW_BASE")) + "/src/auxiliaries/shapesForLimit";

  TFile* TheFile = new TFile((aux_shapes + dirInput+"/"+inputFile+".root").c_str());

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

  ch::CombineHarvester cb;
  // cb.SetVerbosity(3);

  ch::Categories cats = {
    {1, "0jet"},
    {2, "1jet"},
    {3, "2jet_gg"},
    {4, "2jet_vbf"}
  };

  vector<string> masses = ch::MassesFromRange("125");

  cb.AddObservations({"*"}, {"HMuTau"}, {"2016"}, {"mutauhad"}, cats);

  vector<string> bkg_procs = {"ggH_htt", "qqH_htt", "ggH_hww", "qqH_hww", "Zothers", "EWK", "TT", "T", "Diboson", "Fakes", "ZTauTau"};
  cb.AddProcesses({"*"}, {"HMuTau"}, {"2016"}, {"mutauhad"}, bkg_procs, cats, false);

  vector<string> sig_procs = {"LFVGG", "LFVVBF"};
  cb.AddProcesses(masses, {"HMuTau"}, {"2016"}, {"mutauhad"}, sig_procs, cats, true);

  vector<string> mc_procs = {"ggH_htt", "qqH_htt", "ggH_hww", "qqH_hww", "Zothers", "EWK", "TT", "T", "Diboson"};
  vector<string> rec_procs = {"ggH_htt", "qqH_htt", "ggH_hww", "qqH_hww", "Zothers", "EWK"};

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
                  ({"LFVGG"}, {1}, 0.998)
                  ({"LFVGG"}, {2}, 1.002)
                  ({"LFVGG"}, {3}, 1.007)
                  ({"LFVGG"}, {4}, 1.011)
                  ({"ggH_htt"}, {1}, 0.997)
                  ({"ggH_htt"}, {2}, 1.003)
                  ({"ggH_htt"}, {3}, 1.008)
                  ({"ggH_htt"}, {4}, 1.012)
                  ({"ggH_hww"}, {1}, 0.995)
                  ({"ggH_hww"}, {2}, 1.002)
                  ({"ggH_hww"}, {3}, 1.005)
                  ({"ggH_hww"}, {4}, 1.015)
                  );

  cb.cp().AddSyst(cb,"pdf_Higgs_qqbar_ACCEPT", "lnN", SystMap<process,bin_id>::init
                  ({"LFVVBF"}, {1}, 1.003)
                  ({"LFVVBF"}, {2}, 1.002)
                  ({"LFVVBF"}, {3}, 1.004)
                  ({"LFVVBF"}, {4}, 1.005)
                  ({"qqH_htt"}, {1}, 1.013)
                  ({"qqH_htt"}, {2}, 1.003)
                  ({"qqH_htt"}, {3}, 1.006)
                  ({"qqH_htt"}, {4}, 1.006)
                  ({"qqH_hww"}, {1}, 1.014)
                  ({"qqH_hww"}, {2}, 1.007)
                  ({"qqH_hww"}, {3}, 1.008)
                  ({"qqH_hww"}, {4}, 1.007)
                  );

  cb.cp().AddSyst(cb,"QCDscale_ggH_ACCEPT", "lnN", SystMap<process,bin_id>::init
                  ({"LFVGG"}, {1}, 1.020)
                  ({"LFVGG"}, {2}, 0.980)
                  ({"LFVGG"}, {3}, 0.942)
                  ({"LFVGG"}, {4}, 0.916)
                  ({"ggH_htt"}, {1}, 1.023)
                  ({"ggH_htt"}, {2}, 0.979)
                  ({"ggH_htt"}, {3}, 0.934)
                  ({"ggH_htt"}, {4}, 0.916)
                  ({"ggH_hww"}, {1}, 1.043)
                  ({"ggH_hww"}, {2}, 0.987)
                  ({"ggH_hww"}, {3}, 0.988)
                  ({"ggH_hww"}, {4}, 0.906)
                  );

  cb.cp().AddSyst(cb,"QCDscale_qqH_ACCEPT", "lnN", SystMap<process,bin_id>::init
                  ({"LFVVBF"}, {1}, 0.997)
                  ({"LFVVBF"}, {2}, 0.999)
                  ({"LFVVBF"}, {3}, 1.014)
                  ({"LFVVBF"}, {4}, 0.992)
                  ({"qqH_htt"}, {1}, 1.003)
                  ({"qqH_htt"}, {2}, 0.999)
                  ({"qqH_htt"}, {3}, 1.015)
                  ({"qqH_htt"}, {4}, 0.991)
                  ({"qqH_hww"}, {1}, 1.005)
                  ({"qqH_hww"}, {2}, 0.994)
                  ({"qqH_hww"}, {3}, 1.020)
                  ({"qqH_hww"}, {4}, 0.992)
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
  cb.cp().process({"Zothers"}).AddSyst(cb, "norm_Zothers_mutauh_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"Fakes"}).AddSyst(cb, "norm_Fakes", "lnN", SystMap<>::init(1.30));
  cb.cp().process({"Fakes"}).AddSyst(cb, "norm_Fakes_mutauh_$BIN", "lnN", SystMap<>::init(1.10));

  cb.cp().process({"Diboson"}).AddSyst(cb, "norm_Diboson", "lnN", SystMap<>::init(1.05));
  cb.cp().process({"Diboson"}).AddSyst(cb, "norm_Diboson_mutauh_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"TT"}).AddSyst(cb, "norm_TT ", "lnN", SystMap<>::init(1.06));
  cb.cp().process({"TT"}).AddSyst(cb, "norm_TT_mutauh_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"T"}).AddSyst(cb, "norm_T", "lnN", SystMap<>::init(1.05));
  cb.cp().process({"T"}).AddSyst(cb, "norm_T_mutauh_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"EWK"}).AddSyst(cb, "norm_EWK", "lnN", SystMap<>::init(1.10));
  cb.cp().process({"EWK"}).AddSyst(cb, "norm_EWK_mutauh_$BIN", "lnN", SystMap<>::init(1.05));

  // Luminosity
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_2016", "lnN", SystMap<>::init(1.022));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_XY", "lnN", SystMap<>::init(1.009));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_BBD", "lnN", SystMap<>::init(1.004));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_DB", "lnN", SystMap<>::init(1.005));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_13TeV_GS", "lnN", SystMap<>::init(1.004));

  // Pileup, Prefiring
  AddShapes({"CMS_pileup", "CMS_prefiring"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Trigger
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_eff_trigger_mutauh_2016", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_trigger_emb_mutauh_2016", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_doublemutrg_2016", "lnN", SystMap<>::init(1.04));

  // Muon Efficiency
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_eff_m", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_m", "lnN", SystMap<>::init(1.01));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_m_emb", "lnN", SystMap<>::init(1.01732));

  // Muon Energy Scale
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_m_etaLt1p2", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_m_eta1p2to2p1", "shape", SystMap<>::init(1.0));
  // AddShapes({"CMS_scale_m_etaLt1p2", "CMS_scale_m_eta1p2to2p1"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Tau Efficiency
  AddShapes({"CMS_eff_t_pt30to35_2016", "CMS_eff_t_pt35to40_2016", "CMS_eff_t_ptgt40_2016"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_t_pt30to35_2016", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_t_emb_pt30to35_2016", "shape", SystMap<>::init(0.866));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_t_pt35to40_2016", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_t_emb_pt35to40_2016", "shape", SystMap<>::init(0.866));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_t_ptgt40_2016", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_t_emb_ptgt40_2016", "shape", SystMap<>::init(0.866));

  // Tau Energy Scale
  AddShapes({"CMS_scale_t_1prong_2016", "CMS_scale_t_1prong1pizero_2016", "CMS_scale_t_3prong_2016", "CMS_scale_t_3prong1pizero_2016"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_1prong_2016", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_emb_1prong_2016", "shape", SystMap<>::init(0.866));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_1prong1pizero_2016", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_emb_1prong1pizero_2016", "shape", SystMap<>::init(0.866));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_3prong_2016", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_emb_3prong_2016", "shape", SystMap<>::init(0.866));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_3prong1pizero_2016", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_emb_3prong1pizero_2016", "shape", SystMap<>::init(0.866));

  // Tracking
  AddShapes({"CMS_tau_tracking_prong", "CMS_tau_tracking_prong_2016", "CMS_tau_tracking_pizero", "CMS_tau_tracking_pizero_2016"}, {"ZTauTau"}, &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Recoil Uncertainty
  AddShapes({"CMS_scale_met_0Jet_2016", "CMS_res_met_0Jet_2016", "CMS_scale_met_1Jet_2016", "CMS_res_met_1Jet_2016", "CMS_scale_met_2Jet_2016", "CMS_res_met_2Jet_2016"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, rec_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Reweighting and b-tagging uncertainty
  cb.cp().process({"Zothers"})
    .AddSyst(cb, "CMS_dyShape_2016", "shape", SystMap<>::init(1.0));

  AddShapes({"CMS_eff_b_2016"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Muon Faking Tau
  AddShapes({"CMS_mutauFR_etaLt0p4_2016", "CMS_mutauFR_eta0p4to0p8_2016", "CMS_mutauFR_eta0p8to1p2_2016", "CMS_mutauFR_eta1p2to1p7_2016", "CMS_mutauFR_etaGt1p7_2016"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Electron Faking Tau
  AddShapes({"CMS_etauFR_barrel_2016", "CMS_etauFR_endcap_2016"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Muon Faking Tau ES
  AddShapes({"CMS_scale_mutauFR_1prong_2016", "CMS_scale_mutauFR_1prong1pizero_2016"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Electron Faking Tau ES
  AddShapes({"CMS_scale_etauFR_barrel_1prong_2016", "CMS_scale_etauFR_barrel_1prong1pizero_2016", "CMS_scale_etauFR_endcap_1prong_2016", "CMS_scale_etauFR_endcap_1prong1pizero_2016"}, ch::JoinStr({{"LFVGG", "LFVVBF"}, mc_procs}), &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Fake background Uncertainty
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm0_B_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm1_B_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm10_B_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm11_B_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm0_E_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm1_E_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm10_E_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm11_E_2016", "shape", SystMap<>::init(1.0));

  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm0_B_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm1_B_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm10_B_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm11_B_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm0_E_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm1_E_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm10_E_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm11_E_2016", "shape", SystMap<>::init(1.0));

  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_muFR_p0_2016", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_muFR_p1_2016", "shape", SystMap<>::init(1.0));
  // AddShapes({"CMS_tauFR_p0_dm0_B_2016", "CMS_tauFR_p0_dm1_B_2016", "CMS_tauFR_p0_dm10_B_2016", "CMS_tauFR_p0_dm11_B_2016", "CMS_tauFR_p0_dm0_E_2016", "CMS_tauFR_p0_dm1_E_2016", "CMS_tauFR_p0_dm10_E_2016", "CMS_tauFR_p0_dm11_E_2016", "CMS_tauFR_p1_dm0_B_2016", "CMS_tauFR_p1_dm1_B_2016", "CMS_tauFR_p1_dm10_B_2016", "CMS_tauFR_p1_dm11_B_2016", "CMS_tauFR_p1_dm0_E_2016", "CMS_tauFR_p1_dm1_E_2016", "CMS_tauFR_p1_dm10_E_2016", "CMS_tauFR_p1_dm11_E_2016", "CMS_muFR_p0_2016", "CMS_muFR_p1_2016"}, {"Fakes"}, &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

  // Jet Energy Scale and Resolution
  AddShapes({"CMS_scale_j_Absolute", "CMS_scale_j_Absolute_2016", "CMS_scale_j_BBEC1", "CMS_scale_j_BBEC1_2016", "CMS_scale_j_FlavorQCD", "CMS_scale_j_EC2", "CMS_scale_j_EC2_2016", "CMS_scale_j_HF", "CMS_scale_j_HF_2016", "CMS_scale_j_RelativeBal", "CMS_scale_j_RelativeSample_2016", "CMS_res_j_2016"}, {"TT", "T", "Diboson"}, &cb, TheFile, {"0jet", "1jet", "2jet_gg", "2jet_vbf"});

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

  TFile output((folder + "/"+outputFile+".root").c_str(), "RECREATE");

  for (auto b : bins) {
    for (auto m : masses) {
      cout << ">> Writing datacard for bin: " << b << " and mass: " << m
           << "\n";
      cb.cp().bin({b}).mass({m, "*"}).WriteDatacard(folder + "/" + b + "_m" + m + ".txt", output);
    }
  }
}
