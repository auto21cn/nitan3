#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N端坐不动，一招「裂石式」，手中$w抖得笔直，对准$n的胸腹要害连刺数鞭",
        "force" : 80,
        "attack": 50,
        "dodge" : -5,
        "parry" : 15,
        "damage": 40,
        "lvl"   : 0,
        "skill_name" : "裂石式",
        "damage_type": "刺伤"
]),
([      "action": "$N身形一转，一招「断川式」，手中$w如矫龙般腾空一卷，猛地向$n劈头打下",
        "force" : 210,
        "attack": 58,
        "dodge" : -20,
        "parry" : 50,
        "damage": 90,
        "lvl"   : 80,
        "skill_name" : "断川式",
        "damage_type": "抽伤"
]),
([      "action": "$N力贯鞭梢，一招「破云式」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 240,
        "attack": 65,
        "dodge" : -10,
        "parry" : 55,
        "damage": 120,
        "lvl"   : 100,
        "skill_name" : "破云式",
        "damage_type": "抽伤"
]),
([      "action":"$N力贯鞭梢，一招「分海式」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 270,
        "attack": 70,
        "dodge" : 5,
        "parry" : 60,
        "damage": 150,
        "lvl"   : 120,
        "skill_name" : "分海式",
        "damage_type": "抽伤"
]),
([      "action":"$N力贯鞭梢，一招「裂空式」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 310,
        "attack": 77,
        "dodge" : 6,
        "parry" : 65,
        "damage": 180,
        "lvl"   : 140,
        "skill_name" : "裂空式",
        "damage_type": "抽伤"
]),
([      "action":"$N力贯鞭梢，一招「佛光普照」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 350,
        "attack": 85,
        "dodge" : 12,
        "parry" : 70,
        "damage": 200,
        "lvl"   : 160,
        "skill_name":  "佛光普照",
        "damage_type": "抽伤"
]),
([      "action":"$N力贯鞭梢，一招「金刚伏魔」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 380,
        "attack": 91,
        "dodge" : 17,
        "parry" : 75,
        "damage": 220,
        "lvl"   : 180,
        "skill_name" : "金刚伏魔",
        "damage_type": "抽伤"
]),
([      "action":"$N力贯鞭梢，一招「佛法无边」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 420,
        "attack": 98,
        "dodge" : 20,
        "parry" : 85,
        "damage": 250,
        "lvl"   : 200,
        "skill_name" : "佛法无边",
        "damage_type": "抽伤"
]),
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
        object weapon;

        if ((int)me->query("str") < 26)
                return notify_fail("你研究了半天，感觉膂力有些低，始终无法随意施展。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("你必须先找一条鞭子才能练鞭法。\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力不足，没有办法练日月鞭法，多练些内力再来吧。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候太浅，没有办法练日月鞭法。\n");

        if ((int)me->query_skill("whip", 1) < 100)
                return notify_fail("你的基本鞭法火候太浅，没有办法练日月鞭法。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("riyue-bian", 1))
                return notify_fail("你的基本鞭法水平还不够，无法领会更高深的日月鞭法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("riyue-bian",1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 80)
                return notify_fail("你的体力不够练日月鞭法。\n");

        if ((int)me->query("neili") < 90)
                return notify_fail("你的内力不够练日月鞭法。\n");

        me->receive_damage("qi", 75);
        me->add("neili", -85);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"riyue-bian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;
       // int level;
        object weapon;
        string *msg;
        weapon = me->query_temp("weapon");
        if (! objectp(weapon)) return;
        msg = ({
                HIR"只听得“啊”的一声惨叫，$n背脊为"+weapon->name()+HIR"所击中，摔出了战圈，眼见是不活了。\n"NOR,
                HIR"这一鞭威力极巨，登时打得$p脑浆迸裂，四肢齐折，不成人形。\n"NOR,
                HIR""+weapon->name()+HIR"一抖之下，一股排山倒海的内劲向$n胸口撞到，$n当场肋骨断折，五脏齐碎。\n"NOR,
        });
        result = ([ "damage" : damage_bonus ]);
        result += ([ "msg" : msg[random(sizeof(msg))] ]);
        return result;
}


int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (! me->query_temp("weapon"))
                return 0;

        lvl = me->query_skill("riyue-bian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
