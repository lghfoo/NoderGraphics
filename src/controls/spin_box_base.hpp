#pragma once
#include<QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QPainterPath>
#include<QFocusEvent>
#include<QFontMetrics>
#include<QMouseEvent>
#include<QFont>
#include<QDebug>
#include<QTimer>
#include <QGuiApplication>
#include<QMenu>
#include<QAction>
#include <QApplication>
#include <QClipboard>
#include<QHoverEvent>
class SpinBoxBase : public QWidget{
    Q_OBJECT
private:
    enum Area{VALUE_AREA, STEP_AREA, NO_AREA};
    enum ChangeRepeat{VALUE_UP, VALUE_DOWN, STEP_UP, STEP_DOWN, NO_CHANGE};
public:
    struct DrawInfo{
        QFont font;
        int text_padding = 10;
        int widget_padding = 5;
        float radio = 0.7f;
        float radius = 0.0f;
        QRect box_rect = QRect();
        QRect value_up_rect = QRect();
        QRect value_down_rect = QRect();
        QRect step_up_rect = QRect();
        QRect step_down_rect = QRect();
        QRect value_edit_rect = QRect();
        QRect step_edit_rect = QRect();
        QRect value_edit_rectangle = QRect();
        QRect step_edit_rectangle = QRect();
    };
    SpinBoxBase(){
        this->setMinimumSize(150, 25);
        connect(cursor_timer, &QTimer::timeout, [=]{
            this->is_cursor_on = !this->is_cursor_on;
            this->update();
        });

        connect(change_timer, &QTimer::timeout, this, &SpinBoxBase::RepeatValueChange);
        this->setContextMenuPolicy(Qt::CustomContextMenu);
        right_click_menu->addAction(tr("Copy"));
        right_click_menu->addSeparator();
        right_click_menu->addAction(tr("Paste"));
        right_click_menu->addSeparator();
        right_click_menu->addAction(tr("Cut"));
        right_click_menu->addSeparator();
        right_click_menu->addAction(tr("Delete"));
        connect(this, &QWidget::customContextMenuRequested,
                this, &SpinBoxBase::OnRightClick);

        auto pal = this->palette();
        pal.setColor(QPalette::Background, Qt::transparent);
        this->setPalette(pal);
    }
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        QPen pen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setRenderHint(QPainter::Antialiasing, true);

        auto font = this->font();
        auto font_metric = QFontMetrics(font);
        auto font_size = font_metric.size(Qt::TextSingleLine, value_text);
        int text_padding = 5;
        int widget_padding = 5;
        this->setMinimumHeight(font_size.height() + text_padding * 2 + widget_padding * 2);
        int widget_width = width();
        float box_width = widget_width - widget_padding * 2;
        float box_height = font_size.height() + text_padding * 2;

        float radio = 0.7f;
        int value_edit_width = box_width * radio;
        int step_edit_width = box_width - value_edit_width;

        float radius = box_height / 2.0f;
        float box_rect_x = (widget_width - box_width) / 2;
        float box_rect_y = (height() - box_height) / 2;
        drawInfo.box_rect.setRect(box_rect_x, box_rect_y, box_width, box_height);

        QPainterPath path;
        path.addRoundedRect(box_rect_x, box_rect_y, box_width, box_height, radius, radius, Qt::AbsoluteSize);
        painter.fillPath(path, QBrush(QColor("gray").lighter()));

        painter.drawRoundedRect(box_rect_x, box_rect_y, box_width, box_height, radius, radius, Qt::AbsoluteSize);

        QPoint p0(box_rect_x + value_edit_width, box_rect_y);
        QPoint p1(box_rect_x + value_edit_width, box_rect_y + box_height);
        painter.drawLine(p0, p1);

