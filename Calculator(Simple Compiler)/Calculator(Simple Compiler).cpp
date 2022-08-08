#include <iostream>
#include <string>
#include <map>

using namespace std;

// Глобальные переменные, значения берётся из get_token()
double number_value;
string string_value;
//===============================
double term(bool get);
double prim(bool get);
enum class Token_value get_token();
double error(const string& s);

enum class Token_value {
    NAME,       NUMBER,         END,
    PLUS='+',   MINUS='-',      MUL='*',    DIV='/',
    PRINT=';',   ASSIGN='=',     LP='(',     RP=')'
};

map<string, double> table;//?

Token_value curr_tok = Token_value::PRINT; //(current-текущий) последний возвращённый токен ф-ии get_token();

double expr(bool get) { //сложение и вычитание
    //bool get -> решает брать или нет следующую лексему через get_token()
    double left = term(get);//получение/(или нет) новой лексемы
    for (; ; )
    {
        switch (curr_tok) //проверяем текущий токен 
        { 
            case Token_value::PLUS:
                left += term(true);
                break;
            case Token_value::MINUS:
                left -= term(true);
                break;
            default:
                return left;
        }
    }
}

double term(bool get) { //умножение и деление
    double left = prim(get);

    for( ; ; )
    {
        switch (curr_tok)
        {
            case Token_value::MUL:
                left *= prim(true);
                break;
            case Token_value::DIV:
                if (double d = prim(true))//если d != 0
                {
                    left /= d;
                    break;
                }
                cout << "Divide by 0!" << endl;
                return 0; //вывод об ошибке
            default:
                return left;
        }
    }
}

double prim(bool get) { // обработка первичных выражений 
    if (get) get_token();

    switch (curr_tok)
    {
        case Token_value::NUMBER://
        {
            double v = number_value;
            get_token();
            return v;
        }
        case Token_value::NAME: //
        {
            double& v = table[string_value];
            if (get_token() == Token_value::ASSIGN) v = expr(true);
            return v;
        }
        case Token_value::MINUS://унарный минус
            return -prim(true);
        case Token_value::LP://
        {
            double e = expr(true);
            if (curr_tok != Token_value::RP) cout << "')' expected!" << endl;
            get_token();
            return e;
        }
        default:
            cout << "primary expected!" << endl;
    }
}

Token_value get_token() //???
{
    char ch = 0;
    
    //do
    //{
    //    if (!cin.get(ch)) return curr_tok = Token_value::END; // Калькулятор завершает работу , в случае неудачного чтения(get вернёт 0)
    //} while (ch != '\n' && isspace(ch));

    //switch (ch)
    //{
    //    case ';':
    //    case '\n':
    //        return curr_tok = Token_value::PRINT;
    //    default: //NAME , NAME = , или ошибка
    //    {
    //        if (isalpha(ch))
    //        {
    //            string_value = ch;
    //            while (cin.get(ch) && isalnum(ch)) string_value.push_back(ch);
    //            cin.putback(ch);
    //            return curr_tok = Token_value::NAME;
    //        }
    //        cout << "Bad token " << endl;
    //        return  curr_tok = Token_value::PRINT;
    //    }

    //}

    cin >> ch;
    switch (ch)
    {
        case 0:
            return curr_tok = Token_value::END; //Прекращение
        case ';':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return curr_tok = Token_value(ch);
        case '0': 
        case '1': 
        case '2':
        case '3': 
        case '4': 
        case '5':
        case '6': 
        case '7': 
        case '8':
        case '9': 
        case '.':
        {
            std::cin.putback(ch);
            std::cin >> number_value;
            return curr_tok = Token_value::NUMBER;
        }
        default:
        {
            if (isalpha(ch))
            {
                std::cin.putback(ch);
                std::cin >> string_value;
                return curr_tok = Token_value::NAME;
            }
            std::cout << "Bad token " << std::endl;
            return  curr_tok = Token_value::PRINT;
        }
    }
}

int no_of_errors;

double error(const string& s) {

}

int main()
{

}