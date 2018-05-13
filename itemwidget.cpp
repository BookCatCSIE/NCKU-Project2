#include "itemwidget.h"
#include "optiondialog.h"

ItemWidget::ItemWidget(qint8 number)
	    :_is_editable(true)
{
        setMaximumSize(60, 60);

		if (number == 0) {
			setEditable(true);
			setText("");
		} else {
			setText(QString::number(number));
			setEditable(false);
		}

}

void ItemWidget::mousePressEvent(QMouseEvent *ev)
{
	Q_UNUSED(ev)

	if (!_is_editable) {
		return;
	}
	OptionDialog w(this);
    w.setModal(false);  //close after used
	if (w.exec() == QDialog::Accepted) {
		qint8 value = w.selectValue();
		setValue(value);
	}
}

void ItemWidget::setValue(qint8 number, bool reset)
{
	if (number == 0) {
		setText("");
		setEditable(true);
	} else {
		setText(QString::number(number));
		setEditable(!reset);
	}
}

void ItemWidget::setEditable(bool editable)
{
	this->_is_editable = editable;
	QPalette p = this->palette();
	if (editable) {
        setStyleSheet("color: red");
	} else {
        setStyleSheet("color: black");
	}

	setPalette(p);
}

bool ItemWidget::isEditable() const
{
	return _is_editable;
}

void ItemWidget::lock_filled(qint8 number){
    if (number == 0) {
        setEditable(true);
        setText("");
    } else {
        setText(QString::number(number));
        setEditable(false);
    }
}
