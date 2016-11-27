#ifndef DIALOGINFORM_H
#define DIALOGINFORM_H

#include "layouttoform.h"

class DialogInForm : public QDialog
{
    Q_OBJECT
public:
    explicit DialogInForm(FormPlusData* formP, QWidget *parent = 0);
    ~DialogInForm();
    FormPlusData* form;
protected:
    void keyPressEvent(QKeyEvent *);
signals:

public slots:
};

#endif // DIALOGINFORM_H
