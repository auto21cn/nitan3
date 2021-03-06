// Room:/d/changan/zhongnan.c

#include <room.h>
inherit BUNCH_ROOM; 

void create()
{
        set("short",  "终南山口");
        set("long", @LONG
终南山又称太乙山，距长安城八十多里，素有『锦秀巨屏拱长安』之说。据
传老子曾在山中讲经。这条大官道穿越终南山口，两面秀峰入云，这里却没有一
条路可以上山。西面是往长安的大道，东面前往中原。
LONG );
        set("exits",  ([  /*  sizeof()  ==  4  */
                "east"  :  "/d/changan/road2",
                "west"  :  "/d/changan/road3",
                "north"  :  "/d/changan/questroom",
        ]));
        set("outdoors", "changan");

        set("coor/x", -320);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}
