// Room: /d/xiangyang/qianzhuang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "Ǯׯ");
        set("long", @LONG
������������Ǯׯ����Ϊ������ҵ�൱������ص��̺Ŷ�����������Ǯ��
����Ǯׯ���кܶ����ڴ�ȡǮ��Ҳ�����ڶһ�������������ô���Ǯ�ƹ�����ȥ��
���������۲����������´�е�ǰ��ȫ��һ�µ���Ԫ����Ǯׯ��ҵ���ɻ�ɽ����
�ӹܣ�֧Ԯ���������͹����ˡ�ǽ������һ������(paizi)��
LONG );
	set("item_desc", ([
		"paizi" : @TEXT
     ��Ǯׯ�ṩ���·���
      ��Ǯ        deposit����cun
      ȡǮ        withdraw����qu
      Ǯ�Ҷһ�    convert����duihuan
      ����        check����chazhang
TEXT
	]));
	set("exits", ([
		"east" : "/d/xiangyang/southjie1",
	]));
	set("objects", ([
		"/d/xiangyang/npc/huangzhen" : 1,
	]));
	set("coor/x", -300);
	set("coor/y", -100);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
