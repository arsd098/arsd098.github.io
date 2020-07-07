#!/bin/bash

OUT_DIR=/home/jahn/gem5/m5out/mcf
GEM5_DIR=/home/jahn/gem5
mkdir -p $OUT_DIR

${GEM5_DIR}/build/ARM/gem5.opt --outdir=$OUT_DIR"/LIP" ${GEM5_DIR}/configs/final/LIP.py &
${GEM5_DIR}/build/ARM/gem5.opt --outdir=$OUT_DIR"/DIP" ${GEM5_DIR}/configs/final/DIP.py &
${GEM5_DIR}/build/ARM/gem5.opt --outdir=$OUT_DIR"/BIP" ${GEM5_DIR}/configs/final/BIP.py &
${GEM5_DIR}/build/ARM/gem5.opt --outdir=$OUT_DIR"/LRU" ${GEM5_DIR}/configs/final/LRU.py &
${GEM5_DIR}/build/ARM/gem5.opt --outdir=$OUT_DIR"/TIP" ${GEM5_DIR}/configs/final/TIP.py 

for pid in $(jobs -p)
do
  wait $pid
done



