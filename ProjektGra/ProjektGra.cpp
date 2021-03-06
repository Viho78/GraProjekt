// ProjektGra.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <ctime> 



#define length 20
#define height 10

using namespace std;


class BoardCreate {
public:
        ofstream log;

        BoardCreate() {
        log.open("logs.txt");
        time_t result = time(NULL);
        char str[26]; 
        ctime_s(str, sizeof str, &result);
        log << str << "Init of the title." << endl;
        }

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

            time_t result = time(NULL);
            char str[26];
            ctime_s(str, sizeof str, &result);
            log << str << "Board created." << endl;
    
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

            time_t result = time(NULL);
            char str[26];
            ctime_s(str, sizeof str, &result);
            log << str << "Board showed." << endl;
        }

        vector<vector<int>> start_round(vector<vector<int>> board_c) {

            board_c[5][10] = 5;

            time_t result = time(NULL);
            char str[26];
            ctime_s(str, sizeof str, &result);
            log << str << "Game began." << endl;

            return board_c;
        }
};

class BallMove : public BoardCreate{
    int row_ball_pos;
    int column_ball_pos;

    int row_palet;

    int row_palet_ai;

    bool direction_LD;
    bool direction_LU;
    bool direction_RD;
    bool direction_RU;

public:
    BallMove(vector<vector<int>>& board_c) { //initialisation of ball movement
        search_ball(board_c);
        board_c[row_ball_pos][column_ball_pos] = 0;
        board_c[row_ball_pos + 1][column_ball_pos - 1] = 5;
        direction_LD = 1;
        direction_LU = 0;
        direction_RD = 0;
        direction_RU = 0;

        time_t result = time(NULL);
        char str[26];
        ctime_s(str, sizeof str, &result);
        log << str << "Ball moved to " << row_ball_pos + 1 << " " << column_ball_pos - 1 << endl;
    }

