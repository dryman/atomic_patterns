#!/bin/bash

CYCLE=20
THREAD=1
REPEAT=1
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
nc_thread_local
nc_address
nc_atomic_mutex1
nc_atomic_mutex2
nc_atomic_mutex3
nc_atomic_mutex4
nc_atomic_mutex5
nc_pthread_mutex
nc_pthread_rwlock_r
nc_pthread_rwlock_w
nc_atomic_rwlock_r
nc_atomic_rwlock_w
nc_atomic_punch_card_r
nc_atomic_punch_card_w
)

for program in ${PROGRAMS[@]}; do
  echo $program
  for i in `seq 1 $REPEAT`; do
    perf stat -o "$TARGET/${program}_${THREAD}" --append ./$program -c $CYCLE -t $THREAD $FIX_PROB
  done
done
