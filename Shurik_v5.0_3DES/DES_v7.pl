#!/usr/bin/perl

#---------------------------------------------------------------------------------------------
# @Script CLI args@
# 1) action:      "e" or "d", as one char string
# 2) password:    "myDesPass", as a string
# 3) input file:  "filePath1", as a string, should contain the message to encrypt
# 4) output file: "filePath2", as a string, where the encrypted message will be saved 
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# Ctyptography and Network Security 4th edition by Willian Stallings
#
# DES online calculator:
# https://www.emvlab.org/descalc
# https://asecuritysite.com/encryption/padding_des
#
# DES padding:
# NULL byte in Perl, \x00 or \0
# https://asecuritysite.com/encryption/padding_des
# https://stackoverflow.com/questions/4345789/how-to-add-null-character-to-string-in-perl
# https://www.di-mgt.com.au/cryptopad.html
# https://stackoverflow.com/questions/16082526/finding-null-character-using-regex-in-perl
#
# Perl tutorial:
# https://www.tutorialspoint.com/perl/
# http://www.perlmonks.org/
# 
# unpack/pack:
# https://www.tutorialspoint.com/perl/perl_unpack.htm
# 
# Perl references:
# https://perlmaven.com/array-references-in-perl
#
# Programmatic Conversions:
# http://perltips.wikidot.com/convert-hex-dec-oct-bin
# https://stackoverflow.com/questions/288900/how-can-i-convert-a-string-to-a-number-in-perl
#
# Online Conversions:
# http://www.rapidtables.com/convert/number/hex-to-ascii.htm
# http://www.asciitohex.com/
#
# My! SOS post:
# http://www.perlmonks.org/?node_id=1203344
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
use strict;
# use warnings;
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# DES Internal Conversion Tables
#---------------------------------------------------------------------------------------------
my @SBOXES = (
		#S1
		[
		[14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7],
		[0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8],
		[4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0],
		[15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13]
		],
		#S2
		[
		[15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10],
		[3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5],
		[0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15],
		[13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9]
		],
		#S3
		[
		[10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8],
		[13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1],
		[13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7],
		[1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12]
		],
		#S4
		[
		[7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15],
		[13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9],
		[10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4],
		[3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14]
		],
		#S5
		[
		[2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9],
		[14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6],
		[4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14],
		[11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3]
		],
		#S6
		[
		[12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11],
		[10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8],
		[9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6],
		[4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13]
		],
		#S7
		[
		[4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1],
		[13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6],
		[1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2],
		[6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12]
		],
		#S8
		[
		[13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7],
		[1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2],
		[7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8],
		[2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11]
		]
		);	

my @IP = (
     58,50,42,34,26,18,10,2,
	 60,52,44,36,28,20,12,4,
	 62,54,46,38,30,22,14,6,
	 64,56,48,40,32,24,16,8,
	 57,49,41,33,25,17, 9,1,
	 59,51,43,35,27,19,11,3,
	 61,53,45,37,29,21,13,5,
	 63,55,47,39,31,23,15,7
	 );

my @IP_INVERSE = (
		40,8,48,16,56,24,64,32,
		39,7,47,15,55,23,63,31,
		38,6,46,14,54,22,62,30,
		37,5,45,13,53,21,61,29,
		36,4,44,12,52,20,60,28,
		35,3,43,11,51,19,59,27,
		34,2,42,10,50,18,58,26,
		33,1,41,9,49,17,57,25
		);
	 
my @E = (
		32,1,2,3,4,5,
		4,5,6,7,8,9,
		8,9,10,11,12,13,
		12,13,14,15,16,17,
		16,17,18,19,20,21,
		20,21,22,23,24,25,
		24,25,26,27,28,29,
		28,29,30,31,32,1
		);	 	 

my @P = (
		16,7,20,21,29,12,28,17,
		1,15,23,26,5,18,31,10,
		2,8,24,14,32,27,3,9,
		19,13,30,6,22,11,4,25
		);

my @PC_1 = (
	57,49,41,33,25,17,9,
	,1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4
	);

my @PC_2 = (
	14,17,11,24,1,5,3,28,
	15,6,21,10,23,19,12,4,
	26,8,16,7,27,20,13,2,
	41,52,31,37,47,55,30,40,
	51,45,33,48,44,49,39,56,
	34,53,46,42,50,36,29,32
	);

my @ScheduleOfLeftShifts = (1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1);
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# Globals and CLI args
#---------------------------------------------------------------------------------------------
my $action = checkAction($ARGV[0]); 
my $subKeysRef = createRoundKeys($ARGV[1]);
my $InputFileName = $ARGV[2];
my $OutputFileName = $ARGV[3];

# this is an array where each element is a ref to a bits-array of the index/round sub-key
# @$: dereference a refrence to an array
my @SubKeys = @$subKeysRef;

# holds data to read/write from/to file
my @FileArray = ();

