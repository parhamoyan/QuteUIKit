#include "trimmablepainterpath.h"

TrimmablePainterPath::TrimmablePainterPath() {}

QPainterPath TrimmablePainterPath::trim(const QPainterPath& path, float start_percentage, float end_percentage) {
    if (start_percentage < 0.0 || start_percentage > 1.0 || end_percentage < 0.0 || end_percentage > 1.0) {
        throw std::invalid_argument("Percentage values must be between 0 and 1.");
    }
    if (start_percentage == end_percentage) {
        return QPainterPath();
    }

    QPainterPath trimmed_path;
    qreal total_length = path.length();
    qreal start_length = total_length * start_percentage;
    qreal end_length = total_length * end_percentage;
    qreal current_length = 0;

    int i = 0;
    while (i < path.elementCount() && current_length < end_length) {
        QPainterPath::Element path_element = path.elementAt(i);

        qreal segment_length = 0;
        if (!path_element.isMoveTo()) {
            segment_length = 0;
            if (path_element.isLineTo()) {
                QLineF segment(path.elementAt(i - 1), path_element);
                segment_length = segment.length();
            }
            else if (path_element.isCurveTo()) {
                QPointF p0(path.elementAt(i - 1).x, path.elementAt(i - 1).y);
                QPointF p1(path.elementAt(i).x, path.elementAt(i).y);
                QPointF p2(path.elementAt(i + 1).x, path.elementAt(i + 1).y);
                QPointF p3(path.elementAt(i + 2).x, path.elementAt(i + 2).y);

                QPainterPath bezier_path;
                bezier_path.moveTo(p0);
                bezier_path.cubicTo(p1, p2, p3);
                segment_length = bezier_path.length();
            }

            if (current_length < start_length && current_length + segment_length <= start_length) {
                current_length += segment_length;
                i += path_element.type;
                continue;
            }
        }

        if (path_element.isMoveTo()) {
            trimmed_path.moveTo(path_element.x, path_element.y);
            i += 1;
        }
        else if (path_element.isLineTo()) {
            QLineF segment(path.elementAt(i - 1), path_element);
            qreal segment_length = segment.length();
            if (current_length <= start_length && start_length < current_length + segment_length ||
                current_length <= end_length && end_length < current_length + segment_length) {
                qreal _start = (start_length - current_length) / segment_length;
                if (_start < 0) {
                    _start = 0;
                }
                qreal _end = (end_length - current_length) / segment_length;
                if (_end > 1) {
                    _end = 1;
                }
                QPointF start_point = segment.pointAt(_start);
                QPointF end_point = segment.pointAt(_end);
                trimmed_path.moveTo(start_point);
                trimmed_path.lineTo(end_point.x(), end_point.y());
                current_length += segment_length;
                i += path_element.type;
            }
            else {
                trimmed_path.lineTo(path_element.x, path_element.y);
                current_length += segment_length;
                i += path_element.type;
            }
        }
        else if (path_element.isCurveTo()) {
            QPointF p0(path.elementAt(i - 1).x, path.elementAt(i - 1).y);
            QPointF p1(path.elementAt(i).x, path.elementAt(i).y);
            QPointF p2(path.elementAt(i + 1).x, path.elementAt(i + 1).y);
            QPointF p3(path.elementAt(i + 2).x, path.elementAt(i + 2).y);

            std::vector<QPointF> new_points;
            if (current_length < start_length) {
                qreal start_percentage = (start_length - current_length) / segment_length;
                if (start_percentage > 1) {
                    start_percentage = 1;
                }
                new_points = trim_cubic_bezier_curve(start_percentage, p0, p1, p2, p3).second;
            }
            else if (current_length + segment_length <= end_length) {
                new_points = { p0, p1, p2, p3 };
            }
            else {
                qreal end_percentage = (end_length - current_length) / segment_length;
                new_points = trim_cubic_bezier_curve(end_percentage, p0, p1, p2, p3).first;
            }

            if (trimmed_path.isEmpty()) {
                trimmed_path.moveTo(new_points[0]);
            }
            QPainterPath cubic_bezier_path;
            cubic_bezier_path.cubicTo(new_points[1], new_points[2], new_points[3]);
            trimmed_path.addPath(cubic_bezier_path);
            current_length += segment_length;
            i += path_element.type;
        }
    }
    return trimmed_path;
}

std::pair<std::vector<QPointF>, std::vector<QPointF>> TrimmablePainterPath::trim_cubic_bezier_curve(qreal u0, const QPointF& p0, const QPointF& p1, const QPointF& p2, const QPointF& p3) {
    if (u0 < 0.0 || u0 > 1.0) {
        throw std::invalid_argument("Percentage value must be between 0 and 1.");
    }

    auto lerp = [](const QPointF& p0, const QPointF& p1, qreal u) -> QPointF {
        return QPointF((1 - u) * p0.x() + u * p1.x(), (1 - u) * p0.y() + u * p1.y());
    };

    QPointF r0 = lerp(p0, p1, u0);
    QPointF r1 = lerp(p1, p2, u0);
    QPointF r2 = lerp(p2, p3, u0);

    QPointF s0 = lerp(r0, r1, u0);
    QPointF s1 = lerp(r1, r2, u0);

    QPointF t0 = lerp(s0, s1, u0);

    return std::make_pair(std::vector<QPointF>{p0, r0, s0, t0}, std::vector<QPointF>{t0, s1, r2, p3});
}
