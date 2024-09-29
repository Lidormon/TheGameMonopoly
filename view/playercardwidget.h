#ifndef PLAYERCARDWIDGET_H
#define PLAYERCARDWIDGET_H

#include <QWidget>

namespace view {

namespace Ui {
class PlayerCardWidget;
}

class PlayerCardWidget : public QWidget
{
    Q_OBJECT

public:
    static constexpr int NOT_IN_JAIL = -1;

public:
    explicit PlayerCardWidget(int index, QWidget *parent = nullptr);
    ~PlayerCardWidget();

public:
    int getIndex() const;
    void setName(const QString &name);
    void setColor(const QColor &color);
    void setMoney(int money);
    void setRailways(int railways);
    void setJail(int turns);
    void setCurrent();
    void unsetCurrent();

public: signals:
    void click(int index);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::PlayerCardWidget *ui;
    int index;
};

} // namespace view
#endif // PLAYERCARDWIDGET_H
