#!/bin/sh

cd /home/willy/Documents/WTGD
changed=0
git remote update 2>&1 >/dev/null && git status -uno | grep -q 'Your branch is behind' && changed=1
if [ $changed = 1 ]; then    
	echo "Remote changes found in WTGD"
    git reset --hard origin/test
    #cd willy
    #catkin_make
    #source devel/setup.bash
    #cd ..
    chmod 777 bin/gitsync.sh
    chmod -R 777 bin
	echo "WTGD Last updated:"
	date
fi

cd /home/willy/Documents/WWEB
changed=0
git remote update 2>&1 >/dev/null && git status -uno | grep -q 'Your branch is behind' && changed=1
if [ $changed = 1 ]; then
    
	echo "Remote changes found in WWEB"
    git reset --hard origin/test
    chmod -R 777 src/views
    chmod -R 777 src/scripts
    chmod 777 src/start.sh
    pkill node
    source devel/setup.bash
    rosrun willyweb start.sh
	echo "WWEB Last updated:"
	date
fi
