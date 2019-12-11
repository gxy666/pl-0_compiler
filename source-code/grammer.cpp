    #include "grammer.h"

Grammer::Grammer(QObject *parent) : QObject(parent)
{

}

void Grammer::advance()
{
    if(current_word_index<max)
    {
        current_word_index++;
    }
    else if(current_word_index==max)
    {
        end = 1;
    }
}

int Grammer::getword()
{
    if(end)
        return NUL;
    else
    {
        if(current_word_index==max)
        {
            end = 1;
            return NUL;
        }
        else
            return display->at(current_word_index)->type;
    }
}

void Grammer::gen_order(QString name, int l, int a)
{
    Order *an_order = new Order(name);
    an_order->a = a;
    an_order->l = l;
    code_list->append(an_order);
}

QVector<Identify*> *Grammer::get_id_list()
{
    return root_table->get_display_id_list();
}

QVector<Order*> *Grammer::get_code_list()
{
    return code_list;
}

Treenode* Grammer::P(QVector<Word*> *d)
{
    end = 0;
    error = false;
    //id_list = new QVector<Identify*>();
    code_list = new QVector<Order*>();
    root_table = new Id_Table();
    current_table = root_table;
    current_level = 0;//
    //id_list_address = 1;//
    display = d;
    max = display->length();
    current_word_index = 0;
    root = new Treenode("P");
    current_node = root;
    FP();
    advance();
    if(!end)
        emit grammererror("程序尾部多余");
    return root;
}

void Grammer::FP()
{
    if(error)
        return;
    Treenode *fp_node = new Treenode("FP",current_node);
    current_node = fp_node;
    if(getword()==CON)
    {
        CI();
        if(error)
            return;
        current_node = fp_node;
    }
    if(getword()==VA)
    {
        VI();
        if(error)
            return;
        current_node = fp_node;
    }
    if(current_level == 0)
        gen_order("jmp",0,0);
    if(getword()==PRO)
    {
        PI();
        if(error)
            return;
        current_node = fp_node;
    }
    gen_order("int",0,current_table->get_id_num()+3);
    if(current_table->par!=nullptr)
    {
        QString name = current_node->parent->children->at(0)->children->at(1)->name;
        int order_index = code_list->length();
        current_table->par->set_pro_entrance(name,order_index-1);
    }
    if(current_level == 0)
        code_list->at(0)->a = code_list->length()-1;
    S();
    if(error)
        return;
    current_node = fp_node;
    gen_order("opr",0,0);
}

void Grammer::CI()
{
    if(error)
        return;
    advance();
    Treenode *CI_node = new Treenode("CI",current_node);
    current_node = CI_node;
    Treenode *const_node = new Treenode("CONST",current_node);
cd:
    if(getword()==CHA)
    {
        CD();
        if(error)
            return;
        if(getword()==DOUHAO)
        {
            advance();
            Treenode *douhao = new Treenode(",",current_node);
            goto cd;
        }
        else if (getword()==FENHAO)
        {
            Treenode *fenhao = new Treenode(";",current_node);
            advance();
        }
        else
        {
            emit grammererror("常量说明部分出错");
            error = true;
        }
    }
    else
    {
        emit grammererror("常量说明部分出错");
        error = true;
    }
}

void Grammer::CD()
{
    if(error)
        return;
    Treenode *CD_node = new Treenode("CD",current_node);

    Identify *const_id = new Identify();//
    const_id->type = CONST_ID;//

    current_node = CD_node;
    if(getword()==CHA)
    {
        Treenode *ID = new Treenode(display->at(current_word_index)->value,current_node);
        const_id->name = display->at(current_word_index)->value;//
        advance();
        if(getword()==EQUAL)
        {
            Treenode *denghao = new Treenode("=",current_node);
            advance();
            if(getword()==INT)
            {
                Treenode *ui = new Treenode(display->at(current_word_index)->value,current_node);
                const_id->value = display->at(current_word_index)->value.toInt();//
                const_id->level = current_level;//
                if(!current_table->append_id(const_id))//
                {
                    emit grammererror("变量名重复");
                    error = true;
                }
                advance();
            }
            else
            {
                emit grammererror("常量定义部分出错");
                error = true;
            }
        }
        else
        {
            emit grammererror("常量定义部分出错");
            error = true;
        }
    }
    else
    {
        error = true;
        emit grammererror("常量定义部分出错");
    }
}

