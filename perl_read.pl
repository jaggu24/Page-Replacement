# print "hello";
use Chart::Gnuplot;
use Test::More;
use Test::Deep;

my $o_file = "output.txt";
my $bin = './lru';
my $bc = './opt';
my $bd = './fifo';
my $be = './sec';
my $bf = './Add';
my $bg = './lfu';
my $bh = './mfu';
# run the C program
$result = `$bin > output.txt`;
$result = `$bc >> output.txt`;
#$result = `$bd >> output.txt`;
$result = `$be >> output.txt`;
$result = `$bf >> output.txt`;
$result = `$bg >> output.txt`;
$result = `$bh >> output.txt`;
print $result;

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
	}elsif($i == 3)
	{
		$save1 = "Additional_bit.jpeg";
	}elsif($i == 4)
	{
		$save1 = "lfu.jpeg";
	}elsif($i == 5)
	{
		$save1 = "mfu.jpeg";
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
		title  => $save1,
		xlabel => "No.of frames",
		ylabel => "Page Fault",
	);
	
	# Create dataset object and specify the properties of the dataset
	my $dataSet = Chart::Gnuplot::DataSet->new(
		xdata => \@x,
		ydata => \@y,
		title => "Plotting no.frames VS Pagefault",
		style => "linespoints",
	);
	
	# Plot the data set on the chart
	$chart->plot2d($dataSet);
	$i += 1;
	print $i;
	#	print $line;
}
