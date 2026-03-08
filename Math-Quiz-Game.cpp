#include <iostream>
#include <time.h>

using namespace std;

enum enOpType { Add = 1, Sub = 2, Div = 3, Mul = 4, MixOp = 5 };
enum enLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };

struct st_Genral_Info
{
    short Number_1;
    short Number_2;
    short Correct_Answer = 0;
    short User_Answer = 0;
    short Number_Of_Questions = 0;
    enLevel Level;
    enOpType Type;
    short NumberOfRigthAnswer = 0;
    short NumberOfWrongAnswer = 0;
};

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

int ReadNumberFromTo(int From, int To, string Message)
{
    int Number = 0;
    do
    {
        cout << Message << endl;
        cin >> Number;
    } while (Number < From || Number > To);

    return Number;
}

enLevel Enter_Level()
{
    short num;
    cout << "Enter Questions Level ? [1]Easy , [2]Med , [3]Hard , [4]Mix :\n";
    cin >> num;

    return (enLevel)num;
}

void OP_INSIDE_LEVEL(st_Genral_Info &Info)
{
    if (Info.Level == enLevel::Easy)
    {
        Info.Number_1 = RandomNumber(1, 9);
        Info.Number_2 = RandomNumber(1, 9);
    }
    else if (Info.Level == enLevel::Med)
    {
        Info.Number_1 = RandomNumber(1, 50);
        Info.Number_2 = RandomNumber(1, 50);
    }
    else if (Info.Level == enLevel::Hard)
    {
        Info.Number_1 = RandomNumber(1, 100);
        Info.Number_2 = RandomNumber(1, 100);
    }
    else
    {
        Info.Number_1 = RandomNumber(1, 100);
        Info.Number_2 = RandomNumber(1, 100);
    }
}

enOpType EnterType()
{
    short num;
    cout << "Please Enter OP Type ? [1]Add , [2]Sub , [3]Div , [4]Mul , [5]Mix :\n";
    cin >> num;

    return (enOpType)num;
}

char Type(enOpType type)
{
    switch (type)
    {
    case enOpType::Add:
        return '+';

    case enOpType::Sub:
        return '-';

    case enOpType::Div:
        return '/';

    case enOpType::Mul:
        return '*';

    case enOpType::MixOp:
        return Type((enOpType)RandomNumber(1, 4));
    }

    return '+';
}

int ResultOfOneRound(st_Genral_Info &Info, enOpType Ty)
{
    char op = Type(Ty);

    if (op == '+')
        return Info.Number_1 + Info.Number_2;
    else if (op == '-')
        return Info.Number_1 - Info.Number_2;
    else if (op == '/')
        return Info.Number_1 / Info.Number_2;
    else if (op == '*')
        return Info.Number_1 * Info.Number_2;

    return 0;
}

void ScreenColor(short Correct_Answer, short User_Answer)
{
    if (Correct_Answer == User_Answer)
        cout << "\033[42m";
    else
        cout << "\033[41m";
}

void ResetColor()
{
    cout << "\033[0m";
}

void Qu_Before_Game_Start (st_Genral_Info &Info)
{
     Info.Number_Of_Questions = ReadNumberFromTo(1, 15, "How Many Question Do You Want To Answer ?");

    Info.Level = Enter_Level();
    Info.Type = EnterType();

}
void One_Equation(st_Genral_Info &Info)
{
    //Info.Number_Of_Questions = ReadNumberFromTo(1, 15, "How Many Question Do You Want To Answer ?");

    // Info.Level = Enter_Level();
    // Info.Type = EnterType();

    OP_INSIDE_LEVEL(Info);

    Info.Correct_Answer = ResultOfOneRound(Info, Info.Type);

    cout << endl << "\n\n " << Info.Number_1 << endl;
    cout << " " << Info.Number_2 << "   " << Type(Info.Type) << endl;
    cout << "_______________________\n";
    cin >> Info.User_Answer;

    ScreenColor(Info.Correct_Answer, Info.User_Answer);

    if (Info.Correct_Answer != Info.User_Answer)
    {
        cout << " Wrong Answer :-( \n";
        cout << "The Right Answer Is : " << Info.Correct_Answer << endl;
        Info.NumberOfWrongAnswer++;
    }
    else
    {
        cout << " Right Answer :-) \n";
        Info.NumberOfRigthAnswer++;
    }

    ResetColor();
}

void PrintStructInfo(st_Genral_Info Info)
{
    cout << "\n\nNumber Of Questions : " << Info.Number_Of_Questions << endl;
    cout << "Question Level      : " << Info.Level << endl;
    cout << "Operation Type      : " << Info.Type << endl;
    cout << "Right Answers       : " << Info.NumberOfRigthAnswer << endl;
    cout << "Wrong Answers       : " << Info.NumberOfWrongAnswer << endl;
}

void FinalResult (st_Genral_Info Info)
{
    if (Info.NumberOfRigthAnswer > Info.NumberOfWrongAnswer)
    {
    cout <<"\n_____________________________________________\n";
    cout <<"                 Final Result Is Pass :-)                 \n";
    cout <<"_____________________________________________\n";
    }
    else
    {
    cout <<"\n_____________________________________________\n";
    cout <<"                 Final Result Is Fail :-(                 \n";
    cout <<"\n_____________________________________________\n";
    }

    PrintStructInfo(Info);
    cout <<"\n_____________________________________________\n";

}

void How_ManyEquations (st_Genral_Info &Info)
{
    Qu_Before_Game_Start(Info);

    for (int i = 1 ; i <= Info.Number_Of_Questions ; i++)
    {
        cout <<" Questions ["<< i <<" /"<<Info.Number_Of_Questions<<"]  : \n";
        One_Equation(Info);
    }

    FinalResult(Info);


}

void RestartGame(st_Genral_Info Info)
{
    char answer;


    cout <<"Do You want To Play AGAIN ? Y/N   : \n";
    cin >> answer;

    if (answer =='Y' || answer == 'y')
    {
        How_ManyEquations(Info);
    }
    
}

int main()
{
    srand((unsigned)time(NULL));

    st_Genral_Info Info;
    How_ManyEquations(Info);
    RestartGame(Info);

    return 0;
}