void Grammer::VI()
{
    if(error)
        return;
    advance();
    Treenode *VI_node = new Treenode("VI",current_node);
    current_node = VI_node;
    Treenode *var_node = new Treenode("VAR",current_node);
id:
    if(getword()==CHA)
    {
        Identify *var_id = new Identify();
        var_id->address = current_table->addr;
        var_id->name = display->at(current_word_index)->value;
        var_id->level = current_level;
        var_id->type = VAR_ID;
        if(!current_table->append_id(var_id))//
        {
            emit grammererror("变量名重复");
            error = true;
        }
        current_table->addr++;
        Treenode *ID = new Treenode(display->at(current_word_index)->value,current_node);
        advance();
        if(getword()==DOUHAO)
        {
            advance();
            Treenode *douhao = new Treenode(",",current_node);
            goto id;
        }
        else if (getword()==FENHAO)
        {
            advance();
            Treenode *fenhao = new Treenode(";",current_node);
            return;
        }
        else
        {
            emit grammererror("变量说明部分出错");
            error = true;
        }
    }
    else
    {
        emit grammererror("变量说明部分出错");
        error = true;
    }
}

void Grammer::S()
{
    if(error)
        return;
    Treenode *s_node = new Treenode("S",current_node);
    current_node = s_node;
    switch (getword()) {
    case CALL:
    {
        COND();
        if(error)
            return;
        current_node = s_node;
        break;
    }
    case CHA:
    {
        GIVE();
        if(error)
            return;
        current_node = s_node;
        break;
    }
    case IF:
    {
        CONS();
        if(error)
            return;
        current_node = s_node;
        break;
    }
    case WHILE:
    {
        WH();
        if(error)
            return;
        current_node = s_node;
        break;
    }
    case WRITE:
    {
        W();
        if(error)
            return;
        current_node = s_node;
        break;
    }
    case READ:
    {
        R();
        if(error)
            return;
        current_node = s_node;
        break;
    }
    case BEGIN:
    {
        FH();
        if(error)
            return;
        current_node = s_node;
        break;
    }
    case NUL:
    {
        break;
    }
    default:
        break;
    }
}

void Grammer::GIVE()
{
    if(error)
        return;
    Treenode *give_node = new Treenode("GIVE",current_node);
    current_node = give_node;
    Treenode *ID_node = new Treenode(display->at(current_word_index)->value,current_node);
    int a = 0;
    int l = 0;
    if(!current_table->get_var_id(&l,&a,display->at(current_word_index)->value,current_level))
    {
        emit grammererror("赋值语句中第一个标识符不存在");
        error = true;
    }
    advance();
    if(getword()==FUZHI)
    {
        Treenode *fuzhi_node = new Treenode(":=",current_node);
        advance();
    }
    else
    {
        emit grammererror("赋值语句部分出错");
        error = true;
    }
    EQ();
    if(error)
        return;
    gen_order("sto",l,a);
}

void Grammer::FH()
{
    if(error)
        return;
    advance();
    Treenode *fh_node = new Treenode("FH",current_node);
    current_node = fh_node;
    Treenode *begin_node = new Treenode("begin",current_node);
s:
    S();
    if(error)
        return;
    current_node = fh_node;
    if(getword()==FENHAO)
    {
        advance();
        goto s;
    }
    else if(getword()==END)
    {
        Treenode *end_node = new Treenode("end",current_node);
        advance();
    }
    else
    {
        emit grammererror("复合语句部分出错");
        error = true;
    }
}

