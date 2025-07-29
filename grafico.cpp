#include "grafico.h"
#include "ui_grafico.h"
#include "drawthewheel.h"
#include <iostream>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>

LifeField fields[9];

Grafico::Grafico(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Grafico)
{
    const char* DEFAULT_FIELDS[] = {
        "Amor", "Familia", "Amigos", "Crecimiento",
        "Propósito", "Dinero", "Espiritualidad", "Físico", "Mente"
    };

    ui->setupUi(this);

    QComboBox* comboBoxes[9] = {
        ui->comboBox,
        ui->comboBox_2,
        ui->comboBox_3,
        ui->comboBox_4,
        ui->comboBox_5,
        ui->comboBox_6,
        ui->comboBox_7,
        ui->comboBox_8,
        ui->comboBox_9,
    };

    for (int i = 0; i < 9; i++)
    {
        comboBoxes[i]->addItems({"0","1","2","3","4","5","6","7","8","9","10"});
        strcpy(fields[i].name,DEFAULT_FIELDS[i]);
        fields[i].level = 0;
    }

    for(int i=0; i <9; i++)
    {
        for (int y = 0; y < 4; y++)
        {
            fields[i].color[y] = DEFAULT_COLORS[i][y];
        }

    }

    draw_wheel(fields, 9, "rueda_de_vida.png");

    QPixmap imagen("rueda_de_vida.png");
    ui->graficoRueda->setPixmap(imagen);
}

Grafico::~Grafico()
{
    delete ui;
}




void Grafico::on_comboBox_currentIndexChanged(int index)
{
    fields[0].level = index;  // Actualiza el nivel del primer campo
    draw_wheel(fields, 9, "rueda_de_vida.png");
    QPixmap imagen("rueda_de_vida.png");
    ui->graficoRueda->setPixmap(imagen);
}

void Grafico::on_comboBox_2_currentIndexChanged(int index)
{
    fields[1].level = index;  // Actualiza el nivel del segundo campo
    draw_wheel(fields, 9, "rueda_de_vida.png");
    QPixmap imagen("rueda_de_vida.png");
    ui->graficoRueda->setPixmap(imagen);
}

void Grafico::on_comboBox_3_currentIndexChanged(int index)
{
    fields[2].level = index;  // Actualiza el nivel del tercer campo
    draw_wheel(fields, 9, "rueda_de_vida.png");
    QPixmap imagen("rueda_de_vida.png");
    ui->graficoRueda->setPixmap(imagen);
}

void Grafico::on_comboBox_4_currentIndexChanged(int index)
{
    fields[3].level = index;  // Actualiza el nivel del cuarto campo
    draw_wheel(fields, 9, "rueda_de_vida.png");
    QPixmap imagen("rueda_de_vida.png");
    ui->graficoRueda->setPixmap(imagen);
}

void Grafico::on_comboBox_5_currentIndexChanged(int index)
{
    fields[4].level = index;  // Actualiza el nivel del quinto campo
    draw_wheel(fields, 9, "rueda_de_vida.png");
    QPixmap imagen("rueda_de_vida.png");
    ui->graficoRueda->setPixmap(imagen);
}

void Grafico::on_comboBox_6_currentIndexChanged(int index)
{
    fields[5].level = index;  // Actualiza el nivel del sexto campo
    draw_wheel(fields, 9, "rueda_de_vida.png");
    QPixmap imagen("rueda_de_vida.png");
    ui->graficoRueda->setPixmap(imagen);
}

void Grafico::on_comboBox_7_currentIndexChanged(int index)
{
    fields[6].level = index;  // Actualiza el nivel del séptimo campo
    draw_wheel(fields, 9, "rueda_de_vida.png");
    QPixmap imagen("rueda_de_vida.png");
    ui->graficoRueda->setPixmap(imagen);
}

void Grafico::on_comboBox_8_currentIndexChanged(int index)
{
    fields[7].level = index;  // Actualiza el nivel del octavo campo
    draw_wheel(fields, 9, "rueda_de_vida.png");
    QPixmap imagen("rueda_de_vida.png");
    ui->graficoRueda->setPixmap(imagen);
}

void Grafico::on_comboBox_9_currentIndexChanged(int index)
{
    fields[8].level = index;  // Actualiza el nivel del noveno campo
    draw_wheel(fields, 9, "rueda_de_vida.png");
    QPixmap imagen("rueda_de_vida.png");
    ui->graficoRueda->setPixmap(imagen);
}



void Grafico::on_pushButton_2_clicked()
{
    QPixmap imagen("rueda_de_vida.png");

    // Crear un nombre predeterminado con fecha actual
    QDateTime ahora = QDateTime::currentDateTime();
    QString fechaStr = ahora.toString("yyyy-MM-dd");
    QString nombrePredeterminado = "Rueda_de_Vida_" + fechaStr + ".png";

    // Abrir diálogo para guardar archivo con nombre predeterminado
    QString nombreArchivo = QFileDialog::getSaveFileName(
        this,
        "Guardar Imagen",
        nombrePredeterminado,  // Nombre predeterminado con extensión
        "Imágenes PNG (*.png);;Imágenes JPEG (*.jpg);;Todos los Archivos (*)"
        );

    // Verificar si se seleccionó un archivo
    if (!nombreArchivo.isEmpty())
    {
        // Guardar la imagen
        bool guardado = imagen.save(nombreArchivo);
        if (guardado) {
            QMessageBox::information(
                this,
                "Guardado Exitoso",
                "La imagen se guardó correctamente en: " + nombreArchivo
                );
        } else {
            QMessageBox::critical(
                this,
                "Error",
                "No se pudo guardar la imagen"
                );
        }
    }
}


void Grafico::on_pushButton_clicked()
{
    this->close();
}
