#!/bin/sh
info="{"
read line
CR=$(printf "\r")
line=${line%$CR}
REQUEST_METHOD=${line%% *}
tmp=${line#* }
REQUEST_URI=${tmp% *}
REQUEST_VER=${tmp#* }
SCRIPT_NAME=${REQUEST_URI%\?*}
QUERY_STRING=${REQUEST_URI#*\?}
while read line; do
	line=${line%$CR}
	if test "$line" = ""; then
		break
	fi
	key=${line%%:*}
	val=${line#*: }
	if test "$key" = "Content-Length"; then
		REQUEST_HEAD_CONTENT_LENGTH=$(($val))
		info="${info}\"REQUEST_HEAD_CONTENT_LENGTH\":${REQUEST_HEAD_CONTENT_LENGTH},"
	else
		info="${info}\"$key\":\"$val\","
	fi
done
if test ! "$REQUEST_HEAD_CONTENT_LENGTH" = ""; then
	if test $REQUEST_HEAD_CONTENT_LENGTH -gt 0; then
		export POST=$(head -c $REQUEST_HEAD_CONTENT_LENGTH)
		info="${info}\"POST\":\"${POST}\","
	fi
fi
echo "$SCRIPT_NAME" | grep "/$" 2>&1 > /dev/null
if test $? -eq 0; then
	SCRIPT_FILENAME="$(pwd)${SCRIPT_NAME}index.htm"
else
	SCRIPT_FILENAME="$(pwd)${SCRIPT_NAME}"
fi
if test -f $SCRIPT_FILENAME; then
	echo "$SCRIPT_FILENAME"|grep ".action$" > /dev/null 2>&1
	if test $? -eq 0; then
		export QUERY_STRING
		msg=$(/bin/sh "$SCRIPT_FILENAME")
	else
		msg=$(cat $SCRIPT_FILENAME)
	fi
else
	msg="404 Not Found"
fi
info="${info}REQUEST_METHOD:\"$REQUEST_METHOD\","
info="${info}REQUEST_URI:\"$REQUEST_URI;\","
info="${info}SCRIPT_NAME:\"$SCRIPT_NAME\","
info="${info}QUERY_STRING:\"$QUERY_STRING\","
info="${info}SCRIPT_FILENAME:\"$SCRIPT_FILENAME\","
info="${info}REQUEST_VER:\"${REQUEST_VER}\","
info="${info}}"
echo "HTTP/1.1 200 OK"
echo "Content-Length: ${#msg}"
echo "Server: TXS/0.3"
echo "X-Info: $info"
echo 
echo -n $msg
