#import("imports");

#- read acc info
filesys::read("username.txt", s<usernameAcc>);
filesys::read("password.txt", s<passwordAcc>);

#- start checks
console::write("Please enter your account username: ");
.i<username>;
ifn(i<username> == s<usernameAcc>)
BEGINIF{
    #- delete files so program can run again
    call("clearFiles");
    console::push("That account doesn't exist!");
    terminate();
}ENDIF

console::write("Please enter your account password: ");
.i<password>;

ifn(i<password> == s<passwordAcc>)
BEGINIF{
    #- delete files so program can run again
    call("clearFiles");
    console::push("That password is incorrect!");
    terminate();
}ENDIF

#- user is verified
console::push("Welcome to your account!");

#- delete files so program can run again
call("clearFiles");