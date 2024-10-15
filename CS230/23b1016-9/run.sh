#!/bin/bash
x=4096
s=("1" "2" "4" "8" "16" "32" "64" "128" "256" "512") 
f=("tex.din"    "spice.din" "cc1.din")
for f in ${f[@]};
do
    echo "For assoc: "$f >> output3.txt
    for x in ${s[@]}; 
    do
        echo "For block size: "$x
        y="./dineroIV -l1-usize 8192 -l1-ubsize 16 -l1-uassoc ${x} -l1-uwback a -l1-uwalloc a -informat d -l1-uccc"
        $y < d4-traces/d4-traces/$f | grep "Demand miss rate" | awk '{print $4}' >> output3.txt
    done
done