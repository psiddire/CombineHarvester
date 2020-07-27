combineCards.py Name1=inputs/HMuTau_mutaue_1_2016_m125.txt Name2=inputs/HMuTau_mutaue_1_2017_m125.txt Name3=inputs/HMuTau_mutaue_1_2018_m125.txt > HMuTau_mutaue_1_m125.txt
combineCards.py Name1=inputs/HMuTau_mutaue_2_2016_m125.txt Name2=inputs/HMuTau_mutaue_2_2017_m125.txt Name3=inputs/HMuTau_mutaue_2_2018_m125.txt > HMuTau_mutaue_2_m125.txt
combineCards.py Name1=inputs/HMuTau_mutaue_3_2016_m125.txt Name2=inputs/HMuTau_mutaue_3_2017_m125.txt Name3=inputs/HMuTau_mutaue_3_2018_m125.txt > HMuTau_mutaue_3_m125.txt
combineCards.py Name1=inputs/HMuTau_mutaue_4_2016_m125.txt Name2=inputs/HMuTau_mutaue_4_2017_m125.txt Name3=inputs/HMuTau_mutaue_4_2018_m125.txt > HMuTau_mutaue_4_m125.txt
combineCards.py Name1=HMuTau_mutaue_1_m125.txt Name2=HMuTau_mutaue_2_m125.txt Name3=HMuTau_mutaue_3_m125.txt Name4=HMuTau_mutaue_4_m125.txt > HMuTau_mutaue_comb_m125.txt
combine -M AsymptoticLimits -m 125 HMuTau_mutaue_1_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.0Jet.mH125.root
combine -M AsymptoticLimits -m 125 HMuTau_mutaue_2_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.1Jet.mH125.root
combine -M AsymptoticLimits -m 125 HMuTau_mutaue_3_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.2JetGG.mH125.root
combine -M AsymptoticLimits -m 125 HMuTau_mutaue_4_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.2JetVBF.mH125.root
combine -M AsymptoticLimits -m 125 HMuTau_mutaue_comb_m125.txt --run blind
mv higgsCombineTest.AsymptoticLimits.mH125.root higgsCombineTest.AsymptoticLimits.Comb.mH125.root
