// look.c
// colored by ReyGod in 1/10/1997 ----- I love colorful world :)

#pragma optimize
#pragma save_binary

#include <room.h>
#include <ansi.h>
#include <combat.h>
#include <armor.h>

// flag of func:look_all_inventroy_of_room/ret_str
#define SHOW_IMMEDIATELY        0
#define RETURN_RESULT      1

inherit F_CLEAN_UP;

int look_room(object me, object env, int brief);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
string look_equiped(object me, object obj, string pro);
string look_all_inventory_of_room(object me, object env, int ret_str);

mapping df_bkpic=([
        "foshan":"xiaozheng",
        "village":"xiaozheng",
        "hangzhou":"hangzhou",
        "heimuya":"heimuya",
        "huashan":"huashan",
        "guanwai":"guanwai",
        "lingjiu":"lingjiu",
        "motianya":"motianya",
        "register":"yanluodian",
        "shenlong":"shenlong",
        "taohua":"taohua",
        "wudang":"wudang",
        "wanjiegu":"wanjiegu",
        "xiakedao":"xiakedao",
        "quanzhen":"quanzhen",
        "beijing":"beijing",
        "changan":"changan",
        "city":"city",
        "city3":"city3",
        "dali":"dali",
        "emei":"emei",
]);

mapping rf_bkpic=([
        "_d_beijing_dangpu":"dangpu",
        "_d_changan_dangpu":"dangpu",
        "_d_city_dangpu":"dangpu",
        "_d_foshan_dangpu":"dangpu",
        "_d_xiangyang_dangpu":"dangpu",
        "_d_suzhou_dangpu":"dangpu",
        "_d_city_shuyuan":"shuyuan",
        "_d_city_shuyuan2":"shuyuan",
        "_d_suzhou_shuyuan":"shuyuan",
        "_d_songshan_shuyuan":"shuyuan",
        "_d_hangzhou_shuyuan":"shuyuan",
        "_d_changan_zahuopu":"zahuopu",
        "_d_fuzhou_zahuopu":"zahuopu",
        "_d_beijing_huichuntang":"yaopu",
        "_d_changan_yaopu":"yaopu",
        "_d_xiangyang_yaopu":"yaopu",
        "_d_suzhou_yaopu":"yaopu",
        "_d_dali_yaoshop":"yaopu",
        "_d_city_zuixianlou":"jiulou",
        "_d_city_shuyuan":"shuyuan",
        "_d_city_shuyuan2":"shuyuan",
        "_d_suzhou_shuyuan":"shuyuan",
        "_d_songshan_shuyuan":"shuyuan",
        "_d_hangzhou_shuyuan":"shuyuan",
        "_d_changan_zahuopu":"zahuopu",
        "_d_fuzhou_zahuopu":"zahuopu",
        "_d_beijing_huichuntang":"yaopu",
        "_d_changan_yaopu":"yaopu",
        "_d_xiangyang_yaopu":"yaopu",
        "_d_suzhou_yaopu":"yaopu",
        "_d_dali_yaoshop":"yaopu",
        "_d_city_zuixianlou":"jiulou",
        "_d_dali_huanggs":"huanggs",
        "_d_emei_jinding":"jingding",
        "_d_death_gate":"guimenguan",
        "_d_changan_bank":"qiangzhuang",
        "_d_beijing_qianzhuang":"qianzhuang",
        "_d_city_qianzhuang":"qianzhuang",
        "_d_changan_bank":"qiangzhuang",
        "_d_beijing_qianzhuang":"qianzhuang",
        "_d_city_qianzhuang":"qianzhuang",
        "_d_emei_jinding":"jingding",
        "_d_dali_huanggs":"huanggs",
        "_d_beijing_dangpu":"dangpu",
        "_d_changan_dangpu":"dangpu",
        "_d_city_dangpu":"dangpu",
        "_d_foshan_dangpu":"dangpu",
        "_d_xiangyang_dangpu":"dangpu",
        "_d_suzhou_dangpu":"dangpu",
]);

//add by JackyBoy@XAJH 2001/5/6
string get_bkpic(object env)
{
        string rf,df;
        rf=replace_string(base_name(env),"/","_");
        df=domain_file(rf);
        if(!undefinedp(rf_bkpic[rf]))
                return rf_bkpic[rf];
        if(!undefinedp(df_bkpic[df]))
                return df_bkpic[df];
        return "";
}

