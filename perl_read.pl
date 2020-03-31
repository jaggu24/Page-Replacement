# print "hello";
use Chart::Gnuplot;
open(data, "<", "output.txt");
#print data[1];
my $i = 0;
my $save1 = "fifo.jpeg";
foreach $line (<data>)
{
	if($i == 0)
	{
		$save1 = "lru.jpeg";
		print "always"; 
	}elsif($i == 1)
	{
		$save1 = "opt.jpeg";
		print "i=1";
	}elsif($i == 2)
	{
		print "i=2";
		$save1 = "sec.jpeg";
	}else{
		print "no";
	}
	chomp $line;
	my @y = split ",", $line;
	my @x = (3 .. 6);
#	my @y = (0 .. 20);
	
	# Create chart object and specify the properties of the chart
	my $chart = Chart::Gnuplot->new(
		output => $save1,
		title  => "Simple testing",
		xlabel => "My x-axis label",
		ylabel => "My y-axis label",
	);
	
	# Create dataset object and specify the properties of the dataset
	my $dataSet = Chart::Gnuplot::DataSet->new(
		xdata => \@x,
		ydata => \@y,
		title => "Plotting a line from Perl arrays",
		style => "linespoints",
	);
	
	# Plot the data set on the chart
	$chart->plot2d($dataSet);
	print "\n";
	$i += 1;
	print $i;
	#	print $line;
}
