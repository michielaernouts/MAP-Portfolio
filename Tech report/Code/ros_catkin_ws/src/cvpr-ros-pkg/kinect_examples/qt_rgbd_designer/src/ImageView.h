#include <QtGui/QWidget>
//#include <QPen>
//#include <qwidget.h>

#define HIST_RES 32
#define HIST_LENGTH HIST_RES*HIST_RES*HIST_RES

#define GAUSS_KERNEL_WIDTH 11
#define GAUSS_SIGMA 3.f
#define PI 3.141592
#define EPSILON 1e-20
#define INFTY 1e6
#define MAX_LAMBDA 2000 //maximum possible weight of smoothness-term


class ImageView : public QWidget {

 Q_OBJECT

 public:

  ImageView(QWidget *parent = 0);
  ~ImageView();

  void calcSegmentation(int lambda = 1);
  bool setImageFileName(QString fileName);

  QImage *image;

 protected:
  void paintEvent(QPaintEvent *pe);
  void mousePressEvent(QMouseEvent *me);
  void mouseReleaseEvent(QMouseEvent *me);
  void mouseMoveEvent(QMouseEvent *me);


 private:
  QString imageFileName;
  


};

