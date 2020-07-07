#!/bin/bash

OUT_DIR=/home/jahn/gem5/m5out
GEM5_DIR=/home/jahn/gem5
mkdir -p $OUT_DIR

${GEM5_DIR}/build/ARM/gem5.opt --outdir=$OUT_DIR"/LRU_S2" ${GEM5_DIR}/configs/final/LRU_s.py &
${GEM5_DIR}/build/ARM/gem5.opt --outdir=$OUT_DIR"/LIP_S2" ${GEM5_DIR}/configs/final/LIP_s.py &
${GEM5_DIR}/build/ARM/gem5.opt --outdir=$OUT_DIR"/BIP_S2" ${GEM5_DIR}/configs/final/BIP_s.py


for pid in $(jobs -p)
do
  wait $pid
done