        auto button_padding = 2;
        auto button_area_height = box_height / 2;
        auto button_area_width = button_area_height;
        auto value_up_btn_area_x = box_rect_x + value_edit_width - button_area_width;
        auto value_up_btn_area_y = box_rect_y;
        auto value_down_btn_area_x = value_up_btn_area_x;
        auto value_down_btn_area_y = value_up_btn_area_y + button_area_height;
        auto step_up_btn_area_x = value_up_btn_area_x + button_area_width;
        auto step_up_btn_area_y = value_up_btn_area_y;
        auto step_down_btn_area_x = step_up_btn_area_x;
        auto step_down_btn_area_y = value_down_btn_area_y;
        auto half_btn_area_width = button_area_width / 2;
        auto half_btn_area_height = button_area_height / 2;
        auto arrow_half_width = (button_area_width - button_padding * 2) / 2;
        auto arrow_half_height = (button_area_height - button_padding * 2) / 2;
        drawInfo.value_up_rect.setRect(value_up_btn_area_x, value_up_btn_area_y,
                                       button_area_width, button_area_height);
        drawInfo.value_down_rect.setRect(value_down_btn_area_x, value_down_btn_area_y,
                                       button_area_width, button_area_height);
        drawInfo.step_up_rect.setRect(step_up_btn_area_x, step_up_btn_area_y,
                                       button_area_width, button_area_height);
        drawInfo.step_down_rect.setRect(step_down_btn_area_x, step_down_btn_area_y,
                                       button_area_width, button_area_height);
        drawInfo.value_edit_rect.setRect(box_rect_x, box_rect_y, value_edit_width - button_area_width, box_height);
        drawInfo.step_edit_rect.setRect(drawInfo.step_up_rect.x() + button_area_width, box_rect_y,
                                        step_edit_width - button_area_width, box_height);

        QPoint value_up_center_pos = QPoint(value_up_btn_area_x + half_btn_area_width, value_up_btn_area_y + half_btn_area_height),
                value_down_center_pos = QPoint(value_down_btn_area_x + half_btn_area_width, value_down_btn_area_y + half_btn_area_height),
                step_up_center_pos = QPoint(step_up_btn_area_x + half_btn_area_width, step_up_btn_area_y + half_btn_area_height),
                step_down_center_pos = QPoint(step_down_btn_area_x + half_btn_area_width, step_down_btn_area_y + half_btn_area_height);
        QPoint points[] = {value_up_center_pos, step_up_center_pos, value_down_center_pos, step_down_center_pos};

        for(int i = 0; i < 2; i++){
            auto point = points[i];
            QPainterPath path;
            QPoint left_down = point + QPoint(-arrow_half_width, arrow_half_height);
            QPoint right_down = point + QPoint(arrow_half_width, arrow_half_height);
            QPoint up = point + QPoint(0, -arrow_half_height);
            path.moveTo(left_down);
            path.lineTo(right_down);
            path.lineTo(up);
            painter.fillPath(path, QBrush(Qt::black));
        }

        for(int i = 2; i < 4; i++){
            auto point = points[i];
            QPainterPath path;
            QPoint left_up = point + QPoint(-arrow_half_width, -arrow_half_height);
            QPoint right_up = point + QPoint(arrow_half_width, -arrow_half_height);
            QPoint down = point + QPoint(0, arrow_half_height);
            path.moveTo(left_up);
            path.lineTo(right_up);
            path.lineTo(down);
            painter.fillPath(path, QBrush(Qt::black));
        }

        QRect value_bounding;
        value_bounding.setSize(font_metric.size(Qt::TextSingleLine, value_text));
        QRect value_edit_rect = QRect(box_rect_x + radius, box_rect_y, value_edit_width - radius - button_area_width, box_height);
        QRect step_edit_rect = QRect(step_up_btn_area_x + button_area_width, box_rect_y, step_edit_width - radius - button_area_width, box_height);
        drawInfo.value_edit_rect = value_edit_rect;
        drawInfo.step_edit_rect = step_edit_rect;
        auto value_text_width = font_metric.size(Qt::TextSingleLine, value_text).width();
        auto step_text_width = font_metric.size(Qt::TextSingleLine, step_text).width();
        int value_rectangle_x = value_edit_rect.right() - value_text_width + value_edit_bounding_pos;
        int step_rectangle_x = step_edit_rect.x() + step_edit_bounding_pos;

        if(value_rectangle_x > value_edit_rect.x() && value_rectangle_x + value_text_width > value_edit_rect.right()){
            int dx = value_rectangle_x - value_edit_rect.x();
            value_rectangle_x -= dx;
            value_edit_bounding_pos -= dx;
        }
        if(step_rectangle_x < step_edit_rect.x() && step_rectangle_x + step_text_width < step_edit_rect.right()){
            int dx = step_edit_rect.x() - step_rectangle_x;
            step_rectangle_x += dx;
            step_edit_bounding_pos += dx;
        }

