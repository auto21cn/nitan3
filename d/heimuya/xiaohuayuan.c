//ROOM: xiaohuayuan.c

inherit ROOM;

void create()
{
	set("short", "小花园");
        set("long", @LONG
从昏暗的地道中出来，你发现自己竟是置身于一个极精致的小花园中，红梅
绿竹，青松翠柏，布置得颇具匠心，往东去是一间精雅小舍。
LONG );
        set("exits", ([
            "south" : "/d/heimuya/didao6",
            "enter" :"/d/heimuya/xiaoshe",   
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