    bool search_ball(vector<vector<int>> board_c) {

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

    bool search_plate(vector<vector<int>> board_c) {
        for (auto i = 0; i != board_c.size(); i++) {
            if (board_c[i][0] == 9) {
                row_palet = i;
                return 0;
            }
        }
        return 0;
    }

    bool search_palet_ai(vector<vector<int>> board_c) {
        for (auto i = 0; i != board_c.size(); i++) {
            if (board_c[i][19] == 9) {
                row_palet_ai = i;
                return 0;
            }
        }
        return 0;
    }

    int move(vector<vector<int>> &board_c, int &rest_palet) {
        
        search_ball(board_c);

        if (direction_LD == 1 && board_c[row_ball_pos - 1][column_ball_pos + 1] == 9 && rest_palet <= 0) {//palete collision
            direction_LD = 0;
            direction_LU = 0;
            direction_RD = 1;
            direction_RU = 0;
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos + 1][column_ball_pos + 1] = 5;
            rest_palet == 2;
            return 0;
        }
        else if (direction_LD == 1 && board_c[row_ball_pos + 1][column_ball_pos - 1] != 1){//regular move
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos + 1][column_ball_pos - 1] = 5;
            return 0;
        }
        else if (direction_LD == 1 && board_c[row_ball_pos + 1][column_ball_pos - 1] == 1) {//top/bot wall collision
            direction_LD = 0;
            direction_LU = 1;
            direction_RD = 0;
            direction_RU = 0;
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos - 1][column_ball_pos - 1] = 5;
            return 0;
        }

        if (direction_LU == 1 && board_c[row_ball_pos - 1][column_ball_pos - 1] == 9 && rest_palet <= 0) {
            direction_LD = 0;
            direction_LU = 0;
            direction_RD = 0;
            direction_RU = 1;
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos - 1][column_ball_pos + 1] = 5;
            rest_palet == 2;
            return 0;
        }
        else if (direction_LU == 1 && board_c[row_ball_pos - 1][column_ball_pos - 1] != 1) {
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos - 1][column_ball_pos - 1] = 5;
            return 0;
        }
        else if (direction_LU == 1 && board_c[row_ball_pos - 1][column_ball_pos - 1] == 1) {
            direction_LD = 1;
            direction_LU = 0;
            direction_RD = 0;
            direction_RU = 0;
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos + 1][column_ball_pos - 1] = 5;

            return 0;
        }

        if (direction_RD == 1 && board_c[row_ball_pos + 1][column_ball_pos + 1] == 9 && rest_palet <= 0) {
            direction_LD = 1;
            direction_LU = 0;
            direction_RD = 0;
            direction_RU = 0;
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos + 1][column_ball_pos - 1] = 5;
            rest_palet == 2;
            return 0;
        }
        else if (direction_RD == 1 && board_c[row_ball_pos + 1][column_ball_pos + 1] != 1) {
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos + 1][column_ball_pos + 1] = 5;
            return 0;
        }
        else if (direction_RD == 1 && board_c[row_ball_pos + 1][column_ball_pos + 1] == 1) {
            direction_LD = 0;
            direction_LU = 0;
            direction_RD = 0;
            direction_RU = 1;
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos - 1][column_ball_pos + 1] = 5;
            return 0;
        }

        if (direction_RU == 1 && board_c[row_ball_pos + 1][column_ball_pos - 1] == 9 && rest_palet <= 0) {
            direction_LD = 0;
            direction_LU = 1;
            direction_RD = 0;
            direction_RU = 0;
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos - 1][column_ball_pos - 1] = 5;
            rest_palet == 2;
            return 0;
        }
        if (direction_RU == 1 && board_c[row_ball_pos - 1][column_ball_pos + 1] != 1) {
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos - 1][column_ball_pos + 1] = 5;
            return 0;
        }
        else if (direction_RU == 1 && board_c[row_ball_pos - 1][column_ball_pos + 1] == 1) {
            direction_LD = 0;
            direction_LU = 0;
            direction_RD = 1;
            direction_RU = 0;
            board_c[row_ball_pos][column_ball_pos] = 0;
            board_c[row_ball_pos + 1][column_ball_pos + 1] = 5;
            return 0;
        }
    }

    void palet_move1(vector<vector<int>>& board_c, int input) {

        search_plate(board_c);
        //search_palet_ai(board_c);

        if (input == 119 && row_palet != 1) {//up
            board_c[row_palet][0] = 2;
            board_c[row_palet - 1][0] = 9;
        }
        else if (input == 115 && row_palet != 8) {//down
            board_c[row_palet][0] = 2;
            board_c[row_palet + 1][0] = 9;
        }

        //if (row_ball_pos <= row_palet_ai && row_palet_ai != 1) {//up ai
            //board_c[row_palet_ai][19] = 2;
            //board_c[row_palet_ai - 1][19] = 9;
        //}
        //else if (row_palet_ai != 8) {//down ai
            //board_c[row_palet_ai][19] = 2;
            //board_c[row_palet_ai + 1][19] = 9;
        //}
    }

    void palet_move2(vector<vector<int>>& board_c, int input) {

        //search_plate(board_c);
        search_palet_ai(board_c);

        if (input == 119 && row_palet_ai != 1) {//up
            board_c[row_palet_ai][19] = 2;
            board_c[row_palet_ai - 1][19] = 9;
        }
        else if (input == 115 && row_palet_ai != 8) {//down
            board_c[row_palet_ai][19] = 2;
            board_c[row_palet_ai + 1][19] = 9;
        }
    }
    void win_cond(vector<vector<int>>& board_c) {

        for (auto i = 0; i != board_c.size(); i++) {
            if (board_c[i][0] == 5) {
                system("CLS");
                cout << "wygral gracz 2";
                time_t result = time(NULL);
                char str[26];
                ctime_s(str, sizeof str, &result);
                log << str << "Player 2 won." << endl;
                log << str << "Closing." << endl;
                exit(0);
            }
        }
        for (auto i = 0; i != board_c.size(); i++) {
            if (board_c[i][19] == 5) {
                system("CLS");
                cout << "wygral gracz 1";
                time_t result = time(NULL);
                char str[26];
                ctime_s(str, sizeof str, &result);
                log << str << "Player 1 won." << endl;
                log << str << "Closing." << endl;
                exit(0);
            }
        }
    }


};

int main()
{
    vector<vector<int>> board_org;
    BoardCreate BC;

    

    board_org = BC.InitBoard();

    board_org = BC.start_round(board_org);

    BallMove BM(board_org);

    BC.ShowBoard(board_org);

    int input1 = 0;
    int input2 = 0;

    int rest_pal = 0;

    while(true) {
        input1 = _getch();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        system("CLS");
        BM.move(board_org, rest_pal);
        BM.win_cond(board_org);
        BM.palet_move1(board_org, input1);
        BC.ShowBoard(board_org);
        

        input2 = _getch();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        system("CLS");
        BM.move(board_org, rest_pal);
        BM.win_cond(board_org);
        BM.palet_move2(board_org, input2);
        BC.ShowBoard(board_org);

        rest_pal--;
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
