#!/usr/bin/perl


#---------------------------------------------------------------------------------------------
# @Script Parameters@
# 1) action: e/d as one char string
# 2) message
# 3) output file to save message
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# Ctyptography and Network Security 4th edition by Willian Stallings
#
# conversions:
# https://stackoverflow.com/questions/483655/how-do-i-convert-a-binary-string-to-a-number-in-perl
# https://stackoverflow.com/questions/29047084/perl-decimal-and-binary-conversion-with-big-numbers
#
# pack/unpack:
# http://perldoc.perl.org/functions/pack.html
# http://www.perlmonks.org/?node_id=224666
# http://perldoc.perl.org/perlpacktut.html
# 
# shift:
# https://perldoc.perl.org/functions/shift.html
#
# read whole file:
# http://www.perlmonks.org/?node_id=1952
#
# gcd:
# https://he.wikipedia.org/wiki/%D7%9E%D7%97%D7%9C%D7%A7_%D7%9E%D7%A9%D7%95%D7%AA%D7%A3_%D7%9E%D7%A7%D7%A1%D7%99%D7%9E%D7%9C%D7%99
#
# decimal to binary:
# http://www.perlmonks.org/?node_id=2664
#
# How RSA works:
# https://he.wikipedia.org/wiki/RSA
# http://doctrina.org/How-RSA-Works-With-Examples.html
#
# prime tables:
# http://www.bigprimes.net/archive/prime/14000000/	
# https://www.factmonster.com/math/numbers/prime-numbers-facts-examples-table-all-1000
#
# ASCII info:
# http://www.rapidtables.com/code/text/ascii-table.htm
# https://www.branah.com/ascii-converter
#
# RSA online calculator:
# https://www.cs.drexel.edu/~introcs/Fa11/notes/10.1_Cryptography/RSA_Express_EncryptDecrypt.html
# http://extranet.cryptomathic.com/rsacalc/index
#
# online Convertors:
# http://www.asciitohex.com/
# http://www.binaryhexconverter.com/decimal-to-hex-converter
# 
# proof of concept:
# https://introcs.cs.princeton.edu/java/99crypto/RSA.java.html
#---------------------------------------------------------------------------------------------


#---------------------------------------------------------------------------------------------
# cpan install bignum
# used to wrap integers and floats into dedicated objects that handle very large numbers.
# http://perldoc.perl.org/bignum.html 
#---------------------------------------------------------------------------------------------
use bignum;
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# build in module(at least on ubuntu 16.04 LTS)
# used in: bin2dec(..), dec2bin(..)
# helps deal with big number conversions  
#---------------------------------------------------------------------------------------------
use Math::BigInt;
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
use strict;
# use warnings;
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#Simple RSA algo:
#1) get two satisfactory primes: p, q.
#2) calc n = p*q, M<n (M is the message to be ecnrypted. M should be less then n in binary representation).
#3) calc Euler totient function, phi, for the arg n using the formula: phi(n) = (p-1)*(q-1).
#4) find e where gcd(e,phi(n))=1 and 1<e<phi(n).
#5) calc d the inverse of e mod phi(n). (multiplicative inverse: d*e mod(phi) = 1 mod(phi))
#6) encryp:  PU{e,n}.
#7) decrypt: PR{d,n}.

