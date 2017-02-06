#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stack>
#include <cmath>
#define version_calc_dynamic "1.0.0"
//#define DEBUG_MODE
//#define SHOW_EXPRESSION

using namespace std;

//取值范围限制
enum {
   NONE = 0,//R
   R_S_0,//(-∞,0]
   R_0_M,//[0,+∞)
   R_M1_1,//[-1,1]
   R_N0,//(-∞,0)∪(0,+∞)
   R_0_M_N,//(0,+∞)
   Z_NUM//Z
};

class fun_0
{
  public:
	string name;
	int type;
	int limit;
	string error_msg;
	int priority;//注意，数字越小优先级越小
	void show_msg()
	{
		cout << "Error:" << error_msg << endl;
	}
	int range(double value)
	{
		int lim = limit;
		if (lim == 0)
			return 1;
		else if (lim == R_S_0)
			return value <= 0;
		else if (lim == R_0_M)
			return value >= 0;
		else if (lim == R_M1_1)
			return value >= -1 && value <= 1;
		else if (lim == R_N0)
			return value != 0;
		else if (lim == R_0_M_N)
			return value > 0;
		else if (lim == Z_NUM)
			return (value - (int)value == 0);
	}
};

//一元运算符或函数
class fun_1:public fun_0{
public:
    double (*handle)(double);
};

//二元运算符或函数
class fun_2:public fun_0{
public:
    double (*handle)(double, double);
};

vector<fun_1> func1;
vector<fun_2> func2;


double POW(double a, double b)
{
    return pow(a,b);
}

//创建新函数
void new_function(string name, int type, double (*handle)(double),int priority,int range_limit=NONE,string errmsg="")
{
    fun_1 tmp;
    tmp.name=name;
    tmp.type=type;
    tmp.handle=handle;
    tmp.limit=range_limit;
    tmp.error_msg=errmsg;
    tmp.priority=priority;
    func1.push_back(tmp);
}

void new_function(string name, int type, double (*handle)(double, double),int priority,int range_limit=NONE,string errmsg="")
{
    fun_2 tmp;
    tmp.name=name;
    tmp.type=type;
    tmp.handle=handle;
    tmp.limit=range_limit;
    tmp.error_msg=errmsg;
    tmp.priority=priority;
    func2.push_back(tmp);
}

struct item{
   int type;
   string value;
};

struct var{
    string name;
    double value;
};

vector<var> vars;//储存变量

stack<item> op;
vector<item> ans, list;

bool priority(item op1, item op2)
//用于比较运算符优先级
{
    int find(string), index1=find(op1.value),index2=find(op2.value);
    return ((index1/100==0)?func1[index1%100].priority:func2[index1%100].priority)>((index2/100)==0?func1[index2%100].priority:func2[index2%100].priority);
}

