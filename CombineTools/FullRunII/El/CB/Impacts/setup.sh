find . -type f -name "*_1_*.txt" -exec cp {} ./0Jet/ \;
find . -type f -name "*_2_*.txt" -exec cp {} ./1Jet/ \;
find . -type f -name "*_3_*.txt" -exec cp {} ./2JetGG/ \;
find . -type f -name "*_4_*.txt" -exec cp {} ./2JetVBF/ \;
find . -type f -name "*.input.root" -exec cp {} ./0Jet/ \;
find . -type f -name "*.input.root" -exec cp {} ./1Jet/ \;
find . -type f -name "*.input.root" -exec cp {} ./2JetGG/ \;
find . -type f -name "*.input.root" -exec cp {} ./2JetVBF/ \;
