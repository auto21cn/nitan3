// suti4.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "苏堤");
        set("long", @LONG
春晓，漫步林荫道上，烟柳笼纱，雀鸟欢鸣，一片生机。苏堤春晓被列为西
湖十景之首，果然名不虚传。北边是压堤桥，南面是望山桥。东面一片梅林，林
后似乎有座院落，但看不真切。
LONG );
        set("exits", ([
            "north"     : "/d/hangzhou/suti3",
            "south"     : "/d/hangzhou/suti5",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/liyuanzhi" : 1,
            "/d/hangzhou/npc/wuya" : 1,
            "/d/hangzhou/npc/maque" : 2,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "hangzhou");
        setup();
        replace_program(ROOM);
}
