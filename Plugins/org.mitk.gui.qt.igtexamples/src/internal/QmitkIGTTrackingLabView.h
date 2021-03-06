/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/


#ifndef QmitkIGTTrackingLabView_h
#define QmitkIGTTrackingLabView_h

#include <berryISelectionListener.h>

#include <QmitkAbstractView.h>

#include "ui_QmitkIGTTrackingLabViewControls.h"

#include <mitkNavigationDataToPointSetFilter.h>
#include <mitkNavigationDataLandmarkTransformFilter.h>
#include <mitkNavigationDataReferenceTransformFilter.h>
#include <mitkNavigationDataObjectVisualizationFilter.h>
#include <mitkNavigationDataToPointSetFilter.h>
#include <mitkTrackingDeviceSource.h>
#include <mitkSurface.h>
#include <mitkCameraVisualization.h>

#include <QToolBox>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QTimer>

/*!
  \brief QmitkIGTTrackingLabView

  \warning  This class is not yet documented. Use "git blame" and ask the author to provide basic documentation.

  \sa QmitkFunctionality
  \ingroup ${plugin_target}_internal
*/
class QmitkIGTTrackingLabView : public QmitkAbstractView
{
  // this is needed for all Qt objects that should have a Qt meta-object
  // (everything that derives from QObject and wants to have signal/slots)
  Q_OBJECT

  public:

    static const std::string VIEW_ID;

    /**
    \brief default constructor
    */
    QmitkIGTTrackingLabView();

    /**
    \brief default destructor
    */
    virtual ~QmitkIGTTrackingLabView();

    virtual void CreateQtPartControl(QWidget *parent);

    virtual void SetFocus();

  protected slots:

    void UpdateTimer();

    /**
    \brief This method adds a new fiducial to the tracker fiducials PointSet.
    */
    void OnAddRegistrationTrackingFiducial();
    /**
    \brief This method calls the fiducial registration.
    */
    void OnRegisterFiducials();
    /**
    \brief This method sets up the navigation pipeline before tracking is started.
    */
    void OnSetupNavigation();
    /**
    \brief This method reacts on toolbox item changes.
    */
    void OnToolBoxCurrentChanged(int index);
    /**
    \brief This method initializes the registration for the FiducialRegistrationWidget.
    */
    void InitializeRegistration();
    /**
    \brief This method starts the PointSet recording.
    */
    void OnPointSetRecording(bool record);
    /**
    \brief This method activates the virtual camera.
    */
    void OnVirtualCamera(bool on);
    /**
    \brief This method activates the permanent registration based on one tool's position.
    */
    void OnPermanentRegistration(bool on);

    void OnInstrumentSelected();

    void OnObjectmarkerSelected();



  protected:


    enum ToolBoxElement  // enums for the different ToolBox item tabs.
    {
      NDIConfigurationWidget = 0,
      RegistrationWidget = 1,
      PermanentRecording = 2,
      PointSetRecording = 3,
      VirtualCamera = 4
    };


    Ui::QmitkIGTTrackingLabViewControls m_Controls;
    /**
    \brief This method creates all widgets this bundle needs.
    */
    void CreateBundleWidgets( QWidget* parent );
    /**
    \brief This method creates the SIGNAL SLOT connections.
    */
    void CreateConnections();
    /**
    \brief This method sets up the filter pipeline.
    */
    void SetupIGTPipeline();
    /**
    \brief This method destroys the filter pipeline.
    */
    void DestroyIGTPipeline();



    mitk::TrackingDeviceSource::Pointer m_Source; ///< source that connects to the tracking device

    mitk::NavigationDataObjectVisualizationFilter::Pointer m_PermanentRegistrationFilter; ///< this filter transforms from tracking coordinates into mitk world coordinates if needed it is interconnected before the FiducialEegistrationFilter
    mitk::NavigationDataObjectVisualizationFilter::Pointer m_Visualizer; ///< visualization filter
    mitk::CameraVisualization::Pointer m_VirtualView; ///< filter to update the vtk camera according to the reference navigation data


    bool CheckRegistrationInitialization();///< Checks if everything is initialized for registration. Gives error messages and returns false if not.



private:

  QTimer* m_Timer;

  QToolBox* m_ToolBox;

  mitk::PointSet::Pointer m_PSRecordingPointSet;


  QmitkFiducialRegistrationWidget* m_RegistrationWidget; // landmark registration widget

  std::string m_RegistrationTrackingFiducialsName;
  std::string m_RegistrationImageFiducialsName;

  std::string m_PointSetRecordingDataNodeName;
  bool m_PointSetRecording;
  bool m_PermanentRegistration;
  bool m_CameraView;

  mitk::DataNode::Pointer m_ImageFiducialsDataNode;
  mitk::DataNode::Pointer m_TrackerFiducialsDataNode;

  mitk::PointSet::Pointer m_PermanentRegistrationSourcePoints;

  mitk::NavigationData::Pointer m_InstrumentNavigationData;
  mitk::NavigationData::Pointer m_ObjectmarkerNavigationData;
  mitk::NavigationData::Pointer m_PointSetRecordingNavigationData;

  mitk::NavigationData::Pointer m_T_MarkerRel;
  mitk::NavigationData::Pointer m_T_ObjectReg;
  mitk::AffineTransform3D::Pointer m_T_ImageReg;
  mitk::AffineTransform3D::Pointer m_T_ImageGeo;
  mitk::NavigationData::Pointer m_ObjectmarkerNavigationDataLastUpdate;

  bool IsTransformDifferenceHigh(mitk::NavigationData::Pointer transformA, mitk::NavigationData::Pointer transformB);

  /**
    \brief This method performs GlobalReinit() for the rendering widgets.
    */
  //void GlobalReinit();

};

#endif // QmitkIGTTrackingLabView_h

