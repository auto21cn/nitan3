#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "中央广场");
        set("long", @LONG
这里是城市的正中心，一个很宽阔的广场，铺着青石地面。游手好闲的人常
在这里溜溜达达，经常有艺人在这里表演。中央一棵大榕树(tree)盘根错节，据
传已有千年的树龄，是这座城市的历史见证。树干底部有一个很大的树洞 (dong
)。你可以看到北边有来自各地的行人来来往往，南面人声鼎沸，一派繁华景象，
东边不时地传来朗朗的读书声，西边则见不到几个行人，一片肃静。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "city");
        set("item_desc", ([
                "dong" : WHT "\n这是一个黑不溜湫的大洞，里面不知道"
                         "有些什么古怪。\n" NOR,
                "tree" : GRN "\n这是一棵巨大古老的大榕树，枝叶非常"
                         "的茂密。\n" NOR,
        ]));

        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "south" : __DIR__"nandajie1",
                "west" : __DIR__"xidajie1",
                "north" : __DIR__"beidajie1",
        ]));

        set("objects", ([
                __DIR__"npc/jpl2": 1,
                __DIR__"npc/liapo" : 1,
                "/clone/npc/walker"  : 1,
        ]));

	set("coor/x", 0);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_climb", "climb");
}

int do_enter(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg == "")
        	return 0;

        if (arg == "dong")
        {
                if (objectp(me->query_temp("is_riding")))
                        return notify_fail("没听说过有人能骑坐骑进树洞的。\n");

                if (me->is_busy())
                {
                        return notify_fail("你的动作还没有完成，不能移动。\n");
                        return 1; 
                }

                message("vision", HIC + me->name() + HIC "一弯腰往洞里走"
                                  "了进去。\n" NOR, environment(me), ({me}));

                me->move("/d/gaibang/inhole");
                message("vision", HIC + me->name() + HIC "从洞里走了进来"
                                  "。\n" NOR, environment(me), ({me}));
                return 1;
        }
}

int do_climb(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg == "")
        	return 0;

        if (arg == "tree" || arg == "up")
        {
                if (objectp(me->query_temp("is_riding")))
                        return notify_fail("没听说过有人能骑坐骑还能爬树的。\n");

                if (me->is_busy())
                {
                        return notify_fail("你的动作还没有完成，不能移动。\n");
                        return 1; 
                }

                message_vision(HIC "$N" HIC "攀着榕树的枝杈，三下两下爬了上去。\n"
                               NOR, me);

                me->move(__DIR__"tree");
                message("vision", HIC + me->name() + HIC "从下面的广场攀爬了上来。\n"
                                  NOR, environment(me), ({me}));
                return 1;
        }
}