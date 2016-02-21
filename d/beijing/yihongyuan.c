inherit ROOM;

void create()
{
	set("short", "怡红院");
        set("long", @LONG
你一走进来，一眼就看到大厅的墙上挂着一幅幅春宫图，一下子就明白了这
是什么地方。厅内到处张灯结彩，香气扑鼻。几名打扮得妖里妖气的女人分站两
旁对你发出媚笑。一个老鸨婆连忙上前招呼客人。从楼上传来了阵阵打情骂俏的
声音。
LONG );
	set("exits", ([
		"west" : "/d/beijing/wang_8",
	]));

	set("objects", ([
                "/d/beijing/npc/laobaopo" : 1,
                "/d/beijing/npc/piaoke" : 1,
                "/d/beijing/npc/jinv" : 2,
	]));

	set("coor/x", 10);
	set("coor/y", 300);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
