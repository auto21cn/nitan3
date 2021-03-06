inherit ROOM;

void create()
{ 
        set("short", "无极帮门前");
        set("long", @LONG
这里是无极帮北京分部的大门前面，无极帮的这个大厅只是发布任务的所在，
即使如此，这座建筑也造的风格迥然，让人一眼看上去，就觉得气势不凡。
LONG );
        set("outdoors", "beijing");
        set("exits", ([
                "west" :  "/d/beijing/yongdingdao",
                "east" : "/d/beijing/wjb_bjwdt",
        ])); 
        set("objects", ([   
             "/d/beijing/npc/wjb-guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "east") 
        {
           if (! me->query_temp("good_wjb2") && me->query("bunch/bunch_name") != "无极帮")
               return notify_fail("守卫一把拦住你，朗声喝道：我无极帮怎由闲杂人等随便进出。\n"); 
           else
           {
              me->delete_temp("good_wjb2");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

