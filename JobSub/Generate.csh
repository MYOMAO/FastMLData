#!/bin/csh

# File containing the list of numbers
set filename = "Numbers.txt"

# Loop through each line in the file
foreach num (`cat $filename`)
    echo $num
     
	ls /sphenix/lustre01/sphnxpro/physics/slurp/tracking/new_2024p007/run_00052400_00052500/DST_TRKR_HIT_run2pp_new_2024p007-000${num}*root > RunList/${num}.txt
        

end


