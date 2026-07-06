import copy
from typing import Self
import random

class TicTacToe:
    Board = list[list[str]]  # r,c = row,column
    EMPTY_BOARD: Board = [[" ", " ", " ", " "],
                          [" ", " ", " ", " "],
                          [" ", " ", " ", " "],
                          [" ", " ", " ", " "]]

    def __init__(self, player: str, board: Board = None):
     if board is None:
          board = copy.deepcopy(self.EMPTY_BOARD)
     self.player = player
     self.board = board

    def __repr__(self) -> str:
        header = "    1   2   3   4\n"
        out_str = header
        for r in range(4):
            out_str += f"{r+1} | " + " | ".join(self.board[r]) + " |\n"
            if r < 3:
                out_str += "  " + "-" * 17 + "\n"
        return out_str

    def next_player(self) -> str:
        return "x" if self.player == "o" else "o"

    def mark(self, row: int, col: int) -> Self:
        "Spieler am Zug markiert ein Kästchen und übergibt Brett an den nächsten Spieler"
        b = copy.deepcopy(self.board)
        b[row][col] = self.player
        return TicTacToe(self.next_player(), b)

    def next_boards(self) -> list[Self]:
        "Alle Nachfolger der aktuellen Stellung"
        return [self.mark(r, c) for r in range(4) for c in range(4) if self.board[r][c] == " "]

    def full(self) -> bool:
        return all([self.board[r][c] in ["x", "o"] for r in range(4) for c in range(4)])

    def loose(self) -> bool:
        "True, wenn 2x2 Quadrat gefunden wurde"
        np = self.next_player()
        for r in range(3):       # Zeilen 1 bis 3
            for c in range(3):   # Spalten 1 bis 3
                if (self.board[r][c] == np and
                    self.board[r][c + 1] == np and
                    self.board[r + 1][c] == np and
                    self.board[r + 1][c + 1] == np):
                    return True
        return False

#----------------- Eigene Methoden + Alpha-Beta Minmax-------------------------------

    @staticmethod
    def board_is_empty(board):
      return all(cell == " " for row in board for cell in row)

    @staticmethod
    def get_player_move(board) -> tuple[int, int]:
        while True:
            eingabe = input("Wo soll 'x' gesetzt werden? (Reihe,Spalte): ")
            try:
                row, col = map(int, eingabe.split())
                row -= 1
                col -= 1
                if 0 <= row <= 3 and 0 <= col <= 3 and board[row][col] == " ":
                    return row, col
                else:
                    print("Ungültiger Zug. Feld belegt oder außerhalb des Bereichs.")
            except ValueError:
                print("Ungültige Eingabe. Bitte zwei Zahlen eingeben, z.B. '3 4'.")


    def minimax(self, alpha: int, beta: int) -> int:
        if self.loose():
            # vorheriger Spieler hat verloren
           return 1 if self.next_player() == "x" else -1
        if self.full():
            return 0

        if self.player == "o":  # Computer 'o' - minimieren
            min_eval = float('inf')
            for next_board in self.next_boards():
                eval = next_board.minimax(alpha, beta)
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha: #Abbruch falls beta > alpha --> Weil Gegner diesen Zug nicht zulassen würde
                    break
            return min_eval
        else:  # Spieler 'x' - wir simulieren den besten Zug (maximieren)
            max_eval = -float('inf')  #setzt den wert auf -inf
            for next_board in self.next_boards():
                eval = next_board.minimax(alpha, beta)
                max_eval = max(max_eval, eval)
                alpha = max(alpha, eval)
                if beta <= alpha:
                   break
            return max_eval

    def minimax_depth(self, alpha: int, beta: int, depth: int, max_depth: int) -> int:
    # Beenden bei maximaler Tiefe oder Endzustand
      if self.loose():
        return 1 if self.next_player() == "x" else -1
      if self.full() or depth == max_depth:
        return 0

      if self.player == "o":  # Computer minimiert
        min_eval = float('inf')
        for next_board in self.next_boards():
            eval = next_board.minimax_depth(alpha, beta, depth + 1, max_depth)
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval
      else:  # Spieler maximiert
        max_eval = -float('inf')
        for next_board in self.next_boards():
            eval = next_board.minimax_depth(alpha, beta, depth + 1, max_depth)
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval




    def best_move(self) -> tuple[int, int]:
      # spielt alle Positionnen durch, wenn neuer *best_score* gefunden wird.
      # Dieser wird gegen alle noch verbleibenden Stellungen verglichen,
      # solange bis alle Stellungen durch simuliert wurden.
        best_score = float('inf')
        best_move = None

        for r in range(4):
            for c in range(4):
                if self.board[r][c] == " ":
                    next_board = self.mark(r, c)
                    score = next_board.minimax_depth(-float('inf'), float('inf'),0,8)  #hier auswählen ob minimax mit oder ohne tiefenbeschränkung alpha,beta,init_tiefe,max_tiefe
        #           score = next_board.minimax(-float('inf'), float('inf'))  #hier auswählen ob minimax mit oder ohne tiefenbeschränkung
                    if score < best_score:
                        best_score = score
                        best_move = (r, c)
        return best_move if best_move is not None else (-1, -1)

#----------------- Main ----------------------------------------------

def main():

    #ttt = TicTacToe("x")  # Spieler beginnt
    ttt = TicTacToe("o")   # Computer beginnt
    #ttt = TicTacToe("o",   # Testkonfiguration
    # [[" ", " ", " ", "x"],
    #  [" ", "o", "x", "x"],
    #  [" ", " ", " ", " "],
    #  [" ", "o", " ", " "]])

    while not ttt.full() and not ttt.loose():
        print(ttt)

        if ttt.player == "x":
            row, col = TicTacToe.get_player_move(ttt.board)
            ttt = ttt.mark(row, col)
        else:
            # Computerzug
            if TicTacToe.board_is_empty(ttt.board):
                # Erster Zug: zufällig
                empty = [(r, c) for r in range(4) for c in range(4) if ttt.board[r][c] == " "]
                r, c = random.choice(empty)
                ttt = ttt.mark(r, c)
            else:
                # Spätere Züge: hier mit Minimax
                print(f"Computer (o) am Zug")
                r, c = ttt.best_move()
                print(f"Computer (o) setzt auf: Zeile {r+1}, Spalte {c+1}")
                ttt = ttt.mark(r, c)
    print(ttt)

    if ttt.loose():
        print(f"{ttt.next_player()} hat gewonnen!")
    else:
        print("Unentschieden.")



if __name__ == '__main__':
    main()