int info(object me, object env)
{
        string *dirs,df;
        mapping exits;

        if( mapp(exits = env->query("exits")) )
                dirs = keys(exits);

        if(sizeof(dirs)==1 && sizeof(dirs)!=0)
                write(TMI("bnway "+dirs[0]+";"));
        else if(sizeof(dirs)!=0)
                write(TMI( sprintf("bnway "+"%s;",implode(dirs[0..sizeof(dirs)], ";")) ));
        df=get_bkpic(env);
        if(df=="") return 1;
        if(df!=me->query_temp("bkpic"))
        {
                me->set_temp("bkpic",df);
                write(TMI("bkpic "+df));
        }
        return 1;
}

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj;
        object env;
        int result;
        string objid, where;

        if (! arg) result = look_room(me, environment(me), 0);
        else
        {
                if (sscanf(arg, "%s of %s", objid, where) == 2)
                {
                        if (where == "here")
                                obj = present(objid, environment(me));
                        else
                        if (where == "me")
                                obj = present(objid, me);
                        else
                        {
                                env = present(where, environment(me));
                                if (! objectp(env))
                                        return notify_fail("你要看哪里的东西？\n");
                                obj = present(objid, env);
                                if (env->is_character() && env != me)
                                {
                                        if (! objectp(obj) ||
                                            ! obj->query("equipped") &&
                                            env->query_temp("handing") != obj)
                                                return notify_fail("这人好像并没有漏出来你想看的东西啊。\n");
                                        message("vision", me->name() + "盯着你的" + obj->name() +
                                                "看了一会儿，不知道在打什么主意。\n", env);
                                        message("vision", me->name() + "盯着" + env->name() + "的" +
                                                obj->name() + "看了一会儿，不知道在打什么主意。\n",
                                                environment(me), ({ me, env }));
                                }
                        }

                        if (! obj)
                                return notify_fail("那里没有这样东西。\n");
                }

                if( obj || (obj = present(arg, environment(me))) || (obj = present(arg, me)) )
                {
                        if( obj->is_character() && ! obj->is_corpse()) result = look_living(me, obj);
                        else result = look_item(me, obj);
                } else result = look_room_item(me, arg);
        }

        return result;
}

