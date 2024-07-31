/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 6;		/* border pixel of windows */
static const unsigned int gappx     = 6;
static const unsigned int snap	  	= 32;	   /* snap pixel */
static const int showbar			= 1;		/* 0 means no bar */
static const int topbar			 	= 1;		/* 0 means bottom bar */
static const char *fonts[]		 	= { "Mononoki Nerd Font:size=16" };
static const char dmenufont[]	   	= "Mononoki Nerd Font:size=16";
static unsigned int baralpha		= 0xd0;
static unsigned int borderalpha	 	= OPAQUE;
static const char col_bg[]		  	= "#222222";
static const char col_fg[]		  	= "#cccccc";
static const char col_fga[]		 	= "#eeeeee";
static const char col_bga[]		 	= "#318d56"; //#3fb36d
static const char *colors[][3]	  	= {
	/*			   fg		 bg		 border   */
	[SchemeNorm] = { col_fg,	col_bg,		col_bg 	},
	[SchemeSel]  = { col_fga,   col_bga,   	col_bga	},
};

/* tagging */
static const char *tags[] = { "   ", "   ", "   ", "   ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 "};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	  				instance	title	   	tags mask	isfloating  monitor */
	{ "chromium-browser",  		NULL,	   	NULL,	   	0,	    	0,		   	-1},
	{ "jellyfinmediaplayer",  	NULL,	   	NULL,	 	0,	    	0,		   	-1},
	{ "calcifer",  				NULL,	   	NULL,	 1<<2,	    	0,		   	-1},
	{ "jiji",  					NULL,	   	NULL,	 1<<3,	    	0,		   	-1},
	{ "discord",  				NULL,	   	NULL,	 1<<3,	    	0,		   	-1},
};

