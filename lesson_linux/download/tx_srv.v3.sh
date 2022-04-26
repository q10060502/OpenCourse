#!/bin/bash
read line
method=$(echo $line | cut -d ' ' -f 1)
uri=$(echo $line | cut -d ' ' -f 2)
ver=$(echo $line | cut -d ' ' -f 3)
msg="<div>method: $method; uri: $uri; ver: $ver</div>"
abspath=$(echo $uri | cut -d '?' -f 1)
query=$(echo $uri | cut -d '?' -f 2)
msg=$msg"<div>abspath: $abspath; query: $query"
echo "$abspath"|grep "/$" 2>&1 > /dev/null
if test $? -eq 0; then
	file=".${abspath}index.htm"
else
	file=".${abspath}"
fi
msg=$msg"<div>file: $file </div>"
if test -f $file; then
	echo "$abspath"|grep ".action$" 2>&1 > /dev/null
	if test $? -eq 0; then
		msg=$msg"<div>Action</div>"
		export query
		msg=$(/bin/bash "$file")
	else
		msg=$(cat $file)
	fi
else
	msg="404 Not Found"
fi
echo "HTTP/1.1 200 OK"
echo "Content-Length: ${#msg}"
echo 
echo -n $msg
