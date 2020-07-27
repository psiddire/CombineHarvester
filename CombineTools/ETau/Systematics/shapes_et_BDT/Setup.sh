sed -i '/^HETau_etauhad_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^HETau_etauhad_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^HETau_etauhad_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^HETau_etauhad_/d' HETau_etauhad_4_2018_m125.txt
mkdir BBB
cp H* BBB
cp Limits.sh BBB
cd BBB
source Limits.sh
cd ..
mkdir JES
cp H* JES
cp Limits.sh JES
cd JES
sed -i '/^CMS_Je/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_MET_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_reso_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_scale_met_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_Je/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_MET_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_reso_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_scale_met_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_Je/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_MET_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_reso_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_scale_met_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_Je/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_MET_/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_reso_/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_scale_met_/d' HETau_etauhad_4_2018_m125.txt
source Limits.sh
cd ..
mkdir LepEff
cp H* LepEff
cp Limits.sh LepEff
cd LepEff
sed -i '/^CMS_eff_e/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_emb_tauid_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_etauFR_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_mutauFR_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_tau_t/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_tauid_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_eff_e/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_emb_tauid_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_etauFR_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_mutauFR_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_tau_t/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_tauid_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_eff_e/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_emb_tauid_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_etauFR_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_mutauFR_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_tau_t/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_tauid_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_eff_e/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_emb_tauid_/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_etauFR_/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_mutauFR_/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_tau_t/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_tauid_/d' HETau_etauhad_4_2018_m125.txt
source Limits.sh
cd ..
mkdir LepES
cp H* LepES
cp Limits.sh LepES
cd LepES
sed -i '/^CMS_scale_e/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_scale_mt/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_scale_t/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_scale_e/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_scale_mt/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_scale_t/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_scale_e/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_scale_mt/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_scale_t/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_scale_e/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_scale_mt/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_scale_t/d' HETau_etauhad_4_2018_m125.txt
source Limits.sh
cd ..
mkdir BGNorm
cp H* BGNorm
cp Limits.sh BGNorm
cd BGNorm
sed -i '/^norm/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^norm/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^norm/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^norm/d' HETau_etauhad_4_2018_m125.txt
source Limits.sh
cd ..
mkdir Theory
cp H* Theory
cp Limits.sh Theory
cd Theory
sed -i '/^BR_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^QCDscale/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^acceptance/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^pdf_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^BR_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^QCDscale/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^acceptance/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^pdf_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^BR_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^QCDscale/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^acceptance/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^pdf_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^BR_/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^QCDscale/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^acceptance/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^pdf_/d' HETau_etauhad_4_2018_m125.txt
source Limits.sh
cd ..
mkdir PLP
cp H* PLP
cp Limits.sh PLP
cd PLP
sed -i '/^CMS_P/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_lumi/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS_P/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_lumi/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS_P/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_lumi/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS_P/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^CMS_lumi/d' HETau_etauhad_4_2018_m125.txt
source Limits.sh
cd ..
mkdir Syst
cp H* Syst
cp Limits.sh Syst
cd Syst
sed -i '/^CMS/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^BR_/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^norm/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^QCDscale/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^acceptance/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^pdf/d' HETau_etauhad_1_2018_m125.txt
sed -i '/^CMS/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^BR_/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^norm/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^QCDscale/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^acceptance/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^pdf/d' HETau_etauhad_2_2018_m125.txt
sed -i '/^CMS/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^BR_/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^norm/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^QCDscale/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^acceptance/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^pdf/d' HETau_etauhad_3_2018_m125.txt
sed -i '/^CMS/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^BR_/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^norm/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^QCDscale/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^acceptance/d' HETau_etauhad_4_2018_m125.txt
sed -i '/^pdf/d' HETau_etauhad_4_2018_m125.txt
source Limits.sh
cd ..
