#include "exer.h"

Exer::Exer(QObject *parent) : QObject(parent)
{
    stack = new QVector<int>();
}

void Exer::deal(QVector<int> *ib)
{
    input_index = 0;
    pc = 0;
    stack->clear();
    stack_top = 0;
    sp = 0;
    input_buff = ib;
    stack_push(0);
    bool first = true;
    while (!stack->isEmpty())
    {
        if(pc<order_list->length()&&pc>=0)
        {
            current_order = pc;
        }
        else {
            emit exererror("指令越界");
            return;
        }
        QString order_type = order_list->at(current_order)->name;
        int order_l = order_list->at(current_order)->l;
        int order_a = order_list->at(current_order)->a;
        if(order_type=="opr")
        {
            switch (order_list->at(current_order)->a) {
            case 0:
            {
                ret(sp);
            }
                break;
            case OPR_ADD:
            {
                int a1_add = stack_pop();
                int a2_add = stack_pop();
                int a3_add = a2_add+a1_add;
                stack_push(a3_add);
                pc++;
                break;
            }
            case OPR_SUB:
            {
                int a1_sub = stack_pop();
                int a2_sub = stack_pop();
                int a3_sub = a2_sub-a1_sub;
                stack_push(a3_sub);
                pc++;
                break;
            }
            case OPR_MUL:
            {
                int a1_mul = stack_pop();
                int a2_mul = stack_pop();
                int a3_mul = a2_mul*a1_mul;
                stack_push(a3_mul);
                pc++;
                break;
            }
            case OPR_DIV:
            {
                int a1_div = stack_pop();
                int a2_div = stack_pop();
                int a3_div = 1;
                if(a1_div!=0)
                {
                    a3_div = a2_div/a1_div;
                }
                else
                {
                    emit exererror("除0异常");
                    error_flag = true;
                }
                stack_push(a3_div);
                pc++;
                break;
            }
            case OPR_FU:
            {
                int a1_fu = stack_pop();
                int a3_fu = -a1_fu;
                stack_push(a3_fu);
                pc++;
                break;
            }
            case OPR_LAR:
            {
                int a1_lar = stack_pop();
                int a2_lar = stack_pop();
                int a3_lar = (a2_lar > a1_lar) ? 1 : 0;
                stack_push(a3_lar);
                pc++;
                break;
            }
            case OPR_LARE:
            {
                int a1_lare = stack_pop();
                int a2_lare = stack_pop();
                int a3_lare = (a2_lare >= a1_lare) ? 1 : 0;
                stack_push(a3_lare);
                pc++;
                break;
            }
            case OPR_LES:
            {
                int a1_les = stack_pop();
                int a2_les = stack_pop();
                int a3_les = (a2_les < a1_les) ? 1 : 0;
                stack_push(a3_les);
                pc++;
                break;
            }
            case OPR_LESE:
            {
                int a1_lese = stack_pop();
                int a2_lese = stack_pop();
                int a3_lese = (a2_lese <= a1_lese) ? 1 : 0;
                stack_push(a3_lese);
                pc++;
                break;
            }
            case OPR_EQU:
            {
                int a1_equ = stack_pop();
                int a2_equ = stack_pop();
                int a3_equ = (a2_equ == a1_equ) ? 1 : 0;
                stack_push(a3_equ);
                pc++;
                break;
            }
            case OPR_NEQU:
            {
                int a1_nequ = stack_pop();
                int a2_nequ = stack_pop();
                int a3_nequ = (a2_nequ != a1_nequ) ? 1 : 0;
                stack_push(a3_nequ);
                pc++;
                break;
            }
            case OPR_READ:
            {
                stack_push(read_data());
                pc++;
                break;
            }
            case OPR_WRI:
            {
                int t = stack_pop();
                emit write_data(t);
                pc++;
                break;
            }
            default:
                break;
            }
        }
        else if (order_type == "jmp") {
            pc = order_a;
        }
        else if (order_type == "lit") {
            stack_push(order_a);
            pc++;
        }
        else if (order_type == "jpc") {
            if(stack_pop()==0)
                pc = order_a;
            else {
                pc++;
            }
        }
        else if (order_type == "int") {
            if(first)
            {
                stack_push(0);
                stack_push(0);
                for(int i = 0;i<order_a-3;++i)
                {
                    stack_push(-32768);
                }
                first = false;
            }
            else
            {
                for(int i = 0;i<order_a-3;++i)
                {
                    stack_push(-32768);
                }
            }
            pc++;
        }
        else if (order_type == "cal") {
            int base = sp;
            for(int i = 0;i<order_l;++i)
            {
                base = stack->at(base+2);
            }
            int temp_new_sp = stack_top;
            stack_push(sp);
            stack_push(current_order+1);
            stack_push(base);
            pc = order_a;
            sp = temp_new_sp;
        }
        else if (order_type == "lod") {
            int base = sp;
            for(int i = 0;i<order_l;++i)
            {
                base = stack->at(base+2);
            }
            stack_push(stack->at(base+order_a));
            pc++;
        }
        else if (order_type == "sto") {
            int base = sp;
            for(int i = 0;i<order_l;++i)
            {
                base = stack->at(base+2);
            }
            stack->replace(base+order_a, stack_pop());
            pc++;
        }
        if(error_flag)
            return;
    }
    emit finish();
}

int Exer::stack_pop()
{
    if(stack_top<=0)
    {
        emit exererror("栈向下溢出");
        error_flag = true;
        return 0;
    }
    else
    {
        stack_top--;
        int tmp = stack->at(stack_top);
        stack->removeLast();
        return tmp;
    }
}

void Exer::stack_push(int a)
{
    if(stack_top>=MAX_STACK_LENTH)
    {
        emit exererror("栈向上溢出");
        error_flag = true;
        return;
    }
    else
    {
        stack_top++;
        stack->append(a);
    }
}

int Exer::read_data()
{
    if(input_index<input_buff->length())
    {
        input_index++;
        return input_buff->at(input_index-1);
    }
    else
    {
        InputDialog *a = new InputDialog();
        connect(a,SIGNAL(submit_num(int)),this,SLOT(add_input(int)));
        a->show();
        a->exec();
        return read_data();
    }
}

void Exer::add_input(int a)
{
    input_buff->append(a);
    emit new_read_data(a);
}

void Exer::set_order(QVector<Order *> *a)
{
    order_list = a;
}

void Exer::ret(int a)
{
    int temp_sp = sp;
    sp = stack->at(sp);
    pc = stack->at(temp_sp+1);
    if(a>=0&&a<stack_top)
    {
        stack->remove(a,stack_top-a);
        stack_top = temp_sp;
    }
    else {
        emit exererror("返回时异常");
        error_flag = true;
    }
}
