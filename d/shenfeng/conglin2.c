
inherit ROOM;
void create()
{
	set("short", "峭壁");
	set("long", @LONG
行到了一座大山之侧，只见半山腰里峭壁之上，生着两朵海碗般大的
奇花，花瓣碧绿，四周都是积雪，白中映碧，加上夕阳金光映照，娇艳华
美，奇丽万状。闻到幽幽甜香，从峭壁上飘将下来，那花离地约有二十余
丈，仍然如此芬芳馥郁，足见花香之浓。瞧那峭壁，但见峨然耸立，气象
森严。
LONG );
	set("exits", ([ /* sizeof() == 2 */
                "northup"  : __DIR__"kunlun1",
                "eastdown" : __DIR__"conglin1",
        ]));
	set("no_new_clean_up", 0);
	set("outdoors", "shenfeng");

	setup();
	replace_program(ROOM);
}