int look_room(object me, object env, int brief)
{
        int i;
        object room;
        mapping exits;
        string str, *dirs;

        if( !env ) {
                tell_object(me, "你的四周灰蒙蒙地一片，什么也没有。\n");
                return 1;
        }

        if( !brief )
        {
                str = sprintf( HIC + "%s" + NOR + "%s\n    %s%s" + NOR,
                        env->short(),
                        wizardp(me)? " - " + file_name(env): "",
                        env->long(),
                        env->query("outdoors") ? NATURE_D->outdoor_room_description() : "");
        } else
        {
                str = sprintf( HIC + "%s" + NOR + "%s\n" + NOR,
                        env->short(),
                        wizardp(me)? " - " + file_name(env): "");
        }

        if (mapp(exits = env->query("exits")) &&
            (! brief || (intp(brief) && brief > 2)))
        {
                dirs = keys(exits);
                for(i=0; i<sizeof(dirs); i++)
                        if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
                                dirs[i] = 0;
                dirs -= ({ 0 });
                if (sizeof(dirs) == 0)
                        str += "    这里没有任何明显的出路。\n";
                else if (sizeof(dirs) == 1)
                        str += "    这里唯一的出口是 " + HIY +
                               dirs[0] + NOR + "。\n";
                else
                        str += sprintf("    这里明显的出口是 " + HIY "%s" + NOR + " 和 " + HIY + "%s" + NOR + "。\n",
                                implode(dirs[0..sizeof(dirs)-2], NOR+"、"+HIY), dirs[sizeof(dirs)-1]);
        }

        if (! me->query_temp("tomud")) // by Lonely
                str += look_all_inventory_of_room(me, env, RETURN_RESULT);
        else
        {
                info(me, env); //By JackyBoy@XAJH 2001/5/6
                str +=CLEAN0+ look_all_inventory_of_room(me, env, RETURN_RESULT);
        }
        tell_object(me, str);

        // 以下部分为显示地图
        if (me->query("env/show_map") && ! me->is_fighting())
        {
                if (mapp(exits = env->query("exits")))
                {
                        dirs = keys(exits);
                        for(i=0; i<sizeof(dirs); i++)
                                if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                                        dirs[i] = 0;
                        dirs -= ({ 0 });
                        if (sizeof(dirs) != 0)
                        {
                        if ((int)me->query("env/show_map") == 2)
                        write(FRELINE(8, 40));
                        else write(ESC+"[r"+TOBOT(50));
                        write(SAVEC);

                        write(SETDISPLAY(7, 0) + DELLINE);
                        write(SETDISPLAY(1, 0) + DELLINE);
                        write(SETDISPLAY(2, 0) + DELLINE);
                        write(SETDISPLAY(3, 0) + DELLINE);
                        write(SETDISPLAY(4, 0) + DELLINE);
                        write(SETDISPLAY(5, 0) + DELLINE);
                        write(SETDISPLAY(6, 0) + DELLINE);

                        write(SETDISPLAY(4, 70) + HIR + filter_color(env->query("short")) + NOR);
                        for (i=0; i<sizeof(dirs); i++)
                        switch(dirs[i])
                        {
                        case "north":
                                write(SETDISPLAY(3, 72) + "│");
                                room = load_object(exits["north"]);
                                write(SETDISPLAY(2, 70) + filter_color(room->query("short")));
                                break;
                        case "up":
                                write(SETDISPLAY(3, 72) + "│");
                                room = load_object(exits["up"]);
                                write(SETDISPLAY(2, 70) + filter_color(room->query("short")));
                                break;
                        case "down":
                                write(SETDISPLAY(5, 72) + "│");
                                room = load_object(exits["down"]);
                                write(SETDISPLAY(6, 70) + filter_color(room->query("short")));
                                break;
                        case "south":
                                write(SETDISPLAY(5, 72) + "│");
                                room = load_object(exits["south"]);
                                write(SETDISPLAY(6, 70) + filter_color(room->query("short")));
                                break;
                        case "east":
                                room = load_object(exits["east"]);
                                write(SETDISPLAY(4, 80) + filter_color(room->query("short")));
                                write(SETDISPLAY(4, 78) + "─");
                                break;
                        case "west":
                                room = load_object(exits["west"]);
                                write(SETDISPLAY(4, 60) + filter_color(room->query("short")));
                                write(SETDISPLAY(4, 68) + "─");
                                break;
                        case "westup":
                                room = load_object(exits["westup"]);
                                write(SETDISPLAY(4, 60) + filter_color(room->query("short")));
                                write(SETDISPLAY(4, 68) + "←");
                                break;
                        case "eastup":
                                room = load_object(exits["eastup"]);
                                write(SETDISPLAY(4, 80) + filter_color(room->query("short")));
                                write(SETDISPLAY(4, 78) + "→");
                                break;
                        case "northup":
                                write(SETDISPLAY(3, 72) + "↑");
                                room = load_object(exits["northup"]);
                                write(SETDISPLAY(2, 70) + filter_color(room->query("short")));
                                break;
                        case "southup":
                                write(SETDISPLAY(5, 72) + "↓");
                                room = load_object(exits["southup"]);
                                write(SETDISPLAY(6, 70) + filter_color(room->query("short")));
                                break;
                         case "southdown":
                                write(SETDISPLAY(5, 72) + " ↑ ");
                                room = load_object(exits["southdown"]);
                                write(SETDISPLAY(6, 70) + filter_color(room->query("short")));
                                break;
                        case "northdown":
                                write(SETDISPLAY(3, 72) + " ↓ ");
                                room = load_object(exits["northdown"]);
                                write(SETDISPLAY(2, 70) + filter_color(room->query("short")));
                                break;
                        case "eastdown":
                                room = load_object(exits["eastdown"]);
                                write(SETDISPLAY(4, 80) + filter_color(room->query("short")));
                                write(SETDISPLAY(4, 78) + "←");
                                break;
                        case "westdown":
                                room = load_object(exits["westdown"]);
                                write(SETDISPLAY(4, 60) + filter_color(room->query("short")));
                                write(SETDISPLAY(4, 68) + "→");
                                break;
                        case "northwest":
                                write(SETDISPLAY(3, 68) + "＼");
                                room = load_object(exits["northwest"]);
                                write(SETDISPLAY(2, 60) + filter_color(room->query("short")));
                                break;
                        case "southwest":
                                write(SETDISPLAY(5, 68) + "／");
                                room = load_object(exits["southwest"]);
                                write(SETDISPLAY(6, 60) + filter_color(room->query("short")));
                                break;
                        case "northeast":
                                write(SETDISPLAY(3, 76) + "／");
                                room = load_object(exits["northeast"]);
                                write(SETDISPLAY(2, 80) + filter_color(room->query("short")));
                                break;
                        case "southeast":
                                write(SETDISPLAY(5, 76) + "＼");
                                room = load_object(exits["southeast"]);
                                write(SETDISPLAY(6, 80) + filter_color(room->query("short")));
                                break;
                        }

                        write(SETDISPLAY(1, 58) + "┏━━━━━━━━━━━━━━┓");
                        write(SETDISPLAY(2, 58) + "┃");
                        write(SETDISPLAY(3, 58) + "┃");
                        write(SETDISPLAY(4, 58) + "┃");
                        write(SETDISPLAY(5, 58) + "┃");
                        write(SETDISPLAY(6, 58) + "┃");
                        write(SETDISPLAY(7, 58) + "┗━━━━━━━━━━━━━━┛");
                        write(SETDISPLAY(2, 88) + "┃");
                        write(SETDISPLAY(3, 88) + "┃");
                        write(SETDISPLAY(4, 88) + "┃");
                        write(SETDISPLAY(5, 88) + "┃");
                        write(SETDISPLAY(6, 88) + "┃");

                        write(REST);
                        }
                write(TOBOT(50));
                }
        }

        return 1;
}

