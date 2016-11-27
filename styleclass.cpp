#include "styleclass.h"

StyleClass::StyleClass():QProxyStyle()
{

    colorMain=QColor(234,252,250);
    colorMainBoard=QColor(186,187,235);
    colorSecond=QColor(224,242,240);
    colorFocus=QColor(117,172,166);
    colorFocusBoard=QColor(0,120,215);
    colorContrast=QColor(240,255,250);
    colorSunken=QColor(137,202,200);

    colorMenu=QColor(157,212,210);
    colorMenuSecond=QColor(177,217,215);
    colorMenuBoard=QColor(207,232,230);
    /*
     *    QColor colorMain(205,206,241);
    QColor colorMainBoard(186,187,235);
    QColor colorSecond(186,187,235);
    QColor colorFocus(215,216,245);
    QColor colorFocusBoard(0,120,215);
    QColor colorContrast(225,240,195);
    QColor colorSunken(172,173,232);
 */
}
void StyleClass::drawControl(ControlElement element, const QStyleOption *opt, QPainter *p, const QWidget *w)const
{
    switch(element)
    {
    case CE_HeaderEmptyArea:
        p->fillRect( opt->rect, QBrush(colorMain));
    break;
    case CE_HeaderSection://голова таблицы
    {
            //Активная секция
        if( opt->state & State_Sunken || opt->state & State_On )
        {
            QLinearGradient gradient(0, 0, 0, opt->rect.height());
            gradient.setSpread(QGradient::PadSpread);
            gradient.setColorAt(0, colorMain);
            gradient.setColorAt(1, colorSecond);
            p->fillRect(opt->rect, QBrush( gradient));
        }
        else if (opt->state & State_Horizontal)//неактивная секция
        {
            QLinearGradient gradient(0, 0, 0, opt->rect.height());
            gradient.setSpread(QGradient::PadSpread);
            gradient.setColorAt(0, colorMain);
            gradient.setColorAt(1, colorSecond);
            //Создаем градиент для фона
            p->fillRect(opt->rect, QBrush( gradient));
            QPen pen;
            pen.setStyle(Qt::SolidLine);
            pen.setColor(colorMain);
            p->setPen(pen);
            //рисуем границы секций
            p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);

        }else{
            QLinearGradient gradient(0, 0, opt->rect.width(),0);
            gradient.setSpread(QGradient::PadSpread);
            gradient.setColorAt(0, colorMain);
            gradient.setColorAt(1, colorSecond);
            //Создаем градиент для фона
            p->fillRect(opt->rect, QBrush( gradient));

            QPen pen;
            pen.setStyle(Qt::SolidLine);
            pen.setColor(colorMain);
            p->setPen(pen);
            //рисуем границы секций
            p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);
        }
    }
        break;
    case CE_ComboBoxLabel:{
        QPen pen;
        if (opt->state & State_HasFocus && w->objectName()=="ComboBoxCell"){
            QProxyStyle::drawControl(element, opt, p, w);
            pen.setStyle(Qt::SolidLine);
            pen.setColor(colorFocusBoard);
            p->setPen(pen);
            p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);
            pen.setColor(QColor(0,0,0));
            p->setPen(pen);
        }else{
            QProxyStyle::drawControl(element, opt, p, w);
        }
    }
    break;
    case CE_PushButton:{//кнопка
        const QStyleOptionButton * option = qstyleoption_cast<const QStyleOptionButton  *>(opt);
        QPen pen;
        if (w->objectName()!="ButtonCell"){
            QProxyStyle::drawControl(element, opt, p, w);
            return;
        }
        if( opt->state & State_Sunken){
            QLinearGradient gradient(0, 0, 0, opt->rect.height());
            gradient.setSpread(QGradient::PadSpread);
            gradient.setColorAt(0, colorSecond);
            gradient.setColorAt(1, colorSunken);
            QBrush brush(gradient);
            p->fillRect(opt->rect, brush);
            pen.setStyle(Qt::SolidLine);
            pen.setColor(colorFocusBoard);
            p->setPen(pen);
            p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);
            //нужно узнать размеры виджета, размеры текста, и нарисовать текст по середине

        }else if ((opt->state & State_MouseOver) || (opt->state & State_HasFocus)){
            QLinearGradient gradient(0, 0, 0, opt->rect.height());
            gradient.setSpread(QGradient::PadSpread);
            gradient.setColorAt(0, colorMain);
            gradient.setColorAt(1, colorSecond);

            QBrush brush(gradient);
            p->fillRect(opt->rect, brush);
            pen.setStyle(Qt::SolidLine);
            pen.setColor(colorFocusBoard);
            p->setPen(pen);
            p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);

        }else{
            QLinearGradient gradient(0, 0, 0, opt->rect.height());
            gradient.setSpread(QGradient::PadSpread);
            gradient.setColorAt(0, colorMain);
            gradient.setColorAt(1, colorSecond);
            QBrush brush(gradient);
            p->fillRect(opt->rect, brush);
            pen.setStyle(Qt::SolidLine);
            pen.setColor(colorMainBoard);
            p->setPen(pen);
            p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);
        }
        QFontMetrics fontm (w->font());
        int count = fontm.width(option->text);

        QRect textRect = option->rect;
        int dx = (option->rect.width()-count)/2;
        textRect.setX( textRect.x() + dx );
        textRect.setY( textRect.y() + 5 );
        if(!option->text.isEmpty()){
            //Рисуем текст.
            pen.setColor(QColor( 0,0,0));
            p->setPen(pen);
            p->drawText(textRect,option->text);
        }
    }
    break;
    case CE_CheckBox:{
        QPen pen;
        if (opt->state & State_HasFocus && w->objectName()=="CheckBoxCell"){
            pen.setStyle(Qt::SolidLine);
            pen.setColor(colorFocusBoard);
            p->setPen(pen);
            QCheckBox* chb = (QCheckBox*)w;
            QFontMetrics fntm = w->fontMetrics();
            int count = fntm.width(chb->text())+50;
            p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.x()+count,opt->rect.height()-1);
            pen.setColor(QColor(0,0,0));
            p->setPen(pen);
            QProxyStyle::drawControl(element, opt, p, w);
        }else{
            QProxyStyle::drawControl(element, opt, p, w);
        }
    }
    break;
    case CE_MenuBarEmptyArea:{//меню
//        p->fillRect(opt->rect, colorMain);
        p->fillRect(opt->rect, colorMenu);
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(colorMain);
        p->setPen(pen);
        //рисуем границы секций
        p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);

    }
        break;
    case CE_MenuBarItem:{
        const QStyleOptionMenuItem * option = qstyleoption_cast<const QStyleOptionMenuItem  *>(opt);
             QPen pen;
        if( opt->state & State_Sunken || opt->state & State_On){
            p->fillRect(opt->rect, colorSecond);
            pen.setStyle(Qt::SolidLine);
            pen.setColor(colorMainBoard);
            p->setPen(pen);
            p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);
        }else{
            QLinearGradient gradient(0, 0, 0, opt->rect.height());
            gradient.setSpread(QGradient::PadSpread);
          //  gradient.setColorAt(0, colorMain);
            gradient.setColorAt(0, colorMenu);
          //  gradient.setColorAt(1, colorSecond);
              gradient.setColorAt(1, colorMenuSecond);
                    //рисуем фон
            p->fillRect(opt->rect, QBrush( gradient));
            QPen pen;
            pen.setStyle(Qt::SolidLine);
            pen.setColor(colorMenuBoard);
            p->setPen(pen);
                    //рисуем границы секций
            p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);
        }
        QRect textRect = option->rect;
        textRect.setX( textRect.x() + 5 );
        textRect.setY( textRect.y() + 5 );
        if( !option->text.isEmpty() )
        {
                    //Рисуем текст.
            pen.setColor(QColor( 0,0,0));
            p->setPen(pen);
            if (option->text.indexOf("&")==0){
                p->drawText(textRect,option->text.mid(1));
            }else{
                p->drawText(textRect,option->text);
            }
        }
    }
    break;
    case CE_ToolBar:{
        p->fillRect(opt->rect, colorMain);
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(colorMainBoard);
        p->setPen(pen);
        //рисуем границы секций
        p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);
    }
    break;

    default:
        QProxyStyle::drawControl(element, opt, p, w);

    break;
    }
}