        // value cursor
        QSize value_lstr_font_size = font_metric.size(Qt::TextSingleLine, value_text.left(value_cursor_pos));
        int value_cursor_x = value_rectangle_x + value_lstr_font_size.width();
        {
            if(value_cursor_x < value_edit_rect.x()){
                int dx = value_edit_rect.x() - value_cursor_x;
                value_edit_bounding_pos += dx;
                value_rectangle_x += dx;
                value_cursor_x = value_edit_rect.x();
            }
            else if(value_cursor_x > value_edit_rect.right()){
                int dx = value_cursor_x - (value_edit_rect.right());
                value_edit_bounding_pos -= dx;
                value_rectangle_x -= dx;
                value_cursor_x = value_edit_rect.right();
            }
        }
        // step cursor
        QSize step_lstr_font_size = font_metric.size(Qt::TextSingleLine, step_text.left(step_cursor_pos));
        int step_cursor_x = step_rectangle_x + step_lstr_font_size.width();
        {
            if(step_cursor_x < step_edit_rect.x()){
                int dx = step_edit_rect.x() - step_cursor_x;
                step_edit_bounding_pos += dx;
                step_rectangle_x += dx;
                step_cursor_x = step_edit_rect.x();
            }
            else if(step_cursor_x > step_edit_rect.right()){
                int dx = step_cursor_x - (step_edit_rect.right());
                step_edit_bounding_pos -= dx;
                step_rectangle_x -= dx;
                step_cursor_x = step_edit_rect.right();
            }
        }
        if(is_cursor_on){
            if(active_area == Area::VALUE_AREA){
                QPoint cursor_up = QPoint(value_cursor_x, value_edit_rect.y() + text_padding);
                QPoint cursor_down = QPoint(value_cursor_x, value_edit_rect.y() + value_edit_rect.height() - text_padding);
                painter.drawLine(cursor_up, cursor_down);
            }
            else if(active_area == Area::STEP_AREA){
                QPoint cursor_up = QPoint(step_cursor_x, step_edit_rect.y() + text_padding);
                QPoint cursor_down = QPoint(step_cursor_x, step_edit_rect.y() + step_edit_rect.height() - text_padding);
                painter.drawLine(cursor_up, cursor_down);
            }
        }

