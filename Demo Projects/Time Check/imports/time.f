console::command("cls");
if(s<sys::curTime> == i<timeC>)
BEGINIF{
    console::push("It is time!");
}ENDIF
ifn(s<sys::curTime> == i<timeC>)
BEGINIF{
    console::push("It is not time!");
}ENDIF