// Room: /d/suzhou/dongdajie2.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "东大街");
        set("long", @LONG
你走在东大街上，踩着坚实的青石板地面。东边是东城门，可以听到守城官
兵的吆喝声，北边是一家老字号的药铺，南边是打铁铺，叮叮当当的声音老远就
能听到。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"east"      : "/d/suzhou/dongmen",
		"north"     : "/d/suzhou/yaopu",
		"south"     : "/d/suzhou/datiepu",
		"west"      : "/d/suzhou/dongdajie1",
		"northwest" : "/d/suzhou/hutong3",
	]));
	set("coor/x", 240);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

