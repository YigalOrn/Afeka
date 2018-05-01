#!/usr/bin/perl

#---------------------------------------------------------------------------------------------
# @Script Parameters@
# 1) path to plaintext
# 2) path to the plaintext after substi'(named confusion.txt)
# 3) path confusion mapping to reverse the actions 
#---------------------------------------------------------------------------------------------

use strict;
# use warnings;

my $plaintextFilePath = $ARGV[0];
my $confusionFilePath = $ARGV[1];
my $confusionMapFilePath = $ARGV[2];

open(FILEHANDLER, "<".$plaintextFilePath) or die "#Confusion ERROR: can't open plaintextFilePath#\n";
my @inputLines = <FILEHANDLER>;
close(FILEHANDLER) or die "#Confusion ERROR: couldn't close plaintextFilePath properly#\n";

#-----------------------------------------------------------------------------------------
my $arg1 = "s/param1/param2/g";
my $arg2 = "s/param1/param2/gi";
print("The script supports sed like commands of the form:\n$arg1\n$arg2\n",
	  "The script doesnt support regex as params, only simple/complete words\n");
#-----------------------------------------------------------------------------------------

my $cont = 0;
my @fields = ();

open(FILEHANDLER, ">".$confusionMapFilePath) or die "#Confusion ERROR: can't open confusionMapFilePath#\n";

do {
	print("sed like command>");
	my $sed_command=<STDIN>;
	
	if ($sed_command =~ m/^s\/.*\/.*\/g$/) {
		@fields = split(/\//, $sed_command);
		
		print FILEHANDLER "s/".$fields[2]."/".$fields[1]."/g\n";
		
		for(my $i=0; $i<=$#inputLines; ++$i) {
			$inputLines[$i] =~ s/$fields[1]/$fields[2]/g;	
		}
	}
	elsif ($sed_command =~ m/^s\/.*\/.*\/gi$/) {
		@fields = split(/\//, $sed_command);
		
		print FILEHANDLER "s/".$fields[2]."/".$fields[1]."/gi\n";
		
		for(my $i=0; $i<=$#inputLines; ++$i) {
			$inputLines[$i] =~ s/$fields[1]/$fields[2]/gi;	
		}
	}
	else {
		print("#wrong format no match#\n");
	}
	
	print("continue? (y/n)\n");
	chomp(my $userChoice=<STDIN>);
	if($userChoice eq "y") {
		$cont=1;
	}
	elsif($userChoice eq "n") {
		$cont=0;
	}
} while($cont);	

close(FILEHANDLER) or die "#Confusion ERROR: couldn't close confusionMapFilePath properly#\n";

open(FILEHANDLER, ">".$confusionFilePath) or die "#Confusion ERROR: can't open confusionFilePath#\n";
for(my $i=0; $i<=$#inputLines; ++$i) {
	print FILEHANDLER $inputLines[$i];
}
close(FILEHANDLER) or die "#Confusion ERROR: couldn't close confusionFilePath properly#\n";











