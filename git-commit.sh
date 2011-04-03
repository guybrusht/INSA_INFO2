#! /bin/bash

rm *.out *.o *.*~ *~
git add *
DATE=`date '+%d%h%Y-%H%M%S'`
git commit -m `echo $DATE`
git push -u origin master