bool isletter(char ch)
{
   return (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||ch=='_';
}

bool isdigit(char ch)
{
   return (ch>='0'&&ch<='9')||ch=='.';
}

bool isoperator(char ch)
{
   return !(isletter(ch)||isdigit(ch));
}

string sub(const string & str, int n, int len)
{
   string tmp;
   for(int i=0;i<len;i++)
     tmp+=str[n+i];
   return tmp;
}

void preprocessor(string& exp)
{
    //在函数名以前的数字和函数名之间添加'*'，比如 4sin30转换为4*sin30，可以添加例外
       for(int i=0;i<exp.size();i++)
       {
          if(isdigit(exp[i])&&(isletter(exp[i+1])||exp[i+1]=='('))
          exp.insert(i+1,"*");
          if(exp[i]==')'&&!isoperator(exp[i+1]))
          exp.insert(i+1,"*");
          if(exp[i]=='('&&(exp[i+1]=='+'||exp[i+1]=='-'))
          exp.insert(i+1,"0");
       }
}

int getstatus(char ch)
{
   if(isletter(ch))  return 0;
   if(isdigit(ch))   return 1;
   return 2;
}

int morpheme_analysis(string& exp)
{
   //检查括号配对情况避免出现段错误
    int am_c=0;
    for(int i = 0;i<exp.size();i++)
    {
       if(exp[i]=='(')
          am_c+=1;
       if(exp[i]==')')
          am_c-=1;
       if(am_c<0)
       {
       //因为)总是在(以后出现那么如果先出现了)那么肯定有语法错误。
          cout << "Error: Primary-expression expected.(at row "<<i+1<<")\n";
          return 0;
       }
    }
    if(am_c>0)//'('的数量多于')'的数量
    {
       cout << "Error: \')\' expected.\n";
       return 0;
    }
    else if(am_c<0)//')'的数量多于'('的数量
    {
       cout << "Error: \'(\' expected.\n";
       return 0;
    }

   //第一步   把数据分离出来储存到list里面
   ans.clear();//清空后缀表达式储存
    [&](){
   int status=0;
   string tmp;
   item temp;
   for(int i=0;i<exp.size();i++)
   {
      if(exp[i]==' '||exp[i]=='\t')
      {
         continue;
      }
      tmp+=exp[i];
      status=getstatus(exp[i]);
      if(status==2)
         status=3;
      if(status!=getstatus(exp[i+1]))
      {
         temp.type=status;
         temp.value=tmp;
         list.push_back(temp);
         tmp="";
         status=0;
      }
   }}();
   #if defined(DEBUG_MODE)
   for(int i=0;i<list.size();i++)
   cout << "type=" << list[i].type << ", value=" << list[i].value << endl;
   #endif
   //强制把type=3的转换为0使运算符和变量同类，为下一步确定变量或函数是否定义提供方便
      for(int i=0;i<list.size();i++)
      {
       //  cout << i;
         if(list[i].type==3)
            list[i].type=0;
      }

    //替换变量，将vars里面有的变量都替换成数据的形式。
    //注意   必须在这里替换，否则将会在后面遇到优先级问题。
    //如果变量没有定义将不会替换而是保留原样在下面的语法分析中会提示未定义变量
   for(int i=0;i<list.size();i++)
   {
      for(int j=0;j<vars.size();j++)
      {
         if(list[i].type==0&&(list[i].value==vars[j].name))
         {
            char tmp[10];
            sprintf(tmp,"%lf",vars[j].value);

             list[i].value=tmp;
            list[i].type=1;
         }
      }
   }

   //第二步  转换为后缀表达式
   [&](){
   int t;
	item tmp;
	string s;
	for (int i = 0; i < list.size(); i++)
	{
		t = list[i].type;
		s = list[i].value;
		if (t == 3 || t==0)//是运算符或变量
		{
			if (s == "(")
				op.push(list[i]);
			else if (s == ")")
			{
				do
				{
					tmp = op.top();
					if(tmp.value!="(")
					   ans.push_back(tmp);
					op.pop();
				}
				while (tmp.value!="("&&op.size()>0);//如果是‘）’，依次从op栈弹出运算符加到数组ans的末尾，直到遇到'（'以后停止搜索，同时第二个条件防止数组溢出发生段错误；
			}
			else
			{
			   if(op.size()&&priority(list[i],op.top()))
			       op.push(list[i]);
			    else
			    {
			       while(op.size()&&!priority(list[i],op.top()))
			       {
			           tmp=op.top();
			           if(tmp.value=="(")//如果没有符合条件的那么就一直比较直到遇到括号后停止，并将其插入到括号后面。
			              break;
			           op.pop();
			           ans.push_back(tmp);
			       }
			       op.push(list[i]);
			    }
			}
		}
		if(t == 1)//数字
		{
			ans.push_back(list[i]);
		}
	}

	//如果扫描结束，栈中还有元素，则依次弹出加到数组ans的
	while(op.size()>0)
	{
	    tmp=op.top();
	    op.pop();
	    ans.push_back(tmp);
	}

    for(int i=0;i<ans.size();i++)
    {
        //因为逗号的利用价值已经没有了，所以就把逗号删掉以免影响以后的运算
        //可以考虑在添加的时候不把逗号添加进ans而是直接丢弃
        if(ans[i].value==",")
           ans.erase(ans.begin()+i);
    }
   #if defined(DEBUG_MODE)
	    cout << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << "type=" << ans[i].type << ", value=" << ans[i].value << endl;
	#endif
   }();
}

void new_(string& exp,int warning_mode=1)//分析字符串并创建新的变量
{
    var tmp;
    int m;
    char store[100];
    if(exp.size()>=100)
    {
       cout << "Error:Name of varible is too long to store.\n";
       return;
    }
    if((m=sscanf(exp.c_str(),"%s%s%lf",store,store,&tmp.value))==3)
    {
       tmp.name=store;
       for(int i=0;i<tmp.name.size();i++) if(isoperator(tmp.name[i])||isdigit(tmp.name[i]))
       {
          cout << "Error:Varible name cannot contain digits or operators.\n";
          return;
       }

       for(int i=0;i<vars.size();i++)
       {
          if(vars[i].name==tmp.name)
          {
             vars[i].value=tmp.value;
             if(warning_mode)
                 cout << "Warning:'"<<tmp.name<<"' has been overwritten to new value.\n";
             return;
          }
       }
       if(tmp.name=="new"||tmp.name=="delete"||tmp.name=="list"||tmp.name=="help"||tmp.name=="exit"||tmp.name=="clear"||tmp.name=="repeat")//可以优化为数组编历
       {
          cout << "Error:\'"<<tmp.name<<"\' cannot be declare as a varible.\n";
          return;
       }
       int find(string); if(find(tmp.name)!=-1)//如果已经被定义为函数名，find函数返回值含义见定义
       {
       cout << "Error:\'"<<tmp.name<<"\' cannot be declare as a varible.\n";
          return;
       }

       vars.push_back(tmp);
       return;
    }
    if(m==1)
       cout << "Error:Invalid format of 'new'.\n";
    if(m==2)
       cout << "Error:Invalid format of 'new'.\n";
}

double COMBINE(double x,double y){
//求组合数
   if(x<y||x<=0||y<0)
       return 0;
    double sum=1.0;
    while(y)
    {
       sum*=(x-y+1);
       sum/=y;
       y--;
    }
    return (int)sum;
}
double ARRANGE(double x,double y){
//求排列数
   if(x<y||x<=0||y<0)
       return 0;
    double sum=1.0;
    while(y)
    {
       sum*=(x-y+1);
       y--;
    }
    return (int)sum;
}
double ADD(double a,double b){return a+b;}
double SUB(double a,double b){return a-b;}
double MUL(double a,double b){return a*b;}
double DIV(double a,double b){return a/b;}
double DIVIDER(double a){};
double REMAIN(double a,double b){return (int)a%(int)b;}
double RANDOM(double low,double up){return (rand()%(int)(up-low))+low;}
double FACTORY(double a){
   int sum=1;
   a=(int)a;
   while(a)
     sum*=a--;
   return sum;
}
double CALCULATOR_MODE(double mode)
{
   string output="Calculator switched to '";
   if(mode==1)//scientific
   {
      cout<<scientific;
      output+="scientific";
   }
   else if(mode==2)
   {
      cout<<fixed;
      output+="fixed";
   }
   else
   {
      cout<<"Warning:Invalid argument for function 'mode'.\n";
      return 0;
   }
   //cout << output << "' mode.\n";
   return 0;
}
double DEG_FUNC(double a){return a*3.141593/180;}
double J_N(double n,double x){return jn(n,x);}
double PRINT_LF(double lf){
   cout << "Displayed by print():"<<lf << endl;
   return lf;
}
double FEIBONACI(double n)
{
    n=(int)n;
    if(n>=100)
    {
        cout << "Warning:The argument of feubonaci is too big to calculate, result set to 0.\n";
        return 0;
    }
    if(n==1||n==2)
        return 1;
    return FEIBONACI(n-2)+FEIBONACI(n-1);
}
double E_FUNC(double n)
{
   int sum=1;
   n=(int)n;
   while(n){
      sum*=10;
      n--;
   }
   return sum;
}

void initial()
{
    string str;
   //设置预设变量
   [&](){
      new_(str="new pi 3.141593");
      new_(str="new g 9.8");
      new_(str="new e 2.718281");
      new_(str="new deg 0.017453");
      new_(str="new SCI 1");
      new_(str="new FIXED 2");
      new_(str="new qe 1.602176487E-19");
   }();
   //设置预设函数 (将运算符视为函数)
   //注意   数字越小优先级越小
   //函数使用方法:
   // new_function(函数名, 函数所需操作数数量, 处理函数名称, 优先级, 取值范围[可选，默认实数集], 超过取值范围显示的错误信息[可选，默认无提示信息]);
   [&](){
      new_function(str="+",2,ADD,13);
      new_function(str="-",2,SUB,13);
      new_function(str="*",2,MUL,14);
      new_function(str="/",2,DIV,14,R_N0,"Divisor cannot be zero.");
      new_function(str="%",2,REMAIN,14);
      new_function(str="^",2,POW,15);
      new_function(str=",",2,DIVIDER,-99999);
      new_function(str="feature",1,CALCULATOR_MODE,99);
      new_function(str="arrange",2,ARRANGE,99);
      new_function(str="combine",2,COMBINE,99);
      new_function(str="to_rad",1,DEG_FUNC,99);
      new_function(str="sin",1,sin,99);
      new_function(str="cos",1,cos,99);
      new_function(str="tan",1,tan,99);
      new_function(str="arcsin",1,asin,99,R_M1_1,"Parameter inverse trigonometric function must be greater than or equal to -1 and less than or equal to 1.");
      new_function(str="arccos",1,acos,99,R_M1_1,"Parameter inverse trigonometric function must be greater than or equal to -1 and less than or equal to 1.");
      new_function(str="arctan",1,atan,99,R_M1_1,"Parameter inverse trigonometric function must be greater than or equal to -1 and less than or equal to 1.");
      new_function(str="sqrt",1,sqrt,99,R_0_M,"There are no square root in negative in real number set.");
      new_function(str="ln",1,log,99,R_0_M_N,"Antilog cannot be smaller than or equal to zero.");
      new_function(str="lg",1,log10,99,R_0_M_N,"Antilog cannot be smaller than or equal to zero.");
      new_function(str="sinh",1,sinh,99);
      new_function(str="cosh",1,cosh,99);
      new_function(str="tanh",1,tanh,99);
      new_function(str="exp",1,exp,99);
      new_function(str="abs",1,fabs,99);
      new_function(str="factorial",1,FACTORY,99);
      new_function(str="!",1,FACTORY,99);
      new_function(str="rand",2,RANDOM,99,R_N0,"Operating number cannot be zero.");
            new_function(str="ceil",1,ceil,99);
      new_function(str="floor",1,floor,99);
      new_function(str="cbrt",1,cbrt,99);
      new_function(str="erf",1,erf,99);
      new_function(str="hypot",2,hypot,99);
            new_function(str="lgamma",1,lgamma,99);
      new_function(str="log_one_p",1,log1p,99);
      new_function(str="logb",1,logb,99);
      new_function(str="nextafter",2,nextafter,99);
      new_function(str="remainder",2,remainder,99);
            new_function(str="rint",1,rint,99);
      new_function(str="j_zero",1,j0,99);
      new_function(str="j_one",1,j1,99);
      new_function(str="copysign",2,copysign,99);
      new_function(str="fdim",1,fdim,99);
            new_function(str="round",1,round,99);
      new_function(str="trunc",1,trunc,99);
      new_function(str="drem",1,drem,99);
      new_function(str="jn",2,J_N,99);
      new_function(str="print",1,PRINT_LF,99);
      new_function(str="fib",1,FEIBONACI,99,R_0_M_N,"A feibonaci number must be a positive number.");
      new_function(str="feibonaci",1,FEIBONACI,99,R_0_M_N,"A feibonaci number must be a positive number.");
      new_function(str="E",1,E_FUNC,99);
   }();
   #if defined(DEBUG_MODE_OPERATOR)
   cout << "一元操作符" << endl;
   for(int i=0;i<func1.size();i++)
   {
      cout<<func1[i].name<<" "<<func1[i].type<<"   ";
   }
   cout << "二元操作符" << endl;
   for(int i=0;i<func2.size();i++)
   {
      cout<<func2[i].name<<" "<<func2[i].type<<"   ";
   }
   #endif
}

void save_var_ans(double val)
{
   char str[100];
   string tmp;
   sprintf(str,"new ans %lf",val);
   new_(tmp=str,0);
}

int find(string name)
{
//return values:
// [0,99] functions #1
// [100,199] functions #2
// [200,299] varibles
// -1 Not found
//
   //find in func1
   for(int i=0;i<func1.size();i++)
      if(func1[i].name==name)
      {
         return i;
      }
   for(int i=0;i<func2.size();i++)
      if(func2[i].name==name)
      {
         return i+100;
      }
   for(int i=0;i<vars.size();i++)
      if(vars[i].name==name)
      {
         return i+200;
      }
   return -1;///Not found
}

double syntax_analysis(){
   int what, index=0;//符号位置
   vector<item> calc;
   vector<int> types,indexs;
   int not_declared_var=0;
   //检查函数或变量是否存在
   for(int i=0;i<ans.size();i++)
   {
      if(ans[i].type==0){
      if((what=find(ans[i].value))==-1)
      {
         cout <<"Error:'"<<ans[i].value<<"' was not declared.\n";
         not_declared_var=1;
      }
      }
      if(!not_declared_var){
         types.push_back(what/100);
         indexs.push_back(what%100);
         //如果not_declared_var为0则说明所有这以前的变量名都是存在的，就可以放心的继续入栈的操作
      }
   }
   if(not_declared_var)
   //如果出现了没有定义的变量
      return 0;


   #if defined(DEBUG_MODE)
	    cout << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << "type=" << ans[i].type << ", value=" << ans[i].value << endl;
	#endif

   stack <double> num;
   double lv, rv, tmp;
   for(int i=0;i<ans.size();i++)
   {
      if(ans[i].type!=0)
      //遇到操作数
      {
         sscanf(ans[i].value.c_str(),"%lf",&tmp);
         num.push(tmp);
      }
      else
      //遇到函数
      {
         //确定是一元还是二元
         if(num.size()!=0)
         {
         rv=num.top();
         num.pop();
         }
         else
         {
            cout <<"Error:Digit required.\n";
            return 0;
          // rv=0;
         }
         if(types[i]==1)
         {
           if(num.size()!=0){
             lv=num.top();
             num.pop();
           }
           else
           {
             lv=0;
           }
         }
         //计算值
           if(types[i]==0)//一元运算符
           {
             if(!func1[indexs[i]].range(rv))
             {
             //确定取值范围是否符合要求
                func1[indexs[i]].show_msg();
                return 0;
             } num.push(func1[indexs[i]].handle(rv));
           }
           else
           {
                if(!func2[indexs[i]].range(rv))
             {
             //确定取值范围是否符合要求
                func2[indexs[i]].show_msg();
                return 0;
             } num.push(func2[indexs[i]].handle(lv,rv));

           }
      }
   }
   if(num.size()==0)
   {
      cout << "Error:Operands are required for the expression.\n";
      return 0;
   }
   if(num.size()>1)
   {
      cout << "Error:Operators expected.\n";
      return 0;
   }
   //cout.unsetf(ios_base::scientific);
   cout << "Result: "<<num.top()<<"\n";
   save_var_ans(num.top());
   return num.top();
}

void help(){
    cout << "Expression calculator(ver "<< version_calc_dynamic <<")\n------------------------------\nWelcome to use this calculator.This calculator can calculate expressions.\nHOW TO USE?\nYou can just type expression such as '1/(2-1)sin(pi/6)',and then calculator will give you the result.\n - Warning: Please input brackets when you use functiond like 'arcsin',or some unexpected errors may cause.(Use 'arcsin(-1)' instead of 'arcsin-1'.)\nABOUT ME:\nE-mail: listencpp@gmail.com\nTIEBA:玉蕈残香\nJuly,2013\nThanks for your use and test again\n";
}

void del(string &exp)
{
    var tmp;
    char store[20];
    if(sscanf(exp.c_str(),"%s %s",store,store)==2)
    {
       if((tmp.name=store)=="-all")
       {
          vars.clear();
          return;
       }
       for(int i=0;i<vars.size();i++)
       {
          if(vars[i].name==tmp.name)
          {
             vars.erase(vars.begin()+i);
             return;
          }
       }
       cout << "Error:\'"<<tmp.name<<"\' was not declared.\n";
    }
    else
       cout << "Error:Varible name expected.\n";
}

void show_varibles()
{
   cout << "Declared varibles\nName\tValue\n";
   if(!vars.size())
   {
      cout << " No varible declared.\n";
   }
   for(int i=0;i<vars.size();i++)
      cout << vars[i].name <<"\t"<< vars[i].value<<endl;
}

int main(int argc,char* argv[]){
	cout.setf(ios_base::scientific,ios_base::floatfield);
//	cout.precision(53);
//	cin.precision(53);
    string exp,save,com;
    char command[20];
    cout << "Expression Calculator\n\n"<<fixed;
    initial();//创建函数，创建变量
    while(1)
    {
       cout << ">";
       getline(cin, exp);
       sscanf(exp.c_str(),"%s",command);
       com=command;
       if(exp=="")
          continue;
       else if(com=="help")
       {
          help();
          continue;
       }
       else if(com=="clear")
       {
          system("clear");
          continue;
       }
       else if(com=="exit")
          return 0;
       else if(com=="new")
       {
          new_(exp);
          continue;
       }
       else if(com=="delete")
       {
          del(exp);
          continue;
       }
       else if(com=="list")
       {
          show_varibles();
          continue;
       }
       else if(com=="repeat")
       {
          if(save=="")
          {
             cout << "Error:No expression saved.\n";
             continue;
          }
          cout << " Expression:"<<save<<endl;
          exp=save;
       }
       save=exp;
       preprocessor(exp);
       #if defined(SHOW_EXPRESSION)
       cout << "Expression: " << exp << endl;
       #endif
       if(morpheme_analysis(exp))
          syntax_analysis();
       list.clear();
    }
}