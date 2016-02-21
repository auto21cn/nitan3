//Room: /d/dali/wuyiminju3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","乌夷民居");
        set("long", @LONG
这是一所乌夷族的房屋。此间正处市镇，四周无山势可依，门口正对巷陌。
青石大房，装修颇为不俗，大门是精心雕制的，刻有日、月、虎豹等精美的图案，
看来这里是乌撒部的祭祀大屋。
LONG );
	set("exits",([ /* sizeof() == 1 */
	    "enter"  : "/d/dali/jisidawu1",
	    "east"   : "/d/dali/zhenxiong",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

