#ifndef _ryrfit_h
#define _ryrfit_h

#include <interface.h>
#include <QtGui>
#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_3_Compatibility>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QSurfaceFormat>
#include <vector>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QString>
#include <QCloseEvent>
#include <QContextMenuEvent>
#include <QPoint>
#include <QLine>
#include <QStringList>
#include <QColor>
#include "tetramer.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Cartesian.h>

typedef CGAL::Cartesian<double> R;
typedef R::Point_2 Point_2;

typedef CGAL::Exact_predicates_inexact_constructions_kernel G;
typedef G::Segment_2 Segment;
typedef G::Point_2  APoint;

class QOpenGLShaderProgram;
class QOpenGLFramebufferObject;
class QOpenGLPaintDevice;
class QAction;
class QFont;
class QMenu;
class QOpenGLDebugLogger;

struct tetramerimage
{
    QVector2D vpos;
    QVector3D linecolour;
};

struct NNDval
{
    double NND;
    Point_2 NNDStart;
    Point_2 NNDEnd;
    char classification;
};

class RyRFit : public QOpenGLWindow, protected QOpenGLFunctions_4_3_Compatibility
{
    Q_OBJECT
public:
    RyRFit();
    ~RyRFit() override;
    void HideScreen();
    void Display(int nXdim, int nYdim, int nNoImages, float nmPerPixel, bool b16bit, QString ImWinTitle);
    bool isFileSaved() {return bSavedTetFile;}
    void setScreenParam(QSize ScrnSize, qreal Screendpi) {ScreenSize = ScrnSize; ScreenDPI = Screendpi;}

public slots:
    void ChangeTetramerWidth();
    void saveTetramerFiles();
protected:
    enum {BackBuffer, FrameBuffer};

    void initValues();
    void contextMenuEvent(QContextMenuEvent *event);
    void keyPressEvent( QKeyEvent *e ) override;
    void keyReleaseEvent( QKeyEvent *e ) override;
    void mousePressEvent( QMouseEvent *e ) override;
    void mouseReleaseEvent( QMouseEvent *e ) override;
    void mouseMoveEvent( QMouseEvent *e ) override;
    void wheelEvent(QWheelEvent *event) override;
    void initializeGL() override;
    void paintGL() override;
 //   void resizeGL(int width, int height) override;
    void ValidAddModifyKeys(QKeyEvent *e);
    void ValidClassifyKeys(QKeyEvent *e);

    void createActions();
    void createMenus();

    void changeScaling();
    void changeTranslation(float xs, float ys);
    void changeScalingandTranslation(float xs, float ys);
    void changeProjection(float xm, float ym);

    void resetDisplay();
    void initShaders();
    void calcTetramer(Tetramer tmer, QVector3D tcolor, tetramerimage *tmi);
    void createTextures();

    void loadTetramerData();
    void loadSingleTetramerData();
    void CalculateScaleBar();

    Point_2 LimitMouse(int x, int y);

    template <class T> T to2DViewportPoint(T posn);
    template <class T> T to2DObjectPoint(T posn);

    bool findTetramer(Point_2 posn);
    void tetramerClassification(char c);

    void calculateArea();
    uint FitShape(std::vector<APoint> PixelGroup);
    void calculateNearestNeighbours();
#ifdef GL_DEBUG
    void debugMessageHandler(const QOpenGLDebugMessage& debugMessage);
#endif

private slots:
    void addTetramer();
    void saveTetramer();
    void deleteTetramer();
    void modifyTetramer();
    void classifyTetramer();
    void ZoomNote();
    void showExtent();
    void showNearestNeighbours();
    void changeLookAhead();
    void LookAhead();
    void changeImageScaling();

    void CreateScreenShot();
    void CreateTIFF(int Xdim, int Ydim, int imagetype, int ImageDPI, double Magnification);

    void changeTetramerHighlight();
    void showRedTetramers();
    void displayTetramers();
    void OutputNNDs();
    void Save_DisplayNNDFiles();
    void hideEMImage();
    void FlipImage();

    void changePalette();
    void getScaleBarSize();

    void imageLine();
    void imageFirstPlane();
    void imageLastPlane();
    void imageNextPlane();
    void imagePrevPlane();
    void imageZoomIn();
    void imageZoomOut();

    void ChangeSize();
    void CloseWindow();

protected:
    void LineDraw();

    std::vector <Segment> alphashape;

private:
// menus

    QMenu* imageMenu;
    QMenu* tetramerMenu;

    QAction* addScaleBarAct;
    QAction* createScreenShotAct;
    QAction* createFBOImageAct;
    QAction* showHelpAct;
    QAction* addTetramerAct;
    QAction* modifyTetramerAct;
    QAction* showTetramersAct;
    QAction* FlipImageAct;
    QAction* saveTetramerAct;
    QAction* saveTetFileAct;
    QAction* OutputNNDAct;
    QAction* changeTetramerHighlightAct;
    QAction* showNearestNeighboursAct;
    QAction* showRedTetramersAct;
    QAction* hideEMImageAct;
    QAction* ChangeTetramerWidthAct;
    QAction* showTetramerExtentAct;
    QAction* LookAheadAct;
    QAction* changeLookAheadAct;
    QAction* changePaletteAct;
    QAction* changeImageScalingAct;
    QAction* LineAct;     
    QAction* ZoomInAct;     
    QAction* ZoomOutAct;     
    QAction* QuitAct;     
 
    QFont    basefont;
    QFont    tinyfont;
    QString  infoLabel;

