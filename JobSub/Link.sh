echo "-------------- CHANGING SOFTWARE NOW BRO --------------------"


source /opt/sphenix/core/bin/sphenix_setup.csh -n new

#rm -r install

#mkdir install
setenv MYINSTALL /direct/sphenix+tg+tg01/hf/zshi/FastMLData/install/
setenv LD_LIBRARY_PATH $MYINSTALL/lib:$LD_LIBRARY_PATH
setenv LD_LIBRARY_PATH $MYINSTALL/lib64:$LD_LIBRARY_PATH
set path = ( $MYINSTALL/bin $path )


echo "-------------- BUILD Real Data ------------------------"

#cd HFMLRealData
#make clean
#cd coresoftware/simulation/g4simulation/g4detectors/
#autogen.sh --prefix=$MYINSTALL
#make -j20 install

#cd ..



setenv ROOT_INCLUDE_PATH ${PWD}/macros/common:$ROOT_INCLUDE_PATH

 

#echo "-------------- DONE CHANGING SOFTWARE NOW BRO --------------------"
