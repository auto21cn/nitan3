inherit ROOM;

void create()
{
	set("short", "��ʯ·");
	set("long", @LONG
һ����ʯС·�����¹��꣬·�濴���������ɾ��ģ�һЩ����������
�Լ��ֵ��߲˵������������˲��Ǻܶ࣬ߺ����������Զ��·������һ��
����ؤ���������޼ҿɹ�������Ĵ��ε�����������Կ�����������һ
�档·�����߶��ǵ��ص�һЩ��լ��
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"nandoor",
  		"west" : __DIR__"suishi8",
	]));

	set("coor/x", -180);
	set("coor/y", -50);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}