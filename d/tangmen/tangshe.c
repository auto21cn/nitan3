//tangshe.c		四川唐门—唐舌卧室

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "寝室");
	set("long",
"这是一间简陋的卧室。屋中只有一张硬木床和一张枣木红桌。这里住\n"
"着唐老太太的贴身保镖唐舌。\n"
);
	set("exits", ([
			"east" : __DIR__"nzlang3",
	]));
	set("area", "蜀中");
	set("objects", ([__DIR__"npc/tangshe" : 1,]));
	setup();
	replace_program(ROOM);
}
