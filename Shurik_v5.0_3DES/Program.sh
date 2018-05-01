#!/bin/bash

#------------------------------------------------------------------------------------
# bash, tutorial:
# https://ryanstutorials.net/bash-scripting-tutorial/
# 
# bash, try/catch :
# https://stackoverflow.com/questions/22009364/is-there-a-try-catch-command-in-bash
# 
# bash, random num:
# http://tldp.org/LDP/abs/html/randomvar.html
# 
# bash, string length:
# https://stackoverflow.com/questions/17368067/length-of-string-in-bash
#
# bash, perl script output when ran from bash script:
# https://stackoverflow.com/questions/5681066/get-output-of-perl-script-from-bash-script-and-exit
#
# bash, file checks:
# http://tldp.org/LDP/abs/html/fto.html
#
# bash, file path with white spaces issue:
# https://unix.stackexchange.com/questions/108635/why-i-cant-escape-spaces-on-a-bash-script
#
# bash, function return value:
# http://www.linuxjournal.com/content/return-values-bash-functions
#
# bash, get perl script output!:
# https://stackoverflow.com/questions/5681066/get-output-of-perl-script-from-bash-script-and-exit
#
# bash,:
# https://stackoverflow.com/questions/3871332/how-to-tell-bash-that-the-line-continues-on-the-next-line
#
# http://tldp.org/LDP/abs/html/comparison-ops.html
#
#------------------------------------------------------------------------------------


function stamp {
	echo -e "#############\n#Shurik v4.0#\n#############"
}

function confusion {
	echo -e "#Confusion#"
	
	read -p "do confusion? (y/n) >" userChoice
	if [ "$userChoice" = "y" ] 
	then
		# pass: plaintext full path, workplace dir full path
		perl ./Confusion_v1.pl "${1}" "${2}/confusion.txt" "${2}/confusionMap.txt"
	
		# encrypt confusion map using DES perl script
		# perl ./DES_v7.pl "e" $desKey "$workPlacePrefix/confusionMap.txt" "$workPlacePrefix/confusionMapCipher.txt"
		perl ./ThreeDES_Manager.pl "e" $desKey "${2}/.temp.txt" "${2}/confusionMap.txt" "${2}/confusionMapCipher.txt"

	elif [ "$userChoice" = "n" ]
	then
		# fill confusion file with plaintext if there is no confusion done
		cat "${1}" > "${2}/confusion.txt"
	fi
}

