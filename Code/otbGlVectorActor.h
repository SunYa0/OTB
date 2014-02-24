/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otb_GlVectorActor_h
#define otb_GlVectorActor_h

#include "otbGlActor.h"

#include "otbGenericRSTransform.h"
#include "itkVector.h"
#include "otbOGRDataSourceWrapper.h"
#include "otbOGRLayerWrapper.h"
#include "otbOGRFeatureWrapper.h"

// Forward declaration of GLUtesselator
class GLUtesselator;

namespace otb
{

class GlVectorActor 
  : public GlActor
{
public:
  typedef GlVectorActor                                   Self;
  typedef GlActor                                         Superclass;
  typedef itk::SmartPointer<Self>                         Pointer;
  typedef itk::SmartPointer<const Self>                   ConstPointer;
  typedef otb::GenericRSTransform<>                       RSTransformType;
  typedef RSTransformType::InputPointType                 PointType;
  typedef itk::Vector<double,3>                           ColorType;

  itkNewMacro(Self);
  
  // Initialize with a new file
  void Initialize(const std::string & filename, const std::string & layername = "");

  // Get all available layers
  std::vector<std::string> GetAvailableLayers() const;

  // Get layer name
  std::string GetCurrentLayer() const;

  // Set layer name
  std::string SetCurrentLayer(const std::string & layername);

  // Retrieve the full extent of the actor
  virtual void GetExtent(double & ulx, double & uly, double & lrx, double & lry) const;

  // Update internal actor state with respect to ViewSettings
  virtual void ProcessViewSettings();

  // Heavy load/unload operations of data
  virtual void UpdateData();

  // Gl rendering of current state
  virtual void Render();

  PointType ViewportToVectorTransform(const PointType & point);

  itkSetMacro(Color,ColorType);
  itkGetConstReferenceMacro(Color,ColorType);
  
  itkSetMacro(Alpha,double);
  itkGetConstReferenceMacro(Alpha,double);

  void SetFill(bool flag);
  itkGetMacro(Fill,bool);
  itkBooleanMacro(Fill);

  void SetSolidBorder(bool flag);
  itkGetMacro(SolidBorder,bool);
  itkBooleanMacro(SolidBorder);

  itkSetMacro(LineWidth,double);
  itkGetConstReferenceMacro(LineWidth,double);

  std::string GetWkt() const;

protected:
  GlVectorActor();
  
  virtual ~GlVectorActor();


  // Internal class to hold tiles
  class InternalFeature
  {
  public:
    InternalFeature(OGRFeatureDefn & definition)
      : m_SourceFeature(definition),
        m_RenderedFeature(definition)
    {}

    otb::ogr::Feature m_SourceFeature;
    otb::ogr::Feature m_RenderedFeature;
  };
  
private:
  // prevent implementation
  GlVectorActor(const Self&);
  void operator=(const Self&);

  void InternalFeaturesTransform();

  void UpdateTransforms();

  void UpdateDisplayList();
 
  ColorType            m_Color;
  double               m_Alpha;
  bool                 m_Fill;
  bool                 m_SolidBorder;
  double               m_LineWidth;
  
  RSTransformType::Pointer m_ViewportToVectorTransform;
  RSTransformType::Pointer m_VectorToViewportTransform;

  otb::ogr::DataSource::Pointer m_OGRDataSource;
  otb::ogr::Layer               m_CurrentLayer;

  std::vector<InternalFeature> m_InternalFeatures;

  GLUtesselator * m_GluTesselator;

  unsigned int m_DisplayList;
  bool m_DisplayListNeedsRebuild;

  double m_ExtentULX;
  double m_ExtentULY;
  double m_ExtentLRX;
  double m_ExtentLRY;

}; // End class GlVectorActor

} // End namespace otb

#endif
