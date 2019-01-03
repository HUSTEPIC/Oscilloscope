#!/bin/sh  
  
exe="Oscilloscope" 
des="/home/ansel/GitRepo/Oscilloscope/build/package"
  
deplist=$(ldd $exe | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')  
cp $deplist $des
cp $exe $des
