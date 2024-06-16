
set ylabel "y (m)"
set xlabel "x (m)"

imax = 200
i = 0

set palette rgbformulae 22,13,-31

set cbrange [0:50]

set pm3d map interpolate 0,0 # interpolation auto
set term gif size 1200, 900  animate delay 5
set output "resultat.gif"

set yrange [0:3]
set xrange [0:4]

load "script_animation_convection2D.gnu"

