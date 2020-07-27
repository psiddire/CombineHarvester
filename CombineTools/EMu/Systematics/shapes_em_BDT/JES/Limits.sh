combineCards.py Name1=HETau_etaumu_1_2017_m125.txt Name2=HETau_etaumu_2_2017_m125.txt Name3=HETau_etaumu_3_2017_m125.txt Name4=HETau_etaumu_4_2017_m125.txt > HETau_etaumu_comb_2017_m125.txt
combine -M AsymptoticLimits -m 125 HETau_etaumu_1_2017_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HETau_etaumu_2_2017_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HETau_etaumu_3_2017_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HETau_etaumu_4_2017_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HETau_etaumu_comb_2017_m125.txt --run blind
