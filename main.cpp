#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QLabel label("Qt + C++ 세팅 완료!");
    label.show();
    
    return app.exec();
}