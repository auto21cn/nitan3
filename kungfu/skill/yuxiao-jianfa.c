// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// yuxiao-jianfa.c 玉萧剑法

#include <ansi.h>

inherit SKILL;

string *xue_name = ({ 
        "劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
        "幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
}); 

string *parry_msg = ({
        "却见$n身子微转，轻描淡写的以$w轻轻挡开，口唇未离箫边，乐声竟未有片刻停滞。\n",
});

string query_parry_msg(object weapon)
{
        object me = this_player();

        if (! objectp(weapon)
        ||  ! me->query_temp("exercise/playing"))
                // return SKILL_D("parry")->query_parry_msg(weapon);
                return 0;
        else
                return parry_msg[random(sizeof(parry_msg))];
}

string *action_msg = ({
        "$N身形一闪，手中$w一振，使出一招「山外清音」，圈转手中$w，拦腰横削，陡然呼地一声，$w反撩，风驰电挚般疾刺$n的$l",
        "$N$w一横，使出一式「金声玉振」，身随剑走，寓守于攻，对$n的招式竟是不闪不避，径直削向$n的$l",
        "$N手中$w盘旋飞舞，使出一招「响隔楼台」，反手一剑刺出，半途中已连变好几个方位，刺向$n的$l",
        "$N手中$w蓦然一立，使出一招「月射寒江」，$w如新月般成弧圈转，倏地一展，电光石火般刺向$n的$l",
        "$N挺手中$w，向$n上盘刺到，正是一招「凤曲长鸣」，剑光闪烁，剑尖微颤，手中$w发出嗡嗡之声，点向$n上盘诸处大穴",
        "$N袍袖一拂，顺势使出一招「潇湘水云」，剑势连绵，泠若御风，身形一沾即走，宛如翩翩起舞，飘然刺向$n的$l",
        "$N伸指在$w上一弹，铮的一声清响，一招「棹歌中流」，$w中宫直进，更无丝毫花巧，凌厉无前的刺向$n的$l",
        "$N身形展动，使出一式「萧史乘龙」，手中$w矫夭飞舞，如神龙破空一般，刺向$n的$l，姿态飘逸，大有仙气",
        "$N剑法一变，身形急趋急退，一式「飞花点翠」，剑气森森，剑势如满天花雨一般，向四面八方铺洒开来，实在令人避无可避",
        "$N逆踏先天八卦方位，剑交左手，徐徐使出一招「猗兰履霜」，手中$w斜指，刺向$n，剑势虚虚实实，应左则右，与通常剑理大相径庭",
        "$N手中$w成弧，一招「玉漏催银箭」，刺向$n，去势虽不甚急，但却占尽先机，将$n身周三尺方圆之地尽数封住",
        "$N脚步踉踉跄跄，看似已摇摇欲坠，实则足踩九宫，一招「酒阑闻塞笛」，剑势平平淡淡，若有若无地刺向$n的$l",
        "$N移步换形，一招「歧山别鹤」，$w脱手飞出，疾射$n的$l，接着使出分身捉影，后发先至，紧贴$w飞撩过来，骈指为剑，刺向$n",
        "$N一声长啸，内力源源不绝注入剑身，剑上青芒大盛，一式「广陵止息」，剑发龙吟，\n一道匹练也似的剑光挟着森森剑气破空而起，宛如天河倒泻，沛然莫御",
        "$N脚踩伏羲六十四卦方位，剑势加快，使出一招「星河千帆舞」，只见一片茫茫剑气中，\n无数青色光圈潮涌而至，倾刻之间$n已没入剑光之中",
        "$N跨上一步，$w向前递出，其势增之一分嫌太急，减之一分嫌太缓，正是一式「天际识归舟」，剑势尤如青天白云，无暇无垢",
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");
                
        if ((int)me->query_skill("bibo-shengong", 1) < 50)
                return notify_fail("你的碧波神功火候太浅。\n");
 
        return 1;
}

mapping query_action(object me, object weapon)
{
        int level = me->query_skill("yuxiao-jianfa", 1);
        
        if (random(level) > 200 &&
            me->query_skill("force", 1) > 100 &&
            me->query("neili") > 200)
        {
                return ([
                        "action": HIC "$w" NOR + HIC "上的剑芒，犹似长蛇般伸缩不定......\n\n"
                                  HIG"$N丹田中猛提一口真气，身子滴溜溜的打了半个圈子，手中$w"NOR+HIG"一挺，蓦地剑芒突盛，青芒疾刺$n$l！"NOR,
                        "dodge" : 100,
                        "parry" : 100,
                        "attack": 200,
                        "damage": 200,
                        "damage_type":  "刺伤"
                ]);
        }
                       
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(50),
                "attack": 70 + random(10),
                "dodge" : 70 + random(10),
                "parry" : 70 + random(10),
                "damage_type" : random(2)?"刺伤":"割伤",
        ]);
}
        
int practice_skill(object me)
{
        object weapon;

        if (! (weapon = me->query_temp("weapon")))
                return notify_fail("空手时无法练玉箫剑法。\n");
        if ((string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，无法练玉箫剑法。\n");
        if ((int)me->query("qi") < 80)
                return notify_fail("你的体力不够练玉箫剑法。\n");

        if ((int)me->query("neili") < 80)
                return notify_fail("你的体力不够练玉箫剑法。\n");
                                
        me->receive_damage("qi", 70);
        me->add("neili", -70);
        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"yuxiao-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage) 
{
        mixed result;
        string name, weapon;
        name = xue_name[random(sizeof(xue_name))];

        if( damage < 50 ) return 0;

        if (! objectp(weapon = me->query_temp("weapon"))
        ||  (weapon->query("id") != "yu xiao" &&
            weapon->query("id") != "xiao")) 
                return;

        result = ([ "damage" : damage ]);
        
        if (random(2) != 1)
                result += ([ "msg" : HIR "$n听到耳边传来一阵阵萧声，顿时血气翻滚，一股热流穿心而过！\n" NOR]);
        else
                result += ([ "msg" : HIB "$n被$N剑上所附的一部分螺旋劲气侵入" RED + name + NOR + 
                                     HIB "，顿时经脉倒转，痛苦万分！\n" NOR]);
        return result;
}

int query_effect_parry(object attacker, object me) 
{
        int lvl;

        if (! objectp(me->query_temp("weapon")))
                return 0;

        lvl = me->query_skill("yuxiao-jian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}


