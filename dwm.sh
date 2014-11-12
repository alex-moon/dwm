#!/bin/bash

dwm &

sleep 1

xset r rate 200 120
feh --bg-scale /home/moona/Desktop/desktop.jpg
setxkbmap -layout gb
xscreensaver -no-splash &

exec terminator &
exec thunderbird &
exec pidgin &

while true; do
    xsetroot -name "`date`"
    sleep 1
done