        drawInfo.value_edit_rectangle.setRect(value_rectangle_x,
                                              value_edit_rect.y(),
                                              value_text_width,
                                              value_edit_rect.height()
                                              );
        drawInfo.step_edit_rectangle.setRect(step_rectangle_x,
                                        step_edit_rect.y(),
                                        step_text_width,
                                        step_edit_rect.height());
        DrawText(painter, Area::VALUE_AREA, drawInfo.value_edit_rect, text_padding,
                 drawInfo.value_edit_rectangle, value_text, Qt::AlignCenter | Qt::AlignRight,
                 font_metric);
        DrawText(painter, Area::STEP_AREA, drawInfo.step_edit_rect, text_padding,
                 drawInfo.step_edit_rectangle, step_text, Qt::AlignCenter | Qt::AlignLeft,
                 font_metric);
    }
    void DrawText(QPainter& painter, const int& area, const QRect& edit_rect,
                  int text_padding, const QRect& edit_rectangle,
                  const QString& text, int alignments,
                  const QFontMetrics& font_metric){
        painter.setClipRect(edit_rect);
        if(is_selecting && active_area == area)
        {
            int p0 = 0;
            int p1 = qMin(selection_range.x(), selection_range.y());
            int p2 = qMax(selection_range.x(), selection_range.y());
            int p3 = text.length();
            QString lstr = text.left(p1 - p0);
            QString mstr = text.mid(p1, p2 - p1);
            QString rstr = text.right(p3 - p2);
            int lw = font_metric.size(Qt::TextSingleLine, lstr).width();
            int mw = font_metric.size(Qt::TextSingleLine, mstr).width();
            int rw = font_metric.size(Qt::TextSingleLine, rstr).width();

            int hlx = edit_rectangle.x() + lw;
            int hly = edit_rect.y() + text_padding;
            int hlw = mw;
            int hlh = edit_rect.height() - text_padding * 2;
            painter.fillRect(hlx, hly, hlw, hlh, QBrush(highlight_bg_color));
            QRect lstr_rect(edit_rectangle.x(), edit_rectangle.y(),
                            lw, edit_rectangle.height());
            QRect mstr_rect(edit_rectangle.x() + lw, edit_rectangle.y(),
                            mw, edit_rectangle.height());
            QRect rstr_rect(edit_rectangle.x() + lw + mw, edit_rectangle.y(),
                            rw, edit_rectangle.height());
            painter.drawText(lstr_rect, Qt::AlignRight | Qt::AlignCenter, lstr);
            painter.save();
            QPen pen = painter.pen();
            pen.setColor(highlight_text_color);
            painter.setPen(pen);
            painter.drawText(mstr_rect, alignments, mstr);
            painter.restore();
            painter.drawText(rstr_rect, alignments, rstr);
        }
        else{
            painter.drawText(edit_rectangle,alignments, text);
        }
    }

    void mousePressEvent(QMouseEvent* event)override{
        if(event->button()== Qt::LeftButton)
        {
            is_selecting = false;
            change_timer->stop();
            if(drawInfo.step_edit_rect.contains(event->pos())){
                OnPress(Area::STEP_AREA, step_cursor_pos, event->pos());
            }
            else if(drawInfo.value_edit_rect.contains(event->pos())){
                OnPress(Area::VALUE_AREA, value_cursor_pos, event->pos());
            }
            else if(drawInfo.step_up_rect.contains(event->pos())){
                change_repeat = STEP_UP;
                change_timer->start(value_change_frequency);
                StepUp();
                this->update();
            }
            else if(drawInfo.step_down_rect.contains(event->pos())){
                change_repeat = STEP_DOWN;
                change_timer->start(value_change_frequency);
                StepDown();
                this->update();
            }
            else if(drawInfo.value_up_rect.contains(event->pos())){
                change_repeat = VALUE_UP;
                change_timer->start(value_change_frequency);
                ValueUp();
                this->update();
            }
            else if(drawInfo.value_down_rect.contains(event->pos())){
                change_repeat = VALUE_DOWN;
                change_timer->start(value_change_frequency);
                ValueDown();
                this->update();
            }
        }
        else if(event->button()==Qt::RightButton){

        }
        this->setFocus();
    }

    void mouseReleaseEvent(QMouseEvent* event)override{
        change_timer->stop();
    }

    void wheelEvent(QWheelEvent *event)override{
        this->is_selecting=false;
        Area area = Area::NO_AREA;
        if(drawInfo.step_edit_rect.contains(event->pos())){
            area = Area::STEP_AREA;
        }
        else if(drawInfo.value_edit_rect.contains(event->pos())){
            area = Area::VALUE_AREA;
        }
        else if(drawInfo.step_up_rect.contains(event->pos())){
            area = Area::STEP_AREA;
        }
        else if(drawInfo.step_down_rect.contains(event->pos())){
            area = Area::STEP_AREA;
        }
        else if(drawInfo.value_up_rect.contains(event->pos())){
            area = Area::VALUE_AREA;
        }
        else if(drawInfo.value_down_rect.contains(event->pos())){
            area = Area::VALUE_AREA;
        }
        if(event->delta() > 0){
            if(area == Area::VALUE_AREA){
                ValueUp();
            }
            else if(area == Area::STEP_AREA){
                StepUp();
            }
        }else if(event->delta() < 0){
            if(area == Area::VALUE_AREA){
                ValueDown();
            }
            else if(area == Area::STEP_AREA){
                StepDown();
            }
        }
        else{
            return;
        }
        this->update();
        event->accept();
    }

    void OnPress(const Area& area, int& cursor_pos, const QPoint pos){
        active_area = area;
        cursor_pos = GetTextPosOfMouse(pos);
        is_cursor_on = true;
        this->update();
    }

    void focusInEvent(QFocusEvent* event)override{
        cursor_timer->start(cursor_flicker_frequency);
        this->cached_value = this->value_text;
    }

    void focusOutEvent(QFocusEvent* event)override{
        cursor_timer->stop();
        change_timer->stop();
        this->is_cursor_on = false;
        this->is_selecting = false;
        this->update();
    }

    virtual void keyPressEvent(QKeyEvent* event)override{
        if(active_area == Area::VALUE_AREA){
            OnKeyPress(event->key(),
                       event->text(),
                       value_cursor_pos,
                       value_text);
        }
        else if(active_area == Area::STEP_AREA){
            OnKeyPress(event->key(),
                       event->text(),
                       step_cursor_pos,
                       step_text);
        }
    }

    void OnKeyPress(const int& key,
                    const QString& key_text,
                    int& cursor_pos,
                    QString& text){
        if(QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier)){
            if(key == Qt::Key_C){
                this->CopySelection();
            }
            else if(key == Qt::Key_V){
                this->PasteText();
                this->update();
            }
            else if(key == Qt::Key_X){
                this->CutSelection();
                this->update();
            }
            return;
        }
        if(32 <= key && key <= 126){
            AddText(key_text);
        }
        else if(key == Qt::Key_Right){
            is_cursor_on = true;
            if(QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)){
                selection_range.setY(qMin(cursor_pos+1, text.length()));
                if(!is_selecting){
                    selection_range.setX(cursor_pos);
                    is_selecting = true;
                }
            }
            else{
                is_selecting = false;
            }
            if(cursor_pos < text.length()){
                cursor_pos++;
            }
            this->update();
        }
        else if(key == Qt::Key_Left){
            is_cursor_on = true;
            if(QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)){
                selection_range.setY(qMax(cursor_pos-1, 0));
                if(!is_selecting){
                    selection_range.setX(cursor_pos);
                    is_selecting = true;
                }
            }
            else{
                is_selecting = false;
            }
            if(cursor_pos > 0){
                cursor_pos--;
            }
            this->update();
        }
        else if(key == Qt::Key_Backspace){
            if(is_selecting){
                DeleteSelection();
            }
            else if(cursor_pos>0){
                cursor_pos--;
                text.remove(cursor_pos, 1);
            }
            this->update();
        }
        else if(key == Qt::Key_Delete){
            if(is_selecting){
                DeleteSelection();
            }
            else if(cursor_pos < text.length()){
                text.remove(cursor_pos, 1);
            }
            this->update();
        }
    }

    void mouseDoubleClickEvent(QMouseEvent* event)override{
        if(drawInfo.value_edit_rect.contains(event->pos())){
            is_selecting = true;
            selection_range = QPoint(0, value_text.length());
            value_cursor_pos = value_text.length();
            this->update();
        }
        else if(drawInfo.step_edit_rect.contains(event->pos())){
            is_selecting = true;
            selection_range = QPoint(0, step_text.length());
            step_cursor_pos = step_text.length();
            this->update();
        }
    }

    void DeleteSelection(){
        if(is_selecting)
        {
            if(active_area==Area::VALUE_AREA)
            {
                DeleteSelection(value_text, value_cursor_pos);
            }
            else if(active_area==Area::STEP_AREA){
                DeleteSelection(step_text, step_cursor_pos);
            }
        }
    }

    void DeleteSelection(QString& text, int& cursor_pos){
        int from = qMin(selection_range.x(), selection_range.y());
        int to = qMax(selection_range.x(), selection_range.y());
        text.remove(from, to-from);
        cursor_pos = from;
        is_selecting = false;
    }

    void AddText(QString text){
        if(is_selecting){
            DeleteSelection();
        }
        if(active_area==Area::VALUE_AREA)
        {
            value_text.insert(value_cursor_pos, text);
            value_cursor_pos += text.length();
        }
        else if(active_area==Area::STEP_AREA){
            step_text.insert(step_cursor_pos, text);
            step_cursor_pos += text.length();
        }
        this->update();
    }
    void PasteText(){
        this->AddText(QApplication::clipboard()->text());
    }
    void mouseMoveEvent(QMouseEvent* event)override{
        if(event->buttons()!=Qt::LeftButton)return;
        if(active_area==Area::VALUE_AREA)
        {
            OnMouseMove(value_cursor_pos, event->pos());
        }
        else if(active_area==Area::STEP_AREA){
            OnMouseMove(step_cursor_pos, event->pos());
        }
    }

    void OnMouseMove(int& cursor_pos, const QPoint& pos){
        if(!is_selecting){
            is_selecting = true;
            cursor_pos = GetTextPosOfMouse(pos);
            selection_range.setX(cursor_pos);
            selection_range.setY(cursor_pos);
            this->update();
        }
        else{
            cursor_pos = GetTextPosOfMouse(pos);
            selection_range.setY(cursor_pos);
            this->update();
        }
    }

    int GetTextPosOfMouse(const QPoint& mouse_pos){
        if(active_area==Area::VALUE_AREA)
        {
            return GetTextPosOfMouse(drawInfo.value_edit_rectangle,
                                     mouse_pos,
                                     value_text);
        }
        else if(active_area==Area::STEP_AREA){
            return GetTextPosOfMouse(drawInfo.step_edit_rectangle,
                                     mouse_pos,
                                     step_text);
        }
        else{
            return 0;
        }
    }

    int GetTextPosOfMouse(const QRect& edit_rectangle,
                          const QPoint& mouse_pos,
                          const QString& text){
        int pos = edit_rectangle.x();
        if(mouse_pos.x() <= pos){
            return 0;
        }
        else if(mouse_pos.x() >= edit_rectangle.right()){
            return text.length();
        }
        else{
            auto font_metric = QFontMetrics(drawInfo.font);
            for(int i = 0; i < text.length(); i++){
                int w = font_metric.size(Qt::TextSingleLine, text.at(i)).width();
                int half_w = w / 2;
                if(mouse_pos.x() < pos + half_w){
                    return i;
                }
                else if(mouse_pos.x() < pos + w){
                    return i + 1;
                }
                pos += w;
            }
        }
        return text.length();
    }
    void CopySelection(){
        if(is_selecting){
            const QString& text = this->GetSelectedText();
            QClipboard * clipboard = QApplication::clipboard();
            clipboard->setText(text);
        }
    }
    void CutSelection(){
        CopySelection();
        this->DeleteSelection();
    }
    QString GetSelectedText(){
        if(active_area==Area::VALUE_AREA){
            return GetSelectedValueText();
        }
        else if(active_area==Area::STEP_AREA){
            return GetSelectedStepText();
        }
        return "";
    }
    QString GetSelectedValueText(){
        if(!is_selecting)return "";
        int p1 = qMin(selection_range.x(), selection_range.y());
        int p2 = qMax(selection_range.x(), selection_range.y());
        return value_text.mid(p1, p2 - p1);
    }
    QString GetSelectedStepText(){
        if(!is_selecting)return "";
        int p1 = qMin(selection_range.x(), selection_range.y());
        int p2 = qMax(selection_range.x(), selection_range.y());
        return step_text.mid(p1, p2 - p1);
    }

    virtual void ValueUp(){

    }
    virtual void ValueDown(){

    }
    virtual void StepUp(){

    }
    virtual void StepDown(){

    }

    virtual ~SpinBoxBase()override{
        cursor_timer->stop();
        delete cursor_timer;
        change_timer->stop();
        delete change_timer;
        right_click_menu->close();
        delete right_click_menu;

    }
