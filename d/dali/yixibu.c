//Room: /d/dali/yixibu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","易溪部");
        set("long", @LONG
易溪部也是乌夷族乌杂蛮的部落。这里处半坡地，附近有不少农田，但农业
落后，需要换季轮耕，因而村民经常迁徙，镇子里除了祭祀大屋外，其它房屋都
很简陋。
LONG );
	set("objects", ([
	   "/d/dali/npc/shaonu": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "northwest"  : "/d/dali/atoubu",
	    "south"      : "/d/dali/wuyiminju4",
	    "east"       : "/d/dali/biluoshan",
	]));
	setup();
	replace_program(ROOM);
}

