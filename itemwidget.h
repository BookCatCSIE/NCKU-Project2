#ifndef ITEMWIDGET
#define ITEMWIDGET

#include <QPushButton>
class ItemWidget : public QPushButton
{
	Q_OBJECT
	public:
		ItemWidget(qint8 number);
		~ItemWidget();

		void setValue(qint8 number, bool reset = false);
		bool isEditable() const;
		void setEditable(bool editable);
        void lock_filled(qint8 number);

	protected:
		void mousePressEvent(QMouseEvent *ev);

	private:
		bool _is_editable;
};
											
#endif
