#pragma once

#include <qt/QtWidgets/QLineEdit>
#include <qt/QtWidgets/QPushButton>
#include <qt/QtWidgets/QVBoxLayout>
#include <qt/QtWidgets/QHBoxLayout>
#include <qt/QtWidgets/QListWidget>
#include <qt/QtWidgets/QMainWindow>
#include "service/all.hpp"

class UI : public QWidget
{
private:
    Service& service;
    QListWidget* view;
    QLineEdit* filterInput;

public:
    UI(Service& service) : service(service)
    {
        QHBoxLayout* layout = new QHBoxLayout(this);
    
        view = new QListWidget();
        for(auto data : service.get_all_data())
            view->addItem(QString(data.to_string().c_str()));

        layout->addWidget(view);

        QVBoxLayout* layout2 = new QVBoxLayout();
        filterInput = new QLineEdit();
        QPushButton* button = new QPushButton("Filter");
        layout2->addWidget(filterInput);
        layout2->addWidget(button);

        connect(button, &QPushButton::clicked, this, &UI::filter_data);

        layout->addLayout(layout2);

        QVBoxLayout* layout3 = new QVBoxLayout();

        

        QLineEdit* descriptionEdit = new QLineEdit();
        QLineEdit* startTimeEdit = new QLineEdit();
        QPushButton* timeButton = new QPushButton("Show intervals and total time");

        layout3->addWidget(descriptionEdit);
        layout3->addWidget(startTimeEdit);
        layout3->addWidget(timeButton);

        layout->addLayout(layout3);
        

        resize(960, 540);
    }

    void filter_data()
    {
        view->clear();
        for(auto data : service.get_all_data_filtered(std::stoi(filterInput->text().toStdString())))
            view->addItem(QString(data.to_string().c_str()));
    }
};