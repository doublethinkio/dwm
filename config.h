/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2;        /* border pixel of windows */
static const unsigned int gappx    = 5;        /* gaps between windows */
static const unsigned int snap     = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray       = 1;     /* 0 means no systray */
static const int showbar           = 1;        /* 0 means no bar */
static const int topbar            = 1;        /* 0 means bottom bar */
static const char *fonts[]         = { "SauceCodePro Nerd Font Mono:size=10" };
static const char col_gray[]       = "#CCCCCC";
static const char col_blue[]       = "#3498DB";
static const char col_blue2[]      = "#0D47A1";
static const char col_black[]      = "#000000";
static const char col_white[]      = "#FFFFFF";

static const unsigned int baralpha 	  = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const Bool viewontag           = True;     /* Switch view on tag switch */
static const char *colors[][3]        = {
	/*              fg             bg           border   */
	[SchemeNorm]  = { col_gray,    col_black,   col_black },
	[SchemeSel]   = { col_white,   col_blue2,   col_blue  },
	[SchemeHid]   = { col_blue,    col_black,   col_black },
};
static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm]  = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]   = { OPAQUE, baralpha, borderalpha },
	[SchemeHid]   = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title         tags mask     isfloating   monitor */
	{ "Peek",        NULL,       NULL,         0,            1,           -1 },
	{ "flameshot",   NULL,       NULL,         0,            1,           -1 },
	{ "scrcpy",      NULL,       NULL,         0,            1,           -1 },
	{ "idea",        NULL,       "win0",       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      monocle },
	{ "",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]   = { "st", NULL };
static const char *chromium[]  = { "chromium", "--proxy-server=socks://127.0.0.1:1080", NULL };
static const char *ranger[]    = { "st", "-e", "ranger", NULL };
static const char *nvim[]      = { "st", "-e", "nvim", NULL };
static const char *music[]     = { "electron-netease-cloud-music", NULL };
static const char *flameshot[] = { "flameshot", "gui", NULL };
static const char *upvol[]     = { "/home/doublethink/scripts/vol-up.sh", NULL };
static const char *downvol[]   = { "/home/doublethink/scripts/vol-down.sh", NULL };
static const char *mutevol[]   = { "/home/doublethink/scripts/vol-toggle.sh", NULL };
static const char *rofirun[]   = { "rofi", "-show", "run", NULL };
static const char *rofiapp[]   = { "rofi", "-show", "drun", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_a,      spawn,          {.v = rofiapp} },
	{ MODKEY,                       XK_r,      spawn,          {.v = rofirun} },
	{ MODKEY,           			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,           			XK_g,	   spawn,          {.v = chromium } },
	{ MODKEY,						XK_e,	   spawn,          {.v = ranger } },
	{ MODKEY,						XK_n,	   spawn,          {.v = nvim } },
	/* { MODKEY,						XK_m,	   spawn,          {.v = music } }, */
	{ MODKEY,						XK_F1,	   spawn,          {.v = flameshot } },
	{ MODKEY,						XK_F11,	   spawn,          {.v = upvol } },
	{ MODKEY,						XK_F10,	   spawn,          {.v = downvol } },
	{ MODKEY,						XK_F9,	   spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_i,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,         		  		XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
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
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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

