// Room: /d/xiangyang/guofuhuayuan.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "郭府后花园");
        set("long", @LONG
这里是郭府的后花园，园内假山林立，西边种着一些青竹，东边是几棵枝叶
茂盛的木笔花树。你一走进来，就闻到一阵阵清新的、淡淡的花香。
LONG );
	set("exits", ([
		"east"  : "/d/xiangyang/guofuwoshi",
		"west"  : "/d/xiangyang/guofukefang",
		"south" : "/d/xiangyang/guofuting",
		"north" : "/d/xiangyang/guofushufang",
	]));
	set("objects", ([
                // CLASS_D("taohua") + "/rong" : 1,
	]));
	set("coor/x", -300);
	set("coor/y", -50);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

