//Room: /d/dali/yaopu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","药铺");
        set("long", @LONG
这是一家神秘的药铺，座落在大和街和市中心的交界处，普通的门面和招牌，
街坊们都说这家药铺的药灵验的很。从药柜上的几百个小抽屉里散发出来的一股
浓浓的药味，让你几欲窒息。据说这家店铺有一种很神密的药物。
LONG );
	set("objects", ([
	   "/d/dali/npc/hehongyao": 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "north"  : "/d/dali/taiheeast",
	]));
	setup();
	replace_program(ROOM);
}

