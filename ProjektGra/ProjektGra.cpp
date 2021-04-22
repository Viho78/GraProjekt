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
public :
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

class BallMove {
public:
    vector<vector<int>> move(vector<vector<int>> board_c, int position_row, int position_collumn, int first_round) {

        if (first_round == 1) {

            board_c[position_collumn][position_row] = board_c[position_collumn - 1][position_row - 1];

        }

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

    for(int i = 0; i != -1; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("CLS");
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
