/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 27;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = {"hack:pixelsize=14:antialias=true:autohint=true"};

static const char dmenufont[]       = "hack:pixelsize=14:antialias=true:autohint=true";

static const char unfocues_border[]	= "#282a36";

static const char selected[]	    = "#6699df";
static const char bar_fg1[]	        = "#bd93f9";
static const char unfocues_fg[]     = "#282a36";

static const unsigned int baralpha = 0xf0;
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#f8f8f2", unfocues_fg,  unfocues_border},
	[SchemeSel]  = { "#f8f8f2", "#545771",   selected},
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",           NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "St",             NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Alacritty",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,             NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-h", "27", "-m", dmenumon, "-fn", dmenufont, "-nb",unfocues_fg , "-nf", "#f8f8f2", "-sb", selected, "-sf", unfocues_fg, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_s,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_w,      killclient,     {0} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },	//Tiling
	{ MODKEY,			            XK_y,      fullscreen,     {0} },					//Full Screen
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },	//Monocole
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[3]} },	//Fibonacci
	{ MODKEY,			            XK_o,      setlayout,      {.v = &layouts[12]} },	//Centered master
	{ MODKEY,                       XK_space,  setlayout,      {0} },					//???
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },					//Toggle floating mode
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	//All gaps
	{ MODKEY|ControlMask,           XK_plus,   incrgaps,       {.i = +1 } },
	{ MODKEY|ControlMask,    		XK_minus,  incrgaps,       {.i = -1 } },

	//Gaps between window
	{ MODKEY|ShiftMask,             XK_plus,   incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,    			XK_minus,  incrigaps,      {.i = -1 } },

	//Gaps between screen border
	{ MODKEY,              			XK_plus,   incrogaps,  	   {.i = +1 } },
	{ MODKEY,	 		   			XK_minus,  incrogaps,      {.i = -1 } },

	//Gaps settings
	{ MODKEY|ControlMask,    XK_0,      togglegaps,     {0} },
	{ MODKEY|ControlMask|ShiftMask,    XK_0,      defaultgaps,    {0} },

	{ MODKEY,       XK_w,	        spawn,		SHCMD("brave") },

	{ MODKEY|ControlMask,  XK_F6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_F6,      incrihgaps,     {.i = -1 } },
	{ MODKEY,              XK_F7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_F7,      incrivgaps,     {.i = -1 } },
	{ MODKEY,              XK_F8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_F8,      incrohgaps,     {.i = -1 } },
	{ MODKEY,              XK_F9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_F9,      incrovgaps,     {.i = -1 } },
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

	{ 0,       XK_F2,	        spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0,       XK_F3,	        spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0,       XK_F4,          spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

