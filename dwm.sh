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

alt + Z			tiling mode (default)
alt + X			fullscreen master

alt + Left		make stack bigger
alt + Right		make stack smaller
alt + shift + Left	stack -> master
alt + shift + Right	master -> stack

alt + D			toggle stack h/v
alt + shift + D		rotate stack
alt + ctrl + shift + D	rotate master

alt + Enter		swap to master
alt + shift + Enter	flip layout

alt + [num]		switch to tag
alt + P			launcher
alt + F			shortcuts (i.e. THIS!)
alt + ctrl + L		lock screen
alt + shift + Q		log out
EOF

while true; do
    xsetroot -name "`date`"
    if [[ -z "$(ps -axo comm | grep dwm$)" ]]; then exit; fi
    sleep 1
done

