#!/bin/sh

date
cd /home/willy/Documents/WTGD
if git fetch; then
    echo "No remote changes found in WTDG"
else
    git pull origin test
    cd willy
    catkin_make
    source devel/setup.bash
    echo "Remote changes found in WTGD"
fi
cd /home/willy/Documents/WWEB
if git fetch; then
    echo "No remote changes found in WWEB"
else
    echo "Remote changes found in WWEB"
    git pull origin test
fi