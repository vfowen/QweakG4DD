#/bin/csh
#================================================
#     Macro file for Hadr00 run over all Physics Lists
#     26.06.2009 V.Ivanchneko
#================================================

rm -f $1.out
build/Hadr00 $2.in $1 >& $1.out 

#
