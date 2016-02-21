// yanzhidian.c 胭脂店
// By Dumbness, 2003-5-24 19:23

inherit ROOM;

void create()
{
        set("short", "胭脂店");
        set("long", @LONG
店面不大，里面所有的陈设都是淡色木制品，布局简约，精致。屋里弥漫着
一股隐约的檀香味，柜里，架上摆放的各色胭脂令你眼花缭乱！胭脂鲜红似血，
香气扑鼻。每当朝阳初升，阳光照入店内，映在胭脂上，给人一片耀眼的亮红。
尘世中每个女子都有一种最适合她的属于她自己的胭脂，只是需要等待和寻觅，
实在不容易啊——红颜弹指老，刹那芳华…… 
LONG
        );
        set("exits", ([
                "west"  : "/d/city/beimen",
        ]));
        set("objects", ([
                "/d/city/npc/yao" : 1,
                "/d/city/npc/jpl" : 1,
        ]) );
	set("coor/x", 10);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
