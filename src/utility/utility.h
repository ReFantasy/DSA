#ifndef UTILITY_H
#define UTILITY_H
#include <QDateTime>

/**
 * @brief QString 转为 QDateTime yyyy-MM-dd hh:mm:ss
 */
QDateTime QStringToDateTime(const QString &str);

QStringList Split(QString str, QChar c);

#endif // UTILITY_H
