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

while true; do
    xsetroot -name "`date`"
    if [[ -z "$(ps -axo comm | grep dwm$)" ]]; then exit; fi
    sleep 1
done

