// guimai.c 六阴鬼脉

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "六阴鬼脉" NOR; }

int perform(object me, string skill)
{
        return notify_fail("乃世间千年一遇的特殊经脉，此脉至阴至\n"
                           "寒，身俱此经脉的婴儿常被误诊为寒毒缠\n"
                           "身，医而不得其法，导致幼年夭折。但若\n"
                           "活过三岁不死者，此后修炼各种内功将事\n"
                           "半功倍。无论男女，均可直接修炼辟邪剑\n"
                           "法或是葵花魔功，无需再作自宫。\n");
}
