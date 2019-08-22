#!/bin/sh

# usage: sh test.sh

#======COLORS======#

EOC="\033[0m";
GREEN="\033[32m";
YELLOW="\033[33m";
RED="\033[0;31m";
BLUE="\033[0;36m";
HIGH="\033[1m";

#===PRELIMINARIES==#

preliminaries () {

chmod 777 generator
chmod 777 verifier
chmod 777 map_edit

echo "${HIGH}\nPRELIMINARIES${EOC}"

ATR1=$(cat -e ../author | wc -l | tr -d ' ')
ATR2=$(cat -e ../author | wc -c | tr -d ' ')
if [ $ATR1 -ne '2' ] || [ $ATR2 -lt '6' ]
then
	echo "${RED}Author-file\tfailed${EOC}"
else
	echo "${GREEN}Author-file\tpassed${EOC}"
fi

NRM1=$(norminette ../*.c ../*.h | grep 'Error' | wc -l | tr -d ' ')
NRM2=$(norminette ../*.c ../*.h | grep 'Warning' | wc -l | tr -d ' ')
if [ $NRM1 -gt '0' ] || [ $NRM2 -gt '0' ]
then
	echo "${RED}Norminette\tfailed${EOC}"
else
	echo "${GREEN}Norminette\tpassed${EOC}"
fi

make -C ../ fclean
MK1=$(make -C ../ | grep "Nothing" | wc -l | tr -d ' ')
MK2=$(make -C ../ | grep "Nothing" | wc -l | tr -d ' ')
MK3=$(make -C ../ clean | grep "Nothing" | wc -l | tr -d ' ')
MK4=$(make -C ../ | grep "Nothing" | wc -l | tr -d ' ')
MK5=$(make -C ../ fclean | grep "Nothing" | wc -l | tr -d ' ')
MK6=$(make -C ../ | grep "Nothing" | wc -l | tr -d ' ')
if [ $MK1 -eq '0' ] && [ $MK2 -eq '1' ] && [ $MK4 -eq '1' ] && [ $MK6 -eq '0' ]
then
	echo "${GREEN}Makefile\tpassed${EOC}"
else
	echo "${RED}Makefile\tfailed${EOC}"
fi
make -C ../ clean

sleep 1s

LM=$(ls -l ../ | grep "\blem-in\b" | cut -d ' ' -f 13 | wc -c | tr -d ' ')
if [ $LM -ne '7' ]
then
	echo "${RED}lem-in\t\tnot found${EOC}"
else
	echo "${GREEN}lem-in\t\tfound${EOC}"
fi

sleep 1s

RI=$(echo "" | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}Read std-output\tnot passed${EOC}"
else
	echo "${GREEN}Read std-output\tpassed${EOC}"
fi

sleep 1s

}

#===BAD INPUT==#

bad_input () {

echo "${HIGH}\nBAD INPUT${EOC}"

RI=$(cat test_files/test_0_empty_file | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}Empty map\tnot passed${EOC}"
else
	echo "${GREEN}Empty map\tpassed${EOC}"
fi

RI=$(cat test_files/test_1_no_ants | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}No ants\t\tnot passed${EOC}"
else
	echo "${GREEN}No ants\t\tpassed${EOC}"
fi

RI=$(cat test_files/test_2_zero_ants | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}Zero ants\tnot passed${EOC}"
else
	echo "${GREEN}Zero ants\tpassed${EOC}"
fi

RI=$(cat test_files/test_3_negative_ants | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}Negative ants\tnot passed${EOC}"
else
	echo "${GREEN}Negative ants\tpassed${EOC}"
fi

RI=$(cat test_files/test_4_no_start | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}No start\tnot passed${EOC}"
else
	echo "${GREEN}No start\tpassed${EOC}"
fi

RI=$(cat test_files/test_5_no_end | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}No end\t\tnot passed${EOC}"
else
	echo "${GREEN}No end\t\tpassed${EOC}"
fi

RI=$(cat test_files/test_6_no_solution | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}No solution\tnot passed${EOC}"
else
	echo "${GREEN}No solution\tpassed${EOC}"
fi

A1=$(cat test_files/test_7_many_comments | wc -l | tr -d ' ')
A2=$(cat test_files/test_7_many_comments | ../lem-in | wc -l | tr -d ' ')
if [ $A1 -gt $A2 ]
then
	echo "${RED}Many comments\tnot passed${EOC}"
else
	echo "${GREEN}Many comments\tpassed${EOC}"
fi

RI=$(cat test_files/test_8_el_rooms | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}L 1st letter\tnot passed${EOC}"
else
	echo "${GREEN}L first letter\tpassed${EOC}"
fi

RI=$(cat test_files/test_9_no_rooms | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}No rooms\tnot passed${EOC}"
else
	echo "${GREEN}No rooms\tpassed${EOC}"
fi

RI=$(cat test_files/test_10_no_connections | ../lem-in | cut -d ':' -f 1)
A1=$(echo $RI | grep "rror" | wc -l | tr -d ' ')
A2=$(echo $RI | grep "RROR" | wc -l | tr -d ' ')
if [ $A1 -ne '1' ] && [ $A2 -ne '1' ]
then
	echo "${RED}No connections\tnot passed${EOC}"
else
	echo "${GREEN}No connections\tpassed${EOC}"
fi

sleep 3s

}

#===BASIC TEST 1==#

basic_test_1 () {

echo "${HIGH}\nBASIC TEST 1${EOC}"

for i in 0 1 2 3 4 5 6 7 8 9
do
	sleep 1s
	./generator --flow-one > test1
	exec 3>&1 4>&2
	tmp=$( { time $(../lem-in < test1 > out1) 1>&3 2>&4; } 2>&1)
	time1=$( echo $tmp | grep "real" | cut -d ' ' -f2 | cut -d 'm' -f2 | sed 's/s//' )
#	exec 3>&- 4>&-
#	../lem-in < test1 > out1
	res=$(./verifier < out1)
	ref=$(tail -n 1 test1 | cut -d ' ' -f8)
	cp out1 output/out1_$i
	rm out1
	rm test1
	if [ $(echo $res | grep "ERROR" | wc -l) -gt 1 ]
	then
		echo "${RED}$(echo $ref | head -n 1)${EOC}"
	else
		CLR1=$EOC
		CLR2=$EOC
		CLR3=$BLUE
		answer="passed"
		if (($res < $ref))
		then
			CLR1=$BLUE
		elif [ $res -lt $(($ref + 2)) ]
		then
			CLR1=$GREEN
			CLR3=$GREEN
		elif [ $res -lt $(($ref + 4)) ]
		then
			CLR1=$YELLOW
			CLR3=$YELLOW
		elif [ $res -gt $(($ref + 3)) ]
		then
			CLR1=$RED
			CLR3=$RED
			answer="not passed"
		fi
		if (( $(echo "$time1<1.0" | bc -l) ))
		then
			CLR2=$BLUE
		elif (( $(echo "$time1<3.0" | bc -l) ))
		then
			CLR2=$GREEN
		elif (( $(echo "$time1<12.0" | bc -l) ))
		then
			CLR2=$YELLOW
		elif (( $(echo "$time1<15.0" | bc -l) ))
		then
			CLR2=$RED
			CLR3=$RED
			answer="not passed"
		fi
		echo "${CLR1}Moves expected: $ref\tgenerated: $res\t${CLR2}time: $time1\t${CLR3}$answer${EOC}"
	fi
done
}

basic_test_2 () {

echo "${HIGH}\nBASIC TEST 2${EOC}"

for i in 0 1 2 3 4 5 6 7 8 9
do
	sleep 1s
	./generator --flow-ten > test2
	exec 3>&1 4>&2
	tmp=$( { time $(../lem-in < test2 > out2) 1>&3 2>&4; } 2>&1)
	time2=$( echo $tmp | grep "real" | cut -d ' ' -f2 | cut -d 'm' -f2 | sed 's/s//' )
#	exec 3>&- 4>&-
#	../lem-in < test2 > out2
	res=$(./verifier < out2)
	ref=$(tail -n 1 test2 | cut -d ' ' -f8)
	cp out2 output/out2_$i
	rm out2
	rm test2
	if [ $(echo $res | grep "ERROR" | wc -l) -gt 1 ]
	then
		echo "${RED}$(echo $ref | head -n 1)${EOC}"
	else
		CLR1=$EOC
		CLR2=$EOC
		CLR3=$BLUE
		answer="passed"
		if (($res < $ref))
		then
			CLR1=$BLUE
		elif [ $res -lt $(($ref + 2)) ]
		then
			CLR1=$GREEN
			CLR3=$GREEN
		elif [ $res -lt $(($ref + 4)) ]
		then
			CLR1=$YELLOW
			CLR3=$YELLOW
		elif [ $res -gt $(($ref + 3)) ]
		then
			CLR1=$RED
			CLR3=$RED
			answer="not passed"
		fi
		if (( $(echo "$time2<1.0" | bc -l) ))
		then
			CLR2=$BLUE
		elif (( $(echo "$time2<3.0" | bc -l) ))
		then
			CLR2=$GREEN
		elif (( $(echo "$time2<12.0" | bc -l) ))
		then
			CLR2=$YELLOW
		elif (( $(echo "$time2<15.0" | bc -l) ))
		then
			CLR2=$RED
			CLR3=$RED
			answer="not passed"
		fi
			echo "${CLR1}Moves expected: $ref\tgenerated: $res\t${CLR2}time: $time2\t${CLR3}$answer${EOC}"
	fi
done

}

basic_test_3 () {

echo "${HIGH}\nBASIC TEST 3${EOC}"

for i in 0 1 2 3 4 5 6 7 8 9
do
	sleep 1s
	./generator --flow-thousand > test3
	exec 3>&1 4>&2
	tmp=$( { time $(../lem-in < test3 > out3) 1>&3 2>&4; } 2>&1)
	time3=$( echo $tmp | grep "real" | cut -d ' ' -f2 | cut -d 'm' -f2 | sed 's/s//' )
#	exec 3>&- 4>&-
#	../lem-in < test3 > out3
	res=$(./verifier < out3)
	ref=$(tail -n 1 test3 | cut -d ' ' -f8)
	cp out3 output/out3_$i
	rm out3
	rm test3
	if [ $(echo $res | grep "ERROR" | wc -l) -gt 1 ]
	then
		echo "${RED}$(echo $ref | head -n 1)${EOC}"
	else
		CLR1=$EOC
		CLR2=$EOC
		CLR3=$BLUE
		answer="passed"
		if (($res < $ref))
		then
			CLR1=$BLUE
		elif [ $res -lt $(($ref + 2)) ]
		then
			CLR1=$GREEN
			CLR3=$GREEN
		elif [ $res -lt $(($ref + 4)) ]
		then
			CLR1=$YELLOW
			CLR3=$YELLOW
		elif [ $res -gt $(($ref + 3)) ]
		then
			CLR1=$RED
			CLR3=$RED
			answer="not passed"
		fi
		if (( $(echo "$time3<1.0" | bc -l) ))
		then
			CLR2=$BLUE
		elif (( $(echo "$time3<3.0" | bc -l) ))
		then
			CLR2=$GREEN
		elif (( $(echo "$time3<12.0" | bc -l) ))
		then
			CLR2=$YELLOW
		elif (( $(echo "$time3<15.0" | bc -l) ))
		then
			CLR2=$RED
			CLR3=$RED
			answer="not passed"
		fi
		echo "${CLR1}Moves expected: $ref\tgenerated: $res\t${CLR2}time: $time3\t${CLR3}$answer${EOC}"
	fi
done

}

big_test () {

echo "${HIGH}\nMEDIUM TEST${EOC}"

for i in 0 1 2 3 4 5 6 7 8 9
do
	sleep 1s
	./generator --big > test4
	exec 3>&1 4>&2
	tmp=$( { time $(../lem-in < test4 > out4) 1>&3 2>&4; } 2>&1)
	time4=$( echo $tmp | grep "real" | cut -d ' ' -f2 | cut -d 'm' -f2 | sed 's/s//' )
#	exec 3>&- 4>&-
#	../lem-in < test4 > out4
	res=$(./verifier < out4)
	ref=$(tail -n 1 test4 | cut -d ' ' -f8)
	cp out4 output/out4_$i
	rm out4
	rm test4
	if [ $(echo $res | grep "ERROR" | wc -l) -gt 1 ]
	then
		echo "${RED}$(echo $ref | head -n 1)${EOC}"
	else
		CLR1=$EOC
		CLR2=$EOC
		CLR3=$BLUE
		answer="passed"
		if (($res < $ref))
		then
			CLR1=$BLUE
		elif [ $res -lt $(($ref + 2)) ]
		then
			CLR1=$GREEN
			CLR3=$GREEN
		elif [ $res -lt $(($ref + 11)) ]
		then
			CLR1=$YELLOW
			CLR3=$YELLOW
		elif [ $res -gt $(($ref + 10)) ]
		then
			CLR1=$RED
			CLR3=$RED
			answer="not passed"
		fi
		if (( $(echo "$time4<1.0" | bc -l) ))
		then
			CLR2=$BLUE
			elif (( $(echo "$time4<3.0" | bc -l) ))
		then
			CLR2=$GREEN
		elif (( $(echo "$time4<12.0" | bc -l) ))
		then
			CLR2=$YELLOW
		elif (( $(echo "$time4<15.0" | bc -l) ))
		then
			CLR2=$RED
			CLR3=$RED
			answer="not passed"
		fi
			echo "${CLR1}Moves expected: $ref\tgenerated: $res\t${CLR2}time: $time4\t${CLR3}$answer${EOC}"
	fi
done

}

super_test () {

echo "${HIGH}\nHARD TEST${EOC}"

for i in 0 1 2 3 4 5 6 7 8 9
do
	sleep 1s
	./generator --big-superposition > test5
	exec 3>&1 4>&2
	tmp=$( { time $(../lem-in < test5 > out5) 1>&3 2>&4; } 2>&1)
	time5=$( echo $tmp | grep "real" | cut -d ' ' -f2 | cut -d 'm' -f2 | sed 's/s//' )
#	exec 3>&- 4>&-
#	../lem-in < test5 > out5
	res=$(./verifier < out5)
	ref=$(tail -n 1 test5 | cut -d ' ' -f8)
	cp out5 output/out5_$i
	rm out5
	rm test5
	if [ $(echo $res | grep "ERROR" | wc -l) -gt 1 ]
	then
		echo "${RED}$(echo $ref | head -n 1)${EOC}"
	else
		CLR1=$EOC
		CLR2=$EOC
		CLR3=$BLUE
		answer="passed"
		if (($res < $ref))
		then
			CLR1=$BLUE
		elif [ $res -lt $(($ref + 2)) ]
		then
			CLR1=$GREEN
			CLR3=$GREEN
		elif [ $res -lt $(($ref + 11)) ]
		then
			CLR1=$YELLOW
			CLR3=$YELLOW
		elif [ $res -gt $(($ref + 10)) ]
		then
			CLR1=$RED
			CLR3=$RED
			answer="not passed"
		fi
		if (( $(echo "$time5<1.0" | bc -l) ))
		then
			CLR2=$BLUE
		elif (( $(echo "$time5<3.0" | bc -l) ))
		then
			CLR2=$GREEN
		elif (( $(echo "$time5<12.0" | bc -l) ))
		then
			CLR2=$YELLOW
		elif (( $(echo "$time5<15.0" | bc -l) ))
		then
			CLR2=$RED
			CLR3=$RED
			answer="not passed"
		fi
			echo "${CLR1}Moves expected: $ref\tgenerated: $res\t${CLR2}time: $time5\t${CLR3}$answer${EOC}"
	fi
done

}

choose () {
	if [ $(echo $1 | wc -c | tr -d ' ') -lt 2 ]
	then
		echo "${HIGH}usage:\ttest.sh flag${EOC}"
		echo "${HIGH}flags:\t-norm${EOC}\t- preliminary requierements test"
		echo "\t${HIGH}-bad${EOC}\t- bad input test"
		echo "\t${HIGH}-basic${EOC}\t- distinct paths test"
		echo "\t${HIGH}-big${EOC}\t- crossing paths test"
		echo "\t${HIGH}-super${EOC}\t- overlaying paths test"
		echo "\t${HIGH}-all${EOC}\t- all tests"
	elif [ $(echo $1 | wc -c | tr -d ' ') -gt 2 ]
	then
	echo $1
	if [ "$1" == "-norm" ] || [ $1 == "-all" ]
	then
		preliminaries
	fi
	if [ "$1" == "-bad" ] || [ $1 == "-all" ]
	then
		bad_input
	fi
	if [ "$1" == "-basic" ] || [ $1 == "-all" ]
	then
		basic_test_1
		basic_test_2
		basic_test_3
	fi
	if [ "$1" == "-big" ] || [ $1 == "-all" ]
	then
		big_test
	fi
	if [ "$1" == "-super" ] || [ $1 == "-all" ]
	then
		super_test
	fi
	fi
}

choose $1
