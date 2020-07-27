combineCards.py Name1=HMuTau_mutaue_1_2018_m125.txt Name2=HMuTau_mutaue_2_2018_m125.txt Name3=HMuTau_mutaue_3_2018_m125.txt Name4=HMuTau_mutaue_4_2018_m125.txt > HMuTau_mutaue_comb_2018_m125.txt
combine -M AsymptoticLimits -m 125 HMuTau_mutaue_1_2018_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HMuTau_mutaue_2_2018_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HMuTau_mutaue_3_2018_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HMuTau_mutaue_4_2018_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HMuTau_mutaue_comb_2018_m125.txt --run blind
