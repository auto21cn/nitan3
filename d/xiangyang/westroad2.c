// Room: /d/xiangyang/westroad2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "西内大街");
        set("long", @LONG
这是一条青石铺就的大街。北面是十字街口。隐隐地能望见南面是一座很高
的彩楼，东面是一堵盖着红色琉璃瓦的高墙，里面是郭府大院。西面是襄阳城内
新开的一家书店，听说里面能买到很好的书。
LONG );
        set("outdoors", "xiangyang");

	set("no_clean_up", 0);
	set("exits", ([
		"west"  : "/d/xiangyang/shudian",
		"south" : "/d/xiangyang/westroad1",
		"north" : "/d/xiangyang/jiekou1",
	]));
	set("coor/x", -320);
	set("coor/y", -60);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

