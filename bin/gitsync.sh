#!/bin/sh

date
cd /home/willy/Documents/WTGD
if git fetch; then
    echo "No remote changes found in WTDG"
else
    echo "Remote changes found in WTGD"
    git pull origin test
    cd willy
    catkin_make
    source devel/setup.bash
    cd ..
    chmod 777 bin/gitsync.sh
fi
cd /home/willy/Documents/WWEB
if git fetch; then
    echo "No remote changes found in WWEB"
else
    echo "Remote changes found in WWEB"
    git pull origin test
fi