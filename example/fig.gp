set term svg
set output "fig.svg"
set key off
set size sq
plot \
"data/fig.points" w p pt 6, \
"<./main data/fig.points data/fig.query" w p pt 6 \