    QCursor* Cursor;

protected:  
    uint nNoTetramers;
    uint nImagedTetramers;

    bool bLookAhead;
    int nLookAhead;

    int nBeingModified;
    int nBeingClassified;
    uint imageindex;

    std::vector<NNDval> NNDtet;
    Tetramer ntm;

    float ImageScale;
    float PixelSize;
    float PixelDim;
    Point_2 Centre;
    Point_2 InitCentre;
    Point_2 ImageOffset;

    GLint viewportparam[4];
    GLuint  em_images;

    GLsizei hl_count;
    QVector2D* hullpts;

    GLsizei al_count;
    QVector2D* alphapts;

    GLint* tl_start;
    GLsizei* tl_count;

    int tno;
    tetramerimage* tetrameroutline;
    tetramerimage SingleTetramer[4];

    int TransparencyLoc;
    int TransformPlaneImageLoc;
    int TransformTetramerLoc;
    int TransformBoundaryLoc;
    int BoundaryColourLoc;
    int nPalette;
    int nScaleBarLength;

    double degtorad;
    double fortyfivedeg;
    double tetramerdiag;
    double tetramerwidth;
    double tetramersize;
    double baseangleinradians;
    double centredistance;
    double sqrt2;
    double AreaAlpha;

    double totalConvexArea;
    double totalAlphaArea;
    double totalTetramerArea;
    double percentTetramerAreaConvex;
    double percentTetramerAreaAlpha;
    double TetramerDensityConvex;
    double TetramerDensityAlpha;

    QSize ScreenSize;
    qreal ScreenDPI;

    enum CUD{black, orange, skyblue, bluegreen, yellow, blue, vermillion, redpurple};
    QVector3D CUD_Colours[8];

    void Palette1();
    void Palette2();

    double fFBOZoom;
    int ImageDPI;

    QColor NNDlineColour;
    QColor NNDtextColour;

    Point_2 ScaleBarPosition;
    Point_2 mousePosn;

    QSurfaceFormat sformat;
    QOpenGLPaintDevice* PaintDevice;
    QRectF ImageSize;
    QRectF ImageDisplaySize;

    QVector4D BoundaryColour;
    QVector4D ScaleBarColour;
    QVector3D PlacingColour;
    QVector3D UnlabeledColour;
    QVector3D ChkrboardColour;
    QVector3D SidebySideColour;
    QVector3D IsolatedColour;
    QVector3D BothColour;
    QVector2D ScaleBar[4];

    QMatrix4x4 orthoproj;
    QMatrix4x4 translation;
    QMatrix4x4 scaling;
    QMatrix4x4 transform;
    QMatrix4x4 invtransform;

    QOpenGLVertexArrayObject vao_image;
    QOpenGLVertexArrayObject vao_hull;
    QOpenGLVertexArrayObject vao_alpha;
    QOpenGLVertexArrayObject vao_scalebar;
    QOpenGLVertexArrayObject vao_tetramers;
    QOpenGLVertexArrayObject vao_singletetramer;

    QOpenGLBuffer alpha_vbo;
    QOpenGLBuffer hull_vbo;
    QOpenGLBuffer scalebar_vbo;
    QOpenGLBuffer tetramers_vbo;
    QOpenGLBuffer singletetramer_vbo;

    QOpenGLFramebufferObject* image_fbo;

    QOpenGLShaderProgram* planeimage;
    QOpenGLShaderProgram* boundary;
    QOpenGLShaderProgram* scalebar;
    QOpenGLShaderProgram* tetplot;

#ifdef GL_DEBUG
    QOpenGLDebugLogger* GLlogger;
#endif
    bool    bScaleBar;
    bool    b16bit;
    bool    bEnteredScale;
    bool    bScaleBarPositionChosen;
    bool    bAltPressed;
    bool    bPickedCentre;
    bool    bShowTetramers;
    bool    bRedColourOnly;
    bool    bShadow;
    bool    bDisplayHulls;
    bool    bDisplayNND;

    bool    bLeftButtonDown;
    bool    bRightButtonDown;
    bool    bMiddleButtonDown;

    bool    bLinePlot;
    bool    bAddTetramer;
    bool    bModifyTetramer;
    bool    bClassifyTetramer;
    bool    bPlacingTetramer;
    bool    bPlotTetramers;
    bool    bSavedTetFile;
    bool    bCalcNearestNeighbours;
    bool    bShowNearestNeighbours;

    bool    bHideEMImage;
    bool    bOldData;
    bool    bShowArea;

    float   fZoom;
    float   fZoomDelta;
    float   fFlipImage;
    float   fFlipBoxes;
    float   fOldZoom;

    Point_2 StartPt;
    Point_2 EndPt;
    Point_2 StartImagePt;
    Point_2 EndImagePt;


// Displayable min & max & Z planes 

    int nZmin;
    int nZmax;

    int NoImages;
    int ImageNo;

    QString Description;
    QString Software;

    int InitXdim;
    int InitYdim;

    float ImageXdim;
    float ImageYdim;

    float fXScreenMax;
    float fYScreenMax;

    double nndmax;
    double nndmin;

    bool  bFirstTime;

    static bool PixelPosnLessThan(const APoint &s1, const APoint &s2)
    {
         return s1.x() < s2.x();
    }
signals:
    void showHelp();
    void NewImageScale(double PixelSize);
    void ClosePgm();
    void AlertMsg(QString q, char Colour);
};
#endif
