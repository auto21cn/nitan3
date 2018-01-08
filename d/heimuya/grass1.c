inherit ROOM;
 
void create()
{
        set("short", "草地");
        set("long", @LONG
你走在一片草地。草地东边有一片墓地。
LONG );
        set("exits", ([
            "east"    : "/d/heimuya/mudi",
            "south"    : "/d/heimuya/fen0", 
            "north"    :"/d/heimuya/grass2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "inn");    
        setup();
	replace_program(ROOM);
}
