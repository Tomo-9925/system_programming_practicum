#!/bin/sh

IP=255.255.255.255

# 講義資料の2.3より
TODAY=`perl -e 'print int(time/86400),"\n";'`
CHGDATE=`ldapsearch -x -h $IP -b dc=kutc,dc=kansai-u,dc=ac,dc=jp \
      uid=k992077 | awk '/^shadowLastChange/{print $2}'`

# パスワード変更からの経過日数
PASSED=`expr $TODAY - $CHGDATE`
echo "パスワードを変更してから${PASSED}日経過しました．"

# パスワード変更から90日以上経過していたとき警告
if [ $PASSED -gt 90 ];
then
  echo "パスワードが12文字未満であればC棟のコンピュータを使用できません．"
fi
