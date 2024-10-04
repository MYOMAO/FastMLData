#!/bin/csh
setenv HOME /star/u/$LOGNAME
#setenv HOME /sphenix/user/$LOGNAME

source /etc/csh.login
foreach i (/etc/profile.d/*.csh)
 source $i
end

source $HOME/.login
#source /direct/star+u/zshi/.login

#source /cvmfs/sphenix.sdcc.bnl.gov/x8664_sl7/opt/sphenix/core/bin/sphenix_setup.csh -n ana.141

#source /cvmfs/sphenix.sdcc.bnl.gov/x8664_sl7/opt/sphenix/core/bin/sphenix_setup.csh -n
#source /cvmfs/sphenix.sdcc.bnl.gov/x8664_sl7/opt/sphenix/core/bin/setup_root6.csh

#source /opt/sphenix/core/bin/sphenix_setup.csh -n
#source /opt/sphenix/core/bin/setup_root6.csh

#source /opt/sphenix/core/bin/setup_root6_include_path.csh


echo "START PRINT ENV"

#printenv


echo "DONE PRINt ENV"


set Name=$argv[1]
set Run=$argv[2]
set Seg=$argv[3]


#source /opt/sphenix/core/bin/sphenix_setup.csh -n





#source Build.sh


echo "Now PWD"

pwd

ls

echo "DONE CHECK"

cd workdir

mkdir ${Name}

#source Reconnect.sh


cp ../Simple.C ${Name}/ 

cp ../Reconnect.sh ${Name}/ 


cd ${Name}

source /opt/sphenix/core/bin/sphenix_setup.csh -n new

source Reconnect.sh
echo "NowList"




root -b -l -q Simple.C'('${Run}','${Seg}')'

echo "Now LS see what we have"



mv DebugFile.root.root /direct/sphenix+tg+tg01/hf/zshi/HFMLDataSample/ROOT/DebigFile_${Run}_${Seg}.root
mv TestZZData.json.root /direct/sphenix+tg+tg01/hf/zshi/NewSiSeedingSamples/AnaSample/Data_${Run}_${Seg}.root

cd ../../

rm -rf workdir/${Name}


