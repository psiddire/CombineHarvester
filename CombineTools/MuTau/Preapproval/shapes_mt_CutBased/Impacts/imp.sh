cd ..
find . -type f -name "*_1_*.txt" -exec cp {} ./Impacts/0Jet/ \;
find . -type f -name "*_2_*.txt" -exec cp {} ./Impacts/1Jet/ \;
find . -type f -name "*_3_*.txt" -exec cp {} ./Impacts/2JetGG/ \;
find . -type f -name "*_4_*.txt" -exec cp {} ./Impacts/2JetVBF/ \;
find . -type f -name "*.input.root" -exec cp {} ./Impacts/0Jet/ \;
find . -type f -name "*.input.root" -exec cp {} ./Impacts/1Jet/ \;
find . -type f -name "*.input.root" -exec cp {} ./Impacts/2JetGG/ \;
find . -type f -name "*.input.root" -exec cp {} ./Impacts/2JetVBF/ \;
cd Impacts
cd 0Jet
source impact.sh
cd ..
cd 1Jet
source impact.sh
cd ..
cd 2JetGG
source impact.sh
cd ..
cd 2JetVBF
source impact.sh
cd ..
