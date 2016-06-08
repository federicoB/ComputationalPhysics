#!/gnuplot
#define a variabile FILE_IN for input file name
FILE_IN='traiettoria.txt'
#define a variabile FILE_OUT for output file name
FILE_OUT='output.png'
#set the output as a png image with 1000 width and 1000 height
set terminal png size 1000,1000
#set the output to output file
set output FILE_OUT
#set the name of the x axis
set xlabel 'x' 
#set the mane of the y axis
set ylabel 'y'
#plot reading input file and using colum 1 and 2 of point, create a blue line with those points
plot FILE_IN using 1:2 with lines linecolor rgb 'blue' linewidth 0.1 title 'uniform circular motion'
