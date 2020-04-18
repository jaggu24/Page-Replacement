# print "hello";
use Chart::Gnuplot;
use Test::More;
use Test::Deep;

open(data, "<", "final.txt");
#print data[1];
my $i = 0;
my $save1 = "fifo.jpeg";
# Create chart object and specify the properties of the chart
my $chart = Chart::Gnuplot->new(
	output => "avgfrms.jpeg",
	title  => "Frames and faults",
	xlabel => "No.of frames",
	ylabel => "Percentage of Hits",
	yrange => [0, 100],
);
my @dataSet = ();
my @x = qw(3Frames 4Frames 5Frames 6Frames);
foreach $line (<data>)
{
	if($i == 0)
	{
		$save1 = "lru";
		# print "always"; 
	}elsif($i == 1)
	{
		$save1 = "opt";
		# print "i=1";
	}elsif($i == 2)
	{
		# print "i=2";
		$save1 = "sec";
	}elsif($i == 3)
	{
		$save1 = "AddBit";
	}elsif($i == 4)
	{
		$save1 = "lfu";
	}elsif($i == 5)
	{
		$save1 = "mfu";
	}elsif($i == 6)
	{
		$save1 = "fifo";
	}elsif($i == 7)
	{
		$save1 = "random";
	}else
	{
		print "Error in if";
	}
	chomp $line;
	my @y = split ",", $line;
#	my @y = (0 .. 20);
		
	# Create dataset object and specify the properties of the dataset
	$dataSet[$i] = Chart::Gnuplot::DataSet->new(
		xdata => \@x,
		ydata => \@y,
		title => $save1,
		style => "histograms",
	);
	
	# Plot the data set on the chart
	$i += 1;
#	print $i;
	#	print $line;
}
$chart->plot2d(@dataSet);
print "Done";
close(data);
