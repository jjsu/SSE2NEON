PWD=`pwd`
SRC_DIR=$PWD/src
BIN_DIR=$PWD/bin


mkdir -p $BIN_DIR

echo "Step.1 compiling ..."

cd $SRC_DIR
make -j8
if [ $? -ne 0 ]
then
	echo "compile error"
	exit
fi
make install

echo "Step.2 generate and push the input file"

cd $BIN_DIR
$BIN_DIR/gen_input
adb push input /data/


echo "Step.3 clean result files and push test_neon"

cd $BIN_DIR
rm -rf results/*
mkdir -p results
adb push test_neon /data


echo "Step.4 ***running on ARM****"
adb shell "/data/test_neon " > results/NEON.log

if [ $? -ne 0 ]
then
	echo "arm run  error"
	exit
fi

echo "Step.5 ***running on x86_64****"
$BIN_DIR/test_sse > results/SSE.log

if [ $? -ne 0 ]
then
	echo "x86_64 run error"
	exit
fi

echo "Step.6 compare the results "
dos2unix $BIN_DIR/results/NEON.log
diff $BIN_DIR/results/SSE.log $BIN_DIR/results/NEON.log > /dev/null

if [ $? -ne 0 ]
then
	echo  "\033[41;37m ~~~~ERROR!!!~~~~ \033[0m "
	exit
else
	echo  "\033[42;37m ~~~~OK~~~ \033[0m "
fi
