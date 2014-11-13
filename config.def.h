/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#000000";
static const char normbgcolor[]     = "#333333";
static const char normfgcolor[]     = "#cccccc";
static const char selbordercolor[]  = "#000000";
static const char selbgcolor[]      = "#666699";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* include(s) depending on the tags array */
#include "flextile.h"
#include "movestack.c"

static const Rule rules[] = {
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",         NULL,       NULL,       0,            True,        -1 },
    { "Thunderbird",  NULL,       NULL,       1 << 1,       False,       0  },
    { "Pidgin",       NULL,       NULL,       1 << 1,       False,       0  },
    { "Firefox",      NULL,       NULL,       1 << 2,       False,       -1 },
    { "Xmessage",     NULL,       NULL,       0,            True,        -1 },
    { "Sublime",      NULL,       NULL,       1,            False,       1  },
    { "Gedit",        NULL,       NULL,       1,            False,       0  },
};

/* layout(s) */
static const float mfact      = 0.75; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */
static const int layoutaxis[] = {
    1,    /* layout axis: 1 = x, 2 = y; negative values mirror the layout, setting the master area to the right / bottom instead of left / top */
    2,    /* master axis: 1 = x (from left to right), 2 = y (from top to bottom), 3 = z (monocle) */
    2,    /* stack axis:  1 = x (from left to right), 2 = y (from top to bottom), 3 = z (monocle) */
};

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "terminator", NULL };
static const char *lockcmd[]  = { "xscreensaver-command", "-lock", NULL };
static const char *shortcutscmd[]  = { "super-shortcuts-key", NULL };
static const char *superdevcmd[] = { "super-dev-key", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_s,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_a,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_s,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_a,      movestack,      {.i = -1 } },
    { MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_z,      setlayout,      {.v = &layouts[0]} },  // tiling layout
    { MODKEY,                       XK_x,      setlayout,      {.v = &layouts[2]} },  // master layout
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_q,      focusmon,       {.i = 0 } },
    { MODKEY,                       XK_w,      focusmon,       {.i = 1 } },
    { MODKEY|ShiftMask,             XK_q,      tagmon,         {.i = 0 } },
    { MODKEY|ShiftMask,             XK_w,      tagmon,         {.i = 1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY,                       XK_d,      rotatelayoutaxis, {.i = 0} },    /* 0 = layout axis */
    { MODKEY|ControlMask|ShiftMask, XK_d,      rotatelayoutaxis, {.i = 1} },    /* 1 = master axis */
    { MODKEY|ShiftMask,             XK_d,      rotatelayoutaxis, {.i = 2} },    /* 2 = stack axis */
    { MODKEY|ShiftMask,             XK_Return, mirrorlayout,     {0} },
    { MODKEY|ShiftMask,             XK_Right,  shiftmastersplit, {.i = -1} },   /* master -> stack */
    { MODKEY|ShiftMask,             XK_Left,   shiftmastersplit, {.i = +1} },   /* stack -> master */
    { MODKEY|ControlMask,           XK_l,      spawn,          {.v = lockcmd } },  /* lock screen */
    { MODKEY,                       XK_f,      spawn,          {.v = shortcutscmd } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

