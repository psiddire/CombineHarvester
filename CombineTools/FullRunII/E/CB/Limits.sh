combineCards.py Name1=inputs/HETau_etaumu_1_2016_m125.txt Name2=inputs/HETau_etaumu_1_2017_m125.txt Name3=inputs/HETau_etaumu_1_2018_m125.txt Name4=inputs/HETau_etauhad_1_2016_m125.txt Name5=inputs/HETau_etauhad_1_2017_m125.txt Name6=inputs/HETau_etauhad_1_2018_m125.txt> HETau_etau_1_m125.txt
combineCards.py Name1=inputs/HETau_etaumu_2_2016_m125.txt Name2=inputs/HETau_etaumu_2_2017_m125.txt Name3=inputs/HETau_etaumu_2_2018_m125.txt Name4=inputs/HETau_etauhad_2_2016_m125.txt Name5=inputs/HETau_etauhad_2_2017_m125.txt Name6=inputs/HETau_etauhad_2_2018_m125.txt> HETau_etau_2_m125.txt
combineCards.py Name1=inputs/HETau_etaumu_3_2016_m125.txt Name2=inputs/HETau_etaumu_3_2017_m125.txt Name3=inputs/HETau_etaumu_3_2018_m125.txt Name4=inputs/HETau_etauhad_3_2016_m125.txt Name5=inputs/HETau_etauhad_3_2017_m125.txt Name6=inputs/HETau_etauhad_3_2018_m125.txt> HETau_etau_3_m125.txt
combineCards.py Name1=inputs/HETau_etaumu_4_2016_m125.txt Name2=inputs/HETau_etaumu_4_2017_m125.txt Name3=inputs/HETau_etaumu_4_2018_m125.txt Name4=inputs/HETau_etauhad_4_2016_m125.txt Name5=inputs/HETau_etauhad_4_2017_m125.txt Name6=inputs/HETau_etauhad_4_2018_m125.txt> HETau_etau_4_m125.txt
combineCards.py Name1=inputs/HETau_etaumu_1_2016_m125.txt Name2=inputs/HETau_etaumu_1_2017_m125.txt Name3=inputs/HETau_etaumu_1_2018_m125.txt Name4=inputs/HETau_etauhad_1_2016_m125.txt Name5=inputs/HETau_etauhad_1_2017_m125.txt Name6=inputs/HETau_etauhad_1_2018_m125.txt Name7=inputs/HETau_etaumu_2_2016_m125.txt Name8=inputs/HETau_etaumu_2_2017_m125.txt Name9=inputs/HETau_etaumu_2_2018_m125.txt Name10=inputs/HETau_etauhad_2_2016_m125.txt Name11=inputs/HETau_etauhad_2_2017_m125.txt Name12=inputs/HETau_etauhad_2_2018_m125.txt Name13=inputs/HETau_etaumu_3_2016_m125.txt Name14=inputs/HETau_etaumu_3_2017_m125.txt Name15=inputs/HETau_etaumu_3_2018_m125.txt Name16=inputs/HETau_etauhad_3_2016_m125.txt Name17=inputs/HETau_etauhad_3_2017_m125.txt Name18=inputs/HETau_etauhad_3_2018_m125.txt  Name19=inputs/HETau_etaumu_4_2016_m125.txt Name20=inputs/HETau_etaumu_4_2017_m125.txt Name21=inputs/HETau_etaumu_4_2018_m125.txt Name22=inputs/HETau_etauhad_4_2016_m125.txt Name23=inputs/HETau_etauhad_4_2017_m125.txt Name24=inputs/HETau_etauhad_4_2018_m125.txt> HETau_etau_comb_m125.txt
combine -M AsymptoticLimits -m 125 HETau_etau_1_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.0Jet.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etau_2_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.1Jet.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etau_3_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.2JetGG.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etau_4_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.2JetVBF.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etau_comb_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.Comb.mH125.root
