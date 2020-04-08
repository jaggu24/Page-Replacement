
#!/usr/bin/perl 
use Chart::Gnuplot;
# Opening a File in Read-only mode 
open(r, "<", "output.txt");   
# Printing content of the File
my @ans;
my $lines = 0; 
foreach $line (<r>)
{
	chomp $line;
	my @y = split ",",$line;
	foreach $elem (@y)
	{
		print $elem+=1,"\n";
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
print(@res);
# Closing the File 
close(r); 
my $save1 = "bars.jpeg";
my $ist = 0;
my $ied = $lines-1;
for ($i = 0;$i < ($siz1 / $lines);$i += 1)
{
	if($i == 0)
	{
		$save1 = "FFlru.jpeg";
		print "always"; 
	}elsif($i == 1)
	{
		$save1 = "FFopt.jpeg";
		print "i=1";
	}elsif($i == 2)
	{
		print "i=2";
		$save1 = "FFsec.jpeg";
	}elsif($i == 3)
	{
		$save1 = "FFAdditional_bit.jpeg";
	}
	else
	{
		print "NO";
	}
	my @re2 = [@res[$ist .. $ied]];
	my $chart = Chart::Gnuplot->new(
		output => $save1,
		xrange => [-1, 10],
		yrange => [0, 50],
	);

	my $boxes = Chart::Gnuplot::DataSet->new(
		ydata  => @re2,
		style => "boxes",
	);

	$chart->plot2d($boxes);
	$ist += $lines;
	$ied += $lines;
}
