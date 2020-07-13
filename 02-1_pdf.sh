#!/bin/sh

ARG=$1
PREFIX=${ARG:=201212}
DESTDIR=/tmp/join$$

mkdir -p ${DESTDIR}

i=0
for file in jvn/${PREFIX}????-*.pdf; do
  if [ `expr $i \< 10` = 1 ]
  then
    count="0$i"
  else
    count="$i"
  fi

  destfile=${DESTDIR}/${PREFIX}${count}.pdf
  cp "$file" ${destfile}

  i=`expr $i + 1`
done

echo "combine all pdf files..."
#
/System/Library/Automator/Combine\ PDF\ Pages.action/Contents/\
Resources/join.py --output jvn/${PREFIX}-jvn.pdf \
${DESTDIR}/${PREFIX}??*.pdf
echo "done"
echo "clean-up working files..."
rm -rf ${DESTDIR}
echo "done"