function encryption_menu {
		
	# ask for plaintext full path
	read -p "Please enter a valid Linux absolute path to the plaintext at hand >" path
	
	# check if path exists and is a regular file and has read permission
	if ! [ -f "${path}" ] && ! [ -r "${path}" ]
	then
		echo -e "#ERROR: the specified path is not a file#"
		exit 0
	fi
	
	# ask for a DES key
	# read -sp, hides password input
	read -p "Please enter an appropriate DES key >" desKey
	
	# check DES key size
	chrlen=${#desKey}
	if [ $chrlen -ne 16 ]
	then
		echo -e "#ERROR: the specified key is not appropriate for DES#"
		exit 1
	fi
	
	workPlacePrefix="$HOME/.Shurik/Shurik_$RANDOM"
	
	# create workplace dir
	mkdir -p "${workPlacePrefix}"  
	
	# only for DEBUG
	# copy original plaintext 
	cp "${path}" "${workPlacePrefix}/plaintext.txt"
	
	# do confusion using mimicked sed perl script
	# creates a new file and makes the changes on it
	# the file is saved in current work place with the name confusion.txt 
	confusion "${path}" "${workPlacePrefix}"
			
	# encrypte plaintext after confusion using DES perl script
	#perl ./DES_v7.pl "e" $desKey "${workPlacePrefix}/confusion.txt" "${workPlacePrefix}/confusionCipher.txt"
	perl ./ThreeDES_Manager.pl "e" $desKey "${workPlacePrefix}/.temp.txt" "${workPlacePrefix}/confusion.txt" "${workPlacePrefix}/confusionCipher.txt"
	
	# encrypte des key using RSA perl script
	perl ./RSA_v6_chunkless_threeDes.pl "e" $desKey "${workPlacePrefix}/desKeyCipher.txt" 
	
	# scramble mem dump
	desKey="qqqqqqqqqqqqqqqqqqqqq"
	
	# could ask if delete plaintext files and leave on the pc only encrypted files
	# rm....
	
	# inform the user with instructions for this part 
	echo -e "\n#NOTICE#\n" \
			"The files to be sent are in: $workPlacePrefix\n" \
			"Not all file may exist\n" \
			"1)$workPlacePrefix/confusionCipher.txt\n" \
			"2)$workPlacePrefix/confusionMapCipher.txt\n" \
			"3)$workPlacePrefix/desKeyCipher.txt\n"
}

function decryption_menu {
		
	# inform the user with instructions for this part 
	echo -e "#NOTICE#\n" \
			"You should enter the full path of the workplace dir of this program\n" \
			"It should be under $HOME/.Shurik/\n"
			
	# ask for workplace dir full path
	read -p "Please enter a valid Linux absolute path to the workplace dir at hand >" workPlacePath
	
	# check workPlacePath
	if ! [ -e "${workPlacePath}" ] && ! [ -d "${workPlacePath}" ]
	then
		echo -e "#ERROR: the specified path is not a dir#"
		exit 0
	fi
	
	# decrypte des key using RSA perl script
	desKey=$(perl ./RSA_v6_chunkless_threeDes.pl "d" "NULL" "${workPlacePath}/desKeyCipher.txt") 
	
	# echo -e "${workPlacePath}/desKeyCipher.txt"
	# echo -e $desKey
	# exit 2
	
	
	# decrypte plaintext cipher using DES perl script
	#perl ./DES_v7.pl "d" $desKey "${workPlacePath}/confusionCipher.txt" "${workPlacePath}/confusionDecryption.txt"
	perl ./ThreeDES_Manager.pl "d" $desKey "${workPlacePath}/.temp.txt" "${workPlacePath}/confusionCipher.txt" "${workPlacePath}/confusionDecryption.txt" 
	
	# check if path exists and is a regular file and has read permission
	if [ -f "${workPlacePath}/confusionMapCipher.txt" ] && [ -r "${workPlacePath}/confusionMapCipher.txt" ]
	then
		# decrypt confusion map using DES perl script
		#perl ./DES_v7.pl "d" $desKey "${workPlacePath}/confusionMapCipher.txt" "${workPlacePath}/confusionMapDecryption.txt" 
		perl ./ThreeDES_Manager.pl "d" $desKey "${workPlacePath}/.temp.txt" "${workPlacePath}/confusionMapCipher.txt" "${workPlacePath}/confusionMapDecryption.txt"   
	
		# use the confusion map to get original plaintext
		perl ./DeConfusion_v1.pl "${workPlacePath}/confusionDecryption.txt" "${workPlacePath}/confusionMapDecryption.txt"
	else
		echo -e "There was no confusion done by user for this cipher"
	fi

}

FILE="/home/yy/Desktop/Linux\ workPlace\ Ubuntu/Projects\ -\ 2017/Linux_Project_2/Tests/Shurik_v4.0_3DES/LinusFuckYou.jpg"
TIMEOUT=2
sh -c "(sleep $TIMEOUT; kill -9 \$\$) & exec eog $FILE"
clear

stamp

while [ 0 -le 1 ]
do
	echo -e "Please choose:\n1) for encryption\n2) for decryption\n3) to exit the program"
	read -p ">" option
	
	case $option in
	1)
	echo -e "#Encryption#"
	encryption_menu 
	;;
	2)
	echo -e "#Decryption#"
	decryption_menu 
	;;
	3)
	echo -e "#Program terminated by user#"
	break
	;;
	*)
	echo -e "#ERROR: There is no such option#"
	;;
	esac
done


