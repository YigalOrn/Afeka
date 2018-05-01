#!/usr/bin/perl

#---------------------------------------------------------------------------------------------
# @Script Parameters@
# 1) path to decrypted confusion file 
# 2) path to decrypted confusion map file
#---------------------------------------------------------------------------------------------

use strict;
# use warnings;

my $confusionDecryptionFilePath = $ARGV[0];
my $confusionMapDecryptionFilePath = $ARGV[1];


open(FILEHANDLER, "<".$confusionDecryptionFilePath) or die "#DeConfusion ERROR: can't open confusionDecryption#\n";
my @confusionDecryptionLines = <FILEHANDLER>;
close(FILEHANDLER) or die "#DeConfusion ERROR: couldn't close confusionDecryption properly#\n";

open(FILEHANDLER, "<".$confusionMapDecryptionFilePath) or die "#DeConfusion ERROR: can't open confusionMapDecryption#\n";
my @confusionMapDecryptionLines = <FILEHANDLER>;
close(FILEHANDLER) or die "#DeConfusion ERROR: couldn't close confusionMapDecryption properly#\n";


my @fields = ();

for(my $i=0; $i<=$#confusionMapDecryptionLines; ++$i) {
	
	my $sed_command = $confusionMapDecryptionLines[$i];
	
	if ($sed_command =~ m/^s\/.*\/.*\/g$/) {
		@fields = split(/\//, $sed_command);
		#print("$fields[1] $fields[2]\n");
		for(my $j=0; $j<=$#confusionDecryptionLines; ++$j) {
			$confusionDecryptionLines[$j] =~ s/$fields[1]/$fields[2]/g;	
			#print("$confusionDecryptionLines[$j]\n");
		}
	}
	elsif ($sed_command =~ m/^s\/.*\/.*\/gi$/) {
		@fields = split(/\//, $sed_command);
		#print("@fields\n");
		for(my $j=0; $j<=$#confusionDecryptionLines; ++$j) {
			$confusionDecryptionLines[$j] =~ s/$fields[1]/$fields[2]/gi;
			#print("$confusionDecryptionLines[$j]\n");	
		}
	}
}

open(FILEHANDLER, ">".$confusionDecryptionFilePath) or die "#DeConfusion ERROR: can't open confusionDecryption#\n";
for(my $j=0; $j<=$#confusionDecryptionLines; ++$j) {
	print FILEHANDLER $confusionDecryptionLines[$j];
	#print("$confusionDecryptionLines[$j]\n");
}
close(FILEHANDLER) or die "#DeConfusion ERROR: couldn't close confusionDecryption properly#\n";





