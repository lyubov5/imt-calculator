#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateWeight(int value);
    void toggleHelp(bool checked);
    void calculateIMT();

private:
    QLabel *titleLabel;

    QLabel *nameLabel;
    QLineEdit *nameEdit;

    QLabel *heightLabel;
    QDoubleSpinBox *heightSpinBox;

    QLabel *weightSliderLabel;
    QSlider *weightSlider;
    QSpinBox *weightSpinBox;

    QCheckBox *helpCheckBox;
    QLabel *helpLabel;

    QPushButton *calcButton;
    QLabel *resultLabel;
};

#endif // MAINWINDOW_H