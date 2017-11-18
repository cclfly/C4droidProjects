/********************************************************************************
** Form generated from reading UI file 'GLWidget_Form.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLWIDGET_FORM_H
#define UI_GLWIDGET_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *layout;
    QPushButton *exit_button;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        layout = new QVBoxLayout(Widget);
        layout->setSpacing(6);
        layout->setContentsMargins(11, 11, 11, 11);
        layout->setObjectName(QStringLiteral("layout"));
        exit_button = new QPushButton(Widget);
        exit_button->setObjectName(QStringLiteral("exit_button"));
        exit_button->setGeometry(QRect(0, 0, 200, 200));

        layout->addWidget(exit_button);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        exit_button->setText(QApplication::translate("Widget", "Exit", 0));
        Q_UNUSED(Widget);
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLWIDGET_FORM_H
