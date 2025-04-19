#!/bin/bash
make test -j16
cd bin
./coretest
llvm-profdata merge -o coretest.profdata default.profraw
llvm-cov show coretest --show-branches=count -instr-profile=coretest.profdata --format html -output-dir=out
firefox out/index.html 
