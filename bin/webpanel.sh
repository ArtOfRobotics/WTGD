#!/bin/bash
# file: webpanel.sh

cd /home/willy/Documents/willyweb
screen -dmS webpanel dotnet Willy.Web.dll
sleep 2

