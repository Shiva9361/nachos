#!/bin/bash
set -e

sudo apt-get install gcc-7 g++-7 gcc-7-multilib g++-7-multilib make

cd ..
#wget https://www.fit.hcmus.edu.vn/~ntquan/os/assignment/mips-decstation.linux-xgcc.gz
tar zxvf mips-decstation.linux-xgcc.gz
