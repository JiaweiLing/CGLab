#include "paintwidget.h"
#include <QFileDialog>
#include <QMessageBox>

void PaintWidget :: Save()
{
    QString path = QFileDialog :: getSaveFileName(this, tr("Save Image"), ".", tr("Images (*.png *.jpg *.bmp)"));
    if (path.length() == 0)
        QMessageBox :: information(NULL, tr("Path"), tr("No path selected."));
    QPixmap pixmap(this->size());
    this->render(&pixmap);
    pixmap.save(path);
}
