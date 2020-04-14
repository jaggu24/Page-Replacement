# print "hello";
use Chart::Gnuplot;
use Test::More;
use Test::Deep;

my $sta = 3;
my $fin = 6;
my $inc = 1;
my $o_file = "output.txt";
my $bin = './lru'.' '.$sta.' '.$fin.' '.$inc;
my $bc = './opt'.' '.$sta.' '.$fin.' '.$inc;
my $bd = './fifo'.' '.$sta.' '.$fin.' '.$inc;
my $be = './sec'.' '.$sta.' '.$fin.' '.$inc;
my $bf = './Add'.' '.$sta.' '.$fin.' '.$inc;
my $bg = './lfu'.' '.$sta.' '.$fin.' '.$inc;
my $bh = './mfu'.' '.$sta.' '.$fin.' '.$inc;
my $bi = './random'.' '.$sta.' '.$fin.' '.$inc;
# run the C program
$result = `$bin > $o_file`;
$result = `$bc >> $o_file`;
#$result = `$bd >> output.txt`;
$result = `$be >> $o_file`;
$result = `$bf >> $o_file`;
$result = `$bg >> $o_file`;
$result = `$bh >> $o_file`;
$result = `$bd >> $o_file`;
$result = `$bi >> $o_file`;
print $result;

open(data, "<", $o_file);
#print data[1];
my $i = 0;
my $save1 = "fifo.jpeg";
# Create chart object and specify the properties of the chart
my $chart = Chart::Gnuplot->new(
	output => "barFrms.jpeg",
	title  => "Frames and faults",
	xlabel => "No.of frames",
	ylabel => "Page Fault",
	yrange => [0, 20],
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
	print $i;
	#	print $line;
}
$chart->plot2d(@dataSet);
print "Done";
close(data);