void Grammer::HEAD()
{
    if(error)
        return;
    Treenode *head_node = new Treenode("HEAD",current_node);
    Id_Table *temp_table;
    current_node = head_node;
    if(getword()==PRO)
    {
        if(current_level>3)//
        {
            emit grammererror("层数过多");//
            error = true;
        }
        else
        {
            current_level++;//
            temp_table = new Id_Table(current_table);//
            current_table->append_table(temp_table);//
            Treenode *pro_node = new Treenode("procedure",current_node);
            advance();
        }
    }
    else {
        emit grammererror("过程首部部分出错");
        error = true;
    }
    if(getword()==CHA)
    {
        Treenode *id_node = new Treenode(display->at(current_word_index)->value,current_node);
        Identify *pro_id = new Identify();//
        pro_id->name = display->at(current_word_index)->value;//
        pro_id->level = current_level-1;//
        pro_id->value = -1;
        pro_id->type = PRO_ID;//
        if(!current_table->append_id(pro_id))//
        {
            emit grammererror("变量名重复");
            error = true;
        }
        if(temp_table!=nullptr)//
        {
            current_table = temp_table;//
            current_table->table_name = display->at(current_word_index)->value;//
        }
        advance();
    }
    else {
        emit grammererror("过程首部部分出错");
        error = true;
    }
    if(getword()==FENHAO)
    {
        Treenode *fenhao_node = new Treenode(";",current_node);
        advance();
    }
    else
    {
        emit grammererror("过程首部部分出错");
        error = true;
    }
}

void Grammer::PI()
{
    if(error)
        return;
    Treenode *pi_node = new Treenode("PI",current_node);
    current_node = pi_node;
    HEAD();
    if(error)
        return;
    current_node = pi_node;
    FP();
    if(error)
        return;
    if(getword()==FENHAO)
    {
         Treenode *fenhao_node = new Treenode(";",current_node);
         if(current_level>0)//
         {
             current_level--;//
             current_table = current_table->par;//
             //id_list_address = current_table->id_list->length()+1;
         }
         else
         {
             emit grammererror("层数出错");//
             error = true;
         }
         advance();
    }
    else
    {
        emit grammererror("过程说明部分出错");
        error = true;
    }
    if(getword()==PRO)
        PI();
    if(error)
        return;
}

void Grammer::CON_G()
{
    if(error)
        return;
    Treenode *con_node = new Treenode("CON",current_node);
    current_node = con_node;
    if(getword()==ODD)
    {
        Treenode *odd_node = new Treenode("ODD",current_node);
        advance();
        EQ();
        if(error)
            return;
        current_node = con_node;
    }
    else
    {
        EQ();
        if(error)
            return;
        current_node = con_node;
        REL();
        if(error)
            return;
        current_node = con_node;
        EQ();
        if(error)
            return;
        current_node = con_node;
        if(current_node->children->length()==3&&current_node->children->at(1)->children->length()==1)
        {
            QString rel_op = current_node->children->at(1)->children->at(0)->name;
            if(rel_op=="#")
            {
                gen_order("opr",0,OPR_NEQU);
            }
            else if (rel_op=="=")
            {
                gen_order("opr",0,OPR_EQU);
            }
            else if (rel_op==">")
            {
                gen_order("opr",0,OPR_LAR);
            }
            else if (rel_op==">=") {
                gen_order("opr",0,OPR_LARE);
            }
            else if (rel_op=="<") {
                gen_order("opr",0,OPR_LES);
            }
            else if (rel_op=="<=") {
                gen_order("opr",0,OPR_LESE);
            }
            else{
                emit grammererror("条件语句出错");
                error = true;
            }

        }
    }
}

void Grammer::X()
{
    if(error)
        return;
    Treenode *x_node = new Treenode("X",current_node);
    current_node = x_node;
    int mul_div_flag = 0;
son:
    SON();
    if(error)
        return;
    switch (mul_div_flag) {
    case 0:
        break;
    case 1:
        mul_div_flag = 0;
        gen_order("opr",0,OPR_MUL);
        break;
    case 2:
        mul_div_flag = 0;
        gen_order("opr",0,OPR_DIV);
        break;
    default:
        break;
    }
    current_node = x_node;
    if(getword() == STAR||getword() == DIVIDE)
    {
        MD();
        if(error)
            return;
        if(current_node->name=="*")
        {
            mul_div_flag = 1;
        }
        else if(current_node->name=="/")
        {
            mul_div_flag = 2;
        }
        current_node = x_node;
        goto son;
    }
}

void Grammer::AS()
{
    if(error)
        return;
    if(getword()==PLUS)
    {
        Treenode *plus_node = new Treenode("+",current_node);
        current_node = plus_node;//
        advance();
    }
    else if(getword()==SUB)
    {
        Treenode *sub_node = new Treenode("-",current_node);
        current_node = sub_node;//
        advance();
    }
    else
    {
        emit grammererror("加减号出错");
        error = true;
    }
}

