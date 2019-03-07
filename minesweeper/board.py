# -*- coding: utf-8 -*-
# @Author: Li Qin
# @Date:   2019-03-07 12:11:13
# @Last Modified by:   Li Qin
# @Last Modified time: 2019-03-07 12:25:04
class MineBoard():
    def __init__(self, width=9, height=9):
        self.width = width
        self.height = height
        self.reset()

    def reset(self):
        self.board = [[0]*self.width for _ in range(self.height)]

    def available(self):
        return all([self.boomsArround(i,j)==self.board[i][j] 
        for i in range(self.height) for j in range(self.width)])

    def neighbors(self, row, column):
        directions = [(0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,1),(-1,-1)]
        return [self.board[row+i][column+j] for i, j in directions 
                if 0<=row+i<self.height and 0<=column+j<self.width]

    def boomsArround(self, row, column):
        return len([n for n in self.neighbors(row, column) if n==9])

if __name__ == "__main__":
    board = MineBoard()
    print(board.available())