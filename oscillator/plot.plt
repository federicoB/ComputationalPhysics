#!/gnuplot
FILE_IN='traiettoria.txt'
FILE_OUT='output.png'
set terminal png size 1000,1000
set output FILE_OUT
set xlabel 'x' 
set ylabel 'y'
plot FILE_IN using 1:2 with lines linecolor rgb 'blue' linewidth 0.1 title 'uniform circular motion'
