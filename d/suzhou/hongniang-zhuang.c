//Room: /d/suzhou/hongniang-zhaung.c
// by llm 99/06/12

#include <ansi.h>

inherit ROOM;

string look_sign(object me);

void create()
{
	set("short", "������");
        set("long", @LONG
����������·򸾶�Լ��Ե�ĺ����ã�ֻ��������޽��Լ���ǽ����Լ��
�ܵõ����˵ĳ��ϡ�������һ����������������Ǿ���һ������֮���Ե�ʮ��
�����ɡ��������й���һ������ֵ���ľ����(sign)��
LONG );
	set("exits", ([
		"west" : "/d/suzhou/hong-zoulang",
		"east" : "/d/suzhou/yinyuan-tang",
   ]) );

   set("item_desc", ([
   	"sign": (: look_sign :),
   ]) );

   set("objects", ([
        "/adm/npc/meipo" : 1,
      ]) );
   set("coor/x", 230);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
}

string look_sign(object me)
{
	return HIM"Ȱ�Ͳ�Ȱ��\n"
   "��Ե�����\n"
   "����ǰ��ϵ\n"
   "����һ����\n"NOR;
}

int valid_leave(object me, string dir)
{
 	if (dir=="west"&& me->query_temp("pending/pro") )
      me->delete_temp("pending/pro");
      return ::valid_leave(me, dir);
}