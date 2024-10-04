#!/bin/csh

# File containing the list of numbers
set filename = "Numbers.txt"

# Loop through each line in the file
foreach num (`cat $filename`)
    echo $num
     
	ls /sphenix/lustre01/sphnxpro/physics/slurp/tracking/run_00051600_00051700/DST_TRKR_HIT_run2pp_new_2024p007-000${num}*root > RunList/${num}.txt
        

end


