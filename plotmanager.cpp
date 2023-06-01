#include "plotmanager.h"

#include <QValueAxis>


PlotManager::PlotManager(QObject *parent):QObject(parent), m_size(400, 400)
{
    m_view = new QChartView(m_chart);
}

PlotManager::~PlotManager()
{
    if (m_chart)
    {
        delete m_chart;
    }

    delete m_view;
}

const QSize &PlotManager::getSize() const
{
    return m_size;
}

void PlotManager::setSize(const QSize &size)
{
    m_size = size;
}

void PlotManager::plot(const QVector<QPointF> data, QString title, QString titleX, QString titleY)
{
    // Попробовал по максимуму использовать динамическую память
    // в классе QChartView нельзя выставить диаграмму в nullptr, поэтому запоминаем старую для ее удаления
    auto oldChart = m_chart;
    m_chart = new QChart();
    m_chart->legend()->setVisible(false);
    auto series = new QLineSeries();

    for(auto& p: data)
    {
        series->append(p);
    }

    // QChart начинает владеть series
    m_chart->addSeries(series);
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText(titleX);
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText(titleY);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    m_chart->setTitle(title);
    m_view->setChart(m_chart);
    if (oldChart)
    {
        delete oldChart;
    }

    m_view->resize(m_size);
    m_view->show();
}

