combineCards.py Name1=HETau_etaumu_1_2018_m125.txt Name2=HETau_etaumu_2_2018_m125.txt Name3=HETau_etaumu_3_2018_m125.txt Name4=HETau_etaumu_4_2018_m125.txt > HETau_etaumu_comb_2018_m125.txt
combine -M AsymptoticLimits -m 125 HETau_etaumu_1_2018_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.0Jet.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etaumu_2_2018_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.1Jet.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etaumu_3_2018_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.2JetGG.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etaumu_4_2018_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.2JetVBF.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etaumu_comb_2018_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.Comb.mH125.root
