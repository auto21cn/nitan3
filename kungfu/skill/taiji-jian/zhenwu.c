// zhenwu.c 真武除邪

#include <ansi.h>
#include <combat.h>

#define PFM_NAME        "真武除邪"

inherit F_SSERVER;
#include <balance.h>

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
                
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「" + PFM_NAME + "」只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
                
        if ((int)me->query_skill("taiji-jian", 1) < 250)
                return notify_fail("你的太极剑法不够娴熟，不会使用「" + PFM_NAME + "」。\n");
                                
        if ((int)me->query_skill("force", 1) < 250)
                return notify_fail("你的内功修为不够高，难以运用「" + PFM_NAME + "」。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 250)
                return notify_fail("你的太极神功修为不够高，难以运用「" + PFM_NAME + "」。\n");

        if (userp(me) && ! me->query("can_perform/taiji-jian/zhenwu"))
                return notify_fail("你没有经过张三丰祖师的亲自提点，无法使用领会「" +
                                    PFM_NAME + "」的精髓。\n");
                                    
        if ((int)me->query("neili") < 2000)
                return notify_fail("你现在真气不够，不能使用「" + PFM_NAME + "」。\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("你没有激发太极剑法，不能使用「" + PFM_NAME + "」。\n");

        msg = HIY "$N" HIY "闭目凝神，心如点转，一招充满太极剑意的「" HIW + PFM_NAME +
              HIY "」缓缓使出，剑招返朴归真，看似平淡无奇，\n实则汇集了天地之间的正气，"
              HIY "由手中" + weapon->name()+ "幻化出无数太极剑圈，铺天盖地的压向$n！\n" NOR;

        ap = ap_power(me, "sword");
        dp = dp_power(target, "parry");
        
        // 增强 ap
        if (weapon->name() == "真武剑") ap += (30 + random(20));
        if (target->is_bad()) ap = ap * 3 / 2;
        // 削弱 ap
        if (me->is_not_good()) ap = ap / 2;
        if (me->is_bad()) ap = ap / 3;
        if (target->is_good()) ap = ap * 4 / 5;

        if (wizardp(me) && me->query("env/combat_test"))
        {
                tell_object(me, HIY "AP: " + ap + ". DP: " + dp + ".\n" NOR);
        }
        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = da_power(me, "sword");

                me->add("neili", -(damage * 1 + (random(2))));
//              tell_object(me, HIC "DAMAGE: " + damage + ".\n" NOR);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "\n$p" HIR "被$P的正气所慑，竟然吓得顾不上招架，"
                                           "这一剑自胸口向小腹横划而过，\n顿时鲜血飞溅！\n" NOR);
                me->start_busy(3);
        } else 
        {
                msg += WHT "\n然而$p" WHT "竟然丝毫不以为意，轻描淡写的将$P"
                       WHT "的剑招架开。\n" NOR;
                me->add("neili", -50);
                me->start_busy(4);
        }
        message_combatd(msg, me, target, 0, 1);

        return 1;
}

