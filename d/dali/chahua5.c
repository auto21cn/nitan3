//Room: /d/dali/chahua5.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","茶花园");
        set("long", @LONG
大理茶花冠绝天下，镇南王府的茶花自然更非凡品。你站在茶花园中，发现
几朵娇嫩欲滴的茶花，你不禁多看了两眼。西面是一个小湖，湖面碧绿如玉，暖
风吹来，曛曛入醉。
LONG );
	set("objects", ([
	   "/d/dali/obj/chahua11": 1,
	   "/d/dali/obj/chahua12": 1,
	   "/d/dali/obj/chahua13": 1,
	   "/d/dali/npc/huanu": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "northwest"  : "/d/dali/chahua3",
	    "southwest"  : "/d/dali/chahua4",
	]));
	setup();
	replace_program(ROOM);
}

