#!/bin/bash

CYCLE=20
THREAD=1
REPEAT=1
SLOT=""
TARGET=""
FIX_PROB=""

while [[ $# -gt 1 ]]; do
  key="$1"

  case $key in
    -c|--cycle)
      CYCLE="$2"
      shift
      ;;
    -t|--thread)
      THREAD="$2"
      shift
      ;;
    -r|--repeat)
      REPEAT="$2"
      shift
      ;;
    -s|--slot)
      SLOT="_$2"
      shift
      ;;
    -f|--fix-prob)
      FIX_PROB="-f"
  esac
  shift
done

TARGET=${1?"$0 <OUTPUT_DIR>. Need to specify output directory"}

echo CYCLE = "$CYCLE"
echo THREAD = "$THREAD"
echo REPEAT = "$REPEAT"
echo TARGET = "$TARGET"
echo FIX_PROB = "$FIX_PROB"

mkdir -p $TARGET

PROGRAMS=(
atomic_wait_free
pthread_mutex
atomic_mutex1
atomic_mutex2
atomic_mutex3
atomic_mutex4
atomic_mutex5
pthread_rwlock
atomic_rwlock
atomic_punch_card
)

for program in ${PROGRAMS[@]}; do
  echo $program
  for i in `seq 1 $REPEAT`; do
    perf stat -o "$TARGET/${program}${SLOT}_${THREAD}" --append ./${program}${SLOT} -c $CYCLE -t $THREAD $FIX_PROB
  done
done
