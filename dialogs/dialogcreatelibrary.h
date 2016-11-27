#ifndef DIALOGCREATELIBRARY_H
#define DIALOGCREATELIBRARY_H

#include "layouttoform.h"

class DialogCreateLibrary : public QDialog
{
    Q_OBJECT
public:
    explicit DialogCreateLibrary(QWidget *parent = 0);
    FormPlusData* form;
signals:

public slots:
};

#endif // DIALOGCREATELIBRARY_H