string desc_of_objects(object *obs)
{
        int i;

        string  str;
        mapping count;
        mapping unit;
        string  short_name;
        string  *dk;

        if (obs && sizeof(obs) > 0)
        {
                str = "";
                count   = ([]);
                unit    = ([]);

                for (i = 0; i < sizeof(obs); i++)
                {
                        short_name = obs[i]->short();
                        if (undefinedp(count[short_name]))
                        {
                                count += ([ short_name : 1 ]);
                                unit += ([ short_name : obs[i]->query("unit") ]);
                        }
                        else
                                count[short_name] += 1;
                }

                dk = sort_array(keys(count), 1);
                for (i = 0; i < sizeof(dk); i++)
                {
                        str += "  ";
                        if (count[dk[i]] > 1)
                                str += chinese_number(count[dk[i]]) + unit[dk[i]];
                        str += dk[i] + "\n";
                }
                return str;
        }

        return "";
}

string look_all_inventory_of_room(object me, object env, int ret_str)
{
        object *inv;
        object *obs;
        object ob;
        string  str;

        if (! env || ! me) return "";

        str = "";

        inv = all_inventory(env);
        if (! sizeof(inv)) return str;

        if (me->query_temp("tomud"))
        {
                foreach(ob in inv)
                if (ob != me && me->visible(ob))
                        str += ADD0(ob); //By JackyBoy@XAJH 2001/5/6
        }

        if (! me->query("env/brief") || (intp(me->query("env/brief")) &&
            me->query("env/brief") > 1))
        {
                obs = filter_array(inv, (: $(me) != $1 && userp($1) && $(me)->visible($1) :));
                str += desc_of_objects(obs);

                obs = filter_array(inv, (: $(me) != $1 && ! userp($1) && $1->is_character() &&
                                           $(me)->visible($1) :));
                str += desc_of_objects(obs);

                obs = filter_array(inv, (: ! $1->is_character() :), me);
                str += desc_of_objects(obs);
        }
        if (! ret_str)
                tell_object(me, str);

        return str;
}

