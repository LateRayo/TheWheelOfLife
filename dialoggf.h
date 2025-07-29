#ifndef DIALOGGF_H
#define DIALOGGF_H

#include <QDialog>

namespace Ui {
class Dialoggf;
}

class Dialoggf : public QDialog
{
    Q_OBJECT

public:
    explicit Dialoggf(QWidget *parent = nullptr);
    ~Dialoggf();

private:
    Ui::Dialoggf *ui;
};

#endif // DIALOGGF_H
