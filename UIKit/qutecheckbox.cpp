#include "qutecheckbox.h"
#include <QPainter>
#include <QBrush>
#include <QPainterPath>
#include <QPointF>
#include <QLineF>
#include <Qt>
#include <QPen>
#include <QPropertyAnimation>
#include <QTimer>
#include "trimmablepainterpath.h"



QuteCheckbox::QuteCheckbox(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

void QuteCheckbox::onClicked() {
    update();
}

// TODO code clean up
void QuteCheckbox::mousePressEvent(QMouseEvent *event) {
    check_state = !check_state;

    float endPercentageDuration;

    if (check_state) {
        endPercentageDuration = duration * .36;
    }
    else {
        endPercentageDuration = duration * (1-.36);
    }

    if (check_state) {
        QTimer::singleShot(0, this, &QuteCheckbox::startBlueEllipseAnimation);
        QTimer::singleShot(endPercentageDuration, this, &QuteCheckbox::startEndPercentageAnimation);
    }
    else {
        QTimer::singleShot(0, this, &QuteCheckbox::startEndPercentageAnimation);
        QTimer::singleShot(endPercentageDuration, this, &QuteCheckbox::startBlueEllipseAnimation);
    }
}

void QuteCheckbox::startBlueEllipseAnimation() {
    QPropertyAnimation *blueEllipseAnimation = new QPropertyAnimation(this, "blueEllipseRadius");
    blueEllipseAnimation->setDuration(duration);

    if (check_state) {
        blueEllipseAnimation->setStartValue(0.0);
        blueEllipseAnimation->setEndValue(this->boundingRect().width() * .8 * .5);
    }
    else {
        blueEllipseAnimation->setStartValue(this->boundingRect().width() * .8 * .5);
        blueEllipseAnimation->setEndValue(0.0);
    }
    if (check_state)
        blueEllipseAnimation->setEasingCurve(QEasingCurve::OutBack);
    else
        blueEllipseAnimation->setEasingCurve(QEasingCurve::InBack);
    blueEllipseAnimation->start();
}

void QuteCheckbox::startEndPercentageAnimation() {
    QPropertyAnimation *endPercentageAnimation = new QPropertyAnimation(this, "endPercentage");
    endPercentageAnimation->setDuration(duration * 0.8);

    if (check_state) {
        endPercentageAnimation->setStartValue(0.0);
        endPercentageAnimation->setEndValue(1.0);
    }
    else {
        endPercentageAnimation->setStartValue(1.0);
        endPercentageAnimation->setEndValue(0.0);
    }
    endPercentageAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    endPercentageAnimation->start();
}

void QuteCheckbox::paint(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing);
    QRectF br = this->boundingRect();
    QRectF checkboxRect = QRect(0, 0, br.height() * .8, br.width() * .8);
    checkboxRect.moveCenter(this->boundingRect().center());

    QPen pen;
    pen.setWidth(1 * checkboxRect.width() / 40);
    pen.setColor("#C7C7C7");
    painter->setPen(pen);
    painter->drawEllipse(checkboxRect.adjusted(pen.widthF(), pen.widthF(), -pen.widthF(), -pen.widthF()));

    painter->setBrush(QBrush("#0760FB"));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(this->boundingRect().center(), blueEllipseRadius(), blueEllipseRadius());

    QPainterPath path;
    path.moveTo(br.width() * .1 + 12.22 * checkboxRect.width() / 40, br.width() * .1 + 20.29 * checkboxRect.width() / 40);
    path.lineTo(br.width() * .1 + 17.22 * checkboxRect.width() / 40, br.width() * .1 + 25.56 * checkboxRect.width() / 40);
    path.lineTo(br.width() * .1 + 27.78 * checkboxRect.width() / 40, br.width() * .1 + 14.44 * checkboxRect.width() / 40);

    pen.setWidth(3 * checkboxRect.width() / 40);
    pen.setColor("#FFFFFF");
    pen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);

    painter->setPen(pen);

    QPainterPath trimmedPath = TrimmablePainterPath::trim(path, 0, endPercentage());
    painter->drawPath(trimmedPath);
}

