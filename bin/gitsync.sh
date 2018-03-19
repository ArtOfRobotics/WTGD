#!/bin/sh

date
cd /home/willy/Documents/WTGD
if git fetch > /dev/null 2>&1; then
    echo "No remote changes found in WTDG"
else
    echo "Remote changes found in WTGD"
fi
cd /home/willy/Documents/WWEB
if git fetch > /dev/null 2>&1; then
    echo "No remote changes found in WWEB"
else
    echo "Remote changes found in WWEB"
    git pull origin test
fi