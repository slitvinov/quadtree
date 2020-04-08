set term svg
set output "rectangle.svg"
set key off
set size sq
plot \
"data/points" w p pt 6, \
"<./rectangle data/points data/rectangle.query" w p pt 6 \
