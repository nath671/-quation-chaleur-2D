title_text = sprintf("Temps = %d s", i * 100)

set title title_text

splot "EDP_2D.txt" index (i) u 2:1:3 

i = i+1
if (i<=imax) reread