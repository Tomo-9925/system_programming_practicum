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

  page=`python -c "import os;from CoreGraphics import *; \
    print(CGPDFDocumentCreateWithProvider(\
      CGDataProviderCreateWithFilename(\
      '"${destfile}"')).getNumberOfPages())"`

  # 奇数のとき結合
  if [ `expr $page \% 2` = 1 ]
  then
    # 連番の桁数処理 2桁の場合
    i=`expr $i + 1`
    if [ `expr $i \< 10` = 1 ]
    then
      count="0$i"
    else
      count="$i"
    fi
    # jvnディレクトリのblank.pdfファイルを作業ディレクトリへコピーする
    destfile=${DESTDIR}/${PREFIX}${count}-blank.pdf
    cp jvn/blank.pdf ${destfile}
  fi

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