void Grammer::MD()
{
    if(error)
        return;
    if(getword()==STAR)
    {
        Treenode *star_node = new Treenode("*",current_node);
        current_node = star_node;
        advance();
    }
    else if(getword()==DIVIDE)
    {
        Treenode *div_node = new Treenode("/",current_node);
        current_node = div_node;
        advance();
    }
    else
    {
        emit grammererror("乘除号出错");
        error = true;
    }
}

void Grammer::SON()
{
    if(error)
        return;
    Treenode *son_node = new Treenode("SON",current_node);
    current_node = son_node;
    if(getword()==CHA)
    {
        Treenode *id_node = new Treenode(display->at(current_word_index)->value,current_node);
        int l = 0;
        int a = 0;
        if(current_table->get_var_id(&l,&a,display->at(current_word_index)->value,current_level))
        {
            gen_order("lod",l,a);
        }
        else if(current_table->get_con_id(&a,display->at(current_word_index)->value,current_level))
        {
            gen_order("lit",0,a);
        }
        else
        {
            emit grammererror("符号在符号表中不存在");
            error = true;
        }
        advance();
    }
    else if(getword()==INT)
    {
        Treenode *ui_node = new Treenode(display->at(current_word_index)->value,current_node);
        gen_order("lit",0,display->at(current_word_index)->value.toInt());
        advance();
    }
    else if(getword()==ZUOKUOH)
    {
        Treenode *zkh_node = new Treenode("(",current_node);
        advance();
        EQ();
        if(error)
            return;
        current_node = son_node;
        if(getword()==YOUKUOH)
        {
            Treenode *ykh_node = new Treenode(")",current_node);
            advance();
        }
        else
        {
            emit grammererror("因子出错");
            error = true;
        }
    }
    else
    {
        emit grammererror("因子出错");
        error = true;
    }
}

void Grammer::CONS()
{
    if(error)
        return;
    Treenode *cons_node = new Treenode("CONS",current_node);
    current_node = cons_node;
    advance();
    bool oddflag = false;
    Treenode *if_node = new Treenode("if",current_node);
    if(getword()==ODD)
        oddflag = true;
    CON_G();
    if(error)
        return;
    current_node = cons_node;
    if(getword()==THEN)
    {
        Treenode *then_node = new Treenode("then",current_node);
        advance();
    }
    else
    {
        emit grammererror("条件语句出错");
        error = true;
    }
    if(oddflag)
        gen_order("jpc",0,0);
    else {
        gen_order("jpc",0,0);
    }
    int jp_index = code_list->length()-1;
    S();
    if(error)
        return;
    code_list->at(jp_index)->a = code_list->length();
}

void Grammer::COND()
{
    if(error)
        return;
    Treenode *cond_node = new Treenode("COND",current_node);
    current_node = cond_node;
    advance();
    Treenode *call_node = new Treenode("call",current_node);
    if(getword()==CHA)
    {
        Treenode *id_node = new Treenode(display->at(current_word_index)->value,current_node);
        int a = 0;int l = 0;
        if(current_table->get_pro_entrance(&l,&a,display->at(current_word_index)->value,current_level))
            if(a!=-1)
                gen_order("cal",l,a);
            else {
                emit grammererror("过程调用标识符违法");
                error = true;
            }
        else {
            emit grammererror("过程调用标识符不存在");
            error = true;
        }

        advance();
    }
    else
    {
        emit grammererror("过程调用语句出错");
        error = true;
    }
}

void Grammer::EQ()
{
    if(error)
        return;
    Treenode *eq_node = new Treenode("EQ",current_node);
    current_node = eq_node;
    bool flag = false;//
    if(getword() == PLUS||getword() ==SUB)
    {
        AS();
        if(error)
            return;
        if(current_node->name=="-")
            flag = true;//
        current_node = eq_node;
    }
    int add_sub_flag = 0;
eq:
    X();
    if(error)
        return;
    current_node = eq_node;
    switch (add_sub_flag) {
    case 0:
        break;
    case 1:
        add_sub_flag = 0;
        gen_order("opr",0,OPR_SUB);
        break;
    case 2:
        add_sub_flag = 0;
        gen_order("opr",0,OPR_ADD);
        break;
    default:
        break;
    }
    if(flag)
    {
        flag = false;
        gen_order("opr",0,OPR_FU);
    }
    if(getword() == PLUS||getword() ==SUB)
    {
        AS();
        if(error)
            return;
        if(current_node->name=="-")
        {
            add_sub_flag = 1;
        }
        else if (current_node->name=="+") {
            add_sub_flag = 2;
        }
        current_node = eq_node;
        goto eq;
    }
}

