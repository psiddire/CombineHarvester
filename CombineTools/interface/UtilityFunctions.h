//Andrew Loeliger
//File just includes utility functions for use in data card production
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

//Add a given vector of shapes to a given vector of distributions
//takes: a vector of strings for shape names
//a vector of strings for the distributions to add it to
//a pointer ot the combine harvester instance
//a pointer to the tfile that the distributions are in

void AddShapes(std::vector<string> Shapes,
	       std::vector<string> Distributions,
	       ch::CombineHarvester * cb,
	       TFile* TheFile,
	       std::vector<std::string> Categories)
{
  //loop over all of the analysis categories
  for(auto CategoryIt = Categories.begin(); CategoryIt != Categories.end(); ++CategoryIt)
    {
      string DirectoryName = *CategoryIt;
      TDirectory* TheDirectory = (TDirectory*) TheFile->Get(DirectoryName.c_str());
      TH1F* NominalHisto;
      if(TheDirectory == NULL)
	{
	  std::cout<<"\033[1;31mError!\033[0m"<<std::endl;
	  std::cout<<"Bad Directory: "+DirectoryName<<std::endl;
	  throw;
	}
      for(std::vector<string>::iterator it = Distributions.begin(); it != Distributions.end(); ++it)
	{
	  if(*it=="LFVGG" or *it=="LFVVBF")
	    {
	      NominalHisto = (TH1F*) TheDirectory->Get((*it+"125").c_str());
	    }
	  else
	    {
	      NominalHisto = (TH1F*) TheDirectory->Get((*it).c_str());
	    }
	  Float_t NominalIntegral = 0.0;
	  if (NominalHisto==NULL)
	    {
	      std::cout<<"\033[1;34mCheck Me?\033[0m"<<std::endl;
	      std::cout<<"Non Existent Base Histogram: "+*it<<std::endl;
	      std::cout<<"Directory: "<<DirectoryName<<std::endl;
	      std::cout<<"Continuing without doing anything..."<<std::endl;
	      continue;
	    }          
	  NominalIntegral = NominalHisto->Integral();
          TH1F* UpHisto;
          TH1F* DownHisto;	  
          //now loop over all the uncertainties
          for(std::vector<string>::iterator Unc_it = Shapes.begin();Unc_it != Shapes.end(); ++Unc_it)
	    {
	      if(*it=="LFVGG" or *it=="LFVVBF")
		{
		  UpHisto = (TH1F*) TheDirectory->Get((*it+"125_"+*Unc_it+"Up").c_str());
		  DownHisto = (TH1F*) TheDirectory->Get((*it+"125_"+*Unc_it+"Down").c_str());
		}
	      else
		{
		  UpHisto = (TH1F*) TheDirectory->Get((*it+"_"+*Unc_it+"Up").c_str());
		  DownHisto = (TH1F*) TheDirectory->Get((*it+"_"+*Unc_it+"Down").c_str());
		}
	      Float_t UpIntegral = 0.0;
	      Float_t DownIntegral = 0.0;	     
	      Float_t UpInt = 0.0;
	      Float_t DownInt = 0.0;	     
	      if(UpHisto==NULL)
		{
		  std::cout<<"\033[1;31mError!\033[0m"<<std::endl;
		  std::cout<<"Bad Up Histogram: "+(string)(*it+"_"+*Unc_it+"Up")<<std::endl;
		  std::cout<<"Directory: "+DirectoryName<<std::endl;

		  throw;
		}
	      if(DownHisto==NULL)
		{
		  std::cout<<"\033[1;31mError!\033[0m"<<std::endl;
		  std::cout<<"Bad Down Histogram: "+(string)(*it+"_"+*Unc_it+"Down")<<std::endl;
		  std::cout<<"Directory: "+DirectoryName<<std::endl;
		  throw;
		}
	      UpIntegral = UpHisto->Integral();
	      DownIntegral = DownHisto->Integral();
	      UpInt = 1.0 + (UpIntegral - NominalIntegral)/NominalIntegral;
	      DownInt = 1.0 + (DownIntegral - NominalIntegral)/NominalIntegral;
	      if(UpIntegral < NominalIntegral and DownIntegral < NominalIntegral)
		{
		  if(UpIntegral < DownIntegral)
		    {
		      DownInt = 1.0 - (UpIntegral - NominalIntegral)/NominalIntegral;
		    }
		  else
		    {
		      UpInt = 1.0 - (DownIntegral - NominalIntegral)/NominalIntegral;
		    }
		}
	      if(UpIntegral > NominalIntegral and DownIntegral > NominalIntegral)
		{
		  if(UpIntegral < DownIntegral)
		    {
		      UpInt = 1.0 - (DownIntegral - NominalIntegral)/NominalIntegral;
		    }
		  else
		    {
		      DownInt = 1.0 - (UpIntegral - NominalIntegral)/NominalIntegral;
		    }
		}
              if(NominalIntegral != 0.0 and UpIntegral != 0.0 and DownIntegral != 0.0)
		{
		  if(*Unc_it=="CMS_tau_tracking_prong" or *Unc_it=="CMS_tau_tracking_pizero")
		    {
		      UpInt = 1.0 + (0.5 * (UpInt - 1.0));
		      DownInt = 1.0 + (0.5 * (DownInt - 1.0));
                      cb->cp().bin({TheDirectory->GetName()}).process({*it})
                        .AddSyst(*cb, *Unc_it, "lnN", ch::syst::SystMapAsymm<>::init(UpInt, DownInt));		      
		    }
		  else if(*Unc_it=="CMS_tau_tracking_prong_2017" or *Unc_it=="CMS_tau_tracking_pizero_2017")
		    {
		      UpInt = 1.0 + (0.866 * (UpInt - 1.0));
		      DownInt = 1.0 + (0.866 * (DownInt - 1.0));
                      cb->cp().bin({TheDirectory->GetName()}).process({*it})
                        .AddSyst(*cb, *Unc_it, "lnN", ch::syst::SystMapAsymm<>::init(UpInt, DownInt));		      
		    }
		  else
		    {
		      cb->cp().bin({TheDirectory->GetName()}).process({*it})
			.AddSyst(*cb, *Unc_it, "lnN", ch::syst::SystMapAsymm<>::init(UpInt, DownInt));
		    }
                }
              else
		{
                  std::cout<<"Skipping Uncertainty:"<<*Unc_it<<" for "<<*it<<" in category: "<<DirectoryName<<std::endl;
                }
            }
        }
    }
}
