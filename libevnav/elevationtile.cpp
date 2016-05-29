#include "elevationtile.h"
#include <QFile>
#include <QFileDevice>
#include <QDebug>
#include <cmath>

ElevationTile::ElevationTile(QObject *parent) : QObject(parent)
{
}

ElevationTile::~ElevationTile()
{
    if (m_buf) {
        m_file.unmap(m_buf);
    }
}

int ElevationTile::width()
{
    return 1201;
}

int ElevationTile::height()
{
    return 1201;
}

int ElevationTile::valueAt(int x, int y)
{
    int alt = 0;
    if (m_buf) {
        int offset = (y * 1201 + x) * 2;
        alt = m_buf[offset + 1] | m_buf[offset] << 8;
    }
    return alt;
}

void
ElevationTile::load(const QString &path)
{
    m_file.setFileName(path);
    if (m_file.open(QFile::ReadOnly)) {
        qDebug() << "file size:" << m_file.size();
        qDebug() << "theoric file" << (2 * 1201 * 1201);
        m_buf = m_file.map(0, m_file.size());
    }
}

double
ElevationTile::query(double lon, double lat)
{
    // need to check bounds!
    // 3600 / 3 = 1200

    double temp;
    double lon_dec = std::abs(std::modf(lon, &temp));
    double lat_dec = std::abs(std::modf(lat, &temp));

    qDebug() << lon_dec << lat_dec;
    qDebug() << round(lon_dec * 1200);
    qDebug() << round(lat_dec * 1200);

    int row = 1201 - round(lat_dec * 1200) - 1;
    int col = round(lon_dec * 1200) - 1;

    qDebug() << row << col;
    int offset = (row * 1201 + col) * 2;
    int alt = m_buf[offset + 1] | m_buf[offset] << 8;
    qDebug() << "alt" << alt;
    return alt;
}
