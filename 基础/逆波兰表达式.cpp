#include <bits/stdc++.h>

using namespace std;
const int N = 1010;
const int mod = 1e9+7;
typedef long long llt;

char data[N];
int suffix_exp[N];
char op_stack[N];
int op_top, suffix_top;
map<char, int>op_mp = {{'+',-1}, {'-', -2}, {'*', -3}, {'/', -4}};

bool isop(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int priority(char ch)
{
    if(ch == '+' || ch == '-') return 1;
    if(ch == '*' || ch == '/') return 2;
    // 当ch=='(', 返回0
    return 0;
}

void toSuffixExp(char data[])
{
    op_top = suffix_top = 0;
    int len = strlen(data);
    for(int i = 0; i < len; ++i){
        // 如果是操作符
        if(isop(data[i])){
            while(op_top != 0 && priority(data[i]) <= priority(op_stack[op_top-1])){
                suffix_exp[suffix_top++] = op_mp[op_stack[op_top-1]];
                op_top--;
            }
            op_stack[op_top++] = data[i];
        }
        // 如果是数字
        if(isdigit(data[i])){
            int val = 0;
            while(isdigit(data[i])){
                val = val*10+data[i]-'0';
                i++;
            }
            i--;
            suffix_exp[suffix_top++] = val;
        }
        // 如果是'('
        if(data[i] == '('){
            op_stack[op_top++] = data[i];
        }
        // 如果是')'
        if(data[i] == ')'){
            while(op_stack[op_top-1] != '('){
                suffix_exp[suffix_top++] = op_mp[op_stack[op_top-1]];
                op_top--;
            }
            op_top--;
        }
        if(data[i] == ' ')
            continue;
    }
    while(op_top != 0){
        suffix_exp[suffix_top++] = op_mp[op_stack[op_top-1]];
        op_top--;
    }
}

double calc_stack[N];
double calc()
{
    int calc_top = 0;
    for(int i = 0; i < suffix_top; ++i){
        if(suffix_exp[i] >= 0) calc_stack[calc_top++] = suffix_exp[i];
        else{
            double v1,v2,v;
            v2 = calc_stack[calc_top-1];
            calc_top--;
            v1 = calc_stack[calc_top-1];
            calc_top--;
            if(suffix_exp[i] == -1) v = v1+v2;
            if(suffix_exp[i] == -2) v = v1-v2;
            if(suffix_exp[i] == -3) v = v1*v2;
            if(suffix_exp[i] == -4) v = v1/v2;
            calc_stack[calc_top++] = v;
        }
    }
    return calc_stack[calc_top-1];
}

int main()
{
    while(gets(data) && strcmp(data, "0")){
        toSuffixExp(data);
        printf("%.2f\n", calc());
//        for(int i = 0; i < suffix_top; ++i)
//            cout << suffix_exp[i] << " ";
    }
    return 0;
}