int look_item(object me, object obj)
{
        object hob;
        mixed *inv;
        mapping count;
        mapping equiped;
        mapping unit;
        mapping *inset;
        string short_name;

        string str, desc;
        string *dk;
        mapping special_prop, applied_prop;
        string *apply, *apply1, *apply2, *apply3;
        int i, f;
        int n;

        count   = ([]);
        unit    = ([]);
        equiped = ([]);
        special_prop = ([]);
        applied_prop = ([]);
        apply = ({});
        apply1 = ({});
        apply2 = ({});
        apply3 = ({});
                
        str = obj->long();

        // Added by Lonely@nitan3
        if (obj->query("no_identify"))
        {
                str += "-------------------------------------\n";
                str += HIC "此物品未鉴定\n" NOR;
                str += "-------------------------------------\n";
        } else
        if (mapp(obj->query("weapon_prop")) ||
            mapp(obj->query("armor_prop")) ||
            obj->is_enchase_ob())
        {                        
                if (obj->is_item_make() || obj->query("unique"))
                {
                        str += "---------------镶嵌扩展--------------\n";
                        str += HIW "镶嵌槽使用：" + obj->query("enchase/used") + "/" + obj->query("enchase/flute") + "\n" NOR;
                        str += "---------------镶嵌宝物--------------\n";
                        str += HIW "名称           ID                坚固\n" NOR;
                        inset = obj->query("enchase/inset");
                        if (! inset) inset = ({});
                        n = sizeof(inset);
                        if (n > 0)
                                for (i = 0; i < n; i++)
                                        str += sprintf("%-" + (15+color_len(inset[i]["name"])) + "s%-18s%-4d\n",
                                                inset[i]["name"], inset[i]["id"], inset[i]["cur_firm"]);
                } else
                if (! obj->is_enchase_ob())
                {
                        str += "---------------镶嵌扩展--------------\n";
                        str += HIR "镶嵌槽使用：无法扩槽镶嵌\n" NOR;
                }

                if (obj->is_enchase_ob())
                {
                        if (mapp(obj->query("enchase/wspe_data")))
                        apply1 = keys(obj->query("enchase/wspe_data"));
                        if (mapp(obj->query("enchase/aspe_data")))
                        apply2 = keys(obj->query("enchase/aspe_data"));
                }
                else
                if (obj->query("skill_type"))
                        applied_prop = obj->query("weapon_prop");
                else
                if (obj->query("armor_type"))
                        applied_prop = obj->query("armor_prop");
                        
                if (arrayp(apply1) && sizeof(apply1) > 0) {
                        str += "---------------兵器附加--------------\n";
                        for (i = 0; i<sizeof(apply1); i++)
                        {
                                f = obj->query("enchase/wspe_data")[apply1[i]];
                                desc = ENCHASE_D->special_desc(apply1[i]);

                                str += sprintf(HIC "%s%5s%-5d\n" NOR, desc,
                                               f > 0 ? "+" : "-", abs(f));
                        }
                        str += "\n";
                }

                if (arrayp(apply2) && sizeof(apply2) > 0) {
                        str += "---------------防具附加--------------\n";
                        for (i = 0; i<sizeof(apply2); i++)
                        {
                                f = obj->query("enchase/aspe_data")[apply2[i]];
                                desc = ENCHASE_D->special_desc(apply2[i]);

                                str += sprintf(HIC "%s%5s%-5d\n" NOR, desc,
                                               f > 0 ? "+" : "-", abs(f));
                        }
                        str += "\n-------------------------------------\n";
                }

                if (mapp(obj->query("enchase/spe_data")))
                        special_prop += obj->query("enchase/spe_data");
                        
                if (mapp(applied_prop) && sizeof(applied_prop) > 0)
                        apply3 = keys(applied_prop);                        
                if (arrayp(apply3) && sizeof(apply3) > 0)
                {
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                if (undefinedp(special_prop[apply3[i]]))
                                        special_prop[apply3[i]] = applied_prop[apply3[i]];
                                else
                                        special_prop[apply3[i]] += applied_prop[apply3[i]];
                        }
                }
                if (mapp(special_prop) && sizeof(special_prop) > 0)
                        apply = keys(special_prop);
                if (arrayp(apply) && sizeof(apply) > 0) {
                        str += "---------------附加属性--------------\n";
                        for (i = 0; i<sizeof(apply); i++)
                        {
                                f = special_prop[apply[i]];
                                desc = ENCHASE_D->special_desc(apply[i]);

                    		str += sprintf(HIC "%s%5s%-5d\n" NOR, desc,
                                               f > 0 ? "+" : "-", abs(f));
                        }
                }
                str += "\n-------------------------------------\n";
        }
       
        while (mapp(obj->query_temp("daub")))
        {
                if (! obj->query_temp("daub/poison/remain"))
                        // no poison remain now
                        break;

                if (obj->query_temp("daub/poison/id") == me->query("id"))
                {
                        str += HIG "你发现这上面还有你炼制的" +
                               obj->query_temp("daub/poison/name") +
                               HIG "呢。\n" NOR;
                        break;
                }

                if (obj->query_temp("daub/who_id") == me->query("id"))
                {
                        str += HIG "这上面还有你亲手布下的" +
                               obj->query_temp("daub/poison/name") +
                               HIG "呢。\n" NOR;
                        break;
                }

                if (random(4) && random((int)me->query_skill("poison", 1)) < 30)
                        // nothing was worked out
                        break;

                str += HIG "忽然间你发现上面似乎泛着一些奇异荧光";
                if (me->query_skill("poison", 1) >= 120)
                {
                        str += "，可能是" + obj->query_temp("daub/poison/name");
                }

                str += "。\n" NOR;
                break;
        }

        if (obj->query("consistence"))
                str += sprintf("耐久度：" WHT "%d%%\n" NOR, obj->query("consistence"));

        inv = all_inventory(obj);
        if (! sizeof(inv))
        {
                message("vision", str, me);
                return 1;
        }

        if (obj->is_corpse())
        {
                if (objectp(hob = obj->query_temp("handing")))
                {
                        if (hob->query_amount())
                                str += "手中还死死握着一" + hob->query("base_unit") +
                                       hob->name() + "，";
                        else
                                str += "手中还死死握着一" + hob->query("unit") +
                                       hob->name() + "，";
                        inv -= ({ hob });
                        if (! sizeof(inv))
                                str += "没有什么其他遗物了。\n";
                        else
                                str += "里面的遗物有：\n";
                } else
                        str += "里面的遗物有：\n";
        } else
                str += "里面有：\n";

        for (i = 0; i < sizeof(inv); i++)
        {
                short_name = inv[i]->short();
                if (undefinedp(count[short_name]))
                {
                        count += ([ short_name : 1 ]);
                        unit += ([ short_name : inv[i]->query("unit") ]);
                }
                else
                        count[short_name] += 1;

                if (inv[i]->query("equipped"))
                        equiped[short_name] = 1;
        }

        dk = keys(count);
        dk = sort_array(dk, 1);
        for (i = 0; i < sizeof(dk); i++)
        {
            if (equiped[dk[i]])
                str += HIC "  □" NOR;
            else
                str += "    ";

            if (count[dk[i]] > 1)
                str += chinese_number(count[dk[i]]) + unit[dk[i]];
            str += dk[i] + "\n";
        }

        if (strlen(str) > 4096)
                me->start_more(str);
        else
                message("vision", str, me);
        return 1;
}

