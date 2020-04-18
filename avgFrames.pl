
#!/usr/bin/perl 
use Chart::Gnuplot;

my $sta = 3;
my $fin = 6;
my $inc = 1;
# Opening a File in Read-only mode 
open(r, "<", "final.txt");   
# Printing content of the File
my @ans;
my $lines = 0; 
foreach $line (<r>)
{
	chomp $line;
	my @y = split ",",$line;
	foreach $elem (@y)
	{
		# print $elem+=1,"\n";
		push(@ans, int($elem));
	}
	$lines += 1;
}
my $siz1 = scalar @ans;
my @res = ();
for ($a = 0;$a < $lines;$a += 1)
{
	for($b = $a;$b < $siz1; $b += ($siz1 / $lines))
	{
		push(@res, int(@ans[$b]));
	}
} 
# print(@res);
# Closing the File 
close(r); 
my $save1 = "avg2.jpeg";
my $ist = 0;
my $ied = $lines-1;
my @x = qw(LRR OPT SECch ADDbit LFU MFU FIFO RAND);
my $chart = Chart::Gnuplot->new(
		output => $save1,
		title => "Algorithms and page faults",
		ylabel => "Percentage of Hits",
		xlabel => "Algorithms",
		# xrange => [-1, 10],
		yrange => [0, 100],
	);
my @boxes = ();
for ($i = 0;$i < ($siz1 / $lines);$i += 1)
{
	my $name;
	if($i >= 0)
	{
		$name = $sta + $i*$inc;
		$save1 = $name."Frames";
		# print "always"; 
	}
	my @re2 = [@res[$ist .. $ied]];

	$boxes[$i] = Chart::Gnuplot::DataSet->new(
		xdata => \@x,
		ydata  => @re2,
		style => "histograms",
		title => $save1,
	);

	$ist += $lines;
	$ied += $lines;
}
print "Done";
$chart->plot2d(@boxes);
