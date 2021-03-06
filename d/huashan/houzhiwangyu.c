#include <ansi.h>
inherit ROOM;

void message_competition(string msg);
void create()
{
        set("short", "猴子望月");
        set("long", @LONG
此处原是一仞高耸入云的峭壁，不知何年由人从峭壁的半腰硬是开出一条栈
道来，栈道旁有一粗十余丈的擎天石柱，石柱顶生一松，松旁有一天生奇石，宛
如翘首望月的猴子。 
LONG
);
        set("exits", ([ /* sizeof() == 3 */
                "southdown" : __DIR__"liyubei",
                // "northup" : "/adm/npc/huashanjueding",
                "1" : "/adm/npc/biwu1",
                "2" : "/adm/npc/biwu2",
                "3" : "/adm/npc/biwu3",
                "4" : "/adm/npc/biwu4",
        ]));

        set("outdoors", "huashan" );

        set("no_fight", 1);
        setup();
}

void message_competition(string msg)
{
        CHANNEL_D->do_channel(this_object(), "rumor", msg);
}

int valid_leave(object me, string dir)
{
        int i;
        object *inv;
        int age = (int)me->query("age");

        if (dir == "southdown" || (dir == "northup" && !me->query_condition("killer")))
                return 1;
                
        inv = all_inventory(me);
        for(i=sizeof(inv)-1; i>=0; i--)
        {
                if (me->query_condition("killer"))
                        return notify_fail("杀人者不可以进入比武场！！！\n");
                if (! wizardp(me) &&
                    inv[i]->query("weapon_prop/damage") > 100)
                        return notify_fail("不可以携带神器利器进入比武场！！！\n");
                if (! wizardp(me) &&
                    inv[i]->query("armor_prop/armor") > 100)
                        return notify_fail("不可以携带神器利器进入比武场！！！\n");
        }

        if (wizardp(me)
        ||  (dir == "1" && age < 19) 
        ||  (dir == "2" && (age >= 19 && age < 31)) 
        ||  (dir == "3" && ( age >= 31 && age < 41)) 
        ||  (dir == "4" && age >= 41)) 
        {
                /*
                message_competition((ultrap(me) ? "大宗师" : "") +
                            me->name(1) + "进入华山绝顶的武林大会会场。");
                */
                return 1;
        }
        if (dir == "northup")
        {
                /*
                message_competition((ultrap(me) ? "大宗师" : "") +
                            me->name(1) + "进入华山绝顶的武林大会会场。");
                */
                if (me->query_condition("killer"))
                        return notify_fail("杀人者不可以进入比武场！！！\n");
                return 1;
        }
        return notify_fail("你不可以到那边比武！！\n");
}


