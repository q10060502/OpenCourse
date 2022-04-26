#!/bin/sh
read line
CR=$(printf "\r")
line=${line%$CR}
REQUEST_METHOD=${line%% *}
tmp=${line#* }
REQUEST_URI=${tmp% *}
REQUEST_VER=${tmp#* }
echo "$REQUEST_URI" | grep "/$" > /dev/null 2>&1
if test $? -eq 0; then
	SCRIPT_FILENAME="$(pwd)${REQUEST_URI}index.htm"
else
	SCRIPT_FILENAME="$(pwd)${REQUEST_URI}"
fi
if test -f $SCRIPT_FILENAME; then
	msg="$(cat $SCRIPT_FILENAME)"
else
	msg="<h1>404 Not Found</h1>"
fi
info="{"
info="${info}REQUEST_METHOD:\"$REQUEST_METHOD\","
info="${info}REQUEST_URI:\"$REQUEST_URI\","
info="${info}SCRIPT_FILENAME:\"$SCRIPT_FILENAME\","
info="${info}REQUEST_VER:\"${REQUEST_VER}\","
info="${info}}"
echo "HTTP/1.1 200 OK"
echo "Content-Length: ${#msg}"
echo "Server: TXS/0.2"
echo "X-Info: $info"
echo 
echo -n $msg
