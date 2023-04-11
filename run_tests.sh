#!/bin/bash

echo "Removing old binaries..."
make clear > /dev/null
echo "Building new binaries..."
make 1> /dev/null 2> /dev/null

[ ! -d tests ] && echo "Error: tests folder not found!\n" && exit 1
cd tests
[ ! -d "good_tests" ] && echo "Error: tests/good_tests folder not found!\n" && exit 1
[ ! -d "bad_tests" ] && echo "Error: tests/bad_tests folder not found!\n" && exit 1
[ ! -d lexer_output ] && mkdir lexer_output
[ ! -d syntaxer_output ] && mkdir syntaxer_output
[ ! -d syntaxer_visualization ] && mkdir syntaxer_visualization
[ ! -d semantixer_output ] && mkdir semantixer_output
[ ! -d semantixer_visualization ] && mkdir semantixer_visualization
[ ! -d good_output ] && mkdir good_output
[ ! -d bad_output ] && mkdir bad_output

run_test() {
    ./compiler -f $1$2 -l tests/lexer_output/$3.lex -s tests/syntaxer_output/$3.syn -S tests/semantixer_output/$3.sem > "$4/$3.out"
}

draw_test() {
    dot -Tpng tests/syntaxer_output/$1.syn > tests/syntaxer_visualization/$1.png 
    dot -Tpng tests/semantixer_output/$1.sem > tests/semantixer_visualization/$1.png
}

path="tests/"
good_tests_in_path="${path}good_tests/"
bad_tests_in_path="${path}bad_tests/"
good_tests_out_path="${path}good_output/"
bad_tests_out_path="${path}bad_output/"

cd ..
passed_tests=0
all_tests=0

for test in $(ls $good_tests_in_path); do
    all_tests=$(( $all_tests + 1 ))
    testname=${test%.*}
    run_test $good_tests_in_path $test $testname $good_tests_out_path
    if [ $? -eq 0 ]; then
        passed_tests=$(( $passed_tests + 1 ))
        echo -n .
        draw_test $testname
    else
        echo -n !
    fi
done

for test in $(ls $bad_tests_in_path); do
    all_tests=$(( $all_tests + 1 ))
    testname=${test%.*}
    run_test $bad_tests_in_path $test $testname $bad_tests_out_path
    if [ $? -ne 0 ]; then
        passed_tests=$(( $passed_tests + 1 ))
        echo -n .
    else
        echo -n !
    fi
done

echo
echo $passed_tests tests passed out of $all_tests!