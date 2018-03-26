#!/bin/sh

date
cd /home/willy/Documents/WTGD
if git fetch; then
    echo "Remote changes found in WTGD"
    git pull origin test
    cd willy
    catkin_make
    source devel/setup.bash
    cd ..
    chmod 777 bin
else
    echo "No remote changes found in WTDG"
fi
cd /home/willy/Documents/WWEB
if git fetch; then
    echo "Remote changes found in WWEB"
    git pull origin test
else
    echo "No remote changes found in WWEB"
fi