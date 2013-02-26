/*=========================================================================

  Program:   Monteverdi2
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi2 is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtOpenGL>

//
// System includes (sorted by alphabetic order)
// necessary for the opengl variables and methods

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "mvdImageModelRenderer.h"
#include "mvdVectorImageModel.h"

namespace mvd
{
/*
  TRANSLATOR mvd::ImageModelRenderer

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/

/*****************************************************************************/
ImageModelRenderer
::ImageModelRenderer( QObject* parent ) :
  AbstractModelRenderer( parent ),
  m_IsMoving(false)
{
  m_PreviousOriginX = 0.;
  m_PreviousOriginY = 0.;
}

/*****************************************************************************/
ImageModelRenderer
::~ImageModelRenderer()
{
}

/*****************************************************************************/
void ImageModelRenderer::paintGL( const RenderingContext& context )
{
  if( context.m_ImageModel==NULL )
    return;

  // the VectorImageModel used for the rendering
  VectorImageModel* viModel = qobject_cast< VectorImageModel * >(
    const_cast< AbstractImageModel* >( context.m_ImageModel )
  );
  assert( viModel );

  // the region of the image to be rendered
  const ImageRegionType&  region = context.m_ImageRegion;

  ImageRegionType  scaledRegion = region;
  CountType bestLod = viModel->ComputeBestLevelOfDetail(context.m_IsotropicZoom);

  // If it is not the original level of detail recompute the region to request
  double currentResolutionFactorX = 1.;
  double currentResolutionFactorY = 1.;

  if (bestLod != 0)
    {
    ImageRegionType::SizeType  scaledSize;
    ImageRegionType::IndexType scaledOrigin;

    scaledSize[0] = region.GetSize()[0]/(1<<bestLod);
    scaledSize[1] = region.GetSize()[1]/(1<<bestLod);

    currentResolutionFactorX = static_cast<double>(region.GetSize()[0])/static_cast<double>(scaledSize[0]);
    currentResolutionFactorY = static_cast<double>(region.GetSize()[1])/static_cast<double>(scaledSize[1]);

    scaledOrigin[0] = region.GetIndex()[0]/(1<<bestLod);
    scaledOrigin[1] = region.GetIndex()[1]/(1<<bestLod);

    scaledRegion.SetSize(scaledSize) ;
    scaledRegion.SetIndex(scaledOrigin);
    }
  // TODO : remove verbosity
  std::cout <<"Level of detail requested:" << bestLod << std::endl;

  if (!m_IsMoving)
    {
    // request the data for the current region
    m_Buffer = viModel->RasterizeRegion(scaledRegion, 
                                        context.m_IsotropicZoom, 
                                        context.m_ForceRefresh);
    }

  // final zoom factor : take into account the current resolution of
  // the file and the wheel zoom
  double finalZoomFactorX = context.m_IsotropicZoom * currentResolutionFactorX; 
  double finalZoomFactorY = context.m_IsotropicZoom * currentResolutionFactorY;

  // if buffer not null do the rendering
  if (m_Buffer != NULL)
    {
    
    //unsigned int first_displayed_col = 0;
    double originX = 0.;
    double originY = 0.;

    if (!m_IsMoving) // center
      {
      // originX
      if ( context.m_WidgetWidth  > 
           scaledRegion.GetSize()[0] * finalZoomFactorX  )
        {
        originX = (static_cast<double>(context.m_WidgetWidth) - static_cast<double>(scaledRegion.GetSize()[0]) * finalZoomFactorX)/2;
        }
      // originY
      if (context.m_WidgetHeight >
          scaledRegion.GetSize()[1] * finalZoomFactorY)
        {
        originY = (static_cast<double>(context.m_WidgetHeight) - static_cast<double>(scaledRegion.GetSize()[1]) * finalZoomFactorY)/2;
        }

      // when mouse is released, initialize the moving origin with the
      // values computed below. This is needed when the widget is
      // resized and the first displayed column is not at index 0
      // anymore. 
      m_MovingOriginX = originX;
      m_MovingOriginY = originY;
    }

    if (m_IsMoving)// if moving, only displace the rectangle (Gl_QUADS) origin
      {
      double dx = m_PreviousOriginX - static_cast<double>(scaledRegion.GetIndex()[0]) * finalZoomFactorX;
      double dy = m_PreviousOriginY - static_cast<double>(scaledRegion.GetIndex()[1]) * finalZoomFactorY;

      // incremenet the moving origin with the computed delta
      m_MovingOriginX+=dx;
      m_MovingOriginY-=dy;
      
      // set the quads origin to the moving origin
      originX =  m_MovingOriginX;
      originY =  m_MovingOriginY;
      }

    // real size of the region to be rendered
    double sizeX  = static_cast<double>(scaledRegion.GetSize()[0]) * finalZoomFactorX;
    double sizeY  = static_cast<double>(scaledRegion.GetSize()[1]) * finalZoomFactorY;

    // needed cause RGB not RGBA rendering. 
    glPixelStorei(GL_UNPACK_ALIGNMENT,1); 
                                
    // texture 
    glEnable(GL_TEXTURE_2D);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 scaledRegion.GetSize()[0],
                 scaledRegion.GetSize()[1], 
                 0, GL_RGB, GL_UNSIGNED_BYTE, m_Buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture (GL_TEXTURE_2D, texture);

    // rectangle where to draw
    glBegin (GL_QUADS);
      glTexCoord2f (0.0, 1.0); glVertex2f(originX, originY + sizeY);
      glTexCoord2f (1.0, 1.0); glVertex2f(originX + sizeX, originY + sizeY);
      glTexCoord2f (1.0, 0.0); glVertex2f(originX + sizeX, originY);
      glTexCoord2f (0.0, 0.0); glVertex2f(originX, originY);
    glEnd ();
    
    // free texture
    glDeleteTextures(1, &texture);
    glDisable(GL_TEXTURE_2D);

    // emit the new origin of the extent
    IndexType origin;
    origin[0]  = originX;
    origin[1]  = originY;
    emit ViewportOriginChanged(origin);
    }

  // save the previous scaled region origin
  m_PreviousOriginX = static_cast<double>(scaledRegion.GetIndex()[0]) * finalZoomFactorX;
  m_PreviousOriginY = static_cast<double>(scaledRegion.GetIndex()[1]) * finalZoomFactorY;
}

/*****************************************************************************/
/* SLOTS                                                                     */
/*****************************************************************************/

/*****************************************************************************/

} // end namespace 'mvd'
