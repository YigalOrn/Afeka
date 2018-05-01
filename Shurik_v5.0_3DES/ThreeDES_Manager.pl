#!/usr/bin/perl

#---------------------------------------------------------------------------------------------
# @Script Parameters@
# 1) 
# 2) 
# 3) 
#---------------------------------------------------------------------------------------------

use strict;
# use warnings;

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
my $action = $ARGV[0];
my $threeDesKey = $ARGV[1];
my $desKey1 = substr($threeDesKey, 0, 8);
my $desKey2 = substr($threeDesKey, 8);
my $tempTextFilePath = $ARGV[2];
my $inputFilePath = $ARGV[3];
my $outputFilePath = $ARGV[4];
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
sub encryption_3des {
	 `perl ./DES_v7.pl "e" "$desKey1" "$inputFilePath" "$tempTextFilePath"`;
	 `perl ./DES_v7.pl "d" "$desKey2" "$tempTextFilePath" "$tempTextFilePath"`;
	 `perl ./DES_v7.pl "e" "$desKey1" "$tempTextFilePath" "$outputFilePath"`;
	 unlink $tempTextFilePath;
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
sub decryption_3des {
	 `perl ./DES_v7.pl "d" "$desKey1" "$inputFilePath" "$tempTextFilePath"`;
	 `perl ./DES_v7.pl "e" "$desKey2" "$tempTextFilePath" "$tempTextFilePath"`;
	 `perl ./DES_v7.pl "d" "$desKey1" "$tempTextFilePath" "$outputFilePath"`;
	 unlink $tempTextFilePath;
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# Execute
#---------------------------------------------------------------------------------------------
if($action eq "e") {
	encryption_3des();
}
elsif($action eq "d") {
	decryption_3des();
}
else {
	die "#ERROR: action parameter is wrong (\"e\"=encryption, \"d\"=decryption)#\n";
}
