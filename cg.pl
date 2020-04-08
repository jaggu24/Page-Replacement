
#!/usr/bin/perl -w
#use strict;
use Chart::Gnuplot;

# Chart object
my $chart = Chart::Gnuplot->new(
    output => "plotStyle_4.jpeg",
    xrange => [-1, 6],
    yrange => [0, 10],
);

# Boxes
my $boxes = Chart::Gnuplot::DataSet->new(
    ydata  => [4,5,6,7,8],
    style => "boxes",
);

# Plot the graph
$chart->plot2d($boxes);

