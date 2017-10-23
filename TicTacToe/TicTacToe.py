import re
        
class TicTacToe:
    def __init__(self):
        self.board = [[0 for x in range(3)] for y in range(3)]

    def show_board(self):
        for x in range(3):
            print (self.board[x])

    def edit_board(self, new_board):
        self.board = new_board

    def place_at(self, x, y, value):
        if not self.board[x][y]:
            self.board[x][y] = value
            return 0
        else:
            return 1

    def check_win(self):
        for  x in range(3):
            horizontal = self.board[x][0] * self.board[x][1] * self.board[x][2]
            vertical = self.board[0][x] * self.board[1][x] * self.board[2][x]
            if horizontal == 1 or vertical == 1:
                return 1
            elif horizontal == 8 or vertical == 8:
                return 2
        # Two diagonals to check
        left_down = self.board[0][0] * self.board[1][1] * self.board[2][2]
        right_down = self.board[2][0] * self.board[1][1] * self.board[0][2]
        if right_down == 1 or left_down == 1:
            return 1
        elif left_down == 8 or left_down == 8:
            return 2
        return 0

class GameController:
    def __init__(self):
        self.board = TicTacToe()
        
    def take_turn(self, player):
        while (True):
            var = input("Enter location (Player {}):\n".format(player))
            my_input = re.search("(\d) (\d)", var)
            if my_input:
                a,b = my_input.group(1), my_input.group(2)
                c = player
                print ("Placing {} at ({}, {})".format(c, a, b))
                if self.board.place_at(int(a),int(b),c):
                    print("Spot has already been filled, please retry")
                    continue
                break
            else:
                print ("You have given an invalid input")
        

if __name__=="__main__":

    controller = GameController()
    while (not controller.board.check_win()):
        controller.take_turn(1)
        controller.board.show_board()
        controller.take_turn(2)
        controller.board.show_board()
        
    winner = controller.board.check_win()
    print ("Congratulations to Player {} for winning!".format(winner))
