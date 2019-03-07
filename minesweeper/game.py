# -*- coding: utf-8 -*-
# @Author: Li Qin
# @Date:   2019-03-07 11:00:53
# @Last Modified by:   Li Qin
# @Last Modified time: 2019-03-07 11:29:48
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from minesweeper import Ui_MainWindow

class MinesweeperWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MinesweeperWindow, self).__init__(parent)
        self.setupUi(self)

        self.buttons = [self.bt1,self.bt2,self.bt3,self.bt4,self.bt5,self.bt6,self.bt7,self.bt8,self.bt9,
        self.bt1_1,self.bt2_1,self.bt3_1,self.bt4_1,self.bt5_1,self.bt6_1,self.bt7_1,self.bt8_1,self.bt9_1,
        self.bt1_2,self.bt2_2,self.bt3_2,self.bt4_2,self.bt5_2,self.bt6_2,self.bt7_2,self.bt8_2,self.bt9_2,
        self.bt1_3,self.bt2_3,self.bt3_3,self.bt4_3,self.bt5_3,self.bt6_3,self.bt7_3,self.bt8_3,self.bt9_3,
        self.bt1_4,self.bt2_4,self.bt3_4,self.bt4_4,self.bt5_4,self.bt6_4,self.bt7_4,self.bt8_4,self.bt9_4,
        self.bt1_5,self.bt2_5,self.bt3_5,self.bt4_5,self.bt5_5,self.bt6_5,self.bt7_5,self.bt8_5,self.bt9_5,
        self.bt1_6,self.bt2_6,self.bt3_6,self.bt4_6,self.bt5_6,self.bt6_6,self.bt7_6,self.bt8_6,self.bt9_6,
        self.bt1_7,self.bt2_7,self.bt3_7,self.bt4_7,self.bt5_7,self.bt6_7,self.bt7_7,self.bt8_7,self.bt9_7,
        self.bt1_8,self.bt2_8,self.bt3_8,self.bt4_8,self.bt5_8,self.bt6_8,self.bt7_8,self.bt8_8,self.bt9_8,]
        # 此处控制逻辑事件,如按钮的点击
        self.calc.clicked.connect(self.calculateTax)

    def calculateTax(self):
        try:
            prices = self.price.toPlainText() # 获取文本框输入内容
            tax = self.tax.toPlainText()
            total_price = prices + ((tax / 100) * prices)
            total_price_string = "The total price with tax is: " + str(total_price)
            self.result.setText(total_price_string)
        except Exception as e:
            print(e)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    minesweeper = MinesweeperWindow()
    minesweeper.show()
    sys.exit(app.exec_())
