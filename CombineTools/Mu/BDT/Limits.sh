combineCards.py Name1=inputs/HMuTau_mutaue_1_2016_m125.txt Name2=inputs/HMuTau_mutauhad_1_2016_m125.txt > HMuTau_mutau_1_2016_m125.txt
combineCards.py Name1=inputs/HMuTau_mutaue_2_2016_m125.txt Name2=inputs/HMuTau_mutauhad_2_2016_m125.txt > HMuTau_mutau_2_2016_m125.txt
combineCards.py Name1=inputs/HMuTau_mutaue_3_2016_m125.txt Name2=inputs/HMuTau_mutauhad_3_2016_m125.txt > HMuTau_mutau_3_2016_m125.txt
combineCards.py Name1=inputs/HMuTau_mutaue_4_2016_m125.txt Name2=inputs/HMuTau_mutauhad_4_2016_m125.txt > HMuTau_mutau_4_2016_m125.txt
combineCards.py Name1=inputs/HMuTau_mutaue_1_2016_m125.txt Name2=inputs/HMuTau_mutauhad_1_2016_m125.txt Name3=inputs/HMuTau_mutaue_2_2016_m125.txt Name4=inputs/HMuTau_mutauhad_2_2016_m125.txt Name5=inputs/HMuTau_mutaue_3_2016_m125.txt Name6=inputs/HMuTau_mutauhad_3_2016_m125.txt Name7=inputs/HMuTau_mutaue_4_2016_m125.txt Name8=inputs/HMuTau_mutauhad_4_2016_m125.txt > HMuTau_mutau_comb_2016_m125.txt
combine -M AsymptoticLimits -m 125 HMuTau_mutau_1_2016_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.0Jet.mH125.root
combine -M AsymptoticLimits -m 125 HMuTau_mutau_2_2016_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.1Jet.mH125.root
combine -M AsymptoticLimits -m 125 HMuTau_mutau_3_2016_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.2JetGG.mH125.root
combine -M AsymptoticLimits -m 125 HMuTau_mutau_4_2016_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.2JetVBF.mH125.root
combine -M AsymptoticLimits -m 125 HMuTau_mutau_comb_2016_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.Comb.mH125.root
