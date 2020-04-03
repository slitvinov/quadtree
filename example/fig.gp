set term pngcairo
set output "fig.png"
set key off
set size sq
plot \
"data/fig.points" w p pt 6, \
"<./main data/fig.points data/fig.query" w p pt 6 \
