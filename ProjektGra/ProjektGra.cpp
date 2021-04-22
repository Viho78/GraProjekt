// ProjektGra.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <thread>
#include <chrono>


#define length 20
#define height 10

using namespace std;


class BoardCreate {
public:
        vector<vector<int>> InitBoard(){
            vector<int> row_top_bottom (20, 1);
            vector<int> row_middle(20, 0);

            row_middle[0] = 2;
            row_middle[19] = 2;

            vector<vector<int>> board;


            int num = height;
            board.push_back(row_top_bottom);
            for (int i = 1; i < height - 1; i++) {
                board.push_back(row_middle);
            }
            board.push_back(row_top_bottom);

            board[5][0] = 9;
            board[5][19] = 9;
    
            return board;
        }

        void ShowBoard(vector<vector<int>> board_c) {

            for (int i = 0; i < board_c.size(); i++)
            {
                for (int j = 0; j < board_c[i].size(); j++)
                {
                    cout << board_c[i][j];
                }
                cout << endl;
            }
        }

        vector<vector<int>> start_round(vector<vector<int>> board_c) {

            board_c[5][10] = 5;

            return board_c;
        }
};

class BallMove : public BoardCreate{
    int row_ball_pos;
    int column_ball_pos;

    int row_palet;

    bool direction_LD;
    bool direction_LU;
    bool direction_RD;
    bool direction_RU;
public:
    int search_ball(vector<vector<int>> board_c) {

        for (auto i = 0; i != board_c.size(); i++) {
            for (auto j = 0; j != board_c[i].size(); j++) {
                if (board_c[i][j] == 5){
                    row_ball_pos = i;
                    column_ball_pos = j;
                    return 0;
                }
            }
        }
        return 0;
    }

    int search_plate(vector<vector<int>> board_c) {
        for (auto i = 0; i != board_c.size(); i++) {
            if (board_c[i][0] == 9) {
                row_palet = i;
                return 0;
            }
        }
        return 0;
    }

    int move(vector<vector<int>> &board_c, int first_round, int input) {
        
        search_ball(board_c);

        if (first_round == 1) {
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos + 1][column_ball_pos - 1] = 5;
            direction_LD = 1;
            direction_LU = 0;
            direction_RD = 0;
            direction_RU = 0;

        }

        if (direction_LD == 1 && board_c[row_ball_pos + 1][column_ball_pos - 1] != 1){
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos + 1][column_ball_pos - 1] = 5;
        }
        else if (direction_LD == 1 && board_c[row_ball_pos + 1][column_ball_pos - 1] == 1) {
            direction_LD = 0;
            direction_LU = 1;
            direction_RD = 0;
            direction_RU = 0;
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos - 1][column_ball_pos - 1] = 5;
            return 0;
        }

        if (direction_LU == 1 && board_c[row_ball_pos - 1][column_ball_pos - 1] != 1) {
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos - 1][column_ball_pos - 1] = 5;
        }
        else if (direction_LD == 1 && board_c[row_ball_pos + 1][column_ball_pos + 1] == 1) {
            direction_LD = 1;
            direction_LU = 0;
            direction_RD = 0;
            direction_RU = 0;
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos + 1][column_ball_pos - 1] = 5;
            return 0;
        }



        //to jeszcze nie dziala
        if (direction_RD == 1 && board_c[row_ball_pos + 1][column_ball_pos + 1] != 1) {
            board_c[row_ball_pos][column_ball_pos] = board_c[row_ball_pos + 1][column_ball_pos + 1];
        }

        if (direction_RU == 1 && board_c[row_ball_pos + 1][column_ball_pos - 1] != 1) {
            board_c[row_ball_pos][column_ball_pos] = board_c[row_ball_pos + 1][column_ball_pos - 1];
        }

        search_plate(board_c);


        if (input == 119) {//up
            board_c[row_palet][0] = 2;
            board_c[row_palet - 1][0] = 9;
        }
        else if (input == 115) {//down
            board_c[row_palet][0] = 2;
            board_c[row_palet + 1][0] = 9;
        }
    }


};


class Gameplay : public BoardCreate, public BallMove{
public:
    vector<vector<int>> one_round(vector<vector<int>> board_c) {

        


        return board_c;
    }
};

int main()
{
    BoardCreate BC;
    BallMove BM;
    vector<vector<int>> board_org;

    board_org = BC.InitBoard();

    board_org = BC.start_round(board_org);

    BC.ShowBoard(board_org);

    int input = 0;

    for (int i = 0; i != -1; i++) {
        input = _getch();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("CLS");
        BM.move(board_org, i, input);
        BC.ShowBoard(board_org);
    }
    
    
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
