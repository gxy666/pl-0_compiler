# Pl/0语言文法的BNF表示：

〈程序P〉→〈分程序FP〉。

〈分程序FP〉→ [<常量说明部分CI>] [<变量说明部分VI>] [<过程说明部分PI>]〈语句S〉

 <常量说明部分CI> → CONST<常量定义CD>{ ,<常量定义CD>}；

 <常量定义CD> → <标识符ID>=<无符号整数UI>

 <无符号整数UI> → <数字NUM>{<数字NUM>}

 <变量说明部分VI> → VAR<标识符ID>{ ,<标识符ID>}；

 <标识符ID> → <字母CHA>{<字母CHA>|<数字NUM>}

 <过程说明部分PI> → <过程首部HEAD><分程序FP>；{<过程说明部分PI>}

 <过程首部HEAD> → procedure<标识符ID>；

 <语句S> → <赋值语句GIVE>|<条件语句CONS>|<当型循环语句WH>|<过程调用语句COND>|<读语句R>|<写语句W>|<复合语句FH>|<空NUL>

 <赋值语句GIVE> → <标识符ID>:=<表达式EQ>

 <复合语句FH> → begin<语句S>{ ；<语句S>} end

 <条件CON> → <表达式EQ><关系运算符REL><表达式EQ>|odd<表达式EQ>

 <表达式EQ> → [+|-]<项X>{<加减运算符AS><项X>}

 <项X> → <因子SON>{<乘除运算符MD><因子SON>}

 <因子SON> → <标识符ID>|<无符号整数UI>|(<表达式EQ>)

 <加减运符AS> → +|-

 <乘除运算符MD> → *|/

 <关系运算符REL> → =|#|<|<=|>|>=

 <条件语句CONS> → if<条件CON>then<语句S>

 <过程调用语句COND> → call<标识符ID>

 <当型循环语句WH> → while<条件CON>do<语句S>

 <读语句R> → read(<标识符ID>{ ，<标识符ID>})

 <写语句W> → write(<标识符ID>{，<标识符ID>})

 <字母CHA> → a|b|c…x|y|z

 <数字NUM> → 0|1|2…7|8|9

###  示例程序：

```
const a=10;
var d,e,f;
procedure p;
  begin
  	d:=a*2;
  	e:=a/3;
  	if d<=e then f:=d+e
  end;
begin
  read(e,f);
  write(e+f,d);
  call p;
  while odd d do e:=-e+1
end
```

 

 

 

 