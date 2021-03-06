// yiguan.c 驿官

inherit NPC;

void create()
{
    set_name("驿官", ({ "yi guan", "yi", "guan" }));
        set("gender", "男性");
    set("age", 42);
        set("long", "因为常年紧张地从事接待驿马工作，太过于紧张，他显得要比实际老些。\n");

    set("combat_exp", 8000);
        set("shen", 0);

        set_skill("unarmed", 30);
        set_skill("dodge", 40);
        set_skill("parry", 40);

        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 10);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
