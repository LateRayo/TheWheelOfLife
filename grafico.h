#ifndef GRAFICO_H
#define GRAFICO_H

#include <QDialog>

namespace Ui {
class Grafico;
}

class Grafico : public QDialog
{
    Q_OBJECT

public:
    explicit Grafico(QWidget *parent = nullptr);
    ~Grafico();


private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_9_currentIndexChanged(int index);

    void on_comboBox_8_currentIndexChanged(int index);

    void on_comboBox_7_currentIndexChanged(int index);

    void on_comboBox_6_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_5_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_comboBox_4_currentIndexChanged(int index);


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Grafico *ui;

};




#endif // GRAFICO_H
