#!/bin/sh

cd /home/willy/Documents/WTGD
changed=0
git remote update && git status -uno | grep -q 'Your branch is behind' && changed=1
if [ $changed = 1 ]; then    
	echo "Remote changes found in WTGD"
    git pull origin test
    #cd willy
    #catkin_make
    #source devel/setup.bash
    #cd ..
    chmod 777 bin/gitsync.sh
	echo "WTGD Last updated:"
	date
else
    #echo "Up-to-date"
fi
cd /home/willy/Documents/WWEB
changed=0
git remote update && git status -uno | grep -q 'Your branch is behind' && changed=1
if [ $changed = 1 ]; then
    
	echo "Remote changes found in WWEB"
    git pull origin test
	echo "WWEB Last updated:"
	date
else
    #echo "Up-to-date"
fi