# a meta-data var about the DES padding 
my $diff = 0;
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#                         
#---------------------------------------------------------------------------------------------
sub checkAction {
	my $action = $_[0];
	
	if( ($action eq "e") or ($action eq "d") ) {
		return $action;
	}
	else {
		die "#ERROR: action parameter is wrong (\"e\"=encryption, \"d\"=decryption)#\n";
	}
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#                   
#---------------------------------------------------------------------------------------------
sub createRoundKeys {
	
	my $key = $_[0];
	if(length $key != 8) { die "#ERROR: DES key is not 64 bit#\n";}
	
	my ($i, $j);
	
	# to hold references to sub-keys for each round according to array index.
	# the function returns a reference of this array to be farther used.
	my @subKeys = ();
	
	# unpack returns the key string as a corresponding bit string
	# 64 bit where B indicates highest first  
	my @tempArr = unpack("B64", $key);
	
	# split bit string to corresponding bits array and convert to numeric bits
	#PerlMonk:robotics#
	my @keyBitsArr = map { $_+0 } split("", $tempArr[0]);
	
	
	#------------------------------------------------------------
	# permuted choice one(@PC_1)
	# each index in the keyBitsArr56_PC1 gets some bit from the 64-bit original key according to some mapping, PC-1
	#PerlMonk:robotics#
	my @keyBitsArr56_PC1 = map { $keyBitsArr[$PC_1[$_]-1] } 0 .. $#PC_1;
	
	# split permuted choice 1 outcome @keyBitsArr56_PC1 to two 28 bit arrays, left and right
	#PerlMonk:robotics#
	my @leftBitsArr = @keyBitsArr56_PC1[0..27];
    my @rightBitsArr = @keyBitsArr56_PC1[28..55];
	#------------------------------------------------------------
	
	#------------------------------------------------------------
	# create sub-keys for each round
	@tempArr = ();
	for($i=0; $i<16; $i++) {
		
			# shift each part individually
			#PerlMonk:robotics#
			for(0 .. $ScheduleOfLeftShifts[$i]-1) {
				# shift left part according to round
				push(@leftBitsArr, shift(@leftBitsArr));
				# shift right part according to round
				push(@rightBitsArr, shift(@rightBitsArr));
			}
		
		# PC_2, get 48 bit round sub key
		
			# unite to one 56 bits arr
			#PerlMonk:robotics#
			@tempArr = (@leftBitsArr, @rightBitsArr);
			
			# permuted choice two
			# save round key	
			#PerlMonk:robotics#
			@{$subKeys[$i]} = map { $tempArr[$PC_2[$_]-1] } 0 .. $#PC_2;				
	}
	#------------------------------------------------------------

	return \@subKeys;
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#                           
#---------------------------------------------------------------------------------------------
sub des {

	my ($i, $j, $k, $tempVar, @tempArr);
	
	# iterate over input file in chunks of 64 bit, DES ECB-mode of operation
	for($i=0; $i<=$#FileArray; $i++) {
		
		# convert block read from file to its binary rep
		$tempVar = unpack("B64", $FileArray[$i]);
		
=begin		
		#----------------------------------------
        # DEBUG/PoC
        #PerlMonk:robotics#
        my $hex = join("", map { sprintf "%02X", $_ } unpack("C*",$FileArray[$i]));
        # print("($i): $hex <$FileArray[$i]>\n");
        print("($i): $hex\n");
        #----------------------------------------
=cut

		# an array of bits as numeric values, the block rep as numeric binary numbers
		# convert to numeric bits
		#PerlMonk:robotics#
		my @bitsArray = map { $_+0 } split("", $tempVar);
		
		# initial permutation (IP) for each block/64 bit chunk before the 16 rounds
		#PerlMonk:robotics#
		my @bitsArray_ip = map { $bitsArray[$IP[$_]-1] } 0 .. $#IP;
		
		# split to: left and right
		my @leftBitsArr = @bitsArray_ip[0 .. 31];
        my @rightBitsArr = @bitsArray_ip[32 .. 63];
		
		# 16 DES rounds per 64 bit chunk treated as two 32 bit chunks
		for($j=0; $j<16; $j++) {
			
			my @nextLeftBitsArr = @rightBitsArr;
				
			# curr right bits chunk expansion/permutation (E)
			#PerlMonk:robotics#
			@rightBitsArr = map { $rightBitsArr[$E[$_]-1] } 0 .. $#E;
			
			# XOR with round sub-key: check function bool param for encryption/decryption action
			my $ref;
			
			if($action eq "e") {
				$ref =  $SubKeys[$j];# j - index of curr round
			}
			elsif($action eq "d") {
				$ref =  $SubKeys[15-$j];# j - index of curr round reversed
			}
			
			my @roundSubKey = @$ref;# de-ref to bits-array
			
			for($k=0; $k<48; $k++) {	
				$rightBitsArr[$k]^=$roundSubKey[$k];				
			}
			
			# S-box
			#PerlMonk:robotics#
            my $sBoxResult = 0;
            for($k=0; $k<8; $k++) {
                my $sBoxRow = $rightBitsArr[$k*6]*2   + $rightBitsArr[$k*6+5];
                my $sBoxCol = $rightBitsArr[$k*6+1]*8 + $rightBitsArr[$k*6+2]*4 
                            + $rightBitsArr[$k*6+3]*2 + $rightBitsArr[$k*6+4];
                $sBoxResult = ($sBoxResult<<4) + $SBOXES[$k][$sBoxRow][$sBoxCol];
            }
            my $sBoxResStr = unpack("B32", pack("N", $sBoxResult));

			#convert to numeric bits
			#PerlMonk:robotics#
            @rightBitsArr = map { $_+0 } split("", $sBoxResStr);# now 32 bits, $sBoxResStr was loop concat.
			
			 # Permute the bits, then xor the resulting bit with leftBitsArr
            @rightBitsArr = map { $rightBitsArr[$P[$_]-1] ^ $leftBitsArr[$_] } 0 .. $#P;
			
			# assign next values
			@leftBitsArr = @nextLeftBitsArr;
		}
		
		# swap two sides
		my @temp = @leftBitsArr;
		@leftBitsArr = @rightBitsArr;
		@rightBitsArr = @temp;
		
		# merge and inverse initial permutation --> output 64 bit chunk cipher-text
		#PerlMonk:robotics#
		@bitsArray = (@leftBitsArr, @rightBitsArr);
        my @bitsArray_ip_inverse = map { $bitsArray[$IP_INVERSE[$_]-1] } 0 .. $#IP_INVERSE;
		
		#save manipulated chunk to same index in @FileArray
		#PerlMonk:robotics#
		$FileArray[$i] = pack("B64", join("", @bitsArray_ip_inverse));
	}
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# At the minimum scrambles traces of the DES procedure variables that are sensitive                        
#---------------------------------------------------------------------------------------------
sub scrambleMemDump {
		$diff = -1;
		for(my $i=1; $i<$#SubKeys; $i++) {
			$SubKeys[$i] = -1;
		}
		$subKeysRef = -1;
		for(my $i=1; $i<$#FileArray; $i++) {
			$FileArray[$i] = 0;
		}
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# I/O functions                          
#---------------------------------------------------------------------------------------------
sub readInputToArray {
	
	open(FILEHANDLER, "<".$InputFileName) or die "#ERROR: can't open input file#$InputFileName\n$OutputFileName\n";
	my $i = 0;
	while(1) {
		# read a block of data, block size is 8 bytes/64 bits 
		my $bytes = read (FILEHANDLER, my $chunk, 8);

		if($bytes == 0) {
			last;
		}
		else {
			$FileArray[$i] = $chunk;
			$i++;
		}
	} 
	close(FILEHANDLER) or die "#ERROR: couldn't close input file properly#\n";
	
	if($action eq "e") {
		# padding at the end to fit 8 byte/64 bit chunks for DES blocks
		my $lastBlockSize = length $FileArray[$#FileArray];
		# $diff = 0;
		if($lastBlockSize < 8) {
			$diff = 8 - $lastBlockSize;
			# create the padding string
			# "\0" is the NULL byte, i.e. I use the NULL byte pedding method
			#my $padding = "\0" x $diff; 
			my $padding = " " x $diff;
			# concat last block to pedding string
			$FileArray[$#FileArray].=$padding;
		}
		
		# add $diff to beginning of the @FileArray i.e. write it first in the output-file
		# $diff will be ecnrypted as well!
		# if $diff=0 no problem we can write as well.
		unshift(@FileArray, $diff);
	}
}

sub writeOutputToFile {

	open(FILEHANDLER, ">".$OutputFileName) or die "#ERROR: can't open output file#\n";
	
	if($action eq "e") {
		
		for(my $i=0; $i<=$#FileArray; $i++) {
			print FILEHANDLER $FileArray[$i];
		}
	}
	elsif($action eq "d") {
		
		# read first line for the diff meta-data of padding
		$diff = $FileArray[0]; 
		
		# read the rest exclude the last
		for(my $i=1; $i<$#FileArray; $i++) {
			print FILEHANDLER $FileArray[$i];
		}
		
		# do the last one that may be padded
		$FileArray[$#FileArray] = substr($FileArray[$#FileArray], 0, length($FileArray[$#FileArray])-$diff);
		print FILEHANDLER $FileArray[$#FileArray];
	}
	
	close(FILEHANDLER) or die "#ERROR: couldn't close output file properly#\n";
	
	# enhance security
	scrambleMemDump();
}
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# Execute
#--------------------------------------------------------------------------------
readInputToArray();
des();
writeOutputToFile();
scrambleMemDump();
#--------------------------------------------------------------------------------