string look_equiped(object me, object obj, string pro)
{
        mixed *inv;
        string str;
        string subs;
        object hob;
        int i;
        int n;

        inv = all_inventory(obj);
        n = 0;

        str = "";
        subs = "";
        for (i = 0; i < sizeof(inv); i++)
        {
                switch (inv[i]->query("equipped"))
                {
                case "wielded":
                        n++;
                        subs = HIC "  □" NOR + inv[i]->short() + "\n" + subs;
                        break;

                case "worn":
                        n++;
                        subs += HIC "  □" NOR + inv[i]->short() + "\n";
                        break;

                default:
                        break;
                }
        }

        if (n)
                str += pro + "装备着：\n" + subs;

        if (objectp(hob = obj->query_temp("handing")) &&
            (me == obj || obj->query_weight() > 200))
        {
                int mad;

                // dress nothing but handing a cloth !
                mad = (! objectp(obj->query_temp("armor/cloth")) &&
                       hob->query("armor_type") == "cloth");

                str = pro + "手中" + (mad ? "却" : "" ) + "握着一" +
                      (hob->query_amount() ? hob->query("base_unit")
                                           : hob->query("unit")) +
                      hob->name() +
                      (mad ? "，疯了，一定是疯了！\n" : "。\n") + str;
        }

        if (playerp(obj) &&
            ! objectp(obj->query_temp("armor/cloth")))
        {
                str = pro + "身上没有穿衣服啊！\n" + str;
        }

        return str;
}

string description(object obj)
{
        if (playerp(obj))
        {
            int per;
            int age;
            per = obj->query_per();
            age = obj->query("age");
            if (obj->query("special_skill/youth")) age = 14;
            if ((string) obj->query("gender") == "男性" || (string) obj->query("gender") == "无性")
            {
                    if (per >= 30) return "长得宛如玉树临风，风流倜傥，顾盼之间，神采飞扬。真正是人中龙凤！\n";
                    if (per >= 26) return "英俊潇洒，气宇轩昂，风度翩翩，面目俊朗，貌似潘安。\n";
                    if (per >= 22) return "相貌英俊，仪表堂堂。骨格清奇，丰姿非俗。\n";
                    if (per >= 18) return "五官端正。\n";
                    if (per >= 15) return "相貌平平。没什么好看的。\n";
                                   return "长得... 有点对不住别人。\n";
            } else
            {
                    if (per >= 30) return "有倾国倾城之貌，容色丽郁，娇艳绝伦，堪称人间仙子！\n长发如云，肌肤胜雪，风华绝代，不知倾倒了多少英雄豪杰。\n";
                    if (per >= 28) return "清丽绝俗，风姿动人。有沉鱼落雁之容，避月羞花之貌！\n俏脸生春，妙目含情，顾盼神飞，轻轻一笑，不觉让人怦然心动。\n";
                    if (per >= 26) return "肤如凝脂，眉目如画，风情万种，楚楚动人。当真是我见犹怜！\n";
                    if (per >= 24) return "容色秀丽，面带晕红，眼含秋波。举手投足之间，确有一番风韵。\n";
                    if (per >= 21) return "气质高雅，面目姣好，虽算不上绝世佳人，也颇有几份姿色。\n";
                    if (per >= 18) return "相貌平平，还看得过去。\n";
                    if (per >= 15) return "的相貌嘛... 马马虎虎吧。\n";
                                   return "长得和无盐有点相似耶。\n";
            }
        } else
        if (! obj->query("can_speak") && living(obj))
        {
                if (! obj->query_temp("owner"))
                        return "是一只未被驯服的畜生，眼光里满是戒心和敌意。\n";
                else
                        return "是一只被" + obj->query_temp("owner_name") +
                               "驯服的畜生，一副很温驯的样子。\n";
        }

        return "";
}

