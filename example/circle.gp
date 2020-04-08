set term svg
set output "circle.svg"
set key off
set size sq
plot \
"data/points" w p pt 6, \
"<./circle data/points data/circle.query" w p pt 6 \
