//Room: /d/dali/dating.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","大厅");
        set("long", @LONG
这里是五华楼的前大厅，异常宽敞明亮，足有一里见方，全是云石铺地，黑
白相间，足足可以容纳二、三千人。时时可见锦衣侍者手托美食来回行走。
LONG );
	set("objects", ([
	   "/d/dali/npc/shizhe": 3,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "north"   : "/d/dali/louti",
	    "out"     : "/d/dali/gudao",
	]));
	setup();
	replace_program(ROOM);
}