/* layout(s) */
static const float mfact	 = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster	 = 1;	/* number of clients in master area */
static const int resizehints = 1;	/* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol	 arrange function */
	{ "   ",	  tile },	/* first entry is default */
	{ "   ",	  monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,					   		KEY,	  view,		   		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,		   		KEY,	  toggleview,	 	{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,			 		KEY,	  tag,				{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, 	KEY,	  toggletag,	  	{.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] 	= { "/home/penwing/nixos/scripts/dmenu_launcher.sh", NULL };
static const char *termcmd[]  	= { "kodama", NULL };
static const char *chromium[]  	= { "chromium", "--wm-window-animations-disabled", "--animation-duration-scale=0", NULL };
static const char *screenlock[] = { "betterlockscreen", "-l", NULL };


static const Key keys[] = {
	/* modifier				key				function		argument */
	{ MODKEY,				XK_d,	  		spawn,		  	{.v = dmenucmd } 	},
	{ MODKEY,			 	XK_Return, 		spawn,		  	{.v = termcmd } 	},
	{ MODKEY,			 	XK_i, 			spawn,		  	{.v = chromium } 	},
	{ MODKEY,			 	XK_twosuperior, spawn,		  	{.v = screenlock } 	},
	{ MODKEY,               XK_space,      	setlayout,  	{0} 				},
	{ MODKEY,             	XK_f,      		togglefullscreen, {0} 				},
	{ MODKEY,				XK_Down,	  	focusstack,	 	{.i = +1 } 			},
	{ MODKEY,				XK_Up,	  		focusstack,	 	{.i = -1 } 			},
	{ MODKEY,				XK_F12,	  		incnmaster,	 	{.i = +1 } 			},
	{ MODKEY,				XK_F11,	  		incnmaster,	 	{.i = -1 } 			},
	{ MODKEY,				XK_exclam,	  	zoom,	 		{0} 				},
	{ MODKEY,				XK_Left,	  	setmfact,	   	{.f = -0.05} 		},
	{ MODKEY,				XK_Right,	 	setmfact,	   	{.f = +0.05} 		},
	{ MODKEY|ShiftMask,		XK_a,	  		killclient,	 	{0} 				},
	{ MODKEY,				XK_Tab,	  		view,		   	{.ui = ~0 } 		},
	{ MODKEY|ShiftMask,		XK_Tab,	  		tag,			{.ui = ~0 } 		},
	{ MODKEY,				XK_comma,  		focusmon,	   	{.i = -1 } 			},
	{ MODKEY,				XK_semicolon, 	focusmon,	   	{.i = +1 } 			},
	{ MODKEY|ShiftMask,		XK_comma,  		tagmon,		 	{.i = -1 } 			},
	{ MODKEY|ShiftMask,		XK_semicolon, 	tagmon,		 	{.i = +1 } 			},
	{ MODKEY|ShiftMask,		XK_q,	  		quit,		   	{0} 				},
	{ MODKEY,			 	XK_F1, 			spawn,		  	SHCMD("pamixer -t && notify-send -u normal -a \"volume\" \"$(pamixer --get-volume-human)\"") 	},
	{ MODKEY,			 	XK_F2, 			spawn,		  	SHCMD("pamixer -d 5 -u && notify-send -u normal -a \"volume\" \"$(pamixer --get-volume-human)\"") 	},
	{ MODKEY,			 	XK_F3, 			spawn,		  	SHCMD("pamixer -i 5 -u && notify-send -u normal -a \"volume\" \"$(pamixer --get-volume-human)\"") 	},
	{ MODKEY,			 	XK_F4, 			spawn,		  	SHCMD("brightnessctl -d \"amdgpu_bl1\" set 10%- && notify-send -u normal -a \"brightness\" \"$(brightnessctl -d 'amdgpu_bl1' get)\"") 	},
	{ MODKEY,			 	XK_F5, 			spawn,		  	SHCMD("brightnessctl -d \"amdgpu_bl1\" set +10% && notify-send -u normal -a \"brightness\" \"$(brightnessctl -d 'amdgpu_bl1' get)\"") 	},
	{ MODKEY,			 	XK_F6, 			spawn,		  	SHCMD("~/nixos/scripts/usb_guest.sh") 	},
	{ MODKEY,			 	XK_F7, 			spawn,		  	SHCMD("~/nixos/scripts/susuwatari/client.sh") 	},
	{ MODKEY,			 	XK_F8, 			spawn,		  	SHCMD("~/nixos/scripts/hdmi_paint.sh") 	},
	{ MODKEY,			 	XK_F9, 			spawn,		  	SHCMD("~/nixos/scripts/screen_sleep.sh") 	},
	{ ShiftMask,			XK_Print,		spawn,			SHCMD("maim --select \"/home/penwing/Pictures/screenshots/$(date '+%Y_%m_%d %H:%M:%S').png\"")		},
	TAGKEYS(	XK_ampersand,	0)
	TAGKEYS(	XK_eacute,		1)
	TAGKEYS(	XK_quotedbl,	2)
	TAGKEYS(	XK_apostrophe,	3)
	TAGKEYS(	XK_parenleft,	4)
	TAGKEYS(	XK_minus,		5)
	TAGKEYS(	XK_egrave,		6)
	TAGKEYS(	XK_underscore,	7)
	TAGKEYS(	XK_ccedilla,	8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click				event mask	  button		function		argument */
	{ ClkLtSymbol,		  	0,			  Button1,		setlayout,	  	{0} },
	{ ClkTagBar,			0,			  Button1,		view,		   	{0} },
	// { ClkLtSymbol,		  0,			  Button3,		setlayout,	  {.v = &layouts[2]} },
	// { ClkWinTitle,		  0,			  Button2,		zoom,		   {0} },
	// { ClkStatusText,		0,			  Button2,		spawn,		  {.v = termcmd } },
	// { ClkClientWin,		 MODKEY,		 Button1,		movemouse,	  {0} },
	// { ClkClientWin,		 MODKEY,		 Button2,		togglefloating, {0} },
	// { ClkClientWin,		 MODKEY,		 Button3,		resizemouse,	{0} },
	// 
	// { ClkTagBar,			0,			  Button3,		toggleview,	 {0} },
	// { ClkTagBar,			MODKEY,		 Button1,		tag,			{0} },
	// { ClkTagBar,			MODKEY,		 Button3,		toggletag,	  {0} },
};

