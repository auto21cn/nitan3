//Room: /d/dali/sima.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","司马堂");
        set("long", @LONG
这里是大理国司马堂。大理东北强宋，西北吐蕃，历年来边疆宁靖，皆司马
劳顿之功。盖吐蕃垂涎大理已久，每每强辞胁迫，大理不得不重兵于西北。
LONG );
	set("objects", ([
	    CLASS_D("dali")+"/fanye" : 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "west"  : "/d/dali/zonglichu",
	]));
	setup();
	replace_program(ROOM);
}

