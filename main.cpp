#include <QApplication>
#include "widgets/librarywindow.h"
#include "styleclass.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  QFontComboBox* fcb = new QFontComboBox;
  //  fcb->show();
    QTranslator translator;
    translator.load("://resource/myhomelibrary_"+QLocale::system().name());
    a.installTranslator(&translator);
    QApplication::setStyle(new StyleClass);
    QFont font("Times New Roman",8);
    int x = GetSystemMetrics(SM_CXSCREEN);
    if  (x>3000){
        font.setPointSize(13);
    }else if (x>1800){
        font.setPointSize(11);
    }else if(x>1600){
        font.setPointSize(10);
    }else if (x>1400){
        font.setPointSize(9);
    }
    QApplication::setFont(font);
    LibraryWindow lw;
    lw.showMaximized();
   // qDebug()<<"show";
    return a.exec();
}
