echo 'HETau_etauhad_1_2016 autoMCStats 10' >> HETau_etauhad_1_2016_m125.txt
echo 'HETau_etauhad_2_2016 autoMCStats 10' >> HETau_etauhad_2_2016_m125.txt
echo 'HETau_etauhad_3_2016 autoMCStats 10' >> HETau_etauhad_3_2016_m125.txt
echo 'HETau_etauhad_4_2016 autoMCStats 10' >> HETau_etauhad_4_2016_m125.txt
combineCards.py Name1=HETau_etauhad_1_2016_m125.txt Name2=HETau_etauhad_2_2016_m125.txt Name3=HETau_etauhad_3_2016_m125.txt Name4=HETau_etauhad_4_2016_m125.txt > HETau_etauhad_comb_2016_m125.txt
combine -M AsymptoticLimits -m 125 HETau_etauhad_1_2016_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.0Jet.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etauhad_2_2016_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.1Jet.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etauhad_3_2016_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.2JetGG.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etauhad_4_2016_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.2JetVBF.mH125.root
combine -M AsymptoticLimits -m 125 HETau_etauhad_comb_2016_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.Comb.mH125.root
