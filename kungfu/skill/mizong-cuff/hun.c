// hun.c 双龙抢珠

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;
        string *limbs,limb;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("mizong-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("双龙抢珠只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("cuff") != "mizong-cuff") 
                return notify_fail("你没有用迷踪拳，无法使用双龙抢珠绝招！\n");

        if( me->query_skill_prepared("cuff") != "mizong-cuff" ) 
                return notify_fail("你所备的并非迷踪拳，不能使用双龙抢珠绝招！\n"); 

        if (skill < 100)
                return notify_fail("你的迷踪拳等级不够，练好了再来！\n");

        if ( objectp(weapon = me->query_temp("weapon")) )
                return notify_fail("你拿着武器如何使用拳法绝招？\n");

        if (me->query("neili") < 500)
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap += me->query("jiali");
        ap += me->query("jianu");

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIY "$N" HIY "身形飘忽，拳影四面八方向$n" HIY "笼罩而去！\n\n" NOR;

        message_combatd(msg, me, target);

        n = (int)me->query("tianmo_jieti/times");
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        msg = HIR "\n$N" HIR "双拳宛若布下天罗地网，招招击向$n" HIR "的关节要害！\n" NOR;
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                limbs = target->query("limbs");
                limb = limbs[random(sizeof(limbs))];
                msg += HIB "$n" HIB "大惊失色，连连中招，竟被$N" HIB "击中" + limb + "！\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIY "$n" HIY "不退反进，长袖一圈一带，$N" HIY "竟递不进招去。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(me->query("id")) ) target->kill_ob(me);
	me->add("neili",-damage/3);
        return 1;
}


