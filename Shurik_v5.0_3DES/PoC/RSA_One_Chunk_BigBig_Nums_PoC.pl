#!/usr/bin/perl

use strict;
use bignum;
use Math::BigInt;

sub myGCD {
	my ($a, $b) = @_;
	return ($b==0 ? $a : myGCD($b, $a%$b));
}

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
   #(axb)%n = [(a%n)x(b%n)]%n
   if($y2<0) {
		$y2 = $y2+$phi;
	}
   
   return $y2; 
}

sub bin2dec {
  my $bin = shift;
  return Math::BigInt->new("0b$bin");
}

sub dec2bin {
  my $dec = shift;
  my $i = Math::BigInt->new($dec);
  return substr($i->as_bin(), 2);
}

sub fastExpMod2 {
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
# proof of concept:
# https://introcs.cs.princeton.edu/java/99crypto/RSA.java.html
#---------------------------------------------------------------------------------------------
#  public    = 65537
#  private   = 553699199426609
#  modulus   = 825641896390631
#  message   = 48194775244950
#  encrpyted = 321340212160104
#  decrypted = 48194775244950
#---------------------------------------------------------------------------------------------

my $e = 65537;
my $d = 553699199426609;
my $n = 825641896390631;
my $M_dec = "48194775244950";

my $enc = fastExpMod2($M_dec, $e, $n);
print("\$enc = $enc\n");

my $dec = fastExpMod2($enc, $d, $n);
print("\$dec = $dec\n");







