#ifndef EXPMANAGER_H
#define EXPMANAGER_H

#include <QDialog>

namespace Ui {
class ExpManager;
}

class ExpManager : public QDialog
{
    Q_OBJECT

public:
    explicit ExpManager(QWidget *parent = 0);
    ~ExpManager();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ExpManager *ui;
};

#endif // EXPMANAGER_H
