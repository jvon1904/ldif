#! /usr/bin/env sh

function test_example_stdin () {
  EXPECTED='{"name": "Test","age": 99,"uid": "1329692a-9108-47ec-aab1-1a2a4c2663c4","time": "10:55pm","pi": 3.14,"sentence": "The quick brown fox jumps over the lazy dog!","ranking": "#1!"}'
  ACTUAL="$(cat example.ldif | bin/jdif)"
  if [ "$EXPECTED" = "$ACTUAL" ]
  then
    printf '\e[32m#test_example_stdin - PASSED!\e[0m'
    exit 0
  else
    echo "Expected:\n\t$EXPECTED\n"
    echo "Actual:\n\t$ACTUAL\n"
    printf '\e[31m#test_example_stdin - FAILED!\e[0m\n'
    exit 1
  fi
}

test_example_stdin