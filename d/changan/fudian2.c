//Room: fengxu2.c

inherit ROOM;

void create ()
{
        set ("short", "左翼殿");
        set("long", @LONG
左翼殿虽较皇宫大殿为低，亦高出其他建筑物两丈有多，各由一二十丈的长
廊走道连接皇宫大殿。三座大殿一主二副，自成一个体系，气象肃森。
LONG );
        set("exits", 
        ([ //sizeof() == 1
        	"east" : "/d/changan/huanggong",
        ]));
        set("objects", 
        ([ //sizeof() == 1
        	"/d/changan/npc/shiwei" : 2,
        ]));
	
        set("coor/x", -410);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