int look_living(object me, object obj)
{
        int per;
        int age;
        string str="", pro, desc,icon;
        mapping my_fam, fam;
        int me_shen, obj_shen;
        mixed tmp;

        if( (tmp = obj->query("icon")))
        {
                if( intp(tmp) )
                {
                        icon = sprintf("%d",tmp);
                        str=L_ICON(icon);
                }
                else if( stringp(tmp) )
                {
                        icon = tmp;
                        str=L_ICON(icon);
                }
        }
        obj_shen = (int)obj->query("shen");
        per = obj->query_per();
        age = obj->query("age");
        pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));

        if (playerp(obj) && ! (obj->query("born")))
        {
                tell_object(me, pro + "还没有投胎，只有一股元神，什么都看不到耶！\n");
                return 1;
        }

        me_shen = (int)me->query("shen");
        if (me != obj)
        {
                message("vision", me->name() + "正盯著你看，不知道在打什么主意。\n", obj);
                message("vision", me->name() + "盯着" + obj->name() +
                        "看了一会儿，不知道在打什么主意。\n",
                        environment(me), ({ me, obj }));
        }

        str += obj->long();
        if (me != obj && objectp(obj->query_temp("is_riding")))
                str += sprintf("%s正骑在%s上，低头看着你。\n", pro, obj->query_temp("is_riding")->name());

        // if (me != obj && objectp(obj->query_temp("is_changing")))
        if (objectp(obj->query_temp("is_changing")))
        {
                if (obj->query_temp("armor/beast"))
                        str += sprintf("%s全身被铠化的魔幻兽(%s)细胞组织保护着，象全身戴着金色盔甲似的。\n", pro,
                                obj->query_temp("is_changing")->name());
                else
                        str += sprintf("%s的右手臂上留有魔幻兽(%s)依附的痕迹。\n", pro,
                                obj->query_temp("is_changing")->name());
        }

        if (obj->is_character() &&
            obj->query("can_speak"))
        {
                int charlevel;
                charlevel = obj->query("level") ? obj->query("level") : 1;
                str += pro + "是一位第" + chinese_number(charlevel) + "级的人类" + obj->query("gender") + "战士。\n";
                // 是人物角色
                if (age >= 25 && obj->query("special_skill/youth"))
                        str += pro + "看不出年纪的大小，好像只有二十多岁。\n";
                else
                {
                        if (age >= 200)
                                str += pro + "看起来年纪很大了，难以估计。\n";
                        else
                        if (age < 10)
                                str += pro + "看起来年纪尚幼。\n";
                        else
                                str += pro + "看起来有" + chinese_number(age / 10 * 10) +
                                       "多岁。\n";
                }
        }

        desc = description(obj);
        if (desc && desc != "")
                str += pro + desc;

        //check about wife and husband
        if (obj->query("id")== me->query("couple/id"))
        {
                // 夫妻关系
                if ((string)me->query("gender") == "女性")
                        str += sprintf("%s就是你的夫君。\n", pro);
                else
                        str += sprintf("%s就是你的妻子。\n", pro);
        } else
        if (obj->is_brother(me))
        {
                // 兄弟
                if (obj->query("gender") == "女性")
                {
                        if (obj->query("mud_age") > me->query("mud_age"))
                                str += sprintf("%s是你的义姐。\n", pro);
                        else
                                str += sprintf("%s是你的结义妹子。\n", pro);
                } else
                {
                        if (obj->query("mud_age") > me->query("mud_age"))
                                str += sprintf("%s是你的结义兄长。\n", pro);
                        else
                                str += sprintf("%s是你的义弟。\n", pro);
                }
        } else
        if (obj != me && obj->query("league") &&
            obj->query("league/league_name") == me->query("league/league_name"))
        {
                str += sprintf("%s和你均是%s的同盟义士。\n", pro,
                               obj->query("league/league_name"));
        }

        if (obj != me && obj->query("bunch") && stringp(obj->query("bunch/bunch_name")) &&
            obj->query("bunch/bunch_name") == me->query("bunch/bunch_name"))
        {
                str += sprintf("%s和你均是%s的帮友，%s在帮中的职位为%s，", pro,
                               obj->query("bunch/bunch_name"), pro,
                               stringp(obj->query("bunch/title")) ? obj->query("bunch/title") : "帮众");
                if (obj->query("bunch/level") > me->query("bunch/level"))
                        str += "地位比你高。\n";
                else
                if (obj->query("bunch/level") == me->query("bunch/level"))
                        str += "地位和你相当。\n";
                else
                        str += "地位比你低。\n";
        } else
        if (obj != me && obj->query("bunch") && stringp(obj->query("bunch/bunch_name")) &&
            obj->query("bunch/bunch_name") != me->query("bunch/bunch_name"))
        {
                str += sprintf("%s是江湖上%s的%s。\n", pro,
                               obj->query("bunch/bunch_name"),
                               stringp(obj->query("bunch/title")) ? obj->query("bunch/title") : "帮众");
        }

        // If we both has family, check if we have any relations.
        if (obj != me &&
            mapp(fam = obj->query("family")) &&
            mapp(my_fam = me->query("family")) &&
            fam["family_name"] == my_fam["family_name"])
        {

                if (fam["generation"] == my_fam["generation"])
                {

                        if ((string)obj->query("gender") == "男性" ||
                                (string)obj->query("gender") == "无性")
                                str += sprintf( pro + "是你的%s%s。\n",
                                        my_fam["master_id"] == fam["master_id"]? "": "同门",
                                        my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
                        else
                                str += sprintf( pro + "是你的%s%s。\n",
                                        my_fam["master_id"] == fam["master_id"]? "": "同门",
                                        my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
                } else
                if (fam["generation"] < my_fam["generation"])
                {
                        if (my_fam["master_id"] == obj->query("id"))
                                str += pro + "是你的师父。\n";
                        else
                        if (my_fam["generation"] - fam["generation"] > 1)
                                str += pro + "是你的同门长辈。\n";
                        else
                        if (fam["enter_time"] < my_fam["enter_time"])
                                str += pro + "是你的师伯。\n";
                        else
                                str += pro + "是你的师叔。\n";
                } else
                {
                        if (fam["generation"] - my_fam["generation"] > 1)
                                str += pro + "是你的同门晚辈。\n";
                        else
                        if (fam["master_id"] == me->query("id"))
                                str += pro + "是你的弟子。\n";
                        else
                                str += pro + "是你的师侄。\n";
                }
        }

        if (obj->is_chatter())
        {
                message("vision", str, me);
                return 1;
        }

        if (stringp(obj->query_temp("eff_status_msg")))
        {
                str += obj->query_temp("eff_status_msg") + "\n";
        } else
        if (obj->query("max_qi"))
                str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_qi")* 100 / (int)obj->query("max_qi")) + "\n";

        if (obj->query_temp("daub/poison/remain") &&
            (me == obj || random((int)me->query_skill("poison", 1)) > 80))
        {
                str += pro + HIG "身上现在" + (me == obj ? "" : "似乎") +
                       "淬了" + (me == obj ? obj->query_temp("daub/poison/name") : "毒") +
                       NOR "。\n";
        }

        str += look_equiped(me, obj, pro);
        message("vision", str, me);

        if (obj != me && living(obj) &&
            ! me->is_brother(obj) &&
            me->query("couple/id") != obj->query("id") &&
            (((me_shen < 0) && (obj_shen > 0)) ||
             ((me_shen > 0) && (obj_shen < 0))) &&
            (((me_shen - obj_shen) > ((int)obj->query("max_neili") * 20)) ||
             ((obj_shen - me_shen) > ((int)obj->query("max_neili") * 20))))
        {
                tell_object(me, obj->name() + "突然转过头来瞪你一眼。\n");
                /*
                if (obj->query("age") > 15 && me->query("age") > 15)
                   if (! wizardp(obj) && ! wizardp(me))
                        COMBAT_D->auto_fight(obj, me, "berserk");
                */
        }

        return 1;
}

int look_room_item(object me, string arg)
{
        object env;
        mapping item, exits;

        if (! objectp(env = environment(me)))
                return notify_fail("这里只有灰蒙蒙地一片，什么也没有。\n");
        if (mapp(item = env->query("item_desc")) && !undefinedp(item[arg]))
        {
                if (stringp(item[arg]))
                        tell_object(me, item[arg]);
                else
                if(functionp(item[arg]))
                        tell_object(me, (string)(*item[arg])(me));

                return 1;
        }
        if (mapp(exits = env->query("exits")) && ! undefinedp(exits[arg]))
        {
                if (objectp(env = find_object(exits[arg])))
                        look_room(me, env, 0);
                else
                {
                        call_other(exits[arg], "???");
                        look_room(me, find_object(exits[arg]), 0);
                }
                return 1;
        }
        return notify_fail("你要看什么？\n");
}

int help(object me)
{
        write(@HELP
指令格式: look [<物品>|<生物>|<方向>]

这个指令让你查看你所在的环境、某件物品、生物、或是方向。如果
在look指令后面有参数，将先察看身上是否有该物品，如果没有则察
看你所在的环境中是否有该物品或人物。如果你身上的物品和你所在
的环境有ID相同的物品，你可以指明look ??? of me/here 以指明你
想要察看自己身上的物品还是附近环境中的物品。同时，如果使用命
令 look ??? of <id> 可以看他人的装备或是亮出来的物品。

HELP
);
        return 1;
}

