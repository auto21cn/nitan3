// Room: /d/xiangyang/wallw2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "石阶");
        set("long", @LONG
这是登向城头的石阶，因为城墙很高，所以很陡。石阶两侧有可供拉车上下
的斜坡道。
LONG );
        set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"southup"   : "/d/xiangyang/wallw4",
		"northdown" : "/d/xiangyang/westgate1",
	]));
	set("coor/x", -340);
	set("coor/y", -90);
	set("coor/z", 10);
	setup();
}
int valid_leave(object me, string dir)
{
        string c_exp;
        int c_skill;
	if (dir == "southup" )
	{
		c_exp=me->query("combat_exp");
		c_skill=me->query_skill("dodge",1);
                if (me->query("qi") > 10)
                {
		        me->receive_damage("qi",10);
                        if (count_lt(count_div(count_mul(count_mul(c_skill, c_skill), c_skill), 10), c_exp) &&
                            c_skill < 101)  
		        me->improve_skill("dodge", (int)me->query_skill("dodge", 1) / 5);
                } else
                {
                        me->set("qi", 0);
                        return notify_fail("你太累了，还是休息一会儿吧。\n");
                }
	}
	return 1;
}


