#!/bin/bash

dwm &

xset r rate 200 120
feh --bg-scale /home/moona/Desktop/desktop.jpg
setxkbmap -layout gb
xscreensaver -no-splash &

exec terminator &
exec firefox &
exec thunderbird &
exec pidgin &

cat > /tmp/shortcuts.txt <<EOF
alt + Q			previous screen
alt + W			next screen
alt + shift + Q		shift to previous screen
alt + shift + W		shift to next screen

alt + S			next tile
alt + A			previous tile
alt + shift + S		shift to next tile
alt + shift + A		shift to previous tile

alt + Z			make stack bigger
alt + X			make stack smaller
alt + ctrl + Z		stack -> master
alt + ctrl + X		master -> stack

alt + D			toggle stack h/v
alt + ctrl + D		rotate stack
alt + ctrl + shift + D	rotate master

alt + [num]		switch to tag
alt + P			launcher
alt + ctrl + L		lock screen
alt + shift + Q		log out
EOF

while true; do
    xsetroot -name "`date`"
    if [[ -z "$(ps -axo comm | grep dwm$)" ]]; then exit; fi
    sleep 1
done

