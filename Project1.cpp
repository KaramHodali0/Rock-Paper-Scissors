#include <iostream>
#include <ctime>

using namespace std;

enum Choice {Stone = 1 , Paper = 2 , Scissors = 3};
enum Winner {Computer , User , NoOne};

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

Choice Get_Computer_Choice_Randomly ()
{
    int Random_Choice = RandomNumber(1 ,3);
    Choice result = Choice (Random_Choice);
    return result;
}

Choice ReadPositiveNumber(string Message)
{
    int Number = 0;  
    do{
    cout << Message << endl;
    cin >> Number;
 } while (Number <= 0);
    return (Choice)Number;
}

Winner Know_The_Winner (Choice User , Choice Computer , int &User_Won_count , int &Computer_Won_Count , int &DrawCOUNT)
{
    switch (User)
    {
    case Stone :

        if (Computer == Choice::Paper)
        {
            Computer_Won_Count++;
             return Winner::Computer;
             
        }

        else if (Computer == Choice::Scissors)
        {
            User_Won_count++;
             return Winner::User;
             
        }

        else if (Computer == Choice::Stone)
        {
            DrawCOUNT++;
             return Winner::NoOne;
             
        }
        break;

        case Paper:

        if (Computer == Choice::Paper)
        {
            DrawCOUNT++;
             return Winner::NoOne;
             
        }

        else if (Computer == Choice::Scissors)
        {
            Computer_Won_Count++;
             return Winner::Computer;
             
        }

        else if (Computer == Choice::Stone)
        {
            User_Won_count++;
             return Winner::User;
             
        }
        break;

        case Scissors:

                if (Computer == Choice::Paper)
        {
             User_Won_count++;
             return Winner::User;
            
        }

        else if (Computer == Choice::Scissors)
        {
            DrawCOUNT++;
             return Winner::NoOne;
             
        }

        else if (Computer == Choice::Stone)
        {
            Computer_Won_Count++;
             return Winner::Computer;
             
        }
        break;
    
        default:

         DrawCOUNT++;
            return Winner::NoOne;

            break;
    }
}

void ScreenColor (Winner A)
{
    if (A == Winner::User)
    {
        //system("color 2F");
        cout << "\033[42m";
    }

    else if (A == Winner::Computer)
    {
        //system("color 4F");
        cout << "\033[41m";
    }

    else if (A == Winner::NoOne)
    {
        //system("color 6F");
        cout << "\033[43m"; 
    }
}

string ChoiceToString(Choice c)
{
    switch (c)
    {
        case Stone:    return "Stone";
        case Paper:    return "Paper";
        case Scissors: return "Scissors";
        default:       return "Unknown";
    }
}

string WinnerToString(Winner w)
{
    switch (w)
    {
        case User:     return "User";
        case Computer: return "Computer";
        case NoOne:    return "No one";
        default:       return "Unknown";
    }
}

void Result_Of_One_Round (int &NumbersOfRound , int &User_Won_count , int &Computer_Won_Count , int &DrawCOUNT )  // Computer Option And User Option and who IS TEH WINNER   
{
     Choice Computer_Option = Get_Computer_Choice_Randomly();
     Choice User_Option = ReadPositiveNumber("\nYour Choice : [1]: Stone ,  [2]: Paper ,  [3]: Scissor ?  \n");
     Winner GetWinner = Know_The_Winner(User_Option , Computer_Option , User_Won_count , Computer_Won_Count , DrawCOUNT);
      ScreenColor(GetWinner);

     cout <<"__________________Round [ "<<  NumbersOfRound  <<" ] "<<"__________________\n\n";

    cout << "Player One Choice : " << ChoiceToString(User_Option) << endl;
    cout << "Computer  Choice : " << ChoiceToString(Computer_Option) << endl;
    cout << "Round Winner     : [ " << WinnerToString(GetWinner) << " ]" << endl;

     cout <<"_______________________________________________________________________________\n";

}

void Result_OF_The_Rounds (int &lengthRound , int &User_Won_count , int &Computer_Won_Count , int &DrawCOUNT)
{
    cout << "How Many Rounds 1 to 10 ?  \n";
    cin >> lengthRound;

    for (int i =  1 ; i <= lengthRound ; i++)
    {
        Result_Of_One_Round(i , User_Won_count , Computer_Won_Count , DrawCOUNT);
    }
}

void FinalResultsOfTheGame (int lengthRound , int User_Won_count , int Computer_Won_Count , int DrawCOUNT )
{
    Winner FinalWinner;
    cout <<"__________________________________________________________________\n";
    cout <<"                           ++ GAME OVER ++                        \n";
    cout <<"__________________________________________________________________\n";
    cout <<"\n________________________[ GAME Result ] __________________________\n";
    cout <<"Game Rounds : "<<lengthRound<<endl;
    cout <<"Player 1 Won Times : " <<User_Won_count<<endl;
    cout << "Computer Won Times : "<< Computer_Won_Count<<endl;
    cout << "Draw Times         : "<<DrawCOUNT<<endl;

    if (User_Won_count > Computer_Won_Count)
    {
        FinalWinner=Winner::User;
    }

    else if (DrawCOUNT > User_Won_count)
    {
        FinalWinner = Winner::NoOne;
    }

    else 
    {
        FinalWinner = Winner::Computer;
    }

    cout <<"Final Winner       : [ "<< FinalWinner << " ] "<<endl;;
    cout <<"__________________________________________________________________\n";



}

void Play_All_Rounds (int &lengthRound , int &User_Won_count , int &Computer_Won_Count , int &DrawCOUNT)
{
    Result_OF_The_Rounds(lengthRound , User_Won_count , Computer_Won_Count , DrawCOUNT);

    FinalResultsOfTheGame(lengthRound , User_Won_count , Computer_Won_Count , DrawCOUNT );
}

void RestartTheGame (int lengthRound , int User_Won_count , int Computer_Won_Count , int DrawCOUNT)
{
    string result ;
    cout <<"Do You Want To Play Again ? Y / N  ?\n";
    cin >> result;
    if (result == "Y" || result == "y")
    {
            Play_All_Rounds(lengthRound , User_Won_count , Computer_Won_Count , DrawCOUNT );
    }

    else
    {
        cout << "Thank You TO PLAY : \n\n\n";
    }
}

int main ()
{
    srand(unsigned)time(NULL));
    int numberOfRounds = 0; // lengthRound
    int User_Won_count = 0 , Computer_Won_Count = 0  , DrawCOUNT = 0;

    Play_All_Rounds(numberOfRounds , User_Won_count , Computer_Won_Count , DrawCOUNT);

    RestartTheGame (numberOfRounds , User_Won_count , Computer_Won_Count , DrawCOUNT);

    return 0;
}