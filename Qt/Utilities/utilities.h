#ifndef UTILITIES_H
#define UTILITIES_H

#include "common_imports.h"

inline int rand_int(int min, int max)
{
    return min + (rand() % (int)(max - min + 1));
}

inline qreal get_eucliedean_distance(QPointF a, QPointF b)
{
    qreal sq_dist = std::pow( ( a.x() - b.x() ) , 2.0) + std::pow( ( a.y() - b.y() ) , 2.0);
    return std::sqrt(sq_dist);
}

inline void insert_escape_characters(QString &s)
{
    s.replace('"', "\\\"");
}

inline void sortPoints(std::vector < cv::Point > &pointList)
{
    std::sort(pointList.begin(),pointList.end(),Local());
}

struct Local {

    bool operator () (const cv::Point & p1, const cv::Point & p2)
    {
        int X1 = p1.x;
        int Y1 = p1.y;

        int X2 = p2.x;
        int Y2 = p2.y ;

        //return std::tie(X1, Y1) < std::tie(X2, Y2); // sort from bottom to up and left to right
        return std::tie(Y1, X1) < std::tie(Y2, X2) ;// sort from left to right and top to bottom
    }
};

//Getting the current Date as a string
inline QString getCurrentDate()
{
    QDate date = QDate::currentDate();
    return date.toString("MMMM dd, yyyy");
}

inline void remove_escape_characters(QString &s)
{
    s.replace("\\\"", "\"");
}

inline QString appendPath(const QString& path1, const QString& path2)
{
    return QDir::cleanPath(path1 + "/" + path2);
}


inline void copyFolder(QString sourceFolder, QString destFolder)
{
    QDir sourceDir(sourceFolder);
    if(!sourceDir.exists())
        return;
    QDir destDir(destFolder);
    if(!destDir.exists())
    {
        destDir.mkdir(destFolder);
    }
    QStringList files = sourceDir.entryList(QDir::Files);
    for(int i = 0; i< files.count(); i++)
    {
        QString srcName = sourceFolder + "/" + files[i];
        QString destName = destFolder + "/" + files[i];
        QFile::copy(srcName, destName);
    }
    files.clear();
    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for(int i = 0; i< files.count(); i++)
    {
        QString srcName = sourceFolder + "/" + files[i];
        QString destName = destFolder + "/" + files[i];
        copyFolder(srcName, destName);
    }
}

//Transforming points from a rotated(Uncropped)image to the orignal image.
inline void transformPointsPosition(float angle , vector<cv::Point> &inputPnts , QSize inputImgSize , QSize rotatedImgSize )
{
    float sineValue = qSin(qDegreesToRadians(360-angle));
    float cosValue = qCos(qDegreesToRadians(360-angle));

    for(cv::Point &inPnt : inputPnts)
    {

        float transformedX ;
        float transformedY ;

        inPnt.x = inPnt.x - float(rotatedImgSize.width()/2);
        inPnt.y = inPnt.y - float(rotatedImgSize.height()/2);

        //Rotation
        transformedX = (float(inPnt.x) * cosValue) - (float(inPnt.y ) * sineValue);
        transformedY = (float(inPnt.x) * sineValue) + (float(inPnt.y ) * cosValue) ;

        inPnt.x = transformedX;
        inPnt.y = transformedY;

        //Scaling
        inPnt.x = inPnt.x + float(inputImgSize.width()/2) ;
        inPnt.y = inPnt.y + float(inputImgSize.height()/2) ;
    }

}


inline void removeOverlappingPoints(vector < cv::Point > &rectPntList)
{
    const float OVERLAPPING_THRESHOLD = 60.0 ;
    vector < cv::Point > pointList ;

    if (rectPntList.size() == 0)
        return;

    auto in_itr = rectPntList.begin();
    pointList.push_back(*in_itr);
    ++in_itr;

    while (in_itr != rectPntList.end()) {
        bool similar_point_added = false;
        for (auto out_itr = pointList.begin();
             out_itr != pointList.end();
             ++out_itr) {
            if (get_eucliedean_distance((*in_itr) , (*out_itr)) < OVERLAPPING_THRESHOLD) {
                similar_point_added = true;
                break;
            }
        }
        if (similar_point_added == false) {
            pointList.push_back(*in_itr);
        }
        ++in_itr;
    }

    rectPntList.clear();

    for(auto &pnt : pointList)
    {
        rectPntList.push_back(pnt);
    }

}




#endif // UTILITIES_H
