#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include <QObject>
#include <QLineSeries>
#include <QChartView>

// Упрощенный класс для управления одним графиком
class PlotManager: public QObject
{
    Q_OBJECT
public:
    PlotManager(QObject* parent);
    ~PlotManager();
    const QSize& getSize() const;
    void setSize(const QSize& size);

public slots:
    void plot(const QVector<QPointF> data, QString title, QString titleX, QString titleY);

protected:
    QChart* m_chart = nullptr;
    QChartView* m_view = nullptr;
    QSize m_size;
};

#endif // PLOTMANAGER_H
