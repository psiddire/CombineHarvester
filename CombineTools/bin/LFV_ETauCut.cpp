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

  printf ("Creating LFV ETau_had datacards \n ");

  string folder="shapes_et_CutBased";
  string lumi="";
  string inputFile="shapesET";
  string outputFile="HETau_etauhad_2016_m125.input";
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

  cb.AddObservations({"*"}, {"HETau"}, {"2016"}, {"etauhad"}, cats);

  vector<string> bkg_procs = {"ggH_htt", "qqH_htt", "ggH_hww", "qqH_hww", "Zothers", "EWK", "TT", "T", "Diboson", "Fakes", "ZTauTau"};
  cb.AddProcesses({"*"}, {"HETau"}, {"2016"}, {"etauhad"}, bkg_procs, cats, false);

  vector<string> sig_procs = {"LFVGG", "LFVVBF"};
  cb.AddProcesses(masses, {"HETau"}, {"2016"}, {"etauhad"}, sig_procs, cats, true);

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

  cb.cp().AddSyst(cb, "pdf_Higgs_qq", "lnN", SystMap<process,bin_id>::init
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {1}, 1.021)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {2}, 1.021)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {3}, 1.021)
		  ({"LFVVBF", "qqH_htt", "qqH_hww"}, {4}, 1.021)
		  );

  // Acceptance
  cb.cp().AddSyst(cb,"acceptance_pdf_gg", "lnN", SystMap<process,bin_id>::init
                  ({"LFVGG"}, {1}, 0.999)
                  ({"LFVGG"}, {2}, 1.001)
                  ({"LFVGG"}, {3}, 1.004)
                  ({"LFVGG"}, {4}, 1.005)
                  ({"ggH_htt"}, {1}, 0.999)
                  ({"ggH_htt"}, {2}, 1.002)
                  ({"ggH_htt"}, {3}, 1.004)
                  ({"ggH_htt"}, {4}, 1.006)
                  ({"ggH_hww"}, {1}, 0.997)
                  ({"ggH_hww"}, {2}, 1.001)
                  ({"ggH_hww"}, {3}, 1.002)
                  ({"ggH_hww"}, {4}, 1.006)
                  );

  cb.cp().AddSyst(cb,"acceptance_pdf_vbf", "lnN", SystMap<process,bin_id>::init
                  ({"LFVVBF"}, {1}, 1.003)
                  ({"LFVVBF"}, {2}, 1.001)
                  ({"LFVVBF"}, {3}, 1.000)
                  ({"LFVVBF"}, {4}, 0.999)
                  ({"qqH_htt"}, {1}, 1.003)
                  ({"qqH_htt"}, {2}, 1.001)
                  ({"qqH_htt"}, {3}, 0.999)
                  ({"qqH_htt"}, {4}, 0.998)
                  ({"qqH_hww"}, {1}, 1.001)
                  ({"qqH_hww"}, {2}, 1.002)
                  ({"qqH_hww"}, {3}, 1.002)
                  ({"qqH_hww"}, {4}, 0.997)
                  );

  cb.cp().AddSyst(cb,"acceptance_scale_gg", "lnN", SystMap<process,bin_id>::init
                  ({"LFVGG"}, {1}, 1.021)
                  ({"LFVGG"}, {2}, 0.979)
                  ({"LFVGG"}, {3}, 0.944)
                  ({"LFVGG"}, {4}, 0.919)
                  ({"ggH_htt"}, {1}, 1.027)
                  ({"ggH_htt"}, {2}, 0.977)
                  ({"ggH_htt"}, {3}, 0.931)
                  ({"ggH_htt"}, {4}, 0.900)
                  ({"ggH_hww"}, {1}, 1.058)
                  ({"ggH_hww"}, {2}, 1.005)
                  ({"ggH_hww"}, {3}, 0.959)
                  ({"ggH_hww"}, {4}, 0.921)
                  );

  cb.cp().AddSyst(cb,"acceptance_scale_vbf", "lnN", SystMap<process,bin_id>::init
                  ({"LFVVBF"}, {1}, 0.995)
                  ({"LFVVBF"}, {2}, 0.998)
                  ({"LFVVBF"}, {3}, 1.014)
                  ({"LFVVBF"}, {4}, 0.995)
                  ({"qqH_htt"}, {1}, 0.989)
                  ({"qqH_htt"}, {2}, 0.999)
                  ({"qqH_htt"}, {3}, 1.020)
                  ({"qqH_htt"}, {4}, 0.992)
                  ({"qqH_hww"}, {1}, 1.009)
                  ({"qqH_hww"}, {2}, 1.011)
                  ({"qqH_hww"}, {3}, 1.002)
                  ({"qqH_hww"}, {4}, 0.986)
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
  cb.cp().process({"Zothers"}).AddSyst(cb, "norm_Zothers_etauh_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"Fakes"}).AddSyst(cb, "norm_Fakes", "lnN", SystMap<>::init(1.30));
  cb.cp().process({"Fakes"}).AddSyst(cb, "norm_Fakes_etauh_$BIN", "lnN", SystMap<>::init(1.10));

  cb.cp().process({"Diboson"}).AddSyst(cb, "norm_Diboson", "lnN", SystMap<>::init(1.05));
  cb.cp().process({"Diboson"}).AddSyst(cb, "norm_Diboson_etauh_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"TT"}).AddSyst(cb, "norm_TT ", "lnN", SystMap<>::init(1.06));
  cb.cp().process({"TT"}).AddSyst(cb, "norm_TT_etauh_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"T"}).AddSyst(cb, "norm_T", "lnN", SystMap<>::init(1.05));
  cb.cp().process({"T"}).AddSyst(cb, "norm_T_etauh_$BIN", "lnN", SystMap<>::init(1.05));

  cb.cp().process({"EWK"}).AddSyst(cb, "norm_EWK", "lnN", SystMap<>::init(1.10));
  cb.cp().process({"EWK"}).AddSyst(cb, "norm_EWK_etauh_$BIN", "lnN", SystMap<>::init(1.05));

  // Luminosity
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_2016_13TeV", "lnN", SystMap<>::init(1.022));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_xy-factorization_13TeV", "lnN", SystMap<>::init(1.009));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_beam-beam-deflection_13TeV", "lnN", SystMap<>::init(1.004));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_dynamic-beta_13TeV", "lnN", SystMap<>::init(1.005));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_lumi_ghosts-satellites_13TeV", "lnN", SystMap<>::init(1.004));

  // Pileup, Prefiring
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_Pileup_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_Prefiring_13TeV", "shape", SystMap<>::init(1.0));

  // Trigger
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_Trigger_etauh_2016_13TeV", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_Trigger_emb_etauh_2016_13TeV", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_selection_dimuon_emb_2016_13TeV", "lnN", SystMap<>::init(1.04));

  // Electron Efficiency
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_eff_e", "lnN", SystMap<>::init(1.02));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_e", "lnN", SystMap<>::init(1.01));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_eff_emb_e", "lnN", SystMap<>::init(1.01732));

  // Electron Energy Scale
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_e_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_e_emb_13TeV", "shape", SystMap<>::init(1.0));

  // Tau Efficiency
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_tauid_pt30to35_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_tauid_pt30to35_2016_13TeV", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_emb_tauid_pt30to35_2016_13TeV", "shape", SystMap<>::init(0.866));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_tauid_pt35to40_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_tauid_pt35to40_2016_13TeV", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_emb_tauid_pt35to40_2016_13TeV", "shape", SystMap<>::init(0.866));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_tauid_ptgt40_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_tauid_ptgt40_2016_13TeV", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_emb_tauid_ptgt40_2016_13TeV", "shape", SystMap<>::init(0.866));

  // Tau Energy Scale
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_t_1prong_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_1prong_2016_13TeV", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_emb_t_1prong_2016_13TeV", "shape", SystMap<>::init(0.866));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_t_1prong1pizero_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_1prong1pizero_2016_13TeV", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_emb_t_1prong1pizero_2016_13TeV", "shape", SystMap<>::init(0.866));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_t_3prong_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_3prong_2016_13TeV", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_emb_t_3prong_2016_13TeV", "shape", SystMap<>::init(0.866));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_t_3prong1pizero_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_t_3prong1pizero_2016_13TeV", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_scale_emb_t_3prong1pizero_2016_13TeV", "shape", SystMap<>::init(0.866));

  // Tracking
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_tau_tracking_prong_13TeV", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_tau_tracking_prong_2016_13TeV", "shape", SystMap<>::init(0.866));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_tau_tracking_pizero_13TeV", "shape", SystMap<>::init(0.5));
  cb.cp().process({"ZTauTau"})
    .AddSyst(cb, "CMS_tau_tracking_pizero_2016_13TeV", "shape", SystMap<>::init(0.866));

  // Recoil Uncertainty
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_scale_met_0Jet_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_reso_met_0Jet_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_scale_met_1Jet_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_reso_met_1Jet_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_scale_met_2Jet_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, rec_procs}))
    .AddSyst(cb, "CMS_reso_met_2Jet_2016_13TeV", "shape", SystMap<>::init(1.0));

  // Reweighting and b-tagging uncertainty
  cb.cp().process({"Zothers"})
    .AddSyst(cb, "CMS_DYpTreweight_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"TT", "T"})//.bin_id({2})
    .AddSyst(cb, "CMS_eff_btag_2016_13TeV", "shape", SystMap<>::init(1.0));

  // Muon Faking Tau
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_mutauFR_etaLt0p4_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_mutauFR_eta0p4to0p8_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_mutauFR_eta0p8to1p2_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_mutauFR_eta1p2to1p7_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_mutauFR_etaGt1p7_2016_13TeV", "shape", SystMap<>::init(1.0));

  // Electron Faking Tau
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_etauFR_barrel_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_etauFR_endcap_2016_13TeV", "shape", SystMap<>::init(1.0));

  // Muon Faking Tau ES
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_mtauFR_1prong_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_mtauFR_1prong1pizero_2016_13TeV", "shape", SystMap<>::init(1.0));

  // Electron Faking Tau ES
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_etauFR_barrel_1prong_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_etauFR_barrel_1prong1pizero_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_etauFR_endcap_1prong_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process(ch::JoinStr({sig_procs, mc_procs}))
    .AddSyst(cb, "CMS_scale_etauFR_endcap_1prong1pizero_2016_13TeV", "shape", SystMap<>::init(1.0));

  // Fake background Uncertainty
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm0_B_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm1_B_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm10_B_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm11_B_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm0_E_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm1_E_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm10_E_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p0_dm11_E_2016_13TeV", "shape", SystMap<>::init(1.0));

  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm0_B_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm1_B_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm10_B_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm11_B_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm0_E_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm1_E_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm10_E_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_tauFR_p1_dm11_E_2016_13TeV", "shape", SystMap<>::init(1.0));

  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_eFR_p0_2016_13TeV", "shape", SystMap<>::init(1.0));
  cb.cp().process({"Fakes"})
    .AddSyst(cb, "CMS_eFR_p1_2016_13TeV", "shape", SystMap<>::init(1.0));

  // Jet Energy Scale and Resolution
  TString JESNAMES[12] = {"CMS_Jes_JetAbsolute_13TeV", "CMS_Jes_JetAbsolute_2016_13TeV", "CMS_Jes_JetBBEC1_13TeV", "CMS_Jes_JetBBEC1_2016_13TeV", "CMS_Jes_JetFlavorQCD_13TeV", "CMS_Jes_JetEC2_13TeV", "CMS_Jes_JetEC2_2016_13TeV", "CMS_Jes_JetHF_13TeV", "CMS_Jes_JetHF_2016_13TeV", "CMS_Jes_JetRelativeBal_13TeV", "CMS_Jes_JetRelativeSample_13TeV", "CMS_Jer_2016_13TeV"};
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
  //   bbb.MergeBinErrors(cb.cp().process({"ggH_htt", "qqH_htt", "ggH_hww", "qqH_hww", "Zothers", "TT", "T", "EWK", "Diboson", "Fakes", "ZTauTau"}));
  //   bbb.AddBinByBin(cb.cp().backgrounds(), cb);
  // }

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
