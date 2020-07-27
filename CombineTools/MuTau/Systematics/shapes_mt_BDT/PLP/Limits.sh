combineCards.py Name1=HMuTau_mutauhad_1_2017_m125.txt Name2=HMuTau_mutauhad_2_2017_m125.txt Name3=HMuTau_mutauhad_3_2017_m125.txt Name4=HMuTau_mutauhad_4_2017_m125.txt > HMuTau_mutauhad_comb_2017_m125.txt
combine -M AsymptoticLimits -m 125 HMuTau_mutauhad_1_2017_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HMuTau_mutauhad_2_2017_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HMuTau_mutauhad_3_2017_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HMuTau_mutauhad_4_2017_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HMuTau_mutauhad_comb_2017_m125.txt --run blind

