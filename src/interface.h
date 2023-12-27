#ifndef INTERFACE_H
#define INTERFACE_H

#include "tetramer.h"
#include "ui_interface.h"
#include <QtWidgets/QDialog>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QRect>
#include <QString>
#include <vector>

typedef unsigned char GLubyte;
typedef unsigned short GLushort;

class TiffImage;
class QSettings;
class RyRFit;
class QScrollBar;

class em_interface: public QDialog, protected Ui::DataInput
{
    Q_OBJECT
public:
    em_interface(QSize Screensize, qreal Screendpi);

protected:
    enum {MONO, RGB, PALETTE, INVALID};
    bool ReadFiles();
    bool CheckDimAndType();
    bool ReadTiffStack();
    bool ReadTetramerFile();
    void InputTiffMono(TiffImage* Tiff_Image);
    void InputTiffRGB(TiffImage* Tiff_Image);
    bool InputTiffMap(TiffImage* Tiff_Image);
    void closeEvent(QCloseEvent* e) override;
    void keyPressEvent(QKeyEvent* e) override;
    void resetSystem();
    void checkPixelValue();

    std::vector<QString> FileNames;
    QString DirectoryName;
    QString WindowTitle;
    QSettings* imageVal;
    QScrollBar* sb;
    RyRFit* Analyse;

    GLubyte* texelplanesst;
    GLushort* texelplanes16bitst;

    double fnmPerPixel;
    double filescale;
    double enteredscale;

    int nXdim;
    int nYdim;
    int nZdim;
    int nInputType;
    int nBitsPerSample;
    int ImageType;
    int nNoImages;

    bool bOldData;
    bool b16bit;
    bool bMultiImage;
    bool IsFileLoaded;
    bool bFileScale;
    bool bEnteredScale;

public:
    static QPoint RyRFitPosn;
    static QString TetramerFile;
    static QString NNDFile;
    static QString TiffOutputRoot;
    static GLubyte* texelplanes;
    static GLushort* texelplanes16bit;
    static std::vector<Tetramer> tm;

public slots:
    void showHelp();
    void setAlert(QString msg, char color);
    void displayPixelSize(double PixelSize);
private slots:
    void BrowsePressed();
    void LoadPressed();
    void ToggleStack();
    void Close();
    void BadPixelSize();
//    void updateProgressBar(int value);
signals:
    void Display(int x, int y, int nNoImages, float fnmPerPixel, bool b16bit, QString wt);
};

#endif // INTERFACE_H
