#- expected args: username, password

console::push("Welcome to sign in!");
console::write("Please enter your account name: ");
.i<enterName>;

#- check name
ifn(i<enterName> == i<username>)
BEGINIF{
    console::push("That account doesn't exist!");
    terminate(); 
}ENDIF

#- check pass
console::write("Please enter your account password: ");
.i<enterPass>;
ifn(i<enterPass> == i<password>)
BEGINIF{
    console::push("Incorect password!");
    terminate();
}ENDIF

#- if all checks pass, print
console::write("Welcome to your account, ");
console::push(i<username>);