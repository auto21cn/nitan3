// meiren-sanzhao.c 美人三招
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N身子微曲，纤腰轻扭，左足反踢，向$n的小腹踢去，$n后缩相避，\n"
                   "$N顺势反过身来，左手搂住$n头颈，右手握剑对准$n后心，一剑刺去",
        "force" : 70,
        "dodge" : 5,
        "parry" : 10,
        "damage": 100,
        "lvl" : 0,
        "skill_name" : "贵妃回眸",
        "damage_type" : "刺伤"
]),
([      "action" : "$N翻身卧倒，$n伸出右足踏住$N的后腰，$N的脑袋向着她自己的胸口钻落，\n"
                   "顺势在地下一个筋斗，在$n的胯下钻过，右手握剑刺入$n的后心",
        "force" : 80,
        "dodge" : 20,
        "parry" : 20,
        "damage": 120,
        "lvl" : 10,
        "skill_name" : "小怜横陈",
        "damage_type" : "刺伤"
]),
([      "action" : "$N右足向前轻踢，顺势一勾，腿上的剑疾向$n的咽喉刺去",
        "force" : 120,
        "dodge" : 30,
        "parry" : 30,
        "damage": 160,
        "lvl" : 20,
        "skill_name" : "飞燕回翔",
        "damage_type" : "刺伤"
])
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }

   int valid_combine(string combo) { return combo=="jueming-tui" ; }

int valid_learn(object me)
{
        if (me->query("gender") != "女性")
                return notify_fail("你不是女子，又怎么能学会美人三招呢？\n");
        if (me->query_int() < 25)
                return notify_fail("你的悟性不够，无法学美人三招。\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力太弱，无法学美人三招。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("meiren-sanzhao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        int level;

        if( (int)me->query("jingli") < 30 || (int)me->query("jing") < 30 )
                return notify_fail("你的精神不太好，无法继续练习。\n");

        if( (int)me->query("neili") < 200)
                return notify_fail("你的内力不够练美人三招。\n");


        level = (int)me->query_skill("meiren-sanzhao", 1);
        if( level < 30 )
                return notify_fail("你对美人三招的掌握还不够。\n");

        if( level > (int)me->query_skill("sword", 1))
                return notify_fail("你的美人三招再也练不上去了。\n");

        me->add("jingli", -30);
        me->receive_damage("jing", 30);
        me->add("neili",-30);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( damage_bonus < 100 ) return 0;

        if((damage_bonus/2) > victim->query_str()&& 
               !victim->query_temp("boduo")){
                victim->receive_wound("qi", (damage_bonus - 100) / 2 );
                victim->add_temp("boduo",1);                return HIW "只听到一个冷酷的声音："BLINK"第一感剥夺！\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()&& 
                victim->query_temp("boduo")== 1){                victim->receive_wound("qi", (damage_bonus - 90) / 2 );
                victim->add_temp("boduo",1);
                return HIG"只听到一个冷酷的声音："BLINK"第二感剥夺！\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()&& 
                victim->query_temp("boduo")== 2){                victim->receive_wound("qi", (damage_bonus - 80) / 2 );
                victim->add_temp("boduo",1);
                return HIB "只听到一个冷酷的声音："BLINK"第三感剥夺！\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()&& 
                victim->query_temp("boduo")== 3){       
                victim->receive_wound("qi",(damage_bonus - 70) / 2 );
                victim->add_temp("boduo",1);
                return HIY"只听到一个冷酷的声音："BLINK"第四感剥夺！\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str() && 
                victim->query_temp("boduo")== 4){
                victim->receive_wound("qi", (damage_bonus - 60) / 2 );
                victim->add_temp("boduo",1);
                return HIC"只听到一个冷酷的声音："BLINK"第五感剥夺！\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()&& 
                victim->query_temp("boduo")== 5){
                victim->receive_wound("qi", (damage_bonus - 50) / 2 );
                victim->add_temp("boduo",1);
                return HIR "只听到一个冷酷的声音："BLINK"第六感剥夺！\n" NOR;
        }
        if( (damage_bonus/2) > victim->query_str()&& 
                victim->query_temp("boduo")== 6){
                victim->delete_temp("boduo");
                return WHT"只听到一个冷酷的声音："BLINK"再次剥夺开始！\n" NOR;
        }
        
}
string perform_action_file(string action)
{
        return __DIR__"meiren-sanzhao/" + action;
}


