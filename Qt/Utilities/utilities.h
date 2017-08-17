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



#endif // UTILITIES_H
