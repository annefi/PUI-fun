#! /usr/bin/env python
# -*- coding: utf-8 -*-
#
import sys
from PyQt4.QtGui import *

def msg():
    # Show a message box
    result = QMessageBox.question(w, 'Message', "Do you like Python?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
 
    if result == QMessageBox.Yes:
        print 'Yes.'
    else:
        print 'No.'        


# Create an PyQT4 application object.
a = QApplication(sys.argv)      
# The QWidget widget is the base class of all user interface objects in PyQt4.
w = QWidget()
 
# Set window size.
w.resize(740, 480)
 
# Set window title  
w.setWindowTitle("Hello World!")
 
# Add a button
btn = QPushButton('Quit', w)
btn.setToolTip('Click to quit!')
btn.clicked.connect(w.close)
btn.resize(btn.sizeHint())
btn.move(100, 80)
btn2 = QPushButton('MSG', w)
btn2.setToolTip('Click to open MSG!')
btn2.clicked.connect(msg)
btn2.resize(btn.sizeHint())
btn2.move(100, 180)
# Create textbox
textbox = QLineEdit(w)
textbox.move(20, 20)
textbox.resize(280,40)
# Create combobox
combo = QComboBox(w)
combo.addItem("Python")
combo.addItem("Perl")
combo.addItem("Java")
combo.addItem("C++")
combo.move(20,20) 
# Create calendar
cal = QCalendarWidget(w)
cal.setGridVisible(True)
cal.move(320, 240)
cal.resize(320,240)   
# Show window
w.show() 

sys.exit(a.exec_())