void Grammer::REL()
{
    if(error)
        return;
    Treenode *rel_node = new Treenode("REL",current_node);
    current_node = rel_node;
    switch (getword()) {
    case EQUAL:
    {
        Treenode *eq_node = new Treenode("=",current_node);
        advance();
        break;
    }
    case JING:
    {
        Treenode *j_node = new Treenode("#",current_node);
        advance();
        break;
    }
    case LESS:
    {
        Treenode *less_node = new Treenode("<",current_node);
        advance();
        break;
    }
    case LARGER:
    {
        Treenode *larger_node = new Treenode(">",current_node);
        advance();
        break;
    }
    case LARGEREQUAL:
    {
        Treenode *largereq_node = new Treenode(">",current_node);
        advance();
        break;
    }
    case LESSEQUAL:
    {
        Treenode *lesseq_node = new Treenode("<=",current_node);
        advance();
        break;
    }
    default:
        emit grammererror("关系表达式出错");
        error = true;
        break;
    }
}

void Grammer::R()
{
    if(error)
        return;
    Treenode *r_node = new Treenode("R",current_node);
    current_node = r_node;
    advance();
    Treenode *read_node = new Treenode("read",current_node);
    if(getword()==ZUOKUOH)
    {
        Treenode *zkh_node = new Treenode("(",current_node);
        advance();
r:
        if(getword()==CHA)
        {
            Treenode *id_node = new Treenode(display->at(current_word_index)->value,current_node);
            gen_order("opr",0,OPR_READ);
            int a = 0;int l = 0;
            if(current_table->get_var_id(&l,&a,display->at(current_word_index)->value,current_level))
            {
                gen_order("sto",l,a);
            }
            else {
                emit grammererror("读语句出错");
                error = true;
            }
            advance();
            if(getword()==DOUHAO)
            {
                Treenode *dh_node = new Treenode(",",current_node);
                advance();
                goto r;
            }
            else if (getword()==YOUKUOH) {
                Treenode *ykh_node = new Treenode(")",current_node);
                advance();
            }
            else
            {
                emit grammererror("读语句出错");
                error = true;
            }
        }
        else
        {
            emit grammererror("读语句出错");
            error = true;
        }
    }
    else
    {
        emit grammererror("读语句出错");
        error = true;
    }
}

void Grammer::W()
{
    if(error)
        return;
    Treenode *w_node = new Treenode("W",current_node);
    current_node = w_node;
    advance();
    Treenode *write_node = new Treenode("write",current_node);
    if(getword()==ZUOKUOH)
    {
        Treenode *zkh_node = new Treenode("(",current_node);
        advance();
w:
        EQ();
        if(error)
            return;
        current_node = w_node;
        gen_order("opr",0,OPR_WRI);
        if(getword()==DOUHAO)
        {
            Treenode *dh_node = new Treenode(",",current_node);
            advance();
            goto w;
        }
        else if (display->at(current_word_index)->type==YOUKUOH) {
            Treenode *ykh_node = new Treenode(")",current_node);
            advance();
        }
        else
        {
            emit grammererror("写语句出错");
            error = true;
        }
    }
    else
    {
        error = true;
        emit grammererror("写语句出错");
    }
}

void Grammer::WH()
{
    if(error)
        return;
    Treenode *while_node = new Treenode("WH",current_node);
    current_node = while_node;
    advance();
    Treenode *wh_node = new Treenode("while",current_node);
    int ret_add = code_list->length();
    CON_G();
    if(error)
        return;
    current_node = while_node;
    int jmp_add = code_list->length();
    gen_order("jpc",0,0);
    if(getword()==DO)
    {
        Treenode *do_node = new Treenode("do",current_node);
        advance();
        S();
        if(error)
            return;
        gen_order("jmp",0,ret_add);
        code_list->at(jmp_add)->a = code_list->length();
    }
    else
    {
        emit grammererror("循环语句出错");
        error = true;
    }
}

