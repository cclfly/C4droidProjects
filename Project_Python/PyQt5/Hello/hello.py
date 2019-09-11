import sys
from PyQt5.QtWidgets import *

app : QApplication = QApplication(sys.argv)
btn : QPushButton = QPushButton("Hello, World!")
btn.clicked.connect(app.quit)
btn.show()
app.exec()