#checked manually that M<n for this given primes, M is the 64-bit.
#{primes}/n: {32416187567,32416190071}/n(70-bit)
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# CLI parameters and globals
#---------------------------------------------------------------------------------------------
my $p = 32416187567;
my $q = 32416190071;
my $n = $p*$q;
my $phi = ($p-1)*($q-1);
my ($e, $d) = initRSA();
my $filePath = $ARGV[2];
my $M = $ARGV[1];
my $action = $ARGV[0];
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# Takes 2 numbers: a and b (a>=b).          
# Finds the geratest common divisor of a and b.
# From all x such x<=max(a,b), if max(X) is a divisor of a and b then it is the GCD output .                   
#---------------------------------------------------------------------------------------------
sub myGCD {
	my ($a, $b) = @_;
	return ($b==0 ? $a : myGCD($b, $a%$b));
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# Takes 1 number: phi.          
# Finds a number e such that e and phi are coprime integres and e<phi.
# The gcd of e and phi is 1 i.e. their max common divisor is 1 or gcd(phi,1) is 1.                  
#---------------------------------------------------------------------------------------------
sub find_e {
	my ($phi) = $_[0];
	my $e = 2;
	while(1) {
		my $r = myGCD($phi, $e);
		if($e == $phi) {
			die "#ERROR: cant do RSA, e>=phi#\n";
		}
		elsif($r == 1) {
			return $e;	
		}
		else {
			$e++;
		}
	}
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# Takes 2 numbers: phi and e           
# Finds a number d such that:          
# d*e mod(phi) = 1 mod(phi)            
#---------------------------------------------------------------------------------------------
sub multiplicativeInverse {
   
   my ($a, $b) = @_;
   my $phi = $a;
   my $y1 = 1;
   my $y2 = 0;

   while ($b > 0)
   {
      my $q = int($a/$b);
      my $y = $y2 -($q * $y1);
      my $r = $a % $b;
      $a = $b;
      $b = $r;
      $y2 = $y1, $y1 = $y;
   }
   
   # modular arthmetic properties(page 103, 271)
   # (axb)%n = [(a%n)x(b%n)]%n
   if($y2<0) {
		$y2 = $y2+$phi;
	}
   
   return $y2; 
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# representation conversion functions
#---------------------------------------------------------------------------------------------
sub bin2dec {
  my $bin = shift;
  return Math::BigInt->new("0b$bin");
}

sub dec2bin {
  my $dec = shift;
  my $i = Math::BigInt->new($dec);
  return substr($i->as_bin(), 2);
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# calc: (a^b) mod n
# page: 271-272
# the suggested technique allows the use of big numbers in the calculation while in the same time
# it also incorporates several math ops
#---------------------------------------------------------------------------------------------
sub fastExpModExtended {
	my ($a, $b, $n) = @_;
	my $b_bin_str = dec2bin($b);
	my @b_bin_arr = split("", $b_bin_str);
	my $f=1;
	for(my $i=0; $i<=$#b_bin_arr; $i++) {
		$f = ($f*$f)%$n; 
		if($b_bin_arr[$i] == 1) {
			$f = ($f*$a)%$n;
		}			
	}
	return $f;
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#           
#                   
#---------------------------------------------------------------------------------------------
sub checkAction {
	my $action = $_[0];
	
	if($action eq "e") {
		encryption();
	}
	elsif($action eq "d") {
		decryption();
	}
	else {
		die "#ERROR: action parameter is wrong (\"e\"=encryption, \"d\"=decryption)#\n";
	}
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
sub initRSA {
	my $e = find_e($phi);
	my $d = multiplicativeInverse($phi, $e);
	return ($e, $d);
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#           
#                   
#---------------------------------------------------------------------------------------------
sub writeToFile {
	my ($enc_1, $enc_2) = @_;
	open(FILEHANDLER, ">".$filePath) or die "#ERROR: can't open output file#\n";
	print FILEHANDLER $enc_1, "\n";
	print FILEHANDLER $enc_2, "\n";
	close(FILEHANDLER) || die "#ERROR: couldn't close output file properly#\n";
}
#--------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#           
#                   
#---------------------------------------------------------------------------------------------
sub readFromFile {
	#my $enc;
	#local $/ = undef;
	#open FILE, $filePath or die "Couldn't open file: $!";
	#binmode FILE;
	#$enc = <FILE>;
	#close FILE;
	#return $enc;
	
	open(FILEHANDLER, "<".$filePath) or die "#ERROR: can't open file#\n";
	my @inputLines = <FILEHANDLER>;
	close(FILEHANDLER) or die "#ERROR: couldn't close file properly#\n";
	
	return @inputLines;
}
#--------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
sub encryption {
	my @M_bin_arr = unpack("B64B64", $M);	
	my $M_bin_1 = $M_bin_arr[0];
	my $M_bin_2 = $M_bin_arr[1];
	
	my $M_num_1 = bin2dec($M_bin_1);
	my $enc_1 = fastExpModExtended($M_num_1, $e, $n);
	my $M_num_2 = bin2dec($M_bin_2);
	my $enc_2 = fastExpModExtended($M_num_2, $e, $n);
	
	
	writeToFile($enc_1, $enc_2);
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
sub decryption {
	
	my $diff = 0;
	my ($enc_1, $enc_2) = readFromFile();
	
	my $dec_1 = fastExpModExtended($enc_1, $d, $n);
	my $M_bin_1 = dec2bin($dec_1);
	$diff = 64-length($M_bin_1);
	$M_bin_1 = ("0"x$diff).$M_bin_1;
	my $M_1 = pack("B64", $M_bin_1);
	
	my $dec_2 = fastExpModExtended($enc_2, $d, $n);
	my $M_bin_2 = dec2bin($dec_2);
	$diff = 64-length($M_bin_2);
	$M_bin_2 = ("0"x$diff).$M_bin_2;
	my $M_2 = pack("B64", $M_bin_2);
	
	my $M = "$M_1"."$M_2";
	
	print("$M\n");# for bash to catch
}
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
# Execute
#---------------------------------------------------------------------------------------------
checkAction($action);

