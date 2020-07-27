sed -i '/^HETau_etaumu_/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^HETau_etaumu_/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^HETau_etaumu_/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^HETau_etaumu_/d' HETau_etaumu_4_2016_m125.txt
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
sed -i '/^CMS_Je/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS_MET_/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS_reso_/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS_scale_met_/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS_Je/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS_MET_/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS_reso_/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS_scale_met_/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS_Je/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS_MET_/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS_reso_/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS_scale_met_/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS_Je/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^CMS_MET_/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^CMS_reso_/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^CMS_scale_met_/d' HETau_etaumu_4_2016_m125.txt
source Limits.sh
cd ..
mkdir LepEff
cp H* LepEff
cp Limits.sh LepEff
cd LepEff
sed -i '/^CMS_eff_e/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS_eff_m/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS_eff_e/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS_eff_m/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS_eff_e/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS_eff_m/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS_eff_e/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^CMS_eff_m/d' HETau_etaumu_4_2016_m125.txt
source Limits.sh
cd ..
mkdir LepES
cp H* LepES
cp Limits.sh LepES
cd LepES
sed -i '/^CMS_scale_e_/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS_scale_m_/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS_scale_e_/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS_scale_m_/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS_scale_e_/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS_scale_m_/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS_scale_e_/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^CMS_scale_m_/d' HETau_etaumu_4_2016_m125.txt
source Limits.sh
cd ..
mkdir BGNorm
cp H* BGNorm
cp Limits.sh BGNorm
cd BGNorm
sed -i '/^norm/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^norm/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^norm/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^norm/d' HETau_etaumu_4_2016_m125.txt
source Limits.sh
cd ..
mkdir Theory
cp H* Theory
cp Limits.sh Theory
cd Theory
sed -i '/^BR_/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^QCDscale/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^acceptance/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^pdf_/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^BR_/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^QCDscale/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^acceptance/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^pdf_/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^BR_/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^QCDscale/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^acceptance/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^pdf_/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^BR_/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^QCDscale/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^acceptance/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^pdf_/d' HETau_etaumu_4_2016_m125.txt
source Limits.sh
cd ..
mkdir PLP
cp H* PLP
cp Limits.sh PLP
cd PLP
sed -i '/^CMS_P/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS_lumi/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS_P/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS_lumi/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS_P/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS_lumi/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS_P/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^CMS_lumi/d' HETau_etaumu_4_2016_m125.txt
source Limits.sh
cd ..
mkdir Syst
cp H* Syst
cp Limits.sh Syst
cd Syst
sed -i '/^CMS/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^BR_/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^norm/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^QCDscale/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^acceptance/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^pdf/d' HETau_etaumu_1_2016_m125.txt
sed -i '/^CMS/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^BR_/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^norm/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^QCDscale/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^acceptance/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^pdf/d' HETau_etaumu_2_2016_m125.txt
sed -i '/^CMS/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^BR_/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^norm/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^QCDscale/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^acceptance/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^pdf/d' HETau_etaumu_3_2016_m125.txt
sed -i '/^CMS/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^BR_/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^norm/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^QCDscale/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^acceptance/d' HETau_etaumu_4_2016_m125.txt
sed -i '/^pdf/d' HETau_etaumu_4_2016_m125.txt
source Limits.sh
cd ..
