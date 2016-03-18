#!/gnuplot
FILE_IN='traiettoria.txt'
FILE_OUT='confronto.png'
set terminal pngcairo
set output FILE_OUT
set xlabel 'x' 
set ylabel 'y'
set pointsize 0.2
plot FILE_IN u 1:2 w points pt 7 lc rgb 'blue' lw 3 t 'eulero'
