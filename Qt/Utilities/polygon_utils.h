#ifndef POLYGON_UTILS_H
#define POLYGON_UTILS_H


inline QVector<QPointF> generate_random_polygon(QPoint start_pos)
{
    QVector<QPointF> polygon_points;
    polygon_points << QPointF(start_pos.x(), start_pos.y());
    for(int i= 0 ; i < 2 ; i++)
    {
        polygon_points << QPointF(start_pos.x() + rand_int(-400,400),start_pos.y() + rand_int(-400,400));
    }

    return polygon_points;
}

inline QPolygonF generate_random_quadrilateral(QPointF start_pos)
{

    QPolygonF polygon_points;

    int y_disp = rand_int(100,250);
    polygon_points << QPointF(start_pos.x(), start_pos.y());
    polygon_points << QPointF(start_pos.x() + rand_int(100,200), start_pos.y());
    polygon_points << QPointF(start_pos.x() + rand_int(200,300), start_pos.y() + y_disp);
    polygon_points << QPointF(start_pos.x() + rand_int(0,100), start_pos.y() + y_disp);

    return polygon_points;
}

#endif // POLYGON_UTILS_H
