// ROOM : linjxd4.c
inherit ROOM;
void create()
{
  set("short","林间小道");
        set("long", @LONG
你走在一条阴暗的林间小道上，两旁是阴森森的树林。一阵阵风吹过树梢，
发出沙沙的响声，令你不寒而栗。
LONG );
  set("exits",([
      "south" : "/d/heimuya/linjxd6",
      "north" : "/d/heimuya/linjxd1",     
      "east"  : "/d/heimuya/linjxd2",
      "west"  : "/d/heimuya/linjxd5",
  ]));
        set("objects", ([
            CLASS_D("riyue") + "/renwoxing": 1,

        ]));

  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
