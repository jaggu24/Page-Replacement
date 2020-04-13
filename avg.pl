open(r, "<", "output.txt");   
my $line;
my @y;
foreach $line (<r>)
{
	chomp $line;
    push(@y, [split ",",$line ]);
}
open(rl, "<", "output22.txt");
my @z;
foreach $line (<rl>)
{
        chomp $line;
        push(@z, [split ",",$line ]);
}
close(r);
close(r1);
open(w, ">", "final.txt"); 
my $siz = 25;
my $ro = scalar @y;
my $co = scalar @{ $y[0] };
#print @{ $y[0] }[3];
#print $z[0]->[3];
my @x;
for( $i = 0; $i < $ro; $i += 1)
{
	for( $j = 0; $j < $co; $j += 1)
	{
		@{ $y[$i] }[$j] = sprintf "%.2f", (($siz-@{ $y[$i] }[$j])/$siz + ($siz-@{ $z[$i] }[$j])/$siz)/2 * 100;
	}
	my $starq = join ",", @{ $y[$i] };
	print w $starq.","."\n";
}
print $ro , $co;
