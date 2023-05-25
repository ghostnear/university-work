#include <QApplication>
#include "ui/all.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Repository repository;
    repository.read_from_file("build/input.txt");
    Service service(repository);
    UI ui(service);
    ui.show();
    return app.exec();
}