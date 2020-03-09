#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_restartButton_clicked();

  void on_userAnswerText_returnPressed();
  void exam_timer_timeout();

 private:
  Ui::MainWindow *ui;
  QTimer *timer;

  const int total_questions = 100;
  int score = total_questions;

  const int op_sum_max_result = 20;
  const int op_sum_min_result = 2;

  const int op_sub_max_number_first = 20;
  const int op_sub_min_number_first = 5;

  const int sum = 0;
  const int sub = 1;

  time_t start_time = 0;

  int answer = 0;
  int questions = 0;
  bool started = false;

  void new_question();
  void prepare_new_exam();
  void stop_exam();
};
#endif  // MAINWINDOW_H
