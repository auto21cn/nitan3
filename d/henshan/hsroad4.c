inherit ROOM;

void create()
{
        set("short", "����·");
        set("long", @LONG
������һ����������Ļ���·�ϣ�����������ɭɭ�����֡�
���治Զ���Ǻ����س��ˡ�����������һ�������
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "east"  : __DIR__"hengyang11",
                "west"  : __DIR__"hsroad5",
        ]));

        set("coor/x", -30);
	set("coor/y", -110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}