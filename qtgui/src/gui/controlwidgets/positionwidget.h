#ifndef POSITIONWIDGET_H
#define POSITIONWIDGET_H

#include "gui/controlwidget.h"
#include "qpainter.h"

namespace gui
{

  class KleinesFeld : public QWidget
  {
    Q_OBJECT
  public:
    KleinesFeld(QWidget* parent, int xsize_, int ysize_);
		void setPos(const QPoint& p);
  signals:
    void posChanged(const QPoint&);
  protected:
    void paintEvent(QPaintEvent* pe);
    void mouseMoveEvent(QMouseEvent* e);
  private:
    void drawCuteLittleCross(const QPoint& p, QPainter& painter);
    QPoint pos, oldPos;
    QPainter mainPainter;
    int xsize;
    int ysize;

  };


	class PositionControlWidget:public gui::ControlWidget
  	{
		Q_OBJECT
		public:
    		PositionControlWidget(QWidget* parent, const std::string& name,
			  int controlID,int nodeID,int inIndex);
			virtual void controlValueChanged(int nodeID,int intputIndex,
			   const utils::Buffer& newValue);
		public slots:
			void postNewPoint(const QPoint&);
  		private:
    		KleinesFeld* mausFresser;
			bool itWasMe;
  };

class PositionControlWidgetConstructor:public ControlWidgetConstructor
{
	public:
	PositionControlWidgetConstructor();
	virtual ControlWidget* construct(QWidget* parent, const std::string& name, int controlID,
				  int nodeID, int inputIndex);
};
}
#endif