public slots:
    void OnRightClick(const QPoint& pos){
        QPoint globalPos = this->mapToGlobal(pos);
        QAction* selectedItem = right_click_menu->exec(globalPos);
        if (selectedItem)
        {
            if(selectedItem->text().compare("Copy") == 0){
                CopySelection();
            }
            else if(selectedItem->text().compare("Paste")==0){
                PasteText();
            }
            else if(selectedItem->text().compare("Delete")==0){
                this->DeleteSelection();
                this->update();
            }
            else if(selectedItem->text().compare("Cut")==0){
                CutSelection();
                this->update();
            }
        }
    }
    void RepeatValueChange(){
        switch (change_repeat) {
        case NO_CHANGE:
            return;
        case VALUE_UP:
            ValueUp();
            break;
        case VALUE_DOWN:
            ValueDown();
            break;
        case STEP_UP:
            StepUp();
            break;
        case STEP_DOWN:
            StepDown();
            break;
        }
        this->update();
    }
private:
    DrawInfo drawInfo;
    Area active_area = Area::NO_AREA;
    ChangeRepeat change_repeat = ChangeRepeat::NO_CHANGE;
    int value = 0;
    int step = 0;
    QPoint selection_range;
    QTimer* cursor_timer = new QTimer();
    QTimer* change_timer = new QTimer();
    int value_cursor_pos = 1;
    int value_edit_bounding_pos = 0;
    int step_cursor_pos = 1;
    int step_edit_bounding_pos = 0;
    QColor highlight_text_color = Qt::white;
    QColor highlight_bg_color = Qt::black;
    bool is_cursor_on = true;
    int cursor_flicker_frequency = 350;
    int value_change_frequency = 150;
    bool is_selecting = false;
    QMenu* right_click_menu = new QMenu();
protected:
    QString value_text = "0";
    QString step_text = "1";
    QString cached_value = "";
};

