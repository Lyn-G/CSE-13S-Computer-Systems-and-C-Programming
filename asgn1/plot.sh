#!/bin/bash

make clean && make collatz

# count the amount of lines from the collatz file for the first plot
for i in {2..10000}; do ./collatz -n $i | wc -l >> /tmp/plot.dat; done

# sort the numbers in numerical value, then reverse the order from the callatz file for the second plot
for j in {2..10000}; do ./collatz -n $j | sort -n | tail -n 1 >> /tmp/plot2.dat; done

# find the amount of lines in the collatz file and put into a data file
# sort this data file by numerical value
# find how many unique values there are
# put the second values into another data file
# put the first values into another data file
# graph as a histogram; (second values,first values) = (x,y)
echo "2" > /tmp/data.dat
for l in {2..10000}; do ./collatz -n $l | wc -l >> /tmp/data.dat; done
sort -n < /tmp/data.dat | uniq -c > /tmp/plot3.dat
awk '{print $2}' < /tmp/plot3.dat > data1.dat 
awk '{print $1}' < /tmp/plot3.dat > data2.dat 

# count the amount of bytes from each value in the collatz file for the fourth plot
for k in {2..10000}; do ./collatz -n $k | wc -c >> /tmp/plot4.dat; done

# we are going to produce four pdfs with one plot each
gnuplot <<END
    set terminal pdf
    set output "plot.pdf"
    set title "Collatz Sequence Lengths"
    set xlabel "n"
    set ylabel "length"
    set zeroaxis
    plot [i = 2:10000] "/tmp/plot.dat" with points pointtype 0.1 pointsize 0.1
    
    set output "plot2.pdf"
    set title "Maximum Collatz Sequence Value"
    set xlabel "n"
    set ylabel "value"
    set zeroaxis
    set yrange [:100000]
    set xrange [:10000]
    plot "/tmp/plot2.dat" with points pointtype 0.1 pointsize 0.1
    
    set output "plot3.pdf"
    set title "Collatz Sequence Length Histogram"
    set xlabel "length"
    set ylabel "frequency"
    set zeroaxis
    set yrange [:200]
    set xrange [0:225]
    set xtics 25
    set style fill solid 0.3
    plot "<paste data1.dat data2.dat" with boxes
    
    set output "interesting.pdf"
    set title "Byte Count of Each Value in Collatz Sequence"
    set xlabel "value"
    set ylabel "byte count"
    set xrange [0:5000]
    set yrange [0:1400]
    set zeroaxis
    set xtics 400
    plot "/tmp/plot4.dat" with points pointtype 0.1 pointsize 0.1  
    
END
