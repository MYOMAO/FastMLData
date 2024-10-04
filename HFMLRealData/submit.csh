#!/bin/csh

# File containing the list of numbers
set filename = "Numbers.txt"




# Loop through each line in the file
foreach num (`cat $filename`)
	echo $num

	set runname = "RunList/${num}.txt"


	foreach file (`cat $runname`)
	# Extract the filename
	
	echo "file: " $file
# Extract the digits before .root after the last -
set last_segment = `echo $file | sed 's/^.*-\([0-9]*\)\.root$/\1/'`

# Remove leading zeros
set seg = `echo $last_segment | sed 's/^0*//'`
echo "num = " $num 
	echo "seg = " $seg
	sed -i "13s/.*/Run=${num}/" condor.sh	
	sed -i "14s/.*/Seg=${seg}/" condor.sh	

	condor_submit condor.sh
#	@ i = $i + 1

	end

end


