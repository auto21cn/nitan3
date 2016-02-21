#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
�������ҹ�ǰ��һ��ʯ����������Σ����ͱ��Ϻ������
��������졣���׿�һ��¯���ڴ������Ϊ������ͷ�㡹����
��͵������Ը��ʯ�����������������޷�����ǰ�а������ƣ�
����������Ԩ����һʧ�㣬��ʬ���޴档
LONG);
        set("exits", ([
                "northup" : __DIR__"nanyanfeng",
                "enter" : __DIR__"nanyangong",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
	set("coor/x", -360);
	set("coor/y", -330);
	set("coor/z", 100);
	setup();
}

void init()
{
        add_action("do_mianbi", "think");
}

int do_mianbi(string arg)
{
        object ob = this_player();

        if (! arg)
        {
                message_vision("$N�����ʯ��������˼���ã���"
                               "æһ����һ������\n",ob);
                return 1;
        }

        if ((int)ob->query_skill("literate", 1) < 100)
        {
                message_vision("$N�����ʯ������������ģ�û"
                               "һ������ʶ��\n",ob);
                return 1;
        }

        if ((int)ob->query_skill("taoism", 1) < 100)
        {
                message_vision("$N��ʯ����ÿһ���ֶ���ʶ����"
                               "�ǲ�֪��˵����ʲô��\n",ob);
                return 1;
        }

        if (arg == "taiji-jian" ||
            arg == "taiji-quan" ||
            arg == "tiyunzong")
        {
                if ((int)ob->query_skill(arg, 1) < 100)
                {
                        message_vision("$N��" + to_chinese(arg) +
                                       "��Ȼ̫�ͣ��޷�����ʯ�����ݡ�\n",ob);
                        return 1;
                }

                if ((int)ob->query_skill(arg, 1) > 180)
                {
                        message_vision("$N��" + to_chinese(arg) +
                                       "�Ѿ�û��Ҫ��ʯ�������ˡ�\n", ob);
                        return 1;
                }

                if (! ob->can_improve_skill(arg))
                {
                        message_vision("$N��ʵս���鲻�㣬�޷�"
                                       "����ʯ�����ݡ�\n", ob);
                        return 1;
                }

                if (ob->query("jing") < 150)
                {
                        message_vision("$N̫���ˣ������޷���"
                                       "��ʯ�����ݡ�\n", ob);
                        return 1;
                }
                ob->improve_skill(arg, 1 + random(ob->query("int")));
                ob->add("jing", -100 - random(50));
                message_vision(HIY "$N" HIY "�����ʯ��������˼��������"
                               "�ã���������\n" NOR, ob);
                write(HIC "��ԡ�" + to_chinese(arg) + HIC "�������µ���"
                      "�⡣\n" NOR);
                return 1;
        } else 

        message_vision(HIY "$N" HIY "�����ʯ��������˼���ã����ƺ�ûʲ"
                       "ô������\n" NOR, ob);
        return 1;
}