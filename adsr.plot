#!/usr/bin/gnuplot
#set terminal png large size 1280, 720 enhanced font 'Times-Roman' nocrop transparent
set terminal svg  size 1280, 720 enhanced font 'Times-Roman' 
set output 'ADSR.svg'
set xlabel 'milliseconds'
set ylabel 'Volts'
set yrange[0:12]
plot 'ggg' using 1:2 title 'CV' with lines, 'ggg' using 1:4 title 'Gate' with line, 'ggg' using 1:3 title 'Phase' with lines 
