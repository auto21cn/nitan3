// ding-unarmed.c 一横一勾拳

inherit SKILL;

string *action_msg = ({
        "$N左手轻轻一抹，向$n的$l拍去",
        "$N右手一提，插向$n的$l",
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 210 + random(50), 
                "attack": 30 + random(10), 
                "dodge" : 30 + random(10), 
                "parry" : 30 + random(10), 
                "damage_type" : random(2)?"内伤":"瘀伤", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 40)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 40)
                return notify_fail("你的内力不够练一横一勾拳。\n");
        me->receive_damage("qi", 30);
        me->add("neili", -30);
        return 1;
}


