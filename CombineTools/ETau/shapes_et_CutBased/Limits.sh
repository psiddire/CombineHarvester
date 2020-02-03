combineCards.py Name1=HETau_etauhad_1_2016_m125.txt Name2=HETau_etauhad_2_2016_m125.txt Name3=HETau_etauhad_3_2016_m125.txt Name4=HETau_etauhad_4_2016_m125.txt > HETau_etauhad_comb_2016_m125.txt
combine -M AsymptoticLimits -m 125 HETau_etauhad_1_2016_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HETau_etauhad_2_2016_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HETau_etauhad_3_2016_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HETau_etauhad_4_2016_m125.txt --run blind
combine -M AsymptoticLimits -m 125 HETau_etauhad_comb_2016_m125.txt --run blind
