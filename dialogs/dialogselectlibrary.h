#ifndef DIALOGSELECTLIBRARY_H
#define DIALOGSELECTLIBRARY_H

#include <layouttoform.h>
#include "library_classes/settingsbooksclass.h"

class DialogSelectLibrary : public QDialog
{
    Q_OBJECT
public:
    explicit DialogSelectLibrary(SettingsBooksClass* setting, QWidget *parent = 0);
    ~DialogSelectLibrary();
    FormPlusData* form;
protected:
    void setFormText();
signals:

public slots:
    void slotSelectLibrary();
    void slotSelectDir();
};

#endif // DIALOGSELECTLIBRARY_H
