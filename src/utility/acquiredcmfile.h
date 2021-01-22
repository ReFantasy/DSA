#ifndef ACQUIREDCMFILE_H
#define ACQUIREDCMFILE_H
#include <string>
#include <vector>
#include <QPixmap>
#include <QStringList>

std::vector<std::vector<QPixmap>> AcquireDcmFile(std::string patient_id, QStringList &file_names);

#endif // ACQUIREDCMFILE_H
