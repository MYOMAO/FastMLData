set RunLow=$1
@ RunHigh = $RunLow + 100

echo "Run Range is from " $RunLow "  -  "  $RunHigh

ls /sphenix/lustre01/sphnxpro/physics/slurp/tracking/new_2024p007/run_000${RunLow}_000${RunHigh}/DST_TRKR_TRACKS_run2pp_new_2024p007-000*-00000.root | grep -oP '(?<=000)\d+(?=-)' > Numbers.txt
