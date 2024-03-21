#ifndef QUTECHECKBOX_H
#define QUTECHECKBOX_H

#include <QQuickPaintedItem>
#include <QPropertyAnimation>
#include <QMouseEvent>

class QuteCheckbox : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(double endPercentage READ endPercentage WRITE setEndPercentage NOTIFY endPercentageChanged)
    Q_PROPERTY(double blueEllipseRadius READ blueEllipseRadius WRITE setBlueEllipseRadius NOTIFY blueEllipseRadiusChanged)
public:
    explicit QuteCheckbox(QQuickPaintedItem *parent = nullptr);

    void paint(QPainter *painter) override;

    double endPercentage() const { return m_endPercentage; }

    void setEndPercentage(double percentage) {
        m_endPercentage = percentage;
        emit endPercentageChanged();
        update();
    }

    double blueEllipseRadius() const { return m_blueEllipseRadius; }

    void setBlueEllipseRadius(double newValue) {
        m_blueEllipseRadius = newValue;
        emit blueEllipseRadiusChanged();
        update();
    }
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void startEndPercentageAnimation();
    void startBlueEllipseAnimation();
signals:
    void endPercentageChanged();
    void blueEllipseRadiusChanged();
    void clicked();
private:
    qreal m_endPercentage = 0;
    qreal m_blueEllipseRadius = 0;
    bool check_state = false;
    int duration = 1000 * .3;

public slots:
    void onClicked();
};

#endif // QUTECHECKBOX_H
