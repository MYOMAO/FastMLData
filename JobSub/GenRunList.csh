#!/bin/csh

# File containing the list of numbers
set filename = "Numbers.txt"

# Loop through each line in the file
foreach num (`cat $filename`)
    #echo $num
   
	@ RunLow = ($num / 100) * 100
	@ RunHigh = $RunLow + 100

	
	echo "Range: " $RunLow "  - " $RunHigh

	ls /sphenix/lustre01/sphnxpro/physics/slurp/tracking/new_2024p007/run_000${RunLow}_000${RunHigh}/DST_TRKR_HIT_run2pp_new_2024p007-000${num}*root > RunList/${num}.txt
        

end


