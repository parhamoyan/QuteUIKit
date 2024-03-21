#ifndef TRIMMABLEPAINTERPATH_H
#define TRIMMABLEPAINTERPATH_H

#include <QPainterPath>

class TrimmablePainterPath
{
public:
    TrimmablePainterPath();
    static QPainterPath trim(const QPainterPath& path, float start_percentage, float end_percentage);
private:
    static std::pair<std::vector<QPointF>, std::vector<QPointF>> trim_cubic_bezier_curve(qreal u0, const QPointF& p0, const QPointF& p1, const QPointF& p2, const QPointF& p3);
};

#endif // TRIMMABLEPAINTERPATH_H