void StyleClass::drawComplexControl(ComplexControl control, const QStyleOptionComplex *opt, QPainter *p, const QWidget *w) const{
    switch(control){
    case CC_ScrollBar:{
       /* p->fillRect(opt->rect, colorContrast);
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(colorMain);
        p->setPen(pen);
        //рисуем границы секций
        p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);*/



        QProxyStyle::drawComplexControl(control, opt, p, w);
    }break;
    default:
        QProxyStyle::drawComplexControl(control, opt, p, w);
    }

}

void StyleClass::drawItemPixmap(QPainter *p, const QRect &rect, int align, const QPixmap &pix) const{
    QProxyStyle::drawItemPixmap(p,rect,align,pix);
}

void StyleClass::drawItemText(QPainter *p, const QRect &rect, int flags, const QPalette &pal, bool en, const QString &text, QPalette::ColorRole textRole) const{
    QProxyStyle::drawItemText(p,rect,flags,pal,en,text,textRole);
}

void StyleClass::drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w)const{
    switch(pe){
    case PE_PanelLineEdit:{
        if (w->objectName()=="LabelCell"){
            LabelCell* lbl = (LabelCell*) w;

            CellPlusClass* cell = lbl->getCellPlusBase();
            if (cell!=0){
                p->fillRect(opt->rect, cell->getColor());
            }else{
                QWidget* wgt = w->parentWidget();
                if (wgt!=0){
                    QBrush brush = wgt->palette().background();
                    p->fillRect(opt->rect,brush);
                }else{
                    p->fillRect(opt->rect, QColor(255,255,255));
                }

            }
            QPen pen;
            pen.setStyle(Qt::SolidLine);
            pen.setWidth(1);
            pen.setCapStyle(Qt::RoundCap);
            if( opt->state & State_HasFocus){
                pen.setColor(colorFocusBoard);
            }else{
                pen.setColor(colorMainBoard);
            }

            p->setPen(pen);
            p->drawRect(opt->rect.x(), opt->rect.y(),opt->rect.width()-1,opt->rect.height()-1);
        }else{
            QProxyStyle::drawPrimitive(pe, opt, p, w);
        }
    }
    break;
    case PE_PanelItemViewItem:{
        if (opt->state & State_Selected){
            p->fillRect(opt->rect, colorSunken);
        }else{
            QProxyStyle::drawPrimitive(pe, opt, p, w);
        }
    }break;
    default:
        QProxyStyle::drawPrimitive(pe, opt, p, w);
    break;
    }
}
