// ailao.c ����ɽ����

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int i, a;

        if (!target) target=offensive_target(me);

        if (!target
                || !target->is_character()
                || !me->is_fighting(target))
                return notify_fail("�㲻��ս���У�\n");

//      if (target->is_busy())
//              return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɢ�\n");
        
        weapon=me->query_temp("weapon");
        if (!objectp(weapon) || weapon->query("skill_type") != "sword")
                return notify_fail("�������޽������ʹ�ó�����ɽ���⣿\n");

        if (me->query_skill("kurong-changong", 1)<70)
                return notify_fail("����ڹ����δ�����޷���Ԧ����ɽ���⣡\n");
        
        if (me->query_skill("sword", 1) < 100)
                return notify_fail("�㽣����Ϊ�������޷�ʩչ����ɽ���⣡\n");
        
        if (me->query_skill("duanjia-sword",1)<200)
                return notify_fail("��μҽ���Ϊ�������޷�ʩչ����ɽ���⣡\n");
        
        if( me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("�����õ��ڹ��밧��ɽ������·��㣣�\n");

        if (me->query("neili") <= 500)
                return notify_fail("�����������ʹ�ð���ɽ���⣡\n");
        
        message_vision(HIR "\nͻȻ��$N����ͻ�䣬�����ݺᣬ����������������ǰ����������������������\n\n"NOR, me, target);
        message_vision(HIR "\n��������ʩչ����ɽ�����$n����ʵʵ��������ʮ������\n\n" NOR, me, target);

        if (me->query("combat_exp")*100/target->query("combat_exp")<120)
                a=2;
        else {
                if (me->query("combat_exp")*100/target->query("combat_exp")<150)
                        a=3;
                else {
                        if (me->query("combat_exp")*100/target->query("combat_exp")<180)
                                a=4;
                        else a=5;
                }
        }

        for (i=1; i<=a; i++)
                COMBAT_D->do_attack(me, target, weapon);

        me->start_busy(1);
        if (a>3)
        {
        me->start_busy(a-random(3));
        }
        me->add("neili", -200);
        me->add("jing", -20);
        return 1;
}