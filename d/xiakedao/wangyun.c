// wangyun.c ����̨

inherit ROOM;

#include <ansi.h>
int do_take(string arg);

void create()
{
        set("short", "����̨");
        set("long", @LONG
����������͵���ߵ� "����̨" �������������Զ���󺣣�
�����õ�ʱ���ܿ���һ���澰-- "�ƺ�" ����ʯ��֮�䳤��һ��
�������׳� "������" ����������Χ����ǿ�������ż���С��(cao)��
LONG    );

        set("exits", ([
                "northdown" : __DIR__"road8",
        ]));

        set("outdoors", "xiakedao");
        set("item_desc", ([
                "cao" : "������̵�С�ݣ��㲻������(take)������\n"
        ]));

        set("caocount", 1);
        setup();
}

void init()
{
        add_action("do_take", "take");
}

int do_take(string arg)
{
        object me = this_player();
        object obn;
        int n;

        n = me->query_skill("dodge", 1);
        if (arg != "cao")
        {
                write("��Ҫ��ʲôѽ��\n");
                return 1;
        }

        message_vision("$N������ǰվ�������һ������ͻȻԾ��\n", me);

        if (n >= 150)
        {
                if (query("caocount") > 0)
                {
                        message_vision("ֻ��$N�������ڿ��д��˼���������������Ʈ"
                                       "Ʈ��أ����ж���һ�\n", me);
                        obn = new(__DIR__"obj/cao");
                        obn->move(me, 1);
                        add("caocount", -1);
                } else
                        message_vision("$N����һ�������ֲ��类�������ˣ�ֻʣһ��ݸ��ˡ�\n",
                                       me);
        } else
        {
                me->receive_damage("qi", 50);
                me->receive_wound("qi", 50);
                message_vision(HIR "ֻ��$N" HIR "�������ڿ��д��˼���������ѽ�����ã�����\n" NOR,
                               me);
                me->move(__DIR__"gudi");
                tell_object(me,HIR "���������ˤ��������������ʹ�����˺ü����ˡ�\n" NOR);
                message("vision", HIR "ֻ��" + me->name() + HIR "���������ˤ��������"
                                  "���ڵ��ϣ����첻����\n" NOR, environment(me), me);
        }
        return 1;
}