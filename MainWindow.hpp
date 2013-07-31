#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <utilities/idf/IdfFile.hpp>

class MainWindow : public QWidget
{
  Q_OBJECT

  public:

  MainWindow()
  {
    setMinimumSize(200,200);

    QVBoxLayout * mainVLayout = new QVBoxLayout();
    mainVLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainVLayout);

    QLabel * label = new QLabel();
    label->setText("Hello World");

    mainVLayout->addWidget(label);
  }

  virtual ~MainWindow() {}
